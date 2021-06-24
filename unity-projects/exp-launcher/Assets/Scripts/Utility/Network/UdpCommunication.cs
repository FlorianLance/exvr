/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

namespace Ex{


    public class UdpCommunication{

        private UdpReceiver m_receiver = null;
        private UdpSender m_sender = null;

        public UdpCommunication(bool write, bool read, int wPort, string wAddress, int rPort, string rAddress) {

            var wIp = NetworkInfo.get_ip_addresses(wAddress, false);
            var rIp = NetworkInfo.get_ip_addresses(rAddress, false);

            if (wIp.Count == 0 || rIp.Count == 0) {
                UnityEngine.Debug.LogError("Cannot found ip addreses.");
                m_receiver = null;                
                return;
            }

            if (write) {
                m_sender = new UdpSender();
                m_sender.initialize(wPort, wIp[0]);
            }

            if (read) {

                m_receiver = new UdpReceiver();

                if (rPort == -1) { // undefined reading port
                    for (rPort = wPort + 1; rPort < wPort + 10; ++rPort) {  // try to find aumatically the good reading port

                        m_receiver.initialize(rPort, rIp[0]);
                        if (m_receiver.initialized) {
                            break;
                        }   
                    }
                } else {
                    m_receiver.initialize(rPort, rIp[0]);
                }

                if (!m_receiver.initialized) {
                    m_receiver = null;
                    UnityEngine.Debug.LogError("UDP receiver error with : " + rAddress + ":" + rPort);
                }
            }
        }

        public bool receiver_initialized() {
            return m_receiver != null;
        }

        public bool sender_initialized() {
            return m_sender != null;
        }

        public int receiver_port() {
            if (receiver_initialized()) {
                return m_receiver.readingPort;
            }
            return 0;
        }

        public int sender_port() {
            if (sender_initialized()) {
                return m_sender.writingPort;
            }            
            return 0;
        }

        public void set_reading_mode(bool readingEnabled) {
            if (receiver_initialized()) {
                m_receiver.set_reading_state(readingEnabled);
            }
        }

        public int send_message(string message) {
            if (sender_initialized()) {
                return m_sender.send_message(message);
            }
            return -1;
        }

        public int send_bytes(byte[] bytesToSend) {
            if (sender_initialized()) {
                return m_sender.send_bytes(bytesToSend);
            }
            return -1;
        }
        

        public string read_message() {
            if (receiver_initialized()) {
                return m_receiver.read_message();
            }
            return "";
        }

        public List<string> read_all_messages() {

            if (receiver_initialized()) {
                return m_receiver.read_all_messages();
            }
            return new List<string>();
        }

        public void clean() {
            if (receiver_initialized()) {
                m_receiver.clean();
            }
        }
    }
}