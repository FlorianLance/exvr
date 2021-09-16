/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;

namespace Ex{

    public class CheckJoypadAxisConnector : ExConnector{

        Input.JoypadAxis.Code codeToCompare;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            update_from_gui();

            add_signals(2);
            add_slot(0, (arg) => { base_slot1(arg); });
        }


        protected override void update_from_gui() {
            codeToCompare = (Input.JoypadAxis.Code)Enum.Parse(typeof(Input.JoypadAxis.Code), m_config.get<string>(valueStr));
        }

        protected override void slot1(object arg) {

            var state = (Input.JoypadAxisEvent)arg;
            if (state.code == codeToCompare) {
                invoke_signal(1, state.triggeredExperimentTime);
                invoke_signal(0, state.value);;                
            }
        }
    }
}

