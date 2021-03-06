/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


// unity
using UnityEngine;
using UnityEngine.Events;

namespace Ex{

    namespace Events {

        // base
        public class IntEvent : UnityEvent<int> { }
        public class StringEvent : UnityEvent<string> { }
        public class String4Event : UnityEvent<string, string, string, string> { }
        public class ExComponentMessageEvent : UnityEvent<ExComponent, string> { }

        public class Command {

            public UnityEvent NextElementEvent      = new UnityEvent();
            public UnityEvent PreviousElementEvent  = new UnityEvent();
            public UnityEvent StopExperimentEvent   = new UnityEvent();
            public UnityEvent PauseExperimentEvent  = new UnityEvent();

            public Events.StringEvent NextElementWithNameEvent          = new Events.StringEvent();
            public Events.StringEvent PreviousElementWithNameEvent      = new Events.StringEvent();
            public Events.StringEvent NextElementWithConditionEvent     = new Events.StringEvent();
            public Events.StringEvent PreviousElementWithConditionEvent = new Events.StringEvent();
            public Events.IntEvent GoToSpecificInstanceElementEvent     = new Events.IntEvent();
            public Events.String4Event ModifyRoutineActionConfigEvent   = new Events.String4Event();

            public void next() {
                NextElementEvent.Invoke();
            }

            public void previous() {
                PreviousElementEvent.Invoke();
            }

            public void pause_experiment() {
                PauseExperimentEvent.Invoke();
            }

            public void force_stop_experiment() {
                StopExperimentEvent.Invoke();
            }

            public void next_element_with_name(string elementName) {
                NextElementWithNameEvent.Invoke(elementName);
            }

            public void previous_element_with_name(string elementName) {
                PreviousElementWithNameEvent.Invoke(elementName);
            }

            public void next_element_with_condition(string elementName) {
                NextElementWithConditionEvent.Invoke(elementName);
            }

            public void previous_element_with_condition(string elementName) {
                PreviousElementWithConditionEvent.Invoke(elementName);
            }

            public void modify_routine_action_config(string routineName, string conditionName, string componentName, string newConfigName) {
                ModifyRoutineActionConfigEvent.Invoke(routineName, conditionName, componentName, newConfigName);
            }
        }

        public class Gui {
            public Events.StringEvent MessageFromGUI = new Events.StringEvent();
        }

        public class Log {

            public Events.StringEvent Error = new Events.StringEvent();            
            public Events.StringEvent Warning = new Events.StringEvent();            
            public Events.StringEvent Message = new Events.StringEvent();
            public Events.StringEvent LoggerError = new Events.StringEvent();
            public Events.StringEvent LoggerWarning = new Events.StringEvent();
            public Events.StringEvent LoggerMessage = new Events.StringEvent();
        }

        public class Stacktrace {
            public Events.ExComponentMessageEvent ComponentTrace = new Events.ExComponentMessageEvent();
        }
    }

    public class EventsManager : MonoBehaviour{

        public Events.Log log = null;
        public Events.Gui gui = null;
        public Events.Command command = null;
        public Events.Stacktrace stacktrace = null;

        public void initialize() {
  
            log = new Events.Log();
            gui = new Events.Gui();
            command = new Events.Command();
            stacktrace = new Events.Stacktrace();

            // implement counters...
            // ...
        }
    }
}
