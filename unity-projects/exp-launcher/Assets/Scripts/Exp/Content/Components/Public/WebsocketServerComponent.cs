

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
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Collections.Concurrent;

// unity
using UnityEngine;

using WebSocketServer;

namespace Ex {

    public class TcpListenerJob : ThreadedJob {

        // parameters
        private bool m_useIpv6Address = false;
        private bool m_useAnyAddress = false;
        private string m_address;
        private int m_port;

        // states        
        private bool m_initialized = false;
        private volatile bool m_doLoop = false;
        private IPAddress m_finalIpAddress;

        // network
        public ConcurrentDictionary<string, WebSocketConnection> connnections = new ConcurrentDictionary<string, WebSocketConnection>();        
        private TcpListener m_tcpListener = null;
        private WebSocketServer.WebSocketServer m_server = null;        

        public int listening_port() {
            return m_port;
        }

        public string listening_address() {
            return m_address;
        }

        public IPAddress final_ip_address() {
            return m_finalIpAddress;
        }

        public TcpListenerJob(WebSocketServer.WebSocketServer server) {
            m_server = server;
        }

        public bool initialize(bool anyAddress, bool ipv6, string address, int port, bool exclusiveAddressUse) {

            m_useAnyAddress     = anyAddress;
            m_useIpv6Address    = ipv6;
            m_address           = address;
            m_port              = port;

            try {

                m_finalIpAddress =  m_useIpv6Address ? IPAddress.IPv6Any : IPAddress.Any;

                if (!m_useAnyAddress) {                   

                    // parse for normal ip address
                    bool parsingSuccess = false;
                    IPAddress parsedAddress;
                    if (IPAddress.TryParse(address, out parsedAddress)) {
                        if (m_useIpv6Address && parsedAddress.AddressFamily == AddressFamily.InterNetworkV6) {
                            parsingSuccess = true;
                            m_finalIpAddress = parsedAddress;
                        } else if (!m_useIpv6Address && parsedAddress.AddressFamily == AddressFamily.InterNetwork) {
                            parsingSuccess = true;
                            m_finalIpAddress = parsedAddress;
                        }
                    }

                    if (!parsingSuccess) {

                        // try to get dns
                        bool dnsAddressFound = false;
                        IPAddress[] dnsAddresses = Dns.GetHostAddresses(address);
                        foreach (var dnsAddress in dnsAddresses) {

                            if (m_useIpv6Address && dnsAddress.AddressFamily == AddressFamily.InterNetworkV6) { 
                                m_finalIpAddress = dnsAddress;
                                dnsAddressFound = true;
                                break;
                            } else if (!m_useIpv6Address && dnsAddress.AddressFamily == AddressFamily.InterNetwork) {
                                m_finalIpAddress = dnsAddress;
                                dnsAddressFound = true;
                                break;
                            }
                        }   

                        if (!dnsAddressFound) {
                            m_finalIpAddress = m_useIpv6Address ? IPAddress.IPv6Any : IPAddress.Any;
                        }
                    }                    
                }

                m_tcpListener = new TcpListener(m_finalIpAddress, m_port);
                m_tcpListener.ExclusiveAddressUse = exclusiveAddressUse;
                m_tcpListener.Start();
                m_initialized = true;
            } catch (System.Net.Sockets.SocketException e) {
                ExVR.Log().error(string.Format("Socket error: {0}", e.Message));
                m_initialized = false;
            } catch (System.Exception e) {
                ExVR.Log().error(string.Format("Error: {0}", e.Message));
                m_initialized = false;
            }

            if (m_initialized) {
                // start thread
                m_doLoop = true;
                start();
            } else {
                m_tcpListener = null;
            }

            return m_initialized;
        }

        public void clean() {

            // stop thread 
            m_doLoop = false;

            if (!join(100)) {
                ExVR.Log().error(string.Format("Stop listener thread timeout."));
            }

            // remove connections
            foreach (var connection in connnections) {
                connection.Value.clean();
            }
            connnections = new ConcurrentDictionary<string, WebSocketConnection>();

            // stop listener
            if (m_tcpListener != null) {
                m_tcpListener.Stop();
            }

            m_tcpListener = null;
            m_server      = null;
        }

        public void add_connection(WebSocketConnection connection) {
            ExVR.Log().message(string.Format("Add connection {0}.", connection.id));
            connnections[connection.id] = connection;
        }
        public void remove_connection(WebSocketConnection connection) {
            ExVR.Log().message(string.Format("Remove connection {0}.", connection.id));
            WebSocketConnection removedConnection = null;
            connnections.TryRemove(connection.id, out removedConnection);
            if (removedConnection != null) { 
                ExVR.Log().message(string.Format("Connection {0} succesfully removed.", removedConnection.id));
                removedConnection.clean();
            } else {
                ExVR.Log().error(string.Format("Cannot remove connection {0}.", connection.id));
            }
        }

        protected override void thread_function() {

            if (!m_initialized) {
                return;
            }

            try {

                while (m_doLoop) {

                    // check for waiting connection
                    while (!m_tcpListener.Pending()) {
                        System.Threading.Thread.Sleep(100);
                        if (!m_doLoop) {
                            return;
                        }
                    }    

                    // accept a new client, then open a stream for reading and writing.
                    var connectedTcpClient = m_tcpListener.AcceptTcpClient();

                    // create a new connection
                    WebSocketConnection connection = new WebSocketConnection(connectedTcpClient, m_server);

                    // establish connection
                    connection.Establish();
                }
            } catch (SocketException socketException) {
                ExVR.Log().error(string.Format("Listening to connections, socketException {0}", socketException.ToString()));
                m_doLoop = false;
            }

            ExVR.Log().message("Stop listening for connections.");
        }
    }

    public static class XLExtensions {
        public static IEnumerable<string> split_in_groups(this string original, int size) {
            var p = 0;
            var l = original.Length;
            while (l - p > size) {
                yield return original.Substring(p, size);
                p += size;
            }
            yield return original.Substring(p);
        }
    }

    public class MyWebSocketServer : WebSocketServer.WebSocketServer {

        TcpListenerJob m_listener = null;

        public bool initialize(bool anyAddress, bool ipv6, string address, int port, bool exclusiveAddressUse) {
            m_listener = new TcpListenerJob(this);
            if (m_listener.initialize(anyAddress, ipv6, address, port, exclusiveAddressUse)) {                                
                return true;
            } else {
                m_listener = null;
                return false;
            }
        }

        public void clean() {
            if(m_listener != null) {
                m_listener.clean();
                m_listener = null;
            }
        }

        public IPAddress get_listening_ip_address() {
            return m_listener.final_ip_address();
        }

        override public void on_open(WebSocketConnection connection) {
            m_listener.add_connection(connection);
        }

        override public void on_message(WebSocketMessage message) {
            ExVR.Log().message(string.Format("Message received from client [{0}] : [{1}]", message.connection.id, message.data));
        }

        override public void on_close(WebSocketConnection connection) {
            m_listener.remove_connection(connection);
        }
    
        public void send_messages_to_all_clients(string message) {
            var splittedMessage = message.split_in_groups(125);
            foreach (var connection in m_listener.connnections) {
                connection.Value.send_message(splittedMessage);
            }
        }
    }

    public class WebsocketServerComponent : ExComponent {

        private static readonly string m_messageReadSignalStr = "message read";
        private static readonly string m_newConnectionSignalStr = "new connection";
        private static readonly string m_connectionClosedSignalStr = "connection closed";
        MyWebSocketServer m_server = null;
        
        protected override bool initialize() {

            // signals
            add_signal(m_messageReadSignalStr);
            add_signal(m_newConnectionSignalStr);
            add_signal(m_connectionClosedSignalStr);

            // slots
            add_slot("send message", (message) => {
                m_server.send_messages_to_all_clients((string)message);
            });

            m_server = new MyWebSocketServer();
            m_server.onMessage.AddListener((WebSocketMessage message) => {
                if (is_updating()) {
                    double expTime = ExVR.Time().ellapsed_exp_ms();
                    double routineTime = ExVR.Time().ellapsed_element_ms();
                    invoke_signal(m_messageReadSignalStr, new TimeAny(expTime, routineTime, new StringAny(message.connection.id, message.data)));
                }
            });
            m_server.onOpen.AddListener((WebSocketConnection connection) => {
                if (is_updating()) {
                    invoke_signal(m_newConnectionSignalStr, connection.id);
                }
            });
            m_server.onClose.AddListener((WebSocketConnection connection) => {
                if (is_updating()) {
                    invoke_signal(m_connectionClosedSignalStr, connection.id);
                }
            });

            if (m_server.initialize(initC.get<bool>("any_address"), initC.get<int>("family") == 1, initC.get<string>("address"), initC.get<int>("port"), initC.get<bool>("exclusive_address_use"))) {
                send_infos_to_gui_init_config("listening_ip_address", m_server.get_listening_ip_address().ToString());
                return true;
            }
            m_server = null;

            return false;
        }

        protected override void clean() {
            if(m_server != null) {
                m_server.clean();
                m_server = null;
            }
        }
        protected override void update() {
            // always update
            if(m_server != null) {
                m_server.process_events();
            }
        }
    }

}


