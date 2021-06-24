
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

//unity
using UnityEngine;

namespace Ex{

    public class TheraTrainerTrackingComponent : ExComponent {

        UdpReceiver m_receiver = null;

        protected override bool initialize() {

            // signals
            add_signal("new pos");
            add_signal("battery");

            var ipAddresses = NetworkInfo.get_ip_addresses(initC.get<string>("read_address"));
            if (ipAddresses.Count == 0) {
                log_error("Cannot find any ip address from: " + initC.get<string>("read_address"));
                return false;
            }

            // udp reader
            m_receiver = new UdpReceiver();
            m_receiver.initialize(init_config().get<int>("read_port"), ipAddresses[0]);

            log_message("Thera trainer device intialized: " + m_receiver.initialized);

            return m_receiver.initialized;
        }

        protected override void set_update_state(bool doUpdate){
            m_receiver.set_reading_state(doUpdate);
        }

        protected override void update() {

            var messages = m_receiver.read_all_messages();
            if (messages.Count > 0) {
                var message = messages[messages.Count - 1];
                message = message.Replace(",", ".");
                if (message.Length > 0) {
                    var split = message.Split('_');
                    if (split.Length == 3) {
                        invoke_signal("new pos", new Vector2(Converter.to_float(split[0]), Converter.to_float(split[1])));
                        invoke_signal("battery", Converter.to_int(split[2]));
                    }
                }
            }
        }

        protected override void clean(){
            m_receiver.clean();
        }
    }
}

