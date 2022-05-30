
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
using System.Text;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Threading;

// unity
using UnityEngine;
using UnityRawInput;
using UnityEngine.Profiling;

namespace Ex{

    public class RawKeyboardGetterThread : ThreadedJob {

        volatile public bool doLoop  = false;
        volatile public bool process = false;

        private Dictionary<RawKey, bool> rawKeyboardGetReturn = new Dictionary<RawKey, bool>();
        private Dictionary<RawKey, Input.KeyboardButtonEvent> rawButtonsEvent = new Dictionary<RawKey, Input.KeyboardButtonEvent>();
        public ConcurrentQueue<List<Input.KeyboardButtonEvent>> newEvents = new ConcurrentQueue<List<Input.KeyboardButtonEvent>>();

        protected override void ThreadFunction() {

            Thread.CurrentThread.Name = "RawKeyboardGetterThread";
            Profiler.BeginThreadProfiling("RawKeyboardGetterThread", "RawKeyboardGetterThread 1");

            foreach (var button in Input.Keyboard.RawCodesCorrespondence) {
                rawKeyboardGetReturn[button.Key] = false;
                rawButtonsEvent[button.Key] = new Input.KeyboardButtonEvent(button.Value);
            }

            // 1 tick is 100 nanoseconds
            // 1000 ticks is 10000 nanoseconds -> 0.1 ms
            var ts = new System.TimeSpan(1000);
            while (doLoop) {
      
                foreach (var button in Input.Keyboard.RawCodesCorrespondence) {
                    rawKeyboardGetReturn[button.Key] = RawKeyInput.IsKeyDown(button.Key);
                }

                if (process) {

                    List<Input.KeyboardButtonEvent> events = null;

                    // update events
                    var currentExpTime     = ExVR.Time().ellapsed_exp_ms();
                    var currentElementTime = ExVR.Time().ellapsed_element_ms();
                    foreach (var codePair in Input.Keyboard.RawCodesCorrespondence) {

                        var currentEvent = rawButtonsEvent[codePair.Key];
                        currentEvent.update(rawKeyboardGetReturn[codePair.Key], currentExpTime, currentElementTime);

                        if (currentEvent.state != Input.Button.State.None) {
                            if (events == null) {
                                events = new List<Input.KeyboardButtonEvent>();
                            }
                            events.Add(currentEvent.copy());
                        }
                    }

                    if(events != null) { 
                        newEvents.Enqueue(events);
                    }
                }

                System.Threading.Thread.Sleep(ts);
            }

            Profiler.EndThreadProfiling();
        }
    }


    public class KeyboardComponent : ExComponent{

        private bool sendInfos = false;

        // signals
        private static readonly string buttonOnGuiSignal  = "button";
        // infos
        private static readonly string infosSignal  = "buttons_state_info";

        // events
        // # buttons
        private Dictionary<KeyCode, bool> keyboardGetReturn = new Dictionary<KeyCode, bool>();
        private Dictionary<KeyCode,  Input.KeyboardButtonEvent> buttonsEvent  = new Dictionary<KeyCode, Input.KeyboardButtonEvent>();

        RawKeyboardGetterThread rawKeyGetterJob = null;

        protected override bool initialize() {

            add_signal(buttonOnGuiSignal);


            if (!ExVR.GuiSettings().catchExternalKeyboardEvents) {

                foreach (var code in Input.Keyboard.Codes) {
                    buttonsEvent[code]      = new Input.KeyboardButtonEvent(code);
                    keyboardGetReturn[code] = false;
                }

            } else {
                rawKeyGetterJob = new RawKeyboardGetterThread();
                rawKeyGetterJob.doLoop = true;
                rawKeyGetterJob.start();
            }

            return true;
        }

        protected override void clean() {

            if (ExVR.GuiSettings().catchExternalKeyboardEvents) {
                rawKeyGetterJob.doLoop = false;
                rawKeyGetterJob.stop();
                rawKeyGetterJob = null;
            }
        }


        protected override void update() {
            // reset states infos
            sendInfos = true;
        }

        protected override void set_update_state(bool doUpdate) {

            if (!ExVR.GuiSettings().catchExternalKeyboardEvents && !doUpdate) {

                // reset states
                var currentExpTime     = time().ellapsed_exp_ms();
                var currentElementTime = time().ellapsed_element_ms();
                foreach (KeyCode keyCode in Input.Keyboard.Codes) {
                    buttonsEvent[keyCode].update(false, currentExpTime, currentElementTime);
                }

            } else if(ExVR.GuiSettings().catchExternalKeyboardEvents) {
                rawKeyGetterJob.process = doUpdate;
            }
        }

        protected override void on_gui() {

            var eventType = Event.current.type;           
            if (eventType != EventType.KeyDown && eventType != EventType.KeyUp && eventType != EventType.Repaint) {
                return;
            }


            if (!ExVR.GuiSettings().catchExternalKeyboardEvents) {

                // retrieve current return value
                var currentExpTime     = time().ellapsed_exp_ms();
                var currentElementTime = time().ellapsed_element_ms();
                foreach (KeyCode keyCode in Input.Keyboard.Codes) {
                    keyboardGetReturn[keyCode] = UnityEngine.Input.GetKey(keyCode);
                }

                // update events
                foreach (KeyCode keyCode in Input.Keyboard.Codes) {                    
                    buttonsEvent[keyCode].update(keyboardGetReturn[keyCode], currentExpTime, currentElementTime);   
                }

                // send triggers
                foreach (KeyCode keyCode in Input.Keyboard.Codes) {
                    var currentEvent = buttonsEvent[keyCode];
                    if (currentEvent.state != Input.Button.State.None) {
                        invoke_signal(buttonOnGuiSignal, currentEvent);
                    }
                }


                // send infos only once per frame
                if (sendInfos) {

                    StringBuilder infos = new StringBuilder();
                    foreach (KeyCode button in Input.Keyboard.Codes) {
                        var buttonState = buttonsEvent[button];
                        if (buttonState.state == Input.Button.State.Pressed || buttonState.state == Input.Button.State.Down) {
                            infos.AppendFormat("{0} ", ((int)button).ToString());
                        }
                    }
                    
                    if (infos.Length > 0) {
                        send_infos_to_gui_init_config(infosSignal, infos.ToString());
                    }
                    sendInfos = false;
                }

            } else {

                // retrieve triggers
                var allEvents = new List<List<Input.KeyboardButtonEvent>>();
                var keysEvents = new List<Input.KeyboardButtonEvent>();
                while (rawKeyGetterJob.newEvents.TryDequeue(out keysEvents)) {
                    allEvents.Add(keysEvents);
                }

                // send triggers
                foreach(var events in allEvents) {
                    foreach(var keyEvent in events) {
                        invoke_signal(buttonOnGuiSignal, keyEvent);
                    }
                }

                // send infos only once per frame
                if (sendInfos) {

                    HashSet<KeyCode> toSend = null;  
                    foreach (var events in allEvents) {
                        foreach (var keyEvent in events) {
                            var buttonState = keyEvent;
                            if (buttonState.state == Input.Button.State.Pressed || buttonState.state == Input.Button.State.Down) {
                                if(toSend == null) {
                                    toSend = new HashSet<KeyCode>();
                                }
                                toSend.Add(buttonState.code);                                
                            }
                        }
                    }

                    if (toSend != null) {
                        StringBuilder infos = new StringBuilder();
                        foreach (var code in toSend) {
                            infos.AppendFormat("{0} ", ((int)code).ToString());
                        }        
                        send_infos_to_gui_init_config(infosSignal, infos.ToString());       
                    }
                    sendInfos = false;
                }
            }
        }        
    }
}