/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex {

    public class UpdateRoutineConnector : ExConnector {

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            add_signals(1);
        }

        protected override void update() {            
            invoke_signal(0, ExVR.Time().ellapsed_element_ms());
        }
    }
}