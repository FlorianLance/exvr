/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class DecimalOperationConnector : ExConnector{

        DecimalValue input0 = null;
        DecimalValue input1 = null;

        private string functionStr = "";

        ConnectorsFunctions.DecimalOperator ope;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
        
            functionStr = m_config.get<string>(valueStr);
            ope = ExVR.Functions().get_decimal_operator(functionStr);

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
            add_slot(1, (arg) => { base_slot2(arg); });
        }

        protected override void slot1(object arg) {
            input0 = (DecimalValue)arg;
            send_output();
        }

        protected override void slot2(object arg) {
            input1 = (DecimalValue)arg;
            send_output();
        }

        protected override void update_from_gui() {

            functionStr = m_config.get<string>(valueStr);
            ope = ExVR.Functions().get_decimal_operator(functionStr);
  
            send_output();
        }

        private void send_output() {

            if (input0 != null && input1 != null) {
                var value = new DecimalValue();
                DecimalValue.apply_function(input0, input1, value, ope);
                send_connector_infos_to_gui(Converter.to_string(value, "G4"));
                invoke_signal(0, value);
            }
        }

        protected override void stop_routine() {
            input0 = null;
            input1 = null;
        }
    }
}