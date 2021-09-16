/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex {

    public class StopRoutineConnector : ExConnector {

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            add_signals(2);
        }

        protected override void stop_routine() {
            invoke_signal(0, associatedRoutine.name);
            invoke_signal(1, associatedCondition.name);
        }
    }
}