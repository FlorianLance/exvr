
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex
{

    public class UdpWriterComponent : ExComponent{

        private UdpSender m_udp = null;

        protected override bool initialize() {

            // signals
            add_slot("send message", (message) => { send_message((string)message);});
            add_signal("nb bytes sent");

            bool ipv6 = false; // initC.get<bool>("ipv6");
            var ipAddresses = NetworkInfo.get_ip_addresses(initC.get<string>("writing_address"),ipv6);
            if (ipAddresses.Count == 0) {
                log_error("Cannot find any ip address from: " + initC.get<string>("writing_address"));
                return false;
            }

            m_udp = new UdpSender();
            m_udp.initialize(initC.get<int>("writing_port"), ipAddresses[0]);
            return true;
        }

        public void send_message(string message) {
            if (is_updating()) {
                invoke_signal("nb bytes sent", m_udp.send_message(message));
            }
        }

        public void send_bytes(byte[] bytes) {
            if (is_updating()) {
                invoke_signal("nb bytes sent", m_udp.send_bytes(bytes));
            }
        }
    }
}