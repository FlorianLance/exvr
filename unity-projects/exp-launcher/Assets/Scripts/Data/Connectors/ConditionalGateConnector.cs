/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class ConditionalGateConnector : ExConnector{

        private object inputStateValue = null;
        private bool uiStateValue = false;
        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            uiStateValue = m_config.get<bool>(valueStr);

            add_signals(1);            
            add_slot(0, (arg) =>     { base_slot1(arg); });
            add_slot(1, (arg) =>     { base_slot2(arg); });
        }

        protected override void slot1(object arg) {
            if(inputStateValue == null) {
                if (uiStateValue) {
                    invoke_signal(0, arg);
                }
            } else {
                if ((bool)inputStateValue) {                    
                    invoke_signal(0, arg);
                }
            }
        }

        protected override void slot2(object arg) {
            inputStateValue = (bool)arg;
            send_connector_infos_to_gui(Converter.to_string(inputStateValue));
        }
    }
}