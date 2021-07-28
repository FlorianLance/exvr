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
namespace Ex
{

    [CustomEditor(typeof(Scheduler))]
    public class SchredulerEditor : Editor{

        public override bool RequiresConstantRepaint() {
            return true;
        }

        public override void OnInspectorGUI() {

            base.OnInspectorGUI();

            if (!Application.isPlaying) {
                return;
            }

            EditorGUILayout.LabelField("Current element:");
            var currentElementInfo = ExVR.Schreduler().current_element_info();
            if (currentElementInfo != null) {
                if (currentElementInfo.type() == FlowElement.FlowElementType.Routine) {

                    var routineInfo = (RoutineInfo)currentElementInfo;
                    var routine = (Routine)routineInfo.element;
                    if (routine != null) {
                        EditorGUILayout.LabelField(string.Format("[Routine] with id {0}, called {1} times", currentElementInfo.key().ToString(), routine.calls_nb()));
                        EditorGUILayout.ObjectField(routine, typeof(Routine), true);

                        var condition = routine.current_condition();
                        if (condition != null) {
                            EditorGUILayout.LabelField("With condition:");
                            EditorGUILayout.ObjectField(condition, typeof(Condition), true);
                        } else {
                            EditorGUILayout.LabelField("...");
                        }

                    } else {
                        EditorGUILayout.LabelField("...");
                    }
                } else {

                    var isiInfo = (ISIInfo)currentElementInfo;
                    var isi = (ISI)isiInfo.element;
                    if (isi != null) {
                        EditorGUILayout.LabelField(string.Format("[ISI] with id {0}", currentElementInfo.key().ToString()));
                        EditorGUILayout.ObjectField(isi, typeof(ISI), true);
                    } else {
                        EditorGUILayout.LabelField("...");
                    }
                    //currentCondition = isi.current_condition();
                }
            } else {
                EditorGUILayout.LabelField("...");
            }

            //EditorGUILayout.BeginHorizontal();
            //EditorGUILayout.EndHorizontal();


            //foreach (var info in ExVR.Schreduler().get_elements_info_order()) {
            //    EditorGUILayout.LabelField("[" + (id++).ToString() + "] " + (info.type == Elements.FlowElementType.Routine ? "Routine" : "ISI") + " -> " + info.name, EditorStyles.label);
            //    EditorGUILayout.LabelField("   with condition " + info.conditionName + "(" + info.conditionKey + ") and interval [" + info.interval.tStart + " - " + info.interval.tEnd + "]", EditorStyles.label);
            //}

            //if(currentElementInfo != null) {
            //    EditorGUILayout.LabelField("Current: " + currentElementInfo.name, EditorStyles.boldLabel);
            //} else {
            //    EditorGUILayout.LabelField("Current: ...");
            //}
        }
    }
}
#endif



namespace Ex {


    public class FlowElementInfo{

        public FlowElement element = null;
        public Interval interval;
        public int order;

        public int key() {
            return element.key();
        }
        public FlowElement.FlowElementType type() {
            return element.type();
        }

        public string name() {
            return element.name;
        }
    }

    public class RoutineInfo : FlowElementInfo {

        public RoutineInfo(Routine routine, Condition condition, Interval interval) {
            element = routine;
            this.condition = condition;
            this.interval = interval;
        }

        public Condition condition = null;
    }
    public class ISIInfo : FlowElementInfo {

        public ISIInfo(ISI isi, string durationStr, Interval interval) {
            element = isi;
            this.interval = interval;
            this.durationStr = durationStr;
        }

        public string durationStr;
    }

    public class Scheduler : MonoBehaviour{

        // flow elements
        [SerializeField]
        private int m_currentElementId = 0;

        [SerializeField]
        private FlowElementInfo m_currentElementInfo = null;

        [SerializeField]
        private List<FlowElementInfo> m_elementsOrder = new List<FlowElementInfo>();
        [SerializeField]
        private List<FlowElementInfo> m_randomizerElementsOrder = new List<FlowElementInfo>();

        public int current_element_order() {
            return m_currentElementId;
        }

        public int total_number_of_elements() {
            return m_elementsOrder.Count;
        }

        public FlowElementInfo current_element_info() {
            return m_currentElementInfo;
        }

        public List<FlowElementInfo> get_elements_info_order(bool isARandomizer) {
            if (isARandomizer) {
                return new List<FlowElementInfo>(m_randomizerElementsOrder);
            } else {
                return new List<FlowElementInfo>(m_elementsOrder);
            }
        }

        public List<RoutineInfo> get_routine_infos_order(int elementKey, bool isARandomizer) {

            List<RoutineInfo> infos = new List<RoutineInfo>();
            var elements = isARandomizer ? m_randomizerElementsOrder : m_elementsOrder;
            foreach (var info in elements) {
                if(info.key() == elementKey) {
                    infos.Add((RoutineInfo)info);
                }
            }
            return infos;
        }

        public List<Condition> get_routine_conditions_order(int elementKey, bool isARandomizer) {

            List<Condition> conditions = new List<Condition>();
            var elements = isARandomizer ? m_randomizerElementsOrder : m_elementsOrder;
            foreach (var info in elements) {
                if (info.key() == elementKey) {
                    conditions.Add(((RoutineInfo)info).condition);
                }
            }
            return conditions;
        }

        public List<string> get_routine_conditions_names_order(int elementKey, bool isARandomizer) {

            List<string> conditionsName = new List<string>();
            var elements = isARandomizer ? m_randomizerElementsOrder : m_elementsOrder;
            foreach (var info in elements) {
                if (info.key() == elementKey) {
                    conditionsName.Add(((RoutineInfo)info).condition.name);
                }
            }
            return conditionsName;
        }

        public bool generate(XML.ExperimentFlow experimentFlow) {

            // clean
            m_elementsOrder.Clear();
            m_randomizerElementsOrder.Clear();

            var routinesManager = ExVR.Routines();
            var isisManager = ExVR.ISIs();

            // create flow experiment from instance xml
            foreach (XML.Element element in experimentFlow.Elements) {

                FlowElementInfo elementInfo ; 
                
                if (element.Type == "routine") { // Routine

                    // retrieve routine
                    var routine = routinesManager.get(element.Key);                    
                    if (!routine) {
                        ExVR.Log().error(string.Format("Routine with id {0} from instance not found in experiment.", element.Key));
                        return false;
                    }

                    // retrieve the end routine time
                    Condition currentCondition = routine.condition_from_name(element.Cond);
                    if (!currentCondition) {
                        ExVR.Log().error(string.Format("Condition {0} from instance not found in experiment.", element.Cond));
                        return false;
                    }

                    // create element info                                        
                    if (routine.is_a_randomizer()) {
                        elementInfo = new RoutineInfo(routine, currentCondition, new Interval(0, 0));
                        elementInfo.order = m_randomizerElementsOrder.Count;
                        m_randomizerElementsOrder.Add(elementInfo);
                    } else {
                        elementInfo = new RoutineInfo(routine, currentCondition, new Interval(0, currentCondition.duration()));
                        elementInfo.order = m_elementsOrder.Count;
                        m_elementsOrder.Add(elementInfo);
                    }

                } else { // ISI

                    // retrieve ISI
                    var isi = isisManager.get(element.Key);
                    if (!isi) {
                        ExVR.Log().error(string.Format("IIS with id {0} from instance not found in experiment.", element.Key));
                        return false;
                    }

                    // create element info
                    elementInfo = new ISIInfo(isi, element.Cond, new Interval(0, Converter.to_double(element.Cond)));
                    elementInfo.order = m_elementsOrder.Count;
                    m_elementsOrder.Add(elementInfo);
                }
            }


            return true;
        }

        public bool previous_element() {

            if (m_currentElementId > 0) {  // enable previous element
                --m_currentElementId;
                start_current_flow_element();
                return true;
            }

            // no more element before current element
            return false;
        }

        public bool next_element() {

            if (m_currentElementId < m_elementsOrder.Count - 1) { // enable next element
                m_currentElementId++;
                start_current_flow_element();
                return true;
            }            
            return false;
        }

        public bool next_element_with_name(string elementName) {
            if (m_currentElementId < m_elementsOrder.Count - 1) {
                for (int ii = m_currentElementId + 1; ii < m_elementsOrder.Count; ++ii) {
                    if (m_elementsOrder[ii].name() == elementName) {
                        m_currentElementId = ii;
                        start_current_flow_element();
                        return true;
                    }
                }
            }
            return false;
        }

        public bool previous_element_with_name(string elementName) {
            if (m_currentElementId > 0) {
                for (int ii = m_currentElementId - 1; ii >= 0; --ii) {
                    if (m_elementsOrder[ii].name() == elementName) {
                        m_currentElementId = ii;
                        start_current_flow_element();
                        return true;
                    }
                }
            }
            return false;
        }

        public bool next_element_with_condition(string conditionName) {
            if (m_currentElementId < m_elementsOrder.Count - 1) {
                for (int ii = m_currentElementId + 1; ii < m_elementsOrder.Count; ++ii) {

                    if((m_elementsOrder[ii].type() == FlowElement.FlowElementType.Routine ?
                        ((RoutineInfo)m_elementsOrder[ii]).condition.name : ((ISIInfo)m_elementsOrder[ii]).durationStr) == conditionName) { 
                        m_currentElementId = ii;
                        start_current_flow_element();
                        return true;
                    }
                }
            }
            return false;
        }

        public bool previous_element_with_condition(string conditionName) {
            if (m_currentElementId > 0) {
                for (int ii = m_currentElementId - 1; ii >= 0; --ii) {

                    if ((m_elementsOrder[ii].type() == FlowElement.FlowElementType.Routine ?
                        ((RoutineInfo)m_elementsOrder[ii]).condition.name : ((ISIInfo)m_elementsOrder[ii]).durationStr) == conditionName) {
                        m_currentElementId = ii;
                        start_current_flow_element();
                        return true;
                    }
                }
            }
            return false;
        }

        public bool go_to_specific_instance_element(int elementOrderId) {

            if (elementOrderId < m_elementsOrder.Count) {
                m_currentElementId = elementOrderId;
                start_current_flow_element();
                return true;
            }
            return false;
        }

        public bool start_experiment() {

            if(m_elementsOrder.Count == 0) {
                return false;
            }

            // reset id and info
            m_currentElementId = 0;
            m_currentElementInfo = m_elementsOrder[m_currentElementId];
         
            return true;
        }

        public void start_current_flow_element() {

            // stop previous element
            ExVR.Routines().stop_current_routine();
            ExVR.ISIs().stop_current_isi();

            // retrieve new info
            m_currentElementInfo = m_elementsOrder[m_currentElementId];

            // enable new current flow element
            ExVR.Time().start_element();
            if (m_currentElementInfo.type() == FlowElement.FlowElementType.Isi) {
                // new element is an ISI
                ExVR.ISIs().start_isi((ISIInfo)m_currentElementInfo);
            } else if (m_currentElementInfo.type() == FlowElement.FlowElementType.Routine) {
                // new element is a routine 
                ExVR.Routines().start_routine((RoutineInfo)m_currentElementInfo);
            }
        }

        public FlowElementInfo update_current_flow_element() {

            if (m_elementsOrder.Count == 0) { // no flow element
                return null;
            }
       
            // check if still inside interval
            if (!current_interval().is_in_interval(ExVR.Time().ellapsed_element_s())) {
                // go  for next element
                if(!next_element()) {
                    // no elemen remaining, end of experiment
                    return null; 
                }
            }

            return m_currentElementInfo;
        }


        public void stop_experiment() {
            // nullify current element
            m_currentElementInfo = null;
        }

        public Interval current_interval() {
            if(m_currentElementId >= m_elementsOrder.Count ) {
                return null;
            }
            return m_elementsOrder[m_currentElementId].interval;
        }
    }
}