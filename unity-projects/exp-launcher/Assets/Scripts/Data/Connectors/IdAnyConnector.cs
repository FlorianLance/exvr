/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class IdAnyConnector : ExConnector{

        private int id;
        private object value = null;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            id = m_config.get<int>(valueStr);

            add_signals(1);            
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object arg) {
            value = arg;
            send_output();
        }

        protected override void update_from_gui() {
            id = m_config.get<int>(valueStr);
            send_output();
        }

        void send_output() {
            invoke_signal(0, new IdAny(id, value));
        }

        protected override void stop_routine() {
            value = null;
        }
    }
}