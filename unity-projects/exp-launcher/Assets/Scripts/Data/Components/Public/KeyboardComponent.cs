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
        private static readonly string buttonOnGuiSignal  = "button";
        // infos
        private static readonly string infosSignal  = "buttons_state_info";

        // buttons
        private Dictionary<KeyCode,  Input.KeyboardButtonEvent> buttonsEvent  = new Dictionary<KeyCode, Input.KeyboardButtonEvent>();
        // raw buttons
        private Dictionary<RawKey, Input.KeyboardButtonEvent> rawButtonsEvent = new Dictionary<RawKey, Input.KeyboardButtonEvent>();

        // current 
        public Dictionary<KeyCode, Input.KeyboardButtonState> buttonsStates = new Dictionary<KeyCode, Input.KeyboardButtonState>();


        protected override bool initialize() {

            add_signal(buttonOnGuiSignal);

            foreach (var code in Input.Keyboard.Codes) {
                buttonsEvent[code]  = new Input.KeyboardButtonEvent(code);
                buttonsStates[code] = new Input.KeyboardButtonState(code);
            }

            foreach (var button in Input.Keyboard.RawCodesCorrespondence) {                
                rawButtonsEvent[button.Key] = new Input.KeyboardButtonEvent(button.Value);
            }

            return true;
        }

        protected override void pre_update() {

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

                    // update event
                    var currentEvent = buttonsEvent[keyCode];
                    currentEvent.update(pressed, currentTime);

                    // update state
                    var currentState = buttonsStates[keyCode];
                    currentState.update(pressed, currentTime);


                    if (pressed) {
                        ++pressedKeysCount;
                    }

                    if (currentEvent.state != Input.Button.State.None) {
                        invoke_signal(buttonOnGuiSignal, currentEvent);
                    }

                    buttonsEvent[keyCode] = currentEvent;
                }

                // send infos only once per frame
                if (pressedKeysCount > 0 && sendInfos) {
                    StringBuilder infos = new StringBuilder();
                    int currentKey = 0;

                    foreach (KeyCode button in Input.Keyboard.Codes) {
                        var buttonState = buttonsEvent[button];
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

                    // update state
                    var currentEvent = rawButtonsEvent[codePair.Key];
                    currentEvent.update(pressed, currentTime);

                    // update state
                    var currentState = buttonsStates[codePair.Value];
                    currentState.update(pressed, currentTime);

                    if (pressed) {
                        ++pressedKeysCount;
                    }

                    if (currentEvent.state != Input.Button.State.None) {
                        invoke_signal(buttonOnGuiSignal, currentEvent);
                    }

                    rawButtonsEvent[codePair.Key] = currentEvent;
                }

                // send infos only once per frame
                if (pressedKeysCount > 0 && sendInfos) {
                    StringBuilder infos = new StringBuilder();
                    int currentKey = 0;

                    foreach(var codePair in Input.Keyboard.RawCodesCorrespondence) {
                        var buttonState = rawButtonsEvent[codePair.Key];
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