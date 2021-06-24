/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Text;
using System.Collections.Generic;
// unity
using UnityEngine;


namespace Ex{

    public class MouseComponent : ExComponent{

        private bool sendInfos = false;
        

        // signals
        private static readonly string movementSignal = "movement";
        private static readonly string buttonSignal = "button";
        // infos
        private static readonly string buttonsInfoSignal = "buttons_state_info";

        // buttons
        public Dictionary<KeyCode, Input.MouseButtonEvent> buttonsState = new Dictionary<KeyCode, Input.MouseButtonEvent>();

        protected override bool initialize() {

            //add_signal(movementSignal);
            add_signal(buttonSignal);
                        
            foreach (var code in Input.Mouse.Codes) {
                buttonsState[code] = new Input.MouseButtonEvent(code);
            }
            return true;
        }

        protected override void update() {
            // reset states infos
            sendInfos = true;
        }

        protected override void on_gui() {

            var eventType = Event.current.type;
            if (eventType != EventType.Repaint && eventType != EventType.MouseDown && eventType != EventType.MouseUp && eventType != EventType.MouseMove) {
                return;
            }
            var currentTime = ellapsed_time_exp_ms();

    
            int pressedKeysCount = 0;
            foreach (var code in Input.Mouse.Codes) {

                bool pressed = UnityEngine.Input.GetKey(code);
                var currentState = buttonsState[code];

                if (currentState.state == Input.Button.State.None) {
                    if (pressed) {
                        currentState.state = Input.Button.State.Down;
                    }
                } else if (currentState.state == Input.Button.State.Down) {
                    if (pressed) {
                        currentState.state = Input.Button.State.Pressed;
                    } else {
                        currentState.state = Input.Button.State.Up;
                    }

                } else if (currentState.state == Input.Button.State.Pressed) {
                    if (!pressed) {
                        currentState.state = Input.Button.State.Up;
                    }
                } else if (currentState.state == Input.Button.State.Up) {
                    if (pressed) {
                        currentState.state = Input.Button.State.Down;
                    } else {
                        currentState.state = Input.Button.State.None;
                    }
                }

                if (pressed) {
                    ++pressedKeysCount;
                }

                if (currentState.state != Input.Button.State.None) {
                    currentState.triggeredExperimentTime = currentTime;
                    invoke_signal(buttonSignal, currentState);
                }

                buttonsState[code] = currentState;
            }

            // send infos only once per frame
            if (pressedKeysCount > 0 && sendInfos) {

                StringBuilder infos = new StringBuilder();
                int currentCode = 0;
                foreach (var code in Input.Mouse.Codes) {
                    var buttonState = buttonsState[code];
                    if (buttonState.state == Input.Button.State.Pressed || buttonState.state == Input.Button.State.Down) {
                        if (currentCode != pressedKeysCount - 1) {
                            infos.AppendFormat("{0},", ((int)code).ToString());
                        } else {
                            infos.Append(((int)code).ToString());
                        }
                        ++currentCode;
                    }
                }
                send_infos_to_gui_init_config(buttonsInfoSignal, infos.ToString()); ;
            }

            sendInfos = false;
        }
    }
}