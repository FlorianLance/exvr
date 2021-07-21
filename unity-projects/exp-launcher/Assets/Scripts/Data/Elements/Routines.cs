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


#if UNITY_EDITOR
using UnityEditor;
namespace Ex{

    [CustomEditor(typeof(Routines))]
    public class RoutinesManagerEditor : Editor{

        public override bool RequiresConstantRepaint() {
            return true;
        }

        public override void OnInspectorGUI() {

            base.OnInspectorGUI();

            if (!Application.isPlaying) {
                return;
            }

            var currentR = ExVR.Routines().current();
            EditorGUILayout.LabelField("Current routine: ");
            EditorGUILayout.ObjectField(currentR, typeof(Routine), true);

            EditorGUILayout.LabelField("All routines: ");
            foreach (var routine in ExVR.Routines().get_all()) {
                EditorGUILayout.ObjectField(routine, typeof(Routine), true);
            }
        }
    }
}
#endif

namespace Ex{

    public class Routines : MonoBehaviour{

        private List<Routine> m_routines = new List<Routine>();
        private Dictionary<string, Routine> m_routinesPerName = new Dictionary<string, Routine>();
        private Dictionary<int, Routine> m_routinesPerKey = new Dictionary<int, Routine>();

        private Routine m_currentRoutine = null;

        public Routine current() {            
            return m_currentRoutine;
        }

        public void generate_from_xml(XML.Routines xmlRoutines) {

            m_routines.Clear();
            m_routinesPerName.Clear();
            m_routinesPerKey.Clear();
            foreach (XML.Routine xmlRoutine in xmlRoutines.Routine) {
                var routine = GO.generate_empty_object(xmlRoutine.Name, ExVR.GO().Routines.transform).AddComponent<Routine>();
                routine.initialize(xmlRoutine);
                m_routines.Add(routine);
                m_routinesPerName[routine.name] = routine;
                m_routinesPerKey[routine.key()] = routine;
            }
        }

        public void trigger_update_signals(RoutineInfo info) {

            Routine routine = get(info.key());
            if (routine) {
                foreach (Condition condition in routine.get_conditions()) {

                    // retrieve current condition
                    if (condition.name == info.condition.name) {
                        condition.trigger_update_connector_signals();
                        return;
                    }
                }
            }
        }

        public int count() {
            return m_routines.Count;
        }

        public List<Routine> get_all() {
            return new List<Routine>(m_routines);
        }

        public Routine get(string routineName) {
            if (m_routinesPerName.ContainsKey(routineName)) {
                return m_routinesPerName[routineName];
            }
            ExVR.Log().error(string.Format("Cannot find routine with name {0}.", routineName));
            return null;
        }

        public Routine get(int routineKey) {
            if (m_routinesPerKey.ContainsKey(routineKey)) {
                return m_routinesPerKey[routineKey];
            }
            ExVR.Log().error(string.Format("Cannot find routine with key {0}.", Converter.to_string(routineKey)));
            return null;
        }

        public void enable(RoutineInfo info) {
            m_currentRoutine = (Routine)info.element;
            ExVR.ExpLog().routine_manager(info);
            ExVR.ExpLog().push_to_strackTrace(new RoutinesManagerTrace(m_currentRoutine, "enable", true));
            m_currentRoutine.enable(info.condition);
            ExVR.ExpLog().push_to_strackTrace(new RoutinesManagerTrace(m_currentRoutine, "enable", false));
        }

        public void display_last_info() {

            // display last routine info
            StringBuilder builder = new StringBuilder();
            builder.Append(" [DISABLE] -> ");
            if (m_currentRoutine != null) {
                builder.AppendFormat(" last routine [{0}]", m_currentRoutine.name);
                var currentCond = m_currentRoutine.current_condition();
                if (currentCond != null) {
                    builder.AppendFormat(" with condition [{0}]", currentCond.name);
                    if (currentCond.currentConnector != null) {
                        builder.AppendFormat(" with last connector [{0}] and function [{1}]", currentCond.currentConnector.name, currentCond.currentConnector.currentFunction.ToString());
                    } else {
                        builder.Append(" and no last connector");
                    }
                } else {
                    builder.Append(" with no condition");
                }
            } else {
                builder.Append(" no last routine");
            }
            ExVR.ExpLog().routine_manager(builder.ToString());
        }

        public void disable() {

            // disable routines            
            foreach (var routine in m_routines) {
                routine.disable();
            }
            m_currentRoutine = null;
        }

        public void clean() {
            foreach (var routine in m_routines) {
                routine.clean();
                Destroy(routine.gameObject);
            }
            m_routines.Clear();
            m_routinesPerName.Clear();
            m_routinesPerKey.Clear();
        }

        public void update_components_states(RoutineInfo info) {
            //ExVR.ExpLog().push_to_strackTrace(new RoutinesManagerTrace(routine, "update_components_states", true));
            ExVR.Components().update_states_from_time(info.condition, ExVR.Time().ellapsed_time_element_s());
            //ExVR.ExpLog().push_to_strackTrace(new RoutinesManagerTrace(routine, "update_components_states", false));
        }

        public bool modify_action_config(string routineName, string conditionName, string componentName, string newConfigName) {

            var component = ExVR.Components().get(componentName);
            if (component == null) {
                return false;
            }

            ComponentConfig newConfig = component.get_config(newConfigName);
            if (newConfig == null) {
                return false;
            }

            var routine = get(routineName);
            if(routine == null) {
                return false;
            }

            var condition = routine.get_condition_from_name(conditionName);
            if(condition == null) {
                return false;
            }

            var action = condition.get_action_from_component_name(componentName);
            if(action == null) {
                return false;
            }

            ExVR.ExpLog().push_to_strackTrace(new RoutinesManagerTrace(routine, "modify_action_config", true));
            action.set_config(newConfig);
            ExVR.ExpLog().push_to_strackTrace(new RoutinesManagerTrace(routine, "modify_action_config", false));

            return true;
        }
    }
}