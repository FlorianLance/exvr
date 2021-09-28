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
        private static readonly string buttonOnGuiSignal = "button";
        // infos
        private static readonly string axisInfoSignal     = "axes_state_info";
        private static readonly string buttonsInfoSignal  = "buttons_state_info";
        private static readonly string joypadInfoSignal   = "joysticks_info";

        // events
        // # axis
        private Dictionary<Input.JoypadAxis.Code, Input.JoypadAxisEvent> axisEvent = new Dictionary<Input.JoypadAxis.Code, Input.JoypadAxisEvent>();
        // # buttons
        private Dictionary<Input.JoypadButton.Code, Input.JoypadButtonEvent> buttonsEvent = new Dictionary<Input.JoypadButton.Code, Input.JoypadButtonEvent>();

        // states
        public Dictionary<Input.JoypadAxis.Code, Input.JoypadAxisState> axisState = new Dictionary<Input.JoypadAxis.Code, Input.JoypadAxisState>();
        public Dictionary<Input.JoypadButton.Code, Input.JoypadButtonState> buttonsState = new Dictionary<Input.JoypadButton.Code, Input.JoypadButtonState>();
        

        protected override bool initialize() {

            add_signal(axisSignal);
            add_signal(buttonOnGuiSignal);

            foreach(var code in Input.JoypadAxis.Codes) {
                axisEvent[code] = new Input.JoypadAxisEvent(code);
                axisState[code] = new Input.JoypadAxisState(code);
            }

            foreach(var code in Input.JoypadButton.Codes) {
                buttonsEvent[code] = new Input.JoypadButtonEvent(code);
                buttonsState[code] = new Input.JoypadButtonState(code);
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
            foreach (Input.JoypadButton.Code buttonCode in Input.JoypadButton.Codes) {

                bool pressed = UnityEngine.Input.GetButton(Input.JoypadButton.CodesNames[buttonCode]);

                // update event
                var currentEvent = buttonsEvent[buttonCode];
                currentEvent.update(pressed, currentTime);

                // update state
                var currentState = buttonsState[buttonCode];
                currentState.update(pressed, currentTime);

                if (pressed) {
                    ++pressedKeysCount;
                }

                if (currentEvent.state != Input.Button.State.None) {
                    invoke_signal(buttonOnGuiSignal, currentEvent);
                }

                buttonsEvent[buttonCode] = currentEvent;
            }

            int movedAxisCount = 0;
            foreach (Input.JoypadAxis.Code axisCode in Input.JoypadAxis.Codes) {

                float value = UnityEngine.Input.GetAxis(Input.JoypadAxis.CodesNames[axisCode]);
                if (Math.Abs(value) < deadZone) {
                    value = 0f;
                }

                // update event
                var currentEvent = axisEvent[axisCode];
                currentEvent.update(value, currentTime);

                // update state
                var currentState = axisState[axisCode];
                currentState.update(value, currentTime);


                if(value != 0f) { 
                    ++movedAxisCount;
                    invoke_signal(axisSignal, currentState);
                }

                axisEvent[axisCode] = currentEvent;
            }

            // send infos only once per frame
            if (pressedKeysCount > 0 && sendInfos) {

                StringBuilder infos = new StringBuilder();
                int currentCode = 0;
                foreach (var code in Input.JoypadButton.Codes) {
                    var buttonState = buttonsEvent[code];
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
                    var axeState = axisEvent[code];
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
            if(ii == 0) {
                log_error("No joystick detected.");
            }
            send_infos_to_gui_init_config(joypadInfoSignal, joystickStr.ToString());

        }
    }
}