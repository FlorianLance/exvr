/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class DecimalTrigonometryConnector : ExConnector{

        DecimalValue input = null;

        ConnectorsFunctions.TrigonometryFunction trigonometry;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);

            
            trigonometry = ConnectorsFunctions.get_trigonometry_function(m_config.get<string>(valueStr));

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object arg) {
            input = (DecimalValue)arg;
            send_output();
        }

        protected override void update_from_gui() {
            trigonometry = ConnectorsFunctions.get_trigonometry_function(m_config.get<string>(valueStr));
            send_output();
        }

        private void send_output() {

            if (input != null) {
                var value = new DecimalValue();
                DecimalValue.apply_function(input, value, trigonometry);
                send_connector_infos_to_gui(Converter.to_string(value, "G4"));
                invoke_signal(0, value);
            }
        }

        protected override void stop_routine() {
            input = null;
        }
    }
}