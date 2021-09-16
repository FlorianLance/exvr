/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class StopConnector : ExConnector{

        protected override void initialize(XML.Connector connector) {
            base.initialize(connector);
            add_slot(0, (nullArg) => { base_slot1(null); });
        }

        protected override void slot1(object arg) {
            command().force_stop_experiment();
        }
    }
}