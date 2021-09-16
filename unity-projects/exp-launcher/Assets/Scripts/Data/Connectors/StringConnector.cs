/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class StringConnector : ExConnector{

        private object inputValue = null;
        private string uiValue = "";

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            
            uiValue = m_config.get<string>(valueStr);

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });            
        }

        protected override void slot1(object arg) {
            inputValue = arg;
            if (inputValue != null) {
                send_output(Converter.to_string(inputValue));
            } else {
                send_output(uiValue);
            }
        }

        protected override void update_from_gui() {
            uiValue = m_config.get<string>(valueStr);
            start_routine();
        }

        protected override void start_routine() {

            if (inputGO.Count == 0) {
                send_output(uiValue);
            }
        }

        private void send_output(string value) {

            send_connector_infos_to_gui(value);
            invoke_signal(0, value);
        }

        protected override void stop_routine() {
            inputValue = null;
        }
    }
}