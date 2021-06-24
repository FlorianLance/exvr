/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

namespace Ex{

    public class CurveXConnector : ExConnector{

        public List<double> stackValues = new List<double>();
        public int frequency = 30;
        private int count = 0;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            add_slot(0, (arg) => { base_slot1(arg); });
        }
        
        protected override void slot1(object arg) {
            stackValues.AddRange((List<double>)arg);
        }

        protected override void stop_routine() {
            count = 0;
        }

        protected override void update() {

            double totalTime = ExVR.Time().ellapsed_time_element_ms();
            double deltaTime = 1000.0 / frequency;
            if (totalTime / deltaTime > count) {
                if (stackValues.Count > 0) {
                    send_output(stackValues);
                    stackValues.Clear();
                }
                ++count;
            }
        }

        void send_output(List<double> values) {
            send_connector_infos_to_gui(Converter.to_string(values));
        }
    }
}