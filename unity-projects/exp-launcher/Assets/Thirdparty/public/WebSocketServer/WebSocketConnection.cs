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
        private TcpClient m_client;
        private NetworkStream m_stream;        
        private Thread m_connectionHandler;
        private volatile bool m_doLoop = false;
        private WebSocketServer m_server;
        public WebSocketConnection(TcpClient client, WebSocketServer server) {
            id       = Guid.NewGuid().ToString();
            m_client = client;
            m_stream = client.GetStream();
            m_server = server;
        }

        public void clean() {

            if (m_connectionHandler != null) {
                m_doLoop = false;                
                m_connectionHandler.Join(500);
                m_connectionHandler = null;
            }

            if(m_stream != null) {
                m_stream.Close();
            }
            if (m_client != null) {
                m_client.Close();
            }
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
                m_stream.Write(int_to_byte_array((ushort)header), 0, 2);
                m_stream.Write(list, 0, list.Length);
            }
        }

        public bool Establish() {
            // Wait for enough bytes to be available
            while (!m_stream.DataAvailable);
            while(m_client.Available < 3);
            // Translate bytes of request to a RequestHeader object
            Byte[] bytes = new Byte[m_client.Available];
            m_stream.Read(bytes, 0, bytes.Length);
            RequestHeader request = new RequestHeader(Encoding.UTF8.GetString(bytes));

            // Check if the request complies with WebSocket protocol.
            if (WebSocketProtocol.CheckConnectionHandshake(request)) {
                // If so, initiate the connection by sending a reply according to protocol.
                Byte[] response = WebSocketProtocol.CreateHandshakeReply(request);
                m_stream.Write(response, 0, response.Length);

                Debug.Log("WebSocket client connected." + Encoding.UTF8.GetString(bytes) + " " + request.ToString());

                // Start message handling
                m_doLoop         = true;
                m_connectionHandler = new Thread(new ThreadStart(HandleConnection));
                m_connectionHandler.IsBackground = true;
                m_connectionHandler.Start();

                // Call the server callback.
                WebSocketEvent wsEvent = new WebSocketEvent(this, WebSocketEventType.Open, null);
                m_server.events.Enqueue(wsEvent);
                return true;
            } else {
                return false;
            }
        }

        private void HandleConnection () {

            while (m_doLoop) {

                WebSocketDataFrame dataframe = ReadDataFrame();

                if (dataframe.fin) {
                    if ((WebSocketOpCode)dataframe.opcode == WebSocketOpCode.Text) {
                        // Let the server know of the message.
                        string data = WebSocketProtocol.DecodeText(dataframe);
                        WebSocketEvent wsEvent = new WebSocketEvent(this, WebSocketEventType.Message, data);
                        m_server.events.Enqueue(wsEvent);
                    } else if ((WebSocketOpCode)dataframe.opcode == WebSocketOpCode.Close) {
                        // Handle closing the connection.
                        Debug.LogError("Client closed the connection.");
                        // Close the connection.
                        m_stream.Close();
                        m_client.Close();
                        // Call server callback.
                        WebSocketEvent wsEvent = new WebSocketEvent(this, WebSocketEventType.Close, null);
                        m_server.events.Enqueue(wsEvent);
                        // Jump out of the loop.
                        m_stream = null;
                        m_client = null;
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
            while (!m_stream.DataAvailable && m_client.Available < DataframeHead) {
                if (!m_doLoop) {
                    return WebSocketProtocol.CreateDataFrame();
                }
            }
            Byte[] bytes = new Byte[DataframeHead];
            m_stream.Read(bytes, 0, DataframeHead);

            // Decode the message head, including FIN, OpCode, and initial byte of the payload length.
            WebSocketDataFrame dataframe = WebSocketProtocol.CreateDataFrame();
            WebSocketProtocol.ParseDataFrameHead(bytes, ref dataframe);

            // Depending on the dataframe length, read & decode the next bytes for payload length
            if (dataframe.length == 126) {
                while (m_client.Available < ShortPayloadLength);  // Wait until data is available
                Array.Resize(ref bytes, bytes.Length + ShortPayloadLength);
                m_stream.Read(bytes, bytes.Length - ShortPayloadLength, ShortPayloadLength);   // Read the next two bytes for length
            } else if (dataframe.length == 127) {
                while (m_client.Available < LongPayloadLength);  // Wait until data is available
                Array.Resize(ref bytes, bytes.Length + LongPayloadLength);
                m_stream.Read(bytes, bytes.Length - LongPayloadLength, LongPayloadLength);   // Read the next two bytes for length
            }
            WebSocketProtocol.ParseDataFrameLength(bytes, ref dataframe);    // Parse the length

            if (dataframe.mask) {
                while (m_client.Available < Mask);  // Wait until data is available
                Array.Resize(ref bytes, bytes.Length + Mask);
                m_stream.Read(bytes, bytes.Length - Mask, Mask);   // Read the next four bytes for mask
            } 

            while (m_client.Available < dataframe.length);  // Wait until data is available
            Array.Resize(ref bytes, bytes.Length + dataframe.length);
            m_stream.Read(bytes, bytes.Length - dataframe.length, dataframe.length);    // Read the payload
            dataframe.data = bytes;

            return dataframe;
        }
    }

}