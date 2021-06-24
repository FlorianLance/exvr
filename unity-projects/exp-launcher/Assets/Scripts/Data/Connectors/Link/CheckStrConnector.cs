/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex {

    public class CheckStrConnector : ExConnector {

        private string str = "";
        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            update_from_gui();

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });            
        }

        protected override void update_from_gui() {
            str = m_config.get<string>(valueStr);
        }

        protected override void slot1(object arg) {
            var strAny = (StringAny)arg;
            if (strAny.str == str) {
                invoke_signal(0, strAny.value);
            }
        }
    }
}