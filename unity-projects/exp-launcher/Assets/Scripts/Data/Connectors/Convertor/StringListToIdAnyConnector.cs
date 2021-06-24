/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

namespace Ex{

    public class StringListToIdAnyConnector : ExConnector{

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object arg) {
               
            var list = (List<string>)arg;
            if (list != null) {
                for(int ii = 0; ii < list.Count; ++ii) {
                    invoke_signal(0, new IdAny(ii, list[ii]));
                }                
            }
        }
    }
}