/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


namespace Ex{

    public class TransformToVectorsConnector : ExConnector{

        object input0 = null;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            add_signals(3);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object arg) {
            input0 = arg;
            compute();
        }

        private void compute() {

            if(input0 == null) {
                return;
            }

            var v1 = (TransformValue)input0;
            invoke_signal(0, v1.position);
            invoke_signal(1, v1.rotation.eulerAngles);
            invoke_signal(2, v1.scale);

            send_connector_infos_to_gui(Converter.to_string(v1));
        }
    }
}