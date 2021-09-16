/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class BooleanConnector : ExConnector{

        private object inputValue = null;
        private bool uiValue = false;

        protected override void initialize(XML.Connector connector){

            base.initialize(connector);
            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
            add_slot(1, (nullArg) =>    { base_slot2(null); });

            uiValue = m_config.get<bool>(valueStr);
        }

        protected override void slot1(object arg) {
            inputValue = arg;
            if (inputValue != null) {
                send_output((bool)inputValue);
            } else {
                send_output(uiValue);
            }
        }

        protected override void slot2(object nullArg) {

            if (inputValue != null) {
                inputValue = !(bool)inputValue;                
            } else {
                inputValue = !uiValue;
            }
            send_output((bool)inputValue);
        }

        protected override void update_from_gui() {
            uiValue = m_config.get<bool>(valueStr);
            start_routine();
        }

        protected override void start_routine() {

            foreach (var connection in inputConnections) {
                if (connection.endIndex == 0) { // if we have a connection at index 0, do not send ui value
                    return;
                }
            }

            send_output(uiValue);
        }

        void send_output(bool value) {
            send_connector_infos_to_gui(Converter.to_string(value));
            invoke_signal(0, value);
        }

        protected override void stop_routine() {
            inputValue = null;
        }
    }
}