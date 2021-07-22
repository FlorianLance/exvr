/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class LoggerConnector : ExConnector{

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object arg) {
            ConnectorsFunctions.get_logger(arg.GetType()).Invoke(arg);
        }
    }
}