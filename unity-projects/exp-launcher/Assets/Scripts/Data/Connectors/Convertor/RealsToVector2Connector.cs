/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class RealsToVector2Connector : ExConnector{

        object input0 = null;
        object input1 = null;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            add_signals(1);
            add_slot(0, (arg) => {base_slot1(arg);});
            add_slot(1, (arg) => {base_slot2(arg);});
        }

        protected override void slot1(object arg) {
            input0 = arg;
            compute();
        }

        protected override void slot2(object arg) {
            input1 = arg;
            compute();
        }

        private void compute() {

            double v1 = 0, v2 = 0;
            if (input0 != null) {
                v1 = (double)input0;
            }
            if (input1 != null) {
                v2 = (double)input1;
            }

            if (input0 != null || input1 != null) {
                var vec = new Vector2((float)v1, (float)v2);
                invoke_signal(0, vec);
                send_connector_infos_to_gui(Converter.to_string(vec));
            }
        }
    }
}