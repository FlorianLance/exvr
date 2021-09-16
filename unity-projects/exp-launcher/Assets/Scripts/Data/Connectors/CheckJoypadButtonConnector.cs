/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;

namespace Ex{

    public class CheckJoypadButtonConnector : ExConnector{

        Input.JoypadButton.Code codeToCompare;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            update_from_gui();

            add_signals(4);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void update_from_gui() {
            codeToCompare = (Input.JoypadButton.Code)Enum.Parse(typeof(Input.JoypadButton.Code), m_config.get<string>(valueStr));
        }

        protected override void slot1(object arg) {

            var state = (Input.JoypadButtonEvent)arg;
            if(state.code == codeToCompare) {

                invoke_signal(3, state.triggeredExperimentTime);
                switch (state.state) {
                    case Input.Button.State.Down:
                        invoke_signal(0);
                        invoke_signal(2);
                        break;
                    case Input.Button.State.Up:
                        invoke_signal(1);
                        break;
                    case Input.Button.State.Pressed:
                        invoke_signal(2);
                        break;
                }                
            }
        }
    }
}

