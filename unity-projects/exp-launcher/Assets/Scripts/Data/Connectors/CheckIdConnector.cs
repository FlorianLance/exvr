/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex {

    public class CheckIdConnector : ExConnector {

        private int id = 0;
        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);            
            update_from_gui();

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });            
        }

        protected override void update_from_gui() {
            id = m_config.get<int>(valueStr);
        }

        protected override void slot1(object arg) {
            var idAny = (IdAny)arg;
            if (idAny.id == id) {
                invoke_signal(0, idAny.value);
            }
        }
    }
}