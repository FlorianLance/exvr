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

    public class JoypadComponent : ExComponent{

        private bool sendInfos = false;
        private float deadZone = 0.05f;

        // signals
        private static readonly string axisSignal = "axis";
        private static readonly string buttonSignal = "button";
        // infos
        private static readonly string axisInfoSignal     = "axes_state_info";
        private static readonly string buttonsInfoSignal  = "buttons_state_info";
        private static readonly string joypadInfoSignal   = "joysticks_info";

        // axis
        private Dictionary<Input.JoypadAxis.Code, Input.JoypadAxisEvent> axisStates = new Dictionary<Input.JoypadAxis.Code, Input.JoypadAxisEvent>();
        // buttons
        private Dictionary<Input.JoypadButton.Code, Input.JoypadButtonEvent> buttonsState = new Dictionary<Input.JoypadButton.Code, Input.JoypadButtonEvent>();

        protected override bool initialize() {

            add_signal(axisSignal);
            add_signal(buttonSignal);

            foreach(var code in Input.JoypadAxis.Codes) {
                axisStates[code] = new Input.JoypadAxisEvent(code);
            }

            foreach(var code in Input.JoypadButton.Codes) {
                buttonsState[code] = new Input.JoypadButtonEvent(code);
            }

            send_joystick_info();

            return true;
        }

        protected override void start_experiment() {
            send_joystick_info();
        }

        protected override void update() {
            // reset states infos
            sendInfos = true;
        }

        protected override void on_gui() {

            var eventType = Event.current.type;
            if (eventType != EventType.Repaint) {
                return;
            }
            var currentTime = time().ellapsed_exp_ms();

            int pressedKeysCount = 0;
            foreach (var code in Input.JoypadButton.Codes) {

                bool pressed = UnityEngine.Input.GetButton(Input.JoypadButton.CodesNames[code]);
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

            int movedAxisCount = 0;
            foreach (var code in Input.JoypadAxis.Codes) {

                float value = UnityEngine.Input.GetAxis(Input.JoypadAxis.CodesNames[code]);
                var currentState = axisStates[code];
                if (Math.Abs(value) < deadZone) {
                    value = 0f;
                } else {
                    ++movedAxisCount;
                    currentState.triggeredExperimentTime = currentTime;
                    invoke_signal(axisSignal, currentState);
                }

                axisStates[code].value = value;
            }



            // send infos only once per frame
            if (pressedKeysCount > 0 && sendInfos) {

                StringBuilder infos = new StringBuilder();
                int currentCode = 0;
                foreach (var code in Input.JoypadButton.Codes) {
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
                send_infos_to_gui_init_config(buttonsInfoSignal, infos.ToString());
            }


            if(movedAxisCount > 0 && sendInfos) {

                StringBuilder infos = new StringBuilder();
                int currentCode = 0;
                foreach (var code in Input.JoypadAxis.Codes) {
                    var axeState = axisStates[code];
                    if (Math.Abs(axeState.value) >= deadZone) {
                        if (currentCode != movedAxisCount - 1) {
                            infos.AppendFormat("{0},{1}%", ((int)code).ToString(), Converter.to_string(axeState.value, "0.00"));
                        } else {
                            infos.AppendFormat("{0},{1}", ((int)code).ToString(), Converter.to_string(axeState.value, "0.00"));
                        }
                        ++currentCode;
                    }
                }
                send_infos_to_gui_init_config(axisInfoSignal, infos.ToString());
            }

            sendInfos = false;
        }

        void send_joystick_info() {

            StringBuilder joystickStr = new StringBuilder();
            int ii = 0;
            foreach (string joystick in UnityEngine.Input.GetJoystickNames()) {
                log_message(string.Format("Joystick n°{0} detected: {1}", ii, joystick));
                joystickStr.AppendFormat("{0}%", joystick);
                ++ii;
            }
            send_infos_to_gui_init_config(joypadInfoSignal, joystickStr.ToString());
        }
    }
}