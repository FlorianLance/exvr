/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class BinaryOperationConnector : ExConnector{

        object input0 = null;
        object input1 = null;
        ConnectorsFunctions.BinaryOperator binary;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            binary = ExVR.Functions().get_binary_function(m_config.get<string>(valueStr));

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
            binary = ExVR.Functions().get_binary_function(m_config.get<string>(valueStr));
            send_output();
        }

        private void send_output() {

            if(binary == ConnectorsFunctions.BinaryOperator.not) {
                if (input0 != null) {
                    var value = ExVR.Functions().get(binary).Invoke((bool)input0, false);
                    send_connector_infos_to_gui(Converter.to_string(value));
                    invoke_signal(0, value);
                }
            } else {
                if (input0 != null && input1 != null) {
                    var value = ExVR.Functions().get(binary).Invoke((bool)input0, (bool)input1);
                    send_connector_infos_to_gui(Converter.to_string(value));
                    invoke_signal(0, value);
                }
            }
        }

        protected override void stop_routine() {
            input0 = null;
            input1 = null;
        }
    }
}