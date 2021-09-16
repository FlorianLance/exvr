/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class DecimalCounterConnector : ExConnector{

        DecimalValue current = null;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
            add_slot(1, (arg) => { base_slot2(arg); });
            add_slot(2, (nullArg) => { base_slot3(null); });            
        }

        protected override void slot1(object arg) {
            current.add((DecimalValue)arg);
            send_output();
        }
        protected override void slot2(object arg) {
            current.sub((DecimalValue)arg);
            send_output();
        }
        protected override void slot3(object arg) {
            current = new DecimalValue(0);
            send_output();
        }

        private void send_output() {
            send_connector_infos_to_gui(Converter.to_string(current));
            invoke_signal(0, current);
        }

        protected override void start_routine() {
            current = new DecimalValue(0);
        }

        protected override void stop_routine() {
            current = null;
        }
    }
}