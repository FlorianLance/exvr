/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class NextElementWithNameConnector : ExConnector{

        protected override void initialize(XML.Connector connector) {
            base.initialize(connector);
            add_slot(0, (nullArg) => { base_slot1(null); });
        }

        protected override void slot1(object arg) {
            ExComponent.next_element_with_name(m_config.get<string>(valueStr));
        }
    }
}