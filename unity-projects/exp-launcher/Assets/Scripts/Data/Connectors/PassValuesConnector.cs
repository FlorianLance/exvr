/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class PassValuesConnector : ExConnector{

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
            add_slot(1, (arg) => { base_slot1(arg); });
            add_slot(2, (arg) => { base_slot1(arg); });
            add_slot(3, (arg) => { base_slot1(arg); });
            add_slot(4, (arg) => { base_slot1(arg); });
            add_slot(5, (arg) => { base_slot1(arg); });
            add_slot(6, (arg) => { base_slot1(arg); });
            add_slot(7, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object arg) {
            invoke_signal(0, arg);
        }
    }
}