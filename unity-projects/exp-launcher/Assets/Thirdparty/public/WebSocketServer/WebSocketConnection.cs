using UnityEngine;

using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Concurrent;
// For parsing the client websocket requests
using System.Text; 
using System.Text.RegularExpressions;
// For creating a thread
using System.Threading;
using System.Collections.Generic;


namespace WebSocketServer {

    public enum WebSocketEventType {
        Open,
        Close,
        Message
    }

    public struct WebSocketMessage {
        public WebSocketMessage(WebSocketConnection connection, string data) {
            this.id = Guid.NewGuid().ToString();
            this.connection = connection;
            this.data = data;
        }

        public string id { get; }
        public WebSocketConnection connection { get; }
        public string data { get; }
    }

    public struct WebSocketEvent {
        public WebSocketEvent(WebSocketConnection connection, WebSocketEventType type, string data) {
            this.id = Guid.NewGuid().ToString();
            this.connection = connection;
            this.type = type;
            this.data = data;
        }

        public string id { get; }
        public WebSocketEventType type { get; }
        public WebSocketConnection connection { get; }
        public string data { get; }
    }

    public class WebSocketConnection {

        public string id;
        private TcpClient client;
        private NetworkStream stream;
        private WebSocketServer server;
        private Thread connectionHandler;

        public WebSocketConnection(TcpClient client, WebSocketServer server) {
            this.id = Guid.NewGuid().ToString();
            this.client = client;
            this.stream = client.GetStream();
            this.server = server;
        }

        protected int get_header(bool finalFrame, bool contFrame) {
            int header = finalFrame ? 1 : 0;//fin: 0 = more frames, 1 = final frame
            header = (header << 1) + 0;//rsv1
            header = (header << 1) + 0;//rsv2
            header = (header << 1) + 0;//rsv3
            header = (header << 4) + (contFrame ? 0 : 1);//opcode : 0 = continuation frame, 1 = text
            header = (header << 1) + 0;//mask: server -> client = no mask

            return header;
        }

        protected byte[] int_to_byte_array(ushort value) {
            var ary = System.BitConverter.GetBytes(value);
            if (System.BitConverter.IsLittleEndian) {
                System.Array.Reverse(ary);
            }

            return ary;
        }

        public void send_message(IEnumerable<string> message) {
            Queue<string> que = new Queue<string>(message);
            int len = que.Count;

            while (que.Count > 0) {
                var header = get_header(
                    que.Count > 1 ? false : true,
                    que.Count == len ? false : true
                );

                byte[] list = Encoding.UTF8.GetBytes(que.Dequeue());
                header = (header << 7) + list.Length;
                stream.Write(int_to_byte_array((ushort)header), 0, 2);
                stream.Write(list, 0, list.Length);
            }
        }

        public bool Establish() {
            // Wait for enough bytes to be available
            while (!stream.DataAvailable);
            while(client.Available < 3);
            // Translate bytes of request to a RequestHeader object
            Byte[] bytes = new Byte[client.Available];
            stream.Read(bytes, 0, bytes.Length);
            RequestHeader request = new RequestHeader(Encoding.UTF8.GetString(bytes));

            // Check if the request complies with WebSocket protocol.
            if (WebSocketProtocol.CheckConnectionHandshake(request)) {
                // If so, initiate the connection by sending a reply according to protocol.
                Byte[] response = WebSocketProtocol.CreateHandshakeReply(request);
                stream.Write(response, 0, response.Length);

                Debug.Log("WebSocket client connected." + Encoding.UTF8.GetString(bytes) + " " + request.ToString());

                // Start message handling
                connectionHandler = new Thread(new ThreadStart(HandleConnection));
                connectionHandler.IsBackground = true;
                connectionHandler.Start();

                // Call the server callback.
                WebSocketEvent wsEvent = new WebSocketEvent(this, WebSocketEventType.Open, null);
                server.events.Enqueue(wsEvent);
                return true;
            } else {
                return false;
            }
        }

        private void HandleConnection () {
            while (true) {
                WebSocketDataFrame dataframe = ReadDataFrame();

                if (dataframe.fin) {
                    if ((WebSocketOpCode)dataframe.opcode == WebSocketOpCode.Text) {
                        // Let the server know of the message.
                        string data = WebSocketProtocol.DecodeText(dataframe);
                        WebSocketEvent wsEvent = new WebSocketEvent(this, WebSocketEventType.Message, data);
                        server.events.Enqueue(wsEvent);
                    } else if ((WebSocketOpCode)dataframe.opcode == WebSocketOpCode.Close) {
                        // Handle closing the connection.
                        Debug.LogError("Client closed the connection.");
                        // Close the connection.
                        stream.Close();
                        client.Close();
                        // Call server callback.
                        WebSocketEvent wsEvent = new WebSocketEvent(this, WebSocketEventType.Close, null);
                        server.events.Enqueue(wsEvent);
                        // Jump out of the loop.
                        break;
                    }
                } else {
                    Debug.Log("Fragmentation encoutered.");
                }
            }
        }


        private WebSocketDataFrame ReadDataFrame() {
            const int DataframeHead = 2;        // Length of dataframe head
            const int ShortPayloadLength = 2;   // Length of a short payload length field
            const int LongPayloadLength = 8;    // Length of a long payload length field
            const int Mask = 4;                 // Length of the payload mask

            // Wait for a dataframe head to be available, then read the data.
            while (!stream.DataAvailable && client.Available < DataframeHead);
            Byte[] bytes = new Byte[DataframeHead];
            stream.Read(bytes, 0, DataframeHead);

            // Decode the message head, including FIN, OpCode, and initial byte of the payload length.
            WebSocketDataFrame dataframe = WebSocketProtocol.CreateDataFrame();
            WebSocketProtocol.ParseDataFrameHead(bytes, ref dataframe);

            // Depending on the dataframe length, read & decode the next bytes for payload length
            if (dataframe.length == 126) {
                while (client.Available < ShortPayloadLength);  // Wait until data is available
                Array.Resize(ref bytes, bytes.Length + ShortPayloadLength);
                stream.Read(bytes, bytes.Length - ShortPayloadLength, ShortPayloadLength);   // Read the next two bytes for length
            } else if (dataframe.length == 127) {
                while (client.Available < LongPayloadLength);  // Wait until data is available
                Array.Resize(ref bytes, bytes.Length + LongPayloadLength);
                stream.Read(bytes, bytes.Length - LongPayloadLength, LongPayloadLength);   // Read the next two bytes for length
            }
            WebSocketProtocol.ParseDataFrameLength(bytes, ref dataframe);    // Parse the length

            if (dataframe.mask) {
                while (client.Available < Mask);  // Wait until data is available
                Array.Resize(ref bytes, bytes.Length + Mask);
                stream.Read(bytes, bytes.Length - Mask, Mask);   // Read the next four bytes for mask
            } 

            while (client.Available < dataframe.length);  // Wait until data is available
            Array.Resize(ref bytes, bytes.Length + dataframe.length);
            stream.Read(bytes, bytes.Length - dataframe.length, dataframe.length);    // Read the payload
            dataframe.data = bytes;

            return dataframe;
        }
    }

}