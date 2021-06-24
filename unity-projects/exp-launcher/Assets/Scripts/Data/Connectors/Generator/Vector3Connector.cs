/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class Vector3Connector : ExConnector{

        private object inputValue = null;
        private Vector3 uiValue = new Vector3();

        protected override void initialize(XML.Connector connector) {
            
            base.initialize(connector);            
            uiValue = m_config.get_vector3(valueStr);

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object arg) {
            inputValue = arg;
            if (inputValue != null) {
                send_output((Vector3)inputValue);
            } else {
                send_output(uiValue);
            }
        }

        protected override void update_from_gui() {
            uiValue = m_config.get_vector3(valueStr);
            start_routine();
        }

        protected override void start_routine() {
            if (inputGO.Count == 0) {
                send_output(uiValue);
            }
        }

        void send_output(Vector3 value) {
            send_connector_infos_to_gui(Converter.to_string(value));
            invoke_signal(0, value);
        }

        protected override void stop_routine() {
            inputValue = null;
        }
    }
}