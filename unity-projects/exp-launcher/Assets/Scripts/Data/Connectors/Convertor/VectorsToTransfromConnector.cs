/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class VectorsToTransformConnector : ExConnector{

        object input0 = null;
        object input1 = null;
        object input2 = null;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
            add_slot(1, (arg) => { base_slot2(arg); });
            add_slot(2, (arg) => { base_slot3(arg); });
        }

        protected override void slot1(object arg) {
            input0 = arg;
            compute();
        }

        protected override void slot2(object arg) {
            input1 = arg;
            compute();
        }

        protected override void slot3(object arg) {
            input2 = arg;
            compute();
        }

        private void compute() {

            if (input0 == null || input1 == null || input2 == null) {
                return;
            }

            var v = new TransformValue();
            v.position = (Vector3)input0;
            v.rotation = Quaternion.Euler((Vector3)input1);
            v.scale = (Vector3)input2;
            invoke_signal(0, v);

            send_connector_infos_to_gui(Converter.to_string(v));
        }
    }
}