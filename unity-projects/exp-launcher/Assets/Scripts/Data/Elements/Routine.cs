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

        public void stop_experiment() {

            m_callsNb = 0;
            foreach(var condition in m_conditions) {
                condition.stop_experiment();
            }
        }

        public void start(Condition condition) {

            // update routine current condition
            m_currentCondition = condition;
            // enable it
            gameObject.SetActive(true);

            ExVR.ExpLog().routine(name, current_condition().name, "Start");
            m_startTimer.Restart();
            m_currentCondition.start_routine();
            m_startTimer.Stop();
            ExVR.ExpLog().routine(name, current_condition().name, string.Format("Started in {0} ms", m_startTimer.ElapsedMilliseconds));            
        }

        public void on_gui() {
            m_currentCondition.on_gui();
        }

        public void update() {            
            m_currentCondition.update();
        }

        public void play() {
            m_currentCondition.play();
        }
        public void pause() {
            m_currentCondition.pause();
        }

        public void stop() {  

            ExVR.ExpLog().routine(name, current_condition().name, "Stop");
            m_stopTimer.Restart();
            m_currentCondition.stop_routine();
            m_stopTimer.Stop();
            ExVR.ExpLog().routine(name, current_condition().name, string.Format("Stopped in {0} ms", m_stopTimer.ElapsedMilliseconds));

            // increment nb of calls
            m_callsNb++;

            // disable gameobject
            gameObject.SetActive(false);
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
                if (condition.key() == conditionKey) {
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