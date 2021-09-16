/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex {

    public class ForceComponentConfigConnector : ExConnector {

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            add_slot(0, (nullArg) => { base_slot1(null);});
        }

        protected override void slot1(object arg) {

            var value = m_config.get_component_config(valueStr);

            Condition condition = null;
            ExComponent component = null;
            ComponentConfig config = null;

            if (value != null) {
                condition = value.Item2;
                component = value.Item3;
                config = value.Item4;
            }

            if (config == null) {
                return;
            }

            if (condition != null) {
                var action = condition.get_action_from_component_key(component.key);
                if(action != null) {
                    action.force_config(config);
                }
            }
        }
    }
}