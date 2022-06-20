
/***********************************************************************************
** exvr-exp                                                                       **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// system
using System;
using System.Text;
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class JoypadComponent : ExComponent{

        // signals
        private static readonly string axisOnGuiSignal    = "axis";
        private static readonly string buttonOnGuiSignal  = "button";
        // infos
        private static readonly string axisInfoSignal     = "axes_state_info";
        private static readonly string buttonsInfoSignal  = "buttons_state_info";
        private static readonly string joypadInfoSignal   = "joysticks_info";
        private string m_buttonsInfos = "";
        private string m_axisInfos = "";
        private string m_joystickInfos = "";

        // dead zones
        private Dictionary<Input.JoypadAxis.Code, float> m_axisDeadZones = new Dictionary<Input.JoypadAxis.Code, float>();

        // events
        // # axis
        public Dictionary<Input.JoypadAxis.Code, Input.JoypadAxisEvent> axisEvent = new Dictionary<Input.JoypadAxis.Code, Input.JoypadAxisEvent>();
        // # buttons
        public Dictionary<Input.JoypadButton.Code, Input.JoypadButtonEvent> buttonsEvent = new Dictionary<Input.JoypadButton.Code, Input.JoypadButtonEvent>();
        

        protected override bool initialize() {

            add_signal(axisOnGuiSignal);
            add_signal(buttonOnGuiSignal);

            foreach(var code in Input.JoypadAxis.Codes) {
                axisEvent[code] = new Input.JoypadAxisEvent(code);
            }

            foreach(var code in Input.JoypadButton.Codes) {
                buttonsEvent[code] = new Input.JoypadButtonEvent(code);
            }

            foreach (var code in Input.JoypadAxis.Codes) {
                m_axisDeadZones[code] = Converter.to_float(initC.get<double>(string.Format("dead_zone_{0}", Converter.to_string((int)code))));
            }

            send_joystick_info();

            return true;
        }

        protected override void start_experiment() {
            send_joystick_info();
        }

        protected override void on_gui() {

            // call only once per frame      
            if (Event.current.type != EventType.Repaint) {
                return;
            }

            // get times
            var currentExpTime = time().ellapsed_exp_ms();
            var currentElemTime = time().ellapsed_element_ms();

            // update events
            // # joypad button
            foreach (var bEvent in buttonsEvent) {
                bEvent.Value.update(UnityEngine.Input.GetButton(Input.JoypadButton.CodesNames[bEvent.Key]), currentExpTime, currentElemTime);
            }
            // # joyad axis
            foreach (var aEvent in axisEvent) {
                float value = UnityEngine.Input.GetAxis(Input.JoypadAxis.CodesNames[aEvent.Key]);
                if (Math.Abs(value) < m_axisDeadZones[aEvent.Key]) {
                    value = 0f;
                }
                aEvent.Value.update(value, currentExpTime, currentElemTime);
            }

            if (is_updating()) {

                // joypad button
                var buttonsCodeInfoToSend = new List<Input.JoypadButton.Code>();
                foreach (var bEvent in buttonsEvent) {

                    // trigger signals
                    if (bEvent.Value.triggerSignals) {
                        invoke_signal(buttonOnGuiSignal, bEvent.Value);
                    }
                    // store key code of info to send
                    if (bEvent.Value.sendInfos) {
                        buttonsCodeInfoToSend.Add(bEvent.Key);
                    }
                }

                // joyad axis
                var axisCodeInfoToSend = new List<Input.JoypadAxis.Code>();
                foreach (var aEvent in axisEvent) {
                    // trigger signals
                    if (aEvent.Value.triggerSignals) {
                        invoke_signal(axisOnGuiSignal, aEvent.Value);
                    }
                    // store key code of info to send
                    if (aEvent.Value.sendInfos) {
                        axisCodeInfoToSend.Add(aEvent.Key);
                    }
                }

                // send infos
                // # joypad button
                if (buttonsCodeInfoToSend.Count > 0 ) {
                    StringBuilder infos = new StringBuilder();
                    int currentCode = 0;
                    foreach (var code in buttonsCodeInfoToSend) {
                        if (currentCode != buttonsCodeInfoToSend.Count - 1) {
                            infos.AppendFormat("{0},{1}%", ((int)code).ToString(), buttonsEvent[code].is_pressed() ? "1" : "0");
                        } else {
                            infos.AppendFormat("{0},{1}", ((int)code).ToString(), buttonsEvent[code].is_pressed() ? "1" : "0");
                        }
                        ++currentCode;
                    }
                    send_infos_to_gui_init_config(buttonsInfoSignal, m_buttonsInfos = infos.ToString());
                }
                // # joypad axis
                if (axisCodeInfoToSend.Count > 0) {
                    StringBuilder infos = new StringBuilder();
                    int currentCode = 0;
                    foreach (var code in axisCodeInfoToSend) {
                        var axeEvent = axisEvent[code];
                        if (currentCode != axisCodeInfoToSend.Count - 1) {
                            infos.AppendFormat("{0},{1}%", ((int)code).ToString(), Converter.to_string(axeEvent.value, "0.00"));
                        } else {
                            infos.AppendFormat("{0},{1}", ((int)code).ToString(), Converter.to_string(axeEvent.value, "0.00"));
                        }
                        ++currentCode;
                    }
                    send_infos_to_gui_init_config(axisInfoSignal, m_axisInfos = infos.ToString());
                }
            }      
        }

        void send_joystick_info() {

            StringBuilder joystickStr = new StringBuilder();
            int ii = 0;
            foreach (string joystick in UnityEngine.Input.GetJoystickNames()) {
                if (joystick.Length > 0) {
                    log_message(string.Format("Joystick n°{0} detected: {1}", ii, joystick));
                    joystickStr.AppendFormat("{0}%", joystick);
                    ++ii;
                }
            }
            if(ii == 0) {
                log_warning("No joystick detected.", false);
            }
            send_infos_to_gui_init_config(joypadInfoSignal, m_joystickInfos = joystickStr.ToString());

        }
    }
}