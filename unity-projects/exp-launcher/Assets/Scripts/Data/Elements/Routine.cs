/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;
using System.Diagnostics;

// unity
using UnityEngine;
#if UNITY_EDITOR
using UnityEditor;
namespace Ex{

    [CustomEditor(typeof(Routine))]
    public class RoutineEditor : Editor{

        public override bool RequiresConstantRepaint() {
            return true;
        }

        public override void OnInspectorGUI() {

            base.OnInspectorGUI();
            if (!Application.isPlaying) {
                return;
            }

            Routine routine = (Routine)target;
            EditorGUILayout.LabelField("ID: ", routine.key().ToString());            
            EditorGUILayout.LabelField("Start time: " + routine.start_timer_duration_ms() + " ms");
            EditorGUILayout.LabelField("Stop time: " + routine.stop_timer_duration_ms() + " ms");
            EditorGUILayout.LabelField("Current condition: ");
            EditorGUILayout.ObjectField(routine.current_condition(), typeof(Condition), true);

            EditorGUILayout.LabelField("All conditions: ");
            foreach (var condition in routine.get_conditions()) {
                EditorGUILayout.ObjectField(condition, typeof(Condition), true);
            }            
        }
    }
}
#endif

namespace Ex{

    public class Routine : FlowElement{

        private List<Condition> m_conditions = null;
        private Condition m_currentCondition = null;
        private Stopwatch m_startTimer = new Stopwatch();
        private Stopwatch m_stopTimer = new Stopwatch();
        public int nbTimesCalled = 0;

        public List<Condition> get_conditions() {
            return m_conditions;
        }

        public void clean() {
            foreach(var condition in m_conditions){                
                foreach (var exCo in condition.connectors) {
                    Destroy(exCo.gameObject);
                }
            }
        }

        public Condition current_condition() {
            return m_currentCondition;
        }

        public double start_timer_duration_ms() {
            return m_startTimer.Elapsed.TotalMilliseconds;
        }

        public double stop_timer_duration_ms() {
            return m_stopTimer.Elapsed.TotalMilliseconds;
        }

        public void initialize(XML.Routine routine) {

            m_key    = routine.Key;
            m_keyStr = Converter.to_string(routine.Key);
            m_type  = FlowElementType.Routine;            

            // generate conditions
            m_conditions = new List<Condition>(routine.Conditions.Count);
            foreach (XML.Condition xmlCondition in routine.Conditions) {
                
                var conditionGO = GO.generate_empty_object(xmlCondition.Name, transform, true);
                var condition = conditionGO.AddComponent<Condition>();
                condition.initialize(xmlCondition);
                m_conditions.Add(condition);
            }
        }

        public Condition condition_from_name(string conditionName) {

            foreach (Condition condition in m_conditions) {
                if (condition.name == conditionName) {
                    return condition;
                }
            }
            return null;
        }

        public void enable(Condition condition) {

            // retrieve current condition
            m_currentCondition = condition;
            gameObject.SetActive(true);                    
            start();            
        }

        public void stop_experiment() {
            nbTimesCalled = 0;
        }

        public void disable() {

            if (!gameObject.activeSelf) { // already disabled, do nothing
                return;
            }

            stop();
            gameObject.SetActive(false);
        }

        private void start() {
            
            ExVR.ExpLog().routine(name, current_condition().name, "Start associated components");
            m_startTimer.Restart();            
            {
                // set connections between components and connectors
                m_currentCondition.set_connections();
                ExVR.Components().set_current_config(m_currentCondition);
                ExVR.Components().pre_start_routine(m_currentCondition);
                ExVR.Components().start_routine(m_currentCondition);
                ExVR.Components().post_start_routine(m_currentCondition);
                m_currentCondition.connectors_start_routine();
                nbTimesCalled++;
            }
            m_startTimer.Stop();
            ExVR.ExpLog().routine(name, current_condition().name, "Associated components started in " + m_startTimer.ElapsedMilliseconds + "ms");            
        }

        private void stop() {

            ExVR.ExpLog().routine(name, current_condition().name, "Stop");
            m_stopTimer.Restart();
            {
                m_currentCondition.connectors_stop_routine();
                ExVR.Components().stop_routine(m_currentCondition);
                m_currentCondition.remove_connections();                
            }

            m_stopTimer.Stop();
            ExVR.ExpLog().routine(name, current_condition().name, "Stopped in " + m_startTimer.ElapsedMilliseconds + "ms");
        }

        public int conditions_count() {
            return m_conditions.Count;
        }

        public Condition get_condition_from_id(int id) {
            if(id < conditions_count() && id >= 0) {
                return m_conditions[id];
            }
            ExVR.Log().error(string.Format("Condition with id [{0}] invalid.", Converter.to_string(id)));
            return null;
        }

        public Condition get_condition_from_key(int conditionKey) {
            foreach (var condition in m_conditions) {
                if (condition.key == conditionKey) {
                    return condition;
                }
            }
            ExVR.Log().error(string.Format("Condition with key [{0}] not found.", Converter.to_string(conditionKey)));
            return null;
        }

        public Condition get_condition_from_name(string conditionName) {

            foreach (var condition in m_conditions) {
                if (condition.name == conditionName) {
                    return condition;
                }
            }
            ExVR.Log().error(string.Format("Condition with name [{0}] not found.", conditionName));
            return null;
        }
    }
}