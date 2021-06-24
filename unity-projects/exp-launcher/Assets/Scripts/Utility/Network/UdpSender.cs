/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace Ex {

    public class UdpSender {

        public int writingPort;
        public IPAddress writingAddress = null;
        private IPEndPoint endPoint = null;

        UdpClient sender = null;

        public void initialize(int port, IPAddress ipAddress, bool ipv6 = false) {

            writingPort = port;
            writingAddress = ipAddress;

            endPoint = new IPEndPoint(ipAddress, port);
            sender = new UdpClient(ipv6 ? AddressFamily.InterNetworkV6 : AddressFamily.InterNetwork);
        }

        public int send_message(string message) {
            return send_bytes(Encoding.UTF8.GetBytes(message));
        }

        public int send_bytes(byte[] bytesToSend) {
            return sender.Send(bytesToSend, bytesToSend.Length, endPoint);
        }
    }
}