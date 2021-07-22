/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

namespace Ex{

    public class StringOperationConnector : ExConnector {

        object input0 = null;
        object input1 = null;
        ConnectorsFunctions.StringOperator stringO;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            stringO = ConnectorsFunctions.get_string_operator(m_config.get<string>(valueStr));

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
            add_slot(1, (arg) => { base_slot2(arg); });
        }

        protected override void slot1(object arg) {
            input0 = arg;
            send_output();
        }

        protected override void slot2(object arg) {
            input1 = arg;
            send_output();
        }

        protected override void update_from_gui() {
            stringO = ConnectorsFunctions.get_string_operator(m_config.get<string>(valueStr));
            send_output();
        }

        private void send_output() {

            if (input0 != null && input1 != null) {
                var value = ConnectorsFunctions.get(stringO).Invoke((string)input0, (string)input1);
                invoke_signal(0, value);
                if(value is string) {
                    send_connector_infos_to_gui((string)value);
                } else if (value is List<string>){
                    send_connector_infos_to_gui(Converter.to_string(((List<string>)value).Count));
                }

            }
        }

        protected override void stop_routine() {
            input0 = null;
            input1 = null;
        }
    }
}