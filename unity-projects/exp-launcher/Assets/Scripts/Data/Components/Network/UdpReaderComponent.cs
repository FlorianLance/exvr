
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class UdpReaderComponent : ExComponent{

        private UdpReceiver m_udpReceiver = null;

        protected override bool initialize() {

            // signals
            add_signal("last message received");

            bool ipv6 = false; // initC.get<bool>("ipv6");
            var ipAddresses = NetworkInfo.get_ip_addresses(initC.get<string>("reading_address"), ipv6);
            if(ipAddresses.Count == 0) {
                log_error("Cannot find any ip address from: " + initC.get<string>("reading_address"));
                return false;
            }
  
            m_udpReceiver = new UdpReceiver();
            return m_udpReceiver.initialize(initC.get<int>("reading_port"), ipAddresses[0]);
        }

        protected override void start_routine() {
            m_udpReceiver.set_reading_state(true);
        }    

        protected override void update() {

            var messages = m_udpReceiver.read_all_messages();
            if(messages.Count > 0) {
                invoke_signal("last message received", messages[messages.Count - 1]);                
            }
        }

        protected override void stop_routine() {
            // stop reading messages
            m_udpReceiver.set_reading_state(false);
        }

        public override void play() {
            // read messages
            m_udpReceiver.set_reading_state(true);
        }

        public override void pause() {
            // stop reading messages
            m_udpReceiver.set_reading_state(false);
        }

        protected override void clean() {
            m_udpReceiver.clean();
        }
    }
}