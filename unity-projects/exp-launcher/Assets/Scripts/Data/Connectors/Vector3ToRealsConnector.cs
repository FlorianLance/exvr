/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class Vector3ToRealsConnector : ExConnector{


        protected override void initialize(XML.Connector connector){

            base.initialize(connector);
            add_signals(3);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object arg) {

            if (arg == null) {
                return;
            }

            Vector3 v = (Vector3)arg;
            invoke_signal(0, Converter.to_double(v.x));
            invoke_signal(1, Converter.to_double(v.y));
            invoke_signal(2, Converter.to_double(v.z));

            send_connector_infos_to_gui(Converter.to_string(v));
        }
    }
}

