/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class TimeConnector : ExConnector{

        public bool sinceExp = true;
        public int frequency = 30;
        private int count = 0;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            update_from_gui();

            add_signals(1);
        }

        protected override void update_from_gui() {
            var args  = m_config.get_list<string>(valueStr);
            sinceExp  = (args[0] == "Time since exp");
            frequency = Converter.to_int(args[1]);
            count = 0;
        }

        protected override void update() {

            var currentTime = ExVR.Time().ellapsed_element_ms();
            double deltaTime = 1000.0 / frequency;

            if (currentTime / deltaTime > count) {

                if (sinceExp) {
                    currentTime = ExVR.Time().ellapsed_exp_ms();
                }

                send_connector_infos_to_gui(Converter.to_string((int)currentTime));

                invoke_signal(0, currentTime);
                ++count;
            }
        }

        protected override void stop_routine() {
            count = 0;
        }
    }
}