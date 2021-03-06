/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;

// unity
using UnityEngine;


#if UNITY_EDITOR
using UnityEditor;
namespace Ex{

    [CustomEditor(typeof(Condition))]
    public class ConditionEditor : Editor
    {

        public override bool RequiresConstantRepaint() {
            return true;
        }

        public override void OnInspectorGUI() {

            
            if (!Application.isPlaying) {
                return;
            }

            Condition condition = (Condition)target;

            var win = Screen.width;
            var w1 = win * 0.1f;
            var w2 = win * 0.4f;
            var w3 = win * 0.4f;

            EditorGUILayout.LabelField("All connections: ");
            GUILayout.BeginHorizontal();
            GUILayout.Label("N°", GUILayout.Width(w1));
            GUILayout.Label("output", GUILayout.Width(w2));
            GUILayout.Label("input", GUILayout.Width(w3));
            GUILayout.EndHorizontal();

            for (int ii = 0; ii < condition.connections.Count; ++ii) {

                GUILayout.BeginHorizontal();
                GUILayout.Label("("+ ii +")", GUILayout.Width(w1));
                EditorGUILayout.ObjectField(condition.connections[ii].start, typeof(Routine), true, GUILayout.Width(w2));
                EditorGUILayout.ObjectField(condition.connections[ii].end, typeof(Routine), true, GUILayout.Width(w3));
                GUILayout.EndHorizontal();
            }

        }
    }
}
#endif



namespace Ex{

    [System.Serializable]
    public class Connection{
        public int startIndex;
        public int endIndex;        
        public GameObject start;
        public GameObject end;
    }

    public class Condition : MonoBehaviour{

        // condition info
        private int m_key;
        private string keyStr;
        private double m_durationS = 0.0;
        private int m_callsNb = 0;

        // visual scripting
        private List<XML.Connection> m_connectionsXML = null;
        // # connections
        public List<Connection> connections = new List<Connection>();
        // # connectors
        public List<ExConnector> connectors = null;
        public Dictionary<int, ExConnector> connectorsPerKey = null;
        public ExConnector currentConnector = null;
        
        // actions
        public List<Action> actions = null;
        public List<Action> reverseOrderActions = null;
        public Dictionary<ExComponent.Category, List<Action>> actionsPerComponentCategory = null;
        public Dictionary<Type, List<Action>> actionsPerComponentType   = null;        
        public Dictionary<string, Action> actionPerComponentName = null;
        public Dictionary<int, Action> actionPerComponentKey = null; 


        public int key() {
            return m_key;
        }

        public string key_str() {
            return keyStr;
        }

        public double duration() {
            return m_durationS;
        }

        public int calls_nb() {
            return m_callsNb;
        }

        private void set_current(ExConnector connector) {
            currentConnector = connector;
        }

        public ExConnector get_connector(int connnectorKey) {
            if (connectorsPerKey.ContainsKey(connnectorKey)) {
                return connectorsPerKey[connnectorKey];
            }
            return null;
        }

        public Action get_action_from_component_key(int componentKey) {

            if (actionPerComponentKey.ContainsKey(componentKey)) {
                return actionPerComponentKey[componentKey];
            }
            return null;
        }

        public Action get_action_from_component_name(string componentName) {

            if (actionPerComponentName.ContainsKey(componentName)) {
                return actionPerComponentName[componentName];
            }
            return null;
        }

        public List<ExComponent> get_all_components() {
            List<ExComponent> components = new List<ExComponent>();
            foreach (var action in actions) {
                components.Add(action.component());
            }
            return components;
        }

        public List<ExComponent> get_all_components(ExComponent.Category category) {
            List<ExComponent> componentsWithCategory = new List<ExComponent>();
            foreach (var action in actionsPerComponentCategory[category]) {
                componentsWithCategory.Add(action.component());
            }
            return componentsWithCategory;
        }

        public List<ExComponent> get_all_components(Type type) {
            List<ExComponent> componentsWithType = new List<ExComponent>();
            foreach (var action in actionsPerComponentType[type]) {
                componentsWithType.Add(action.component());
            }
            return componentsWithType;
        }

        public List<T> get_all_components<T>() where T : ExComponent {
            List<T> components = new List<T>();
            var type = typeof(T);
            foreach (var action in actionsPerComponentType[type]) {
                components.Add((T)action.component());
            }
            return components;
        }


        public Routine parent_routine() {
            return transform.parent.GetComponent<Routine>();
        }

        public void initialize(XML.Condition xmlCondition) {

            // save key
            m_key = xmlCondition.Key;
            keyStr = Converter.to_string(xmlCondition.Key);

            // save connections
            m_connectionsXML = xmlCondition.Connections;

            // generate actions            
            var unsortedActions = new List<Action>(xmlCondition.Actions.Count);
            foreach (XML.Action actionXml in xmlCondition.Actions) {
                unsortedActions.Add(new Action(actionXml));
            }


            // store actions by priority
            actions = new List<Action>(xmlCondition.Actions.Count);
            reverseOrderActions = new List<Action>(xmlCondition.Actions.Count);
            foreach (var action in unsortedActions) {
                if (action.component().priority == ExComponent.Pritority.Hight) {
                    actions.Add(action);
                }else if (action.component().priority == ExComponent.Pritority.Low) {
                    reverseOrderActions.Add(action);
                }
            }
            foreach (var action in unsortedActions) {
                if (action.component().priority == ExComponent.Pritority.Medium) {
                    actions.Add(action);
                    reverseOrderActions.Add(action);
                }
            }
            foreach (var action in unsortedActions) {
                if (action.component().priority == ExComponent.Pritority.Low) {
                    actions.Add(action);
                } else if (action.component().priority == ExComponent.Pritority.Hight) {
                    reverseOrderActions.Add(action);
                }
            }

            // store actions in dictionnary
            actionsPerComponentCategory = new Dictionary<ExComponent.Category, List<Action>>();
            actionsPerComponentType = new Dictionary<Type, List<Action>>();
            actionPerComponentName  = new Dictionary<string, Action>();
            actionPerComponentKey   = new Dictionary<int, Action>();
            foreach (var action in actions) {

                var typeComponent = action.component().GetType();
                if (!actionsPerComponentType.ContainsKey(typeComponent)) {
                    actionsPerComponentType[typeComponent] = new List<Action>();
                }
                actionsPerComponentType[typeComponent].Add(action);

                var category = action.component().category;
                if (!actionsPerComponentCategory.ContainsKey(category)) {
                    actionsPerComponentCategory[category] = new List<Action>();
                }
                actionsPerComponentCategory[category].Add(action);


                actionPerComponentName[action.component().name] = action;
                actionPerComponentKey[action.component().key] = action;
            }


            // find duration of the condition
            m_durationS = xmlCondition.Duration;

            // generate connectors
            connectors = new List<ExConnector>(xmlCondition.Connectors.Count);
            connectorsPerKey = new Dictionary<int, ExConnector>(xmlCondition.Connectors.Count);
            foreach (XML.Connector xmlConnector in xmlCondition.Connectors) {
                var connector = ExConnector.generate(xmlConnector);
                if (connector != null) {
                    connector.associatedCondition = this;
                    connector.associatedRoutine = parent_routine();
                    connectors.Add(connector);
                    connectorsPerKey[connector.key] = connector;
                } 
            }
        }

        public void set_connections() {

            connections = new List<Connection>(m_connectionsXML.Count);
            foreach (var connectionXML in m_connectionsXML) {

                Connection connection = new Connection();
                connection.startIndex = connectionXML.StartIndex;
                connection.endIndex   = connectionXML.EndIndex;

                bool componentStartType = connectionXML.StartType == "component";
                bool componentEndType   = connectionXML.EndType   == "component";

                // retrieve output event
                Events.Connections outE = null;
                if(componentStartType) {

                    var action = get_action_from_component_key(connectionXML.StartKey);
                    if (action == null) {
                        ExVR.Log().error(string.Format("Connection start key {0} not found in components.", connectionXML.StartKey));
                        continue;
                    }
                    outE = action.component().connections();
                    connection.start = action.component().gameObject;

                } else {

                    var connector = get_connector(connectionXML.StartKey);
                    if (connector == null) {
                        ExVR.Log().error(string.Format("Connection start key {0} not found in connectors.", connectionXML.StartKey));
                        continue;
                    }
                    
                    outE = connector.connections();
                    connection.start = connector.gameObject;
                }

                // retrieve input event
                Events.Connections inE = null;
                if (componentEndType) {

                    var action = get_action_from_component_key(connectionXML.EndKey);
                    if (action == null) {
                        ExVR.Log().error(string.Format("Connection end key {0} not found in components.", connectionXML.EndKey));
                        continue;
                    }
                    inE = action.component().connections();
                    connection.end = action.component().gameObject;

                } else {

                    var connector = get_connector(connectionXML.EndKey);
                    if (connector == null) {
                        ExVR.Log().error(string.Format("Connection end key {0} not found in connectors.", connectionXML.EndKey));
                        continue;
                    }
                    inE = connector.connections();
                    connection.end = connector.gameObject;                    
                }


                // add input/output to connectors
                if(!componentStartType && componentEndType){

                    connection.start.GetComponent<ExConnector>().outputGO.Add(connection.end);
                    connection.start.GetComponent<ExConnector>().outputConnections.Add(connection);

                } else if (componentStartType && !componentEndType){
                    connection.end.GetComponent<ExConnector>().inputGO.Add(connection.start);
                    connection.end.GetComponent<ExConnector>().inputConnections.Add(connection);

                } else if (!componentStartType && !componentEndType){

                    connection.start.GetComponent<ExConnector>().outputGO.Add(connection.end);
                    connection.start.GetComponent<ExConnector>().outputConnections.Add(connection);

                    connection.end.GetComponent<ExConnector>().inputGO.Add(connection.start);
                    connection.end.GetComponent<ExConnector>().inputConnections.Add(connection);
                }

                var signal = outE.get_signal(connectionXML.Signal);
                if(signal == null) {
                    continue;
                }
                var slot   = inE.get_slot(connectionXML.Slot);
                if(slot == null) {
                    continue;
                }

                // generate the connection
                if (connectionXML.StartDataType == connectionXML.EndDataType) {
                    if(!Events.Connections.connect(signal, slot)) {
                        //connectionXML.StartKey
                        ExVR.Log().error(string.Format("Connection error with signal {0} and slot {1}.", connectionXML.Signal, connectionXML.Slot));
                        continue;
                    }
                } else {
                    // if start data and end data are differents, retrieve the corresponding data convertor
                    string code = string.Format("{0}:{1}", connectionXML.StartDataType, connectionXML.EndDataType);
                    var convertor = ConnectionsConvertors.get(code);
                    if(convertor == null) {
                        continue;
                    }
                    if(!Events.Connections.connect(signal, slot, convertor)) {
                        ExVR.Log().error(string.Format("Connection error with signal {0} and slot {1}.", connectionXML.Signal, connectionXML.Slot));
                        continue;
                    }                    
                }

                connections.Add(connection);
            }
        }

        public void start_routine() {

            // set connections between components and connectors
            set_connections();

            // actions
            {
                // set components config
                foreach (var action in actions) {
                    action.set_current_config(this);                    
                }

                foreach (var action in actions) {
                    action.update_from_current_config();
                }                

                // pre start routine
                ExVR.ExpLog().condition(ExComponent.Function.pre_start_routine, true);
                foreach (var action in actions) {
                    action.pre_start_routine();
                }
                ExVR.ExpLog().condition(ExComponent.Function.pre_start_routine, false);

                // start routine
                ExVR.ExpLog().condition(ExComponent.Function.start_routine, true);
                foreach (var action in actions) {
                    action.start_routine();
                }
                ExVR.ExpLog().condition(ExComponent.Function.start_routine, false);

                // post start routine
                ExVR.ExpLog().condition(ExComponent.Function.post_start_routine, true);
                foreach (var action in actions) {
                    action.post_start_routine();
                }
                ExVR.ExpLog().condition(ExComponent.Function.post_start_routine, false);
            }

            // connectors
            {
                ExVR.ExpLog().condition(ExConnector.Function.start_routine, true);
                foreach (var connector in connectors) {
                    set_current(connector);
                    connector.base_start_routine();
                }
                ExVR.ExpLog().condition(ExConnector.Function.start_routine, false);
            }
        }

        public void on_gui() {

            UnityEngine.Profiling.Profiler.BeginSample("[ExVR][Condition] on_gui");
            foreach (var action in actions) {
                action.on_gui();
            }
            UnityEngine.Profiling.Profiler.EndSample();
        }

        public void update() {

            UnityEngine.Profiling.Profiler.BeginSample("[ExVR][Condition] pre_update");
            foreach (var action in actions) {
                action.pre_update();
            }
            UnityEngine.Profiling.Profiler.EndSample();

            UnityEngine.Profiling.Profiler.BeginSample("[ExVR][Condition] update");
            foreach (var action in actions) {
                action.update();
            }
            UnityEngine.Profiling.Profiler.EndSample();

            UnityEngine.Profiling.Profiler.BeginSample("[ExVR][Condition] post_update");
            foreach (var action in actions) {
                action.post_update();
            }
            UnityEngine.Profiling.Profiler.EndSample();
        }

        public void play() {
            ExVR.ExpLog().condition(ExComponent.Function.play, true);
            foreach (var action in actions) {
                action.play();
            }
            ExVR.ExpLog().condition(ExComponent.Function.play, false);
        }

        public void pause() {
            ExVR.ExpLog().condition(ExComponent.Function.pause, true);
            foreach (var action in actions) {
                action.pause();
            }
            ExVR.ExpLog().condition(ExComponent.Function.pause, false);
        }
        public void stop_routine() {

            // connectors
            {
                ExVR.ExpLog().condition(ExConnector.Function.stop_routine, true);
                foreach (var connector in connectors) {
                    set_current(connector);
                    connector.base_stop_routine();
                }
                ExVR.ExpLog().condition(ExConnector.Function.stop_routine, false);
            }

            // actions
            {
                ExVR.ExpLog().condition(ExComponent.Function.stop_routine, true);
                foreach (var action in reverseOrderActions) {
                    action.stop_routine();
                }
                ExVR.ExpLog().condition(ExComponent.Function.stop_routine, false);
            }
            
            // remove connections between components and connectors
            remove_connections();

            // increment nb of calls
            m_callsNb++;
        }

        public void stop_experiment() {
            m_callsNb = 0;
        }

        public void trigger_update_connector_signals() {

            foreach (var connector in connectors) {
                set_current(connector);
                connector.base_pre_update();
            }

            foreach (var connector in connectors) {
                set_current(connector);
                connector.base_update();
            }

            foreach (var connector in connectors) {
                set_current(connector);
                connector.base_post_update();
            }
        }

        public void remove_connections() {

            foreach (var action in actions) {                
                action.component().connections().clean();
            }
            foreach (var connector in connectors) {
                connector.connections().clean();
            }
        }
    }
}

