

/***********************************************************************************
** exvr-exp                                                                       **
** MIT License                                                                    **
** Copyright (c) [2024] [Florian Lance][Auxime]                                   **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// system
using System.Threading.Tasks;

// unity
using UnityEngine;

// others
using NativeWebSocket;

namespace Ex {

    public class WebsocketClientComponent : ExComponent {

        private static readonly string m_messageReadSignalStr = "message read";
        private static readonly string m_connectionOpenedSignalStr = "connection opened";
        private static readonly string m_connectionClosedSignalStr = "connection closed";
        WebSocket m_webSocket = null;
        private bool m_connectedToServer = false;

        protected override bool initialize() {

            // signals
            add_signal(m_messageReadSignalStr);
            add_signal(m_connectionOpenedSignalStr);
            add_signal(m_connectionClosedSignalStr);

            // slots
            add_slot("connect", (nullArg) => {
                connect_socket();
            });
            add_slot("close", (nullArg) => {
                close_socket();
            });
            add_slot("send message", (message) => {
                send_message((string)message);
            });

            m_webSocket = new WebSocket(initC.get<string>("url"));
            m_webSocket.OnOpen += () => {
                m_connectedToServer = true;
                log_message(string.Format("Connection opened"));
                if (is_updating()) {
                    invoke_signal(m_connectionOpenedSignalStr);
                }
            };
            m_webSocket.OnError += (e) => {
                log_error(string.Format("Error: {0}.", e));
            };
            m_webSocket.OnClose += (WebSocketCloseCode e) => {
                m_connectedToServer = false;
                log_message(string.Format("Connection closed, reason: [{0}].", e.ToString()));
                if (is_updating()) {                    
                    invoke_signal(m_connectionClosedSignalStr);
                }
            };
            m_webSocket.OnMessage += (bytes) => {
                if (is_updating()) {
                    double expTime = ExVR.Time().ellapsed_exp_ms();
                    double routineTime = ExVR.Time().ellapsed_element_ms();
                    try {
                        invoke_signal(m_messageReadSignalStr, new TimeAny(expTime, routineTime, System.Text.Encoding.UTF8.GetString(bytes)));
                    } catch (System.Text.DecoderFallbackException e) {
                        log_error(string.Format("GetString decoder error: {0}", e.Message));
                    } catch (System.ArgumentException e) {
                        log_error(string.Format("GetString argument error: {0}", e.Message));
                    }
                }
            };

            return true;
        }

        protected override void clean() {
            m_webSocket = null;
        }

        protected override void start_experiment() {
            //if (initC.get<bool>("connect_at_start")) {
            //    connect_socket();
            //}
        }

        protected override void stop_experiment() {
            close_socket();
        }

        protected override void start_routine() {
            if (initC.get<bool>("connect_at_start")) {
                if (!m_connectedToServer) {
                    connect_socket();
                }
            }
        }


        protected override void update() {
            if (m_webSocket.State == WebSocketState.Open) {
                m_webSocket.DispatchMessageQueue();
            }
        }

        public void connect_socket() {
            var connectTask = Task.Run(async () => await m_webSocket.Connect());
        }

        public void close_socket() {
            var closeTask = Task.Run(async () => await m_webSocket.Close());
        }

        public void send_message(string message) {
            if (is_updating()) {
                if (m_webSocket.State == WebSocketState.Open) {
                    var sendTask = Task.Run(async () => await m_webSocket.SendText(message));
                } else {
                    log_warning(string.Format("Socket not opened for message {0}", message));
                }
            }
        }
    }
}



//Debug.LogError("WebsocketClientComponent");

//websocket = new NativeWebSocket.WebSocket("ws://localhost:80");
//websocket.OnOpen += () =>
//{
//    Debug.LogError("Connection open!");
//};

//websocket.OnError += (e) =>
//{
//    Debug.LogError("Error! " + e);
//};

//websocket.OnClose += (e) =>
//{
//    Debug.LogError("Connection closed!");
//};

//websocket.OnMessage += (bytes) =>
//{
//    Debug.LogError("OnMessage!");
//    Debug.LogError(bytes);

//    // getting the message as a string
//    // var message = System.Text.Encoding.UTF8.GetString(bytes);
//    // Debug.Log("OnMessage! " + message);
//};

//// signals
//add_signal(m_messageReadSignalStr);

//add_slot("send message", (message) => {
//    if (m_ws.IsAlive) {
//        m_ws.Send((string)message);
//    } else {
//        Debug.LogError("not alive");
//    }
//});

////m_ws = new WebSocket("ws://127.0.0.1:8175");// initC.get<string>("url"));
//m_ws = new WebSocket("ws://127.0.0.1:5000");
////m_ws = new WebSocket()
//Debug.Log("--> " + initC.get<string>("url"));
//m_ws.OnMessage += (sender, e) => {
//    Debug.LogError("client receive message " + e.Data);
//    double expTime = ExVR.Time().ellapsed_exp_ms();
//    double routineTime = ExVR.Time().ellapsed_element_ms();
//    invoke_signal(m_messageReadSignalStr, new TimeAny(expTime, routineTime, sender.ToString() + " | " + e.Data));
//};
//m_ws.OnClose += (sender, e) => {
//    Debug.LogError("client close");
//};
//m_ws.OnOpen += (sender, e) => {
//    Debug.LogError("client open");
//};
//m_ws.OnError += (sender, e) => {
//    Debug.LogError("client error");
//};


//public class WebsocketClient : ThreadedJob {

//    private System.Net.WebSockets.ClientWebSocket m_client = null;
//    private byte[] m_buffer = new byte[65535];
//    private ConcurrentQueue<Tuple<double, double, string>> m_messages = new ConcurrentQueue<Tuple<double, double, string>>();

//    public bool initialize(Uri uri) {

//        Debug.LogError("init1");
//        m_client = new System.Net.WebSockets.ClientWebSocket();
//        Debug.LogError("init2");
//        try {
//            Debug.LogError("init3 " + uri);
//            var task = Task.Run(async () => await m_client.ConnectAsync(uri, System.Threading.CancellationToken.None));
//            task.Wait();

//            Debug.LogError("init4");
//            start();

//        } catch (Exception ex) {
//            m_client = null;
//            Debug.LogError("init5 " + ex.Message);
//        }

//        return m_client != null;
//    }

//    public void clean() {
//        if (m_client != null) {
//            if (m_client.State == System.Net.WebSockets.WebSocketState.Open) {
//                var task = Task.Run(async () => await m_client.CloseAsync(System.Net.WebSockets.WebSocketCloseStatus.NormalClosure, "", System.Threading.CancellationToken.None));
//                task.Wait();
//            }
//            join(500);

//            m_client = null;
//        }
//    }

//    protected override void thread_function() {

//        if (m_client != null) {

//            if (m_client.State == System.Net.WebSockets.WebSocketState.Open) {
//                var receiveTask = Task.Run(async () => await m_client.ReceiveAsync(new ArraySegment<byte>(m_buffer), System.Threading.CancellationToken.None));
//                receiveTask.Wait(100);
//                var result = receiveTask.Result;

//                if (result.MessageType == System.Net.WebSockets.WebSocketMessageType.Close) {
//                    var closeTask = Task.Run(async () => await m_client.CloseAsync(System.Net.WebSockets.WebSocketCloseStatus.NormalClosure, "", System.Threading.CancellationToken.None));
//                    closeTask.Wait();
//                } else {

//                    double expTime = ExVR.Time().ellapsed_exp_ms();
//                    double routineTime = ExVR.Time().ellapsed_element_ms();

//                    try {
//                        m_messages.Enqueue(new Tuple<double, double, string>(expTime, routineTime, System.Text.Encoding.UTF8.GetString(m_buffer, 0, result.Count)));
//                    } catch (DecoderFallbackException e) {
//                        UnityEngine.Debug.LogError(string.Format("GetString decoder error: {0}", e.Message));
//                    } catch (ArgumentException e) {
//                        UnityEngine.Debug.LogError(string.Format("GetString argument error: {0}", e.Message));
//                    }
//                }
//            }

//        }
//    }

//    public List<Tuple<double, double, string>> read_all_messages() {

//        List<Tuple<double, double, string>> messages = null;
//        Tuple<double, double, string> message;
//        int size = m_messages.Count;
//        while (m_messages.TryDequeue(out message)) {
//            if (messages == null) {
//                messages = new List<Tuple<double, double, string>>(size);
//            }
//            messages.Add(message);
//        }
//        return messages;
//    }

//}