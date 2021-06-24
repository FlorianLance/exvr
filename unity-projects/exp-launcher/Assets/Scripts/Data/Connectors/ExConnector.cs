/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;
using System.Text;

// unity
using UnityEngine;

namespace Ex{

    public class ExConnector : MonoBehaviour{

        protected static readonly string valueStr = "value";

        protected static readonly List<string> slotsStr = new List<string>(new string[] {
            "input value 0",
            "input value 1",
            "input value 2",
            "input value 3",
            "input value 4",
            "input value 5",
            "input value 6",
            "input value 7",
        });

        protected static readonly List<string> signalsStr = new List<string>(new string[] {
            "output value 0",
            "output value 1",
            "output value 2",
            "output value 3",
            "output value 4",
            "output value 5",
            "output value 6",
            "output value 7",
        });

        public enum Function{
            initialize,
            update_from_gui,
            start_routine,
            stop_routine,
            pre_update,
            update,
            post_update,
            slot1,
            slot2,
            slot3,
            slot4,
            slot5,
            slot6,
            slot7,
            slot8,
            slot9,
            slot10,
            undefined
        }
        public enum Category{
            Generator,
            Operator,
            Function,
            Convertor,
            Action,
            Flow,
            Component,
            Undefined
        };

        public enum Pritority { Low, Medium, Hight };

        public int key = -1;
        public string keyStr;

        public List<GameObject> inputGO = new List<GameObject>();
        public List<GameObject> outputGO = new List<GameObject>();
        public List<Connection> inputConnections = new List<Connection>();
        public List<Connection> outputConnections = new List<Connection>();

        public Routine associatedRoutine = null;
        public Condition associatedCondition = null;

        protected Config m_config = null;

        public Category category = Category.Undefined;
        public Pritority priority = Pritority.Medium;
        public Function currentFunction = Function.undefined;
        private bool catchExceptions = false;

        // events
        private Events.Connections m_events = null;
        public Events.Connections events() { return m_events; }

        private static readonly string uiId = "v";

        protected void send_connector_infos_to_gui(object value) {
            ExVR.Network().gui_ipc().send_connector_infos_to_GUI(
                associatedRoutine.key_str(),
                associatedCondition.keyStr,
                keyStr,
                uiId, 
                Converter.to_string(value)
            );
        }

        protected void send_connector_infos_to_gui(string value) {
            ExVR.Network().gui_ipc().send_connector_infos_to_GUI(
                associatedRoutine.key_str(),
                associatedCondition.keyStr, 
                keyStr,
                uiId, 
                value
            );
        }



        public void add_slot(int id, System.Action<object> action) {

            if (id < 0 || id > 8) {
                log_error(string.Format("Invalid slod id {0}", id.ToString()));
                return;
            }

            m_events.add_slot(slotsStr[id], action);
        }

        protected void add_signals(int count) {

            if(count <= 0 || count > 8) {
                log_error(string.Format("Invalid number of slots {0}", count.ToString()));
                return;
            }

            for(int ii = 0; ii < count; ++ii) {
                m_events.add_signal(signalsStr[ii]);
            }            
        }

        protected void invoke_signal(int id, object arg = null) {
            m_events.invoke_signal(signalsStr[id], arg);
        }

        protected string verbose_name() {
            return String.Format(" [From connector: [{0}] ({1})([{2}])]",
                name,
                this.GetType().ToString(),
                currentFunction.ToString()
            );
        }

        public void log_message(string message, bool verbose = false) {
            if (verbose) {
                ExVR.Log().message(string.Concat(message, verbose_name()));
            } else {
                ExVR.Log().message(message);
            }
        }

        public void log_warning(string warning, bool verbose = true) {
            if (verbose) {
                ExVR.Log().warning(string.Concat(warning, verbose_name()));
            } else {
                ExVR.Log().warning(warning);
            }
        }

        public void log_error(string error, bool verbose = true) {
            if (verbose) {
                ExVR.Log().error(string.Concat(error, verbose_name()));
            } else {
                ExVR.Log().error(error);
            }
        }

        protected void display_exception(Exception e) {

            var stack = new System.Diagnostics.StackTrace(e, true);
            System.Diagnostics.StackFrame frame = stack.GetFrame(0);

            string className = "Unknow";
            string functionName = "Unknow";

            int lineNb = 0;
            int columnNb = 0;
            string fileName = null;
            if (frame != null) {

                var method = frame.GetMethod();
                if (method != null) {
                    className = method.ReflectedType.Name;
                    functionName = method.ToString();
                }

                lineNb = frame.GetFileLineNumber();
                columnNb = frame.GetFileColumnNumber();
                fileName = frame.GetFileName();
            }

            var builder = new StringBuilder();
            builder.Append("[CONNECTOR]\n");
            if (fileName != null) {
                builder.AppendFormat("  ->LOCATION: from class [{0}] in function " +
                    "[{1}] in file [{2}] at line ({3}) and column ({4})\n",
                    className, functionName, fileName, lineNb.ToString(), columnNb.ToString());
            } else {
                builder.AppendFormat("  ->LOCATION: from class [{0}] in function ({1})\n",
                    className, functionName);
            }
            builder.AppendFormat("  ->EXCEPTION_MESSAGE: {0}", e.Message);
            log_error(builder.ToString(), true);
        }

        static public ExConnector generate(XML.Connector xml){

            // generate type
            Type typeConnector = Type.GetType(String.Format("Ex.{0}Connector", xml.Name));
            if (typeConnector == null) {
                ExVR.Log().error(String.Format("Error when creating connector: {0}", xml.Name));
                return null;
            }

            // genrate gameobject
            var go = new GameObject(String.Format("{0} {1}", xml.Name, xml.Key.ToString()));
            GO.init_local_transform(go, Vector3.zero, Vector3.zero, Vector3.one);
            go.transform.SetParent(ExVR.GO().Connectors.transform);

            // generate component
            var connector = (ExConnector)go.AddComponent(typeConnector);
            if (connector == null) {
                ExVR.Log().error(String.Format("Cannot generate connector from type: {0}", typeConnector.ToString()));
                return null;
            }

            // set priority & category
            // ...

            // init from xml
            connector.initialize(xml);

            return connector;
        }

        protected virtual void initialize(XML.Connector connector) {

            m_events = new Events.Connections(gameObject.name);

            catchExceptions = ExVR.GuiSettings().catchComponentsExceptions;
            currentFunction = Function.initialize;

            key = connector.Key;
            keyStr = Converter.to_string(connector.Key);
            m_config = gameObject.AddComponent<Config>();
            m_config.init_from_xml(connector.Arg);
        }

        public void base_update_from_gui(XML.Arg arg) {
            m_config.init_from_xml(arg);
            currentFunction = Function.update_from_gui;

            if (catchExceptions) {
                try {
                    update_from_gui();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                update_from_gui();
            }
        }

        public void base_start_routine() {

            currentFunction = Function.start_routine;

            if (catchExceptions) {
                try {
                    start_routine();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                start_routine();
            }
        }


        public void base_pre_update() {

            currentFunction = Function.pre_update;

            if (catchExceptions) {
                try {
                    pre_update();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                pre_update();
            }
        }
        public void base_update() {

            currentFunction = Function.update;
   
            if (catchExceptions) {
                try {
                    update();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                update();
            }
        }
        public void base_post_update() {

            currentFunction = Function.post_update;

            if (catchExceptions) {
                try {
                    post_update();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                post_update();
            }
        }

        public void base_stop_routine() {

            currentFunction = Function.stop_routine;
            
            if (catchExceptions) {
                try {
                    stop_routine();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                stop_routine();
            }
        }

        protected void base_slot1(object arg) {

            currentFunction = Function.slot1;

            if (catchExceptions) {
                try {
                    slot1(arg);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                slot1(arg);
            }
        }

        protected void base_slot2(object arg) {

            currentFunction = Function.slot2;

            if (catchExceptions) {
                try {
                    slot2(arg);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                slot2(arg);
            }
        }

        protected void base_slot3(object arg) {

            currentFunction = Function.slot3;

            if (catchExceptions) {
                try {
                    slot3(arg);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                slot3(arg);
            }
        }

        protected void base_slot4(object arg) {

            currentFunction = Function.slot4;

            if (catchExceptions) {
                try {
                    slot4(arg);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                slot4(arg);
            }
        }

        protected void base_slot5(object arg) {

            currentFunction = Function.slot5;

            if (catchExceptions) {
                try {
                    slot5(arg);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                slot5(arg);
            }
        }

        protected void base_slot6(object arg) {

            currentFunction = Function.slot6;

            if (catchExceptions) {
                try {
                    slot6(arg);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                slot6(arg);
            }
        }

        protected void base_slot7(object arg) {

            currentFunction = Function.slot7;

            if (catchExceptions) {
                try {
                    slot7(arg);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                slot7(arg);
            }
        }

        protected void base_slot8(object arg) {

            currentFunction = Function.slot8;

            if (catchExceptions) {
                try {
                    slot8(arg);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                slot8(arg);
            }
        }

        protected virtual void slot1(object arg) {
        }
        protected virtual void slot2(object arg) {
        }
        protected virtual void slot3(object arg) {
        }
        protected virtual void slot4(object arg) {
        }        
        protected virtual void slot5(object arg) {
        }
        protected virtual void slot6(object arg) {
        }
        protected virtual void slot7(object arg) {
        }
        protected virtual void slot8(object arg) {
        }
        protected virtual void update_from_gui() {
        }

        protected virtual void start_routine() {
        }

        protected virtual void pre_update() {
        }
        protected virtual void update() {
        }
        protected virtual void post_update() {
        }

        protected virtual void stop_routine() {
        }
    }
}