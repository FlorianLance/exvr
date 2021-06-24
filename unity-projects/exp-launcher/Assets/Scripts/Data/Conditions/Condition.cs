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

        public int key;
        public string keyStr;
        public double durationS = 0.0;

        private List<XML.Connection> m_connectionsXML = null;

        public List<Connection> connections = new List<Connection>();

        public List<Action> actions = null;
        public List<Action> reverseOrderActions = null;
        public List<ExConnector> connectors = null;

        public ExConnector currentConnector = null;

        private void set_current(ExConnector connector) {
            currentConnector = connector;
        }

        public ExConnector get_connector(int connnectorKey) {
            foreach (ExConnector connector in connectors) {
                if (connector.key == connnectorKey) {
                    return connector;
                }
            }
            return null;
        }

        public Action get_action_from_component_key(int componentKey) {

            foreach (Action action in actions) {
                if (action.component().key == componentKey) {
                    return action;
                }
            }
            return null;
        }

        public Action get_action_from_component_name(string componentName) {

            foreach(Action action in actions) {
                if(action.component().name == componentName) {
                    return action;
                }
            }
            return null;
        }

        public Routine parent_routine() {
            return transform.parent.GetComponent<Routine>();
        }

        public void initialize(XML.Condition xmlCondition) {

            // save key
            key = xmlCondition.Key;
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

            // find duration of the condition
            durationS = xmlCondition.Duration;

            // generate connectors
            connectors = new List<ExConnector>(xmlCondition.Connectors.Count);
            foreach (XML.Connector xmlConnector in xmlCondition.Connectors) {
                var connector = ExConnector.generate(xmlConnector);
                if (connector != null) {
                    connector.associatedCondition = this;
                    connector.associatedRoutine = parent_routine();
                    connectors.Add(connector);
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
                        ExVR.Log().error("Connection start key " + connectionXML.StartKey + " not found in components.");
                        continue;
                    }
                    outE = action.component().events();
                    connection.start = action.component().gameObject;

                } else {

                    var connector = get_connector(connectionXML.StartKey);
                    if (connector == null) {
                        ExVR.Log().error("Connection start key " + connectionXML.StartKey + " not found in connectors.");
                        continue;
                    }
                    
                    outE = connector.events();
                    connection.start = connector.gameObject;
                }

                // retrieve input event
                Events.Connections inE = null;
                if (componentEndType) {

                    var action = get_action_from_component_key(connectionXML.EndKey);
                    if (action == null) {
                        ExVR.Log().error("Connection end key " + connectionXML.EndKey + " not found in components.");
                        continue;
                    }
                    inE = action.component().events();
                    connection.end = action.component().gameObject;

                } else {

                    var connector = get_connector(connectionXML.EndKey);
                    if (connector == null) {
                        ExVR.Log().error("Connection end key " + connectionXML.EndKey + " not found in connectors.");
                        continue;
                    }
                    inE = connector.events();
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
                        ExVR.Log().error("ERROR1: " + connectionXML.Signal + " " + connectionXML.Slot);
                        continue;
                    }
                } else {
                    // if start data and end data are differents, retrieve the corresponding data convertor
                    string code = connectionXML.StartDataType + ":" + connectionXML.EndDataType;
                    var convertor = ExVR.Convertors().get(code);
                    if(convertor == null) {
                        continue;
                    }
                    if(!Events.Connections.connect(signal, slot, convertor)) {
                        ExVR.Log().error("ERROR2: " + connectionXML.Signal + " " + connectionXML.Slot);
                        continue;
                    }                    
                }

                connections.Add(connection);
            }
        }

        public void connectors_start_routine() {

            // depending priority
            // ...
            foreach (var connector in connectors) {
                set_current(connector);
                connector.base_start_routine();
            }
        }

        public void connectors_stop_routine() {
            // depending priority
            // ...
            foreach (var connector in connectors) {
                set_current(connector);
                connector.base_stop_routine();
            }
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
                action.component().events().clean();
            }
            foreach (var connector in connectors) {
                connector.events().clean();
            }
        }

    }
}

