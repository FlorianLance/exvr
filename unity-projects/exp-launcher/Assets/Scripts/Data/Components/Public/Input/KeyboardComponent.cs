/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Text;
using System.Collections.Generic;
// unity
using UnityEngine;
using UnityRawInput;

namespace Ex{

    public class KeyboardComponent : ExComponent{

        private bool sendInfos = false;

        // signals
        private static readonly string buttonSignal = "button";
        // infos
        private static readonly string infosSignal  = "buttons_state_info";

        // buttons
        public Dictionary<KeyCode,  Input.KeyboardButtonEvent> buttonsState    = new Dictionary<KeyCode, Input.KeyboardButtonEvent>();
        // raw buttons
        public Dictionary<RawKey, Input.KeyboardButtonEvent> rawButtonsState = new Dictionary<RawKey, Input.KeyboardButtonEvent>();
        
        protected override bool initialize() {

            add_signal(buttonSignal);

            foreach (var code in Input.Keyboard.Codes) {
                buttonsState[code] = new Input.KeyboardButtonEvent(code);
            }

            foreach (var button in Input.Keyboard.RawCodesCorrespondence) {                
                rawButtonsState[button.Key] = new Input.KeyboardButtonEvent(button.Value);
            }

            return true;
        }

        protected override void update() {
            // reset states infos
            sendInfos = true;
        }

        protected override void on_gui() {

            var eventType = Event.current.type;
            if (eventType != EventType.KeyDown && eventType != EventType.KeyUp && eventType != EventType.Repaint) {
                return;
            }

            var currentTime  = time().ellapsed_exp_ms();

            // retrieve keys states
            int pressedKeysCount = 0;
            if (!ExVR.GuiSettings().catchExternalKeyboardEvents) {

                foreach (KeyCode keyCode in Input.Keyboard.Codes) {

                    bool pressed = UnityEngine.Input.GetKey(keyCode);
                    var currentState = buttonsState[keyCode];

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

                    buttonsState[keyCode] = currentState;
                }

                // send infos only once per frame
                if (pressedKeysCount > 0 && sendInfos) {
                    StringBuilder infos = new StringBuilder();
                    int currentKey = 0;

                    foreach (KeyCode button in Input.Keyboard.Codes) {
                        var buttonState = buttonsState[button];
                        if (buttonState.state == Input.Button.State.Pressed || buttonState.state == Input.Button.State.Down) {
                            if (currentKey != pressedKeysCount - 1) {
                                infos.AppendFormat("{0},", ((int)button).ToString());
                            } else {
                                infos.Append(((int)button).ToString());
                            }
                            ++currentKey;
                        }
                    }

                    send_infos_to_gui_init_config(infosSignal, infos.ToString());
                    sendInfos = false;
                }

            } else { 
            
                foreach (var codePair in Input.Keyboard.RawCodesCorrespondence) {

                    bool pressed = RawKeyInput.IsKeyDown(codePair.Key);
                    var currentState = rawButtonsState[codePair.Key];

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

                    rawButtonsState[codePair.Key] = currentState;
                }

                // send infos only once per frame
                if (pressedKeysCount > 0 && sendInfos) {
                    StringBuilder infos = new StringBuilder();
                    int currentKey = 0;

                    foreach(var codePair in Input.Keyboard.RawCodesCorrespondence) {
                        var buttonState = rawButtonsState[codePair.Key];
                        if (buttonState.state == Input.Button.State.Pressed || buttonState.state == Input.Button.State.Down) {
                            if (currentKey != pressedKeysCount - 1) {
                                infos.AppendFormat("{0},", ((int)codePair.Value).ToString());
                            } else {
                                infos.Append(((int)codePair.Value).ToString());
                            }
                            ++currentKey;
                        }
                    }

                    send_infos_to_gui_init_config(infosSignal, infos.ToString());
                    sendInfos = false;
                }

            }
        }
    }
}