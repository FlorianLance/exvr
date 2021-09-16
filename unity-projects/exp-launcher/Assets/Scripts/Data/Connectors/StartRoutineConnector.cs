/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class StartRoutineConnector : ExConnector{

        protected override void initialize(XML.Connector connector) {
            base.initialize(connector);
            add_signals(4);
        }

        protected override void start_routine() {
            invoke_signal(0, associatedRoutine.name);
            invoke_signal(1, associatedCondition.name);
            invoke_signal(2, associatedRoutine.element_iteration());
            invoke_signal(3, associatedRoutine.condition_iteration());
        }
    }
}