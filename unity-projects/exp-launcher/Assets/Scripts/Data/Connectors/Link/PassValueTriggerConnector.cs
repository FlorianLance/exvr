/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class PassValueTriggerConnector : ExConnector{

        object input = null;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
            add_slot(1, (nullArg) => { base_slot2(null); });
        }

        protected override void slot1(object arg) {
            input = arg;
        }

        protected override void slot2(object nullArg) {
            if (input != null) {
                invoke_signal(0, input);
            }
        }

        protected override void stop_routine() {
            input = null;
        }
    }
}