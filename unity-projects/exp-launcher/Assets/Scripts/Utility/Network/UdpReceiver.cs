/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Threading;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Collections;
using System.Collections.Generic;

namespace Ex {

    public class UdpReceiver : ThreadedJob {

        public bool readingEnabled = false;
        public bool initialized = false;

        public int readingPort;
        public IPAddress readingAddress = null;
        private IPEndPoint clientIpEndPoint = null;

        private Socket clientSocket = null;
        private const int bufSize = 8 * 1024;
        private byte[] buffer = new byte[bufSize];

        public ReaderWriterLock rwl = new ReaderWriterLock();
        public Queue queue = new Queue();
        public bool messageReceived = false;

        //private int m_readSizeBuffer = -1;
        //public void set_buffer_size_to_read(int readSizeBuffer) {
        //    m_readSizeBuffer = readSizeBuffer;
        //}

        public bool initialize(int port, IPAddress ipAddress, int timeoutMs = 10) {

            readingPort = port;
            readingAddress = ipAddress;
            initialized = false;

            clientIpEndPoint = new IPEndPoint(ipAddress, readingPort);
            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            clientSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
            clientSocket.Bind(clientIpEndPoint);
            clientSocket.ReceiveTimeout = timeoutMs;

            return initialized = true;
        }

        public void set_reading_state(bool readingState) {

            if (!initialized) {
                return;
            }

            rwl.AcquireWriterLock(1000);
            if (readingEnabled) {
                if (readingState) {
                    // do nothing
                } else {
                    stop(); // stop thread
                    readingEnabled = false;
                }
            } else {
                if (!readingState) {
                    // do nothing
                } else {
                    readingEnabled = true;
                    start(); // start thread
                }
            }
            rwl.ReleaseWriterLock();
        }

        public string read_message() {

            string message = "";
            if (clientSocket == null) {
                return message;
            }

            try {
                rwl.AcquireWriterLock(5);
                try {
                    if (queue.Count > 0) {
                        message = (string)queue.Dequeue();
                    }
                } finally {
                    rwl.ReleaseWriterLock();
                }
            } catch (ApplicationException) {
                // timeout
            }

            return message;
        }

        public List<string> read_all_messages() {

            if (clientSocket == null) {
                return new List<string>();
            }

            List<string> messages = null;
            try {
                rwl.AcquireWriterLock(5);
                try {
                    var queueA = queue.ToArray();
                    messages = new List<string>(queueA.Length);
                    foreach (var message in queueA) {
                        messages.Add((string)message);
                    }
                    queue.Clear();
                } finally {
                    rwl.ReleaseWriterLock();
                }
            } catch (ApplicationException) {
                // timeout
            }

            if (messages == null) {
                return new List<string>();
            }

            return messages;
        }

        public void clean() {

            readingEnabled = false;
            stop();

            rwl.AcquireWriterLock(300);
            if (clientSocket != null) {
                //try {
                //    clientSocket.Shutdown(SocketShutdown.Both);
                //} finally {
                //    clientSocket.Close();
                //}
                clientSocket.Close();
                clientSocket.Dispose();
                clientSocket = null;
                clientIpEndPoint = null;
                initialized = false;
                messageReceived = false;
                queue.Clear();
            }
            rwl.ReleaseWriterLock();
        }

        protected override void OnFinished() { }


        //private void read_specific_size_buffer_loop() {

        //    while (readingEnabled) {

        //        // Receive a message 
        //        int count;
        //        try {
        //            count = clientSocket.Receive(buffer, 0, m_readSizeBuffer, SocketFlags.None);
        //        } catch (SocketException e) {
        //            if (e.SocketErrorCode != SocketError.TimedOut) {
        //                UnityEngine.Debug.LogError(string.Format("Receive socket error: {0}", e.Message));
        //            }
        //            continue;
        //        }

        //        if (readingEnabled) {
        //            try {
        //                rwl.AcquireWriterLock(1000);
        //                try {
        //                    queue.Enqueue(Encoding.UTF8.GetString(buffer, 0, count));
        //                    messageReceived = true;
        //                } finally {
        //                    rwl.ReleaseWriterLock();
        //                }
        //            } catch (ApplicationException) {
        //                // timeout
        //            }
        //        }

        //        // Sleep while we wait for a message
        //        while (!messageReceived) {
        //            Thread.Sleep(5);
        //        }
        //        messageReceived = false;
        //    }
        //}

        protected override void ThreadFunction() {

            byte[] endByte = Encoding.ASCII.GetBytes(new char[] { '\0' });
            while (readingEnabled) {

                // Receive a message 
                int count;
                try {
                    count = clientSocket.Receive(buffer);
                    int endId = Array.IndexOf(buffer, endByte[0]);
                    if (endId < count) {
                        count = endId;
                    }
                } catch (SocketException e) {
                    if (e.SocketErrorCode != SocketError.TimedOut) {
                        UnityEngine.Debug.LogError(string.Format("Receive socket error: {0}", e.Message));
                    }
                    continue;
                }

                if (readingEnabled) {
                    try {
                        rwl.AcquireWriterLock(1000);
                        try {
                            queue.Enqueue(Encoding.UTF8.GetString(buffer, 0, count));
                            messageReceived = true;
                        } finally {
                            rwl.ReleaseWriterLock();
                        }
                    } catch (ApplicationException) {
                        // timeout
                    }
                }

                // Sleep while we wait for a message
                //while (!messageReceived) {
                //    Thread.Sleep(5);
                //}
                messageReceived = false;
            }
        }
    }
}