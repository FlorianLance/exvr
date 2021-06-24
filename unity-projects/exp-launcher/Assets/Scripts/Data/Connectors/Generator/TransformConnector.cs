/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex {

    public class TransformConnector : ExConnector {

        private TransformValue uiValue = null;
        private TransformValue value = new TransformValue();

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);            
            uiValue = m_config.get_transform(valueStr);

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object inputValue) {

            if (inputValue != null) {
                value = (TransformValue)inputValue;
            }
            send_output();
        }

        protected override void update_from_gui() {
            uiValue = m_config.get_transform(valueStr);
            start_routine();
        }

        protected override void start_routine() {

            value.position = uiValue.position;
            value.rotation = uiValue.rotation;
            value.scale    = uiValue.scale;

            send_output();
        }

        void send_output() {
            invoke_signal(0, value);
            send_connector_infos_to_gui(Converter.to_string(value));            
        }
    }
}