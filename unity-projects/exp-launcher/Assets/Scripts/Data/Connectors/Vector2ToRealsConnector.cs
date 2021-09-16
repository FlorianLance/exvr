/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


// unity
using UnityEngine;

namespace Ex{

    public class Vector2ToRealsConnector : ExConnector{


        protected override void initialize(XML.Connector connector){

            base.initialize(connector);
            add_signals(2);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object arg) {
    
            if (arg != null) {
                Vector2 v = (Vector2)arg;
                invoke_signal(0, Converter.to_double(v.x));
                invoke_signal(1, Converter.to_double(v.y));

                send_connector_infos_to_gui(Converter.to_string(v));
            }
        }

    }
}