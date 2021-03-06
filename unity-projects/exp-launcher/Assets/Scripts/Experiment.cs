
﻿/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.IO;
using System.Diagnostics;
using System.Xml.Serialization;
using System.Collections;
using System.Collections.Generic;

// unity
using UnityEngine;
using UnityEngine.Profiling;

namespace Ex{

    public class ScheduledAction{
        
        public enum Source{
            Command, Gui
        }

        public enum Type{
            Next, Previous,
            NextElementWithName, PreviousElementWithName,
            NextElementWithCondition, PreviousElementWithCondition,
            GoToSpecificInstanceElement,
            ModifyRoutineActionConfig,
            Start, Stop, Quit, Pause, Play,
            UpdateComponentParameter,
            UpdateConnectorParameter,
            ComponentActionFromGui,
        }

        public ScheduledAction(Source source, Type type) {
            this.source = source;
            this.type = type;
        }

        public Type type;
        public Source source;        
        public int elementKey;
        public int conditionKey;
        public int configKey;
        public int componentKey;        
        public int connectorKey;
        public string elementName;
        public string conditionName;
        public string componentName;
        public string configName;
        public string actionName;
        public XML.Arg arg = null;
    }


    public class Experiment : MonoBehaviour{

        [Rename("Components")]
        public Components components = null;

        [Rename("Resources")]
        public ResourcesManager experimentResourcesManager = null;

        // elements and components
        [Rename("Routines")]
        public Routines routines = null;
        [Rename("ISIs")]
        public ISIs ISIs = null;

        // misc info
        public string experimentName;
        public string instanceName;
        public string designerVersion;

        // schreduler
        public Scheduler schreduler = null;
        private List<ScheduledAction> m_scheduledActions = new List<ScheduledAction>();

        // states
        private bool m_experimentCleaned = false;
        private bool m_experimentLoaded = false;


        // xml
        private XML.Experiment m_xmlExperiment = null;
        private XML.ExperimentFlow m_xmlFlow = null;


        #region unity

        private const string expStr = "[EXP] {0}";

        public void log_message(string message, bool extraInfo = false) {
            ExVR.Log().message(string.Format(expStr, message), extraInfo);
        }

        public void log_warning(string warning, bool extraInfo = false) {
            ExVR.Log().warning(string.Format(expStr, warning), extraInfo);
        }

        public void log_error(string error, bool extraInfo = false) {
            ExVR.Log().error(string.Format(expStr, error), extraInfo);
        }

        public bool is_loaded() { return m_experimentLoaded; }
        public bool is_cleaned() { return m_experimentCleaned; }

        public void initialize() {

            experimentResourcesManager.initialize();

            // add listeners
            ExVR.Events().command.NextElementEvent.AddListener(() => {
                schedule_go_to_next_element(ScheduledAction.Source.Command);
            });
            ExVR.Events().command.PreviousElementEvent.AddListener(() => {
                schedule_go_to_previous_element(ScheduledAction.Source.Command);
            });
            ExVR.Events().command.StopExperimentEvent.AddListener(() => {
                if (ExVR.Time().is_experiment_started()) {                    
                    schedule_stop_experiment(ScheduledAction.Source.Command);
                }                
            });
            ExVR.Events().command.PauseExperimentEvent.AddListener(() => {
                if (ExVR.Time().is_experiment_started()) {
                    schedule_pause_experiment(ScheduledAction.Source.Command);
                }
            });
            ExVR.Events().command.NextElementWithNameEvent.AddListener((string name) => {
                schedule_next_element_with_name(ScheduledAction.Source.Command, name);
            });
            ExVR.Events().command.NextElementWithConditionEvent.AddListener((string conditionName) => {
                schedule_next_element_with_condition(ScheduledAction.Source.Command, conditionName);
            });
            ExVR.Events().command.PreviousElementWithNameEvent.AddListener((string name) => {
                schedule_previous_element_with_name(ScheduledAction.Source.Command, name);
            });
            ExVR.Events().command.PreviousElementWithConditionEvent.AddListener((string conditionName) => {
                schedule_previous_element_with_condition(ScheduledAction.Source.Command, conditionName);
            });
            ExVR.Events().command.GoToSpecificInstanceElementEvent.AddListener((int elementOrderId) => {
                schedule_go_to_specific_instance_element(ScheduledAction.Source.Command, elementOrderId);
            });                
            ExVR.Events().command.ModifyRoutineActionConfigEvent.AddListener((string routineName, string conditionName, string componentName, string newConfigName) => {                
                schedule_modify_action_config(ScheduledAction.Source.Command, routineName, conditionName, componentName, newConfigName);
            });
            ExVR.Events().gui.MessageFromGUI.AddListener((strCmd) => {
                execute_command(strCmd);
            });
        }


        //double previousUpdateTime = 0f;

        void Update() {

            //double currentUpdateTime = ExVR.Time().ellapsed_time_program_ms();
            //if (currentUpdateTime - previousUpdateTime < 8.0) { // do not call update more thant 125 times per second
            //    return;
            //}
            //previousUpdateTime = currentUpdateTime;

            if (!ExVR.Time().is_experiment_running()) {
                apply_scheduled_actions();
                send_current_experiment_state_to_gui();
                return;
            }

            ExVR.Time().start_new_frame();            

            FlowElementInfo elementInfo;
            {   // update current element
                Profiler.BeginSample("[ExVR][Experiment] update_current_element");
                elementInfo = schreduler.update_current_flow_element();
                if (elementInfo == null) {                    
                    stop_experiment();
                    ExVR.Log().message("End of experiment");
                    ExVR.ExpLog().exp("End", true, true, true);
                    return;
                }
                Profiler.EndSample();
            }

            {   // update all components states
                Profiler.BeginSample("[ExVR][Experiment] update_components_states");
                if (elementInfo.type() == FlowElement.FlowElementType.Routine) {
                    routines.update_components_states((RoutineInfo)elementInfo);
                }else if (elementInfo.type() == FlowElement.FlowElementType.Isi){
                    ExVR.Components().set_every_component_states_to_false();
                }
                Profiler.EndSample();
            }

            {   // update all components
                Profiler.BeginSample("[ExVR][Experiment] update");
                routines.update_current_routine();
                Profiler.EndSample();
            }

            {   // trigger each time
                Profiler.BeginSample("[ExVR][Experiment] trigger_update_signals");
                if (elementInfo.type() == FlowElement.FlowElementType.Routine) {
                    routines.trigger_update_signals((RoutineInfo)elementInfo);
                }
                Profiler.EndSample();
            }

            {   // apply all scheduled actions from GUI or scripts
                Profiler.BeginSample("[ExVR][Experiment] apply_scheduled_actions");                
                apply_scheduled_actions();
                Profiler.EndSample();
            }

            send_current_experiment_state_to_gui();

            ExVR.Time().end_frame();
        }

        private void OnGUI() {

            if (!ExVR.Time().is_experiment_running()) {
                return;
            }

            routines.on_gui();
        }


        #endregion unity

        #region load_experiment

        private void send_current_experiment_state_to_gui() {

            // not loaded
            if (!is_loaded()) {
                ExVR.Network().set_experiment_state_to_GUI(NetworkManager.ExpState.NotLoaded);
                return;
            }

            // loaded, not running
            if (!ExVR.Time().is_experiment_started()) {
                ExVR.Network().set_experiment_state_to_GUI(NetworkManager.ExpState.Loaded);
                return;
            }

            // if started, send current element
            string infoStr = "";
            var info = schreduler.current_element_info();
            if (info != null) {

                bool isRoutine = (info.type() == FlowElement.FlowElementType.Routine);

                string elementTimeStr   = Converter.to_string(ExVR.Time().ellapsed_element_ms());
                string expTimeStr       = Converter.to_string(ExVR.Time().ellapsed_exp_ms());                
                string interStr         = info.interval() != null ? Converter.to_string(info.interval().tEndS * 1000) : "-";
                string orderStr         = string.Format("{0}/{1}", info.order()+1, schreduler.instance.total_number_of_elements());
                string elementKey       = Converter.to_string(info.key());

                string callsNb          = string.Format("{0};{1}", 
                    Converter.to_string(info.element().calls_nb()),
                    isRoutine ? Converter.to_string(((RoutineInfo)info).condition().calls_nb()) : "-"
                );

                string typeStr          = isRoutine ? "R" : "I";
                string typeSpecificInfo = isRoutine ? ((RoutineInfo)info).condition().key_str() :  ((ISIInfo)info).duration_str();

                infoStr = string.Format("{0}|{1}|{2}|{3}|{4}|{5}|{6}|{7}",
                    elementTimeStr,
                    expTimeStr,
                    interStr,
                    orderStr,
                    elementKey,
                    callsNb,
                    typeStr,
                    typeSpecificInfo
                );
            }

            ExVR.Network().set_experiment_state_to_GUI(
                ExVR.Time().is_paused() ? NetworkManager.ExpState.Paused : NetworkManager.ExpState.Running, infoStr);
        }

        IEnumerator load_full_experiment_c(string xmlExperimentPath, string xmlInstancePath) {

            ExVR.Network().set_launcher_loading_state(xmlExperimentPath, xmlInstancePath);
            
            // flow log
            ExVR.ExpLog().exp(string.Format("Load XML [{0} , {1}]", xmlExperimentPath, xmlInstancePath), true, false, false);

            destroy_experiment();
            yield return new WaitForSeconds(1);
             
            // retrieve instance name
            var split = xmlInstancePath.Split('.')[0].Split('/');
            ExVR.Experiment().instanceName = split[split.Length - 1];

            if (!load_experiment_file(xmlExperimentPath)) {
                ExVR.Network().set_launcher_idle_state();
                ExVR.Network().set_experiment_state_to_GUI(NetworkManager.ExpState.NotLoaded);
                yield break;
            }
            if (!load_instance_file(xmlInstancePath)) {
                ExVR.Network().set_launcher_idle_state();
                ExVR.Network().set_experiment_state_to_GUI(NetworkManager.ExpState.NotLoaded);
                yield break;
            }

            m_experimentLoaded = true;

            ExVR.Network().set_launcher_idle_state();
            ExVR.Network().set_experiment_state_to_GUI(NetworkManager.ExpState.Loaded);

            yield return true;
        }

        public bool load_experiment_file(string xmlExperimentPath) {

            if (ExVR.Time().is_experiment_started()) {
                log_error("Experiment must be stopped before loading a new one.");
                return false;
            }

            if (!File.Exists(xmlExperimentPath)) {
                log_error(string.Format("Experiment file {0} doesn't exists.", xmlExperimentPath));
                return false;
            }

            log_message(string.Format("Load experiment: {0}", xmlExperimentPath));
            Stopwatch generationTimer = new Stopwatch();
            generationTimer.Restart();

            // xml experiment
            var serializer = new XmlSerializer(typeof(XML.Experiment));
            var stream = new FileStream(xmlExperimentPath, FileMode.Open);
            m_xmlExperiment = serializer.Deserialize(stream) as XML.Experiment;            
            stream.Close();            

            ExVR.ExpLog().exp(string.Format("XML [{0}] loaded from designer {1} with version {2}.", m_xmlExperiment.Name, m_xmlExperiment.DesignerUsed, m_xmlExperiment.Version), true, false, false);
            ExVR.ExpLog().exp("Initialize experiment.", false, false ,false);

            // save misc informations
            experimentName = m_xmlExperiment.Name;
            designerVersion = m_xmlExperiment.Version;

            // read settings
            ExVR.GuiSettings().read_from_xml(m_xmlExperiment.Settings);

            // read resources
            experimentResourcesManager.generate_from_xml(m_xmlExperiment.Resources);

            // generate components and flow elements
            if (!ExVR.Components().generate(m_xmlExperiment.Components)) {
                log_error("Experiment loading failed. Please solve errors and start loading again.");
                return false;
            }
            routines.generate_from_xml(m_xmlExperiment.FlowElements.Routines);
            ISIs.generate_from_xml(m_xmlExperiment.FlowElements.ISIs);            

            double generationTime = generationTimer.Elapsed.TotalMilliseconds * 0.001;
            generationTimer.Stop();

            // GUI log
            log_message(string.Format("Experiment loaded in {0}s", generationTime));

            // flow log
            ExVR.ExpLog().exp(string.Format("Experiment initialized in {0}s ", generationTime), true, false, false);

            return true;
        }

        public bool load_instance_file(string xmlInstancePath) {

            log_message(string.Format("Load instance: {0}", xmlInstancePath));

            // xml instance
            var serializer = new XmlSerializer(typeof(XML.ExperimentFlow));
            var stream = new FileStream(xmlInstancePath, FileMode.Open);
            m_xmlFlow = serializer.Deserialize(stream) as XML.ExperimentFlow;
            stream.Close();

            // generate schreduling
            if (!schreduler.generate_instance(m_xmlFlow)) {
                log_error("Instance loading failed. Please select a valid instance file and start loading again.");
                return false;
            }
            log_message("Instance loaded.");

            ExVR.Paths().lastLoadedInstanceFile = xmlInstancePath;

            return true;
        }

#endregion load_experiment

#region experiment_control

        public void start_experiment() {

            if (!is_loaded()) {
                log_error("Experiment must be loaded before starting.");
                return;
            }

            if (ExVR.Time().is_experiment_started()) {
                log_error("Experiment already started.");
                return;
            }

            // flow log
            ExVR.ExpLog().exp("Start", true, false, false);
            if (!schreduler.start_experiment()) {
                return;
            }

            ExVR.Time().start_experiment();
            ExVR.Display().reset_experiment_settings();
            ExVR.ExpLog().reset_strackTrace();

            routines.start_experiment();
            schreduler.start_current_flow_element();

            m_experimentCleaned = false;

            // GUI update
            ExVR.Network().set_experiment_state_to_GUI(NetworkManager.ExpState.Running);

            // flow log
            ExVR.ExpLog().exp("Experiment started", false, false, false);
        }

        public void play_experiment() {

            // flow log
            ExVR.ExpLog().exp("Play", true, true, true);

            ExVR.Time().play_experiment();
            routines.play();

            // GUI update
            ExVR.Network().set_experiment_state_to_GUI(NetworkManager.ExpState.Running);
        }

        public void pause_experiment() {

            // flow log
            ExVR.ExpLog().exp("Pause", true, true, true);

            ExVR.Time().pause_experiment();
            routines.pause();

            // GUI update
            ExVR.Network().set_experiment_state_to_GUI(NetworkManager.ExpState.Paused);
        }

        public void stop_experiment() {

            ExVR.ExpLog().display_strackTrace();
            ExVR.ExpLog().exp("Stop experiment", true, true, true);            

            routines.stop_experiment();

            // stop last current isi 
            ISIs.stop_current_isi();

            // stop schreduler
            schreduler.stop_experiment();
            ExVR.Time().stop_experiment();

            // GUI update
            ExVR.Network().set_experiment_state_to_GUI(NetworkManager.ExpState.Loaded);

            // flow log
            ExVR.ExpLog().exp("Experiment stopped", false, false, false);            
            ExVR.ExpLog().write();
        }

        public void execute_command(string strCommand) {

            if (strCommand.Length == 0) { // empty command
                return;
            }
            var cmd = NetworkManager.str_to_command(strCommand);
            switch (cmd.Item1) {
                case NetworkManager.Command.Load: {

                    if (cmd.Item2.Count != 2) {
                        log_error(string.Format("Load experiment error: bad number of parameters ({0}) with cmd : {1}", cmd.Item2.Count, strCommand));
                        return;
                    }

                    var loadExp = new CoroutineWithData(load_full_experiment_c(cmd.Item2[0], cmd.Item2[1]));
                    return;

                }case NetworkManager.Command.Play: {

                    if (ExVR.Time().is_paused()) {
                        schedule_play_experiment(ScheduledAction.Source.Gui);
                    } else if (!ExVR.Time().is_experiment_started()) {                        
                        schedule_start_experiment(ScheduledAction.Source.Gui);
                    }
                    return;

                }case NetworkManager.Command.Pause: {
                    schedule_pause_experiment(ScheduledAction.Source.Gui);
                    return;
                }case NetworkManager.Command.Stop: {                    
                    schedule_stop_experiment(ScheduledAction.Source.Gui);
                    return;
                }case NetworkManager.Command.Next: {                    
                    schedule_go_to_next_element(ScheduledAction.Source.Gui);
                    return;
                }case NetworkManager.Command.Previous: {
                    schedule_go_to_previous_element(ScheduledAction.Source.Gui);
                    return;
                }case NetworkManager.Command.UpdateComponent: {

                    int componentKey, configKey, dim;
                    Int32.TryParse(cmd.Item2[0], out componentKey);
                    Int32.TryParse(cmd.Item2[1], out configKey);
                    Int32.TryParse(cmd.Item2[5], out dim);

                    XML.Arg arg = new XML.Arg();
                    arg.Name         = cmd.Item2[2];
                    arg.Value        = cmd.Item2[3];
                    arg.Type         = cmd.Item2[4];
                    arg.Dim          = dim;
                    arg.Sizes        = cmd.Item2[6];
                    arg.Separator    = cmd.Item2[7];

                    schedule_update_component_parameter(ScheduledAction.Source.Gui, componentKey, configKey, arg);
                    return;

                }case NetworkManager.Command.UpdateConnector: {

                    int routineKey, conditionKey, connectorKey, dim;
                    Int32.TryParse(cmd.Item2[0], out routineKey);
                    Int32.TryParse(cmd.Item2[1], out conditionKey);
                    Int32.TryParse(cmd.Item2[2], out connectorKey);
                    Int32.TryParse(cmd.Item2[6], out dim);

                    XML.Arg arg = new XML.Arg();
                    arg.Name      = cmd.Item2[3];
                    arg.Value     = cmd.Item2[4];
                    arg.Type      = cmd.Item2[5];
                    arg.Dim       = dim;
                    arg.Sizes     = cmd.Item2[7];
                    arg.Separator = cmd.Item2[8]; //  cmd.Item2.Count > 7 ? cmd.Item2[7] : "";

                    schedule_update_connector_parameter(ScheduledAction.Source.Gui, routineKey, conditionKey, connectorKey, arg);
                    return;
                }case NetworkManager.Command.Quit: {
                    schedule_quit(ScheduledAction.Source.Gui);
                    return;
                }case NetworkManager.Command.Action: {

                    int componentKey, configKey;
                    Int32.TryParse(cmd.Item2[0], out componentKey);
                    Int32.TryParse(cmd.Item2[1], out configKey);
                    string actionName = cmd.Item2[2];

                    schedule_component_action_from_gui(ScheduledAction.Source.Gui, componentKey, configKey, actionName);
                    return;

                }case NetworkManager.Command.GoToSpecificInstanceElement: {

                    if (cmd.Item2.Count != 1) {
                        log_error(string.Format("Go to instance specific element error: bad number of parameters ({0}) with cmd : {1}", cmd.Item2.Count, strCommand));
                        return;
                    }
                    schedule_go_to_specific_instance_element(ScheduledAction.Source.Gui, Converter.to_int(cmd.Item2[0]));
                    return;
                    
                }case NetworkManager.Command.PlayPause: {
                    if (!ExVR.Time().is_experiment_started()) {
                        schedule_start_experiment(ScheduledAction.Source.Gui);
                    }
                    schedule_pause_experiment(ScheduledAction.Source.Gui);
                    return;

                }case NetworkManager.Command.PlayDelay: {

                    if (cmd.Item2.Count != 1) {
                        log_error(string.Format("Play delay error: bad number of parameters ({0}) with cmd : {1}", cmd.Item2.Count, strCommand));
                        return;
                    }

                    ExVR.ExpLog().gui("play_delay");
                    StartCoroutine(start_after_delay(ScheduledAction.Source.Gui, Converter.to_int(cmd.Item2[0])));                        
                    return;

                }case NetworkManager.Command.Error: {
                    log_error("Invalid command from GUI to execute.");
                    return;
                }
            }
        }

        IEnumerator start_after_delay(ScheduledAction.Source source, int delay) {
            yield return new WaitForSeconds(delay);
            if (!ExVR.Time().is_experiment_started()) {
                schedule_start_experiment(source);
            }
        }

        // scheduled actions
        public void schedule_go_to_next_element(ScheduledAction.Source source) {
            m_scheduledActions.Add(new ScheduledAction(source, ScheduledAction.Type.Next));
        }

        public void schedule_go_to_previous_element(ScheduledAction.Source source) {
            m_scheduledActions.Add(new ScheduledAction(source, ScheduledAction.Type.Previous));
        }

        public void schedule_next_element_with_condition(ScheduledAction.Source source, string condition) {
            var action = new ScheduledAction(source, ScheduledAction.Type.NextElementWithCondition);
            action.conditionName = condition;
            m_scheduledActions.Add(action);
        }

        public void schedule_previous_element_with_condition(ScheduledAction.Source source, string condition) {
            var action = new ScheduledAction(source, ScheduledAction.Type.PreviousElementWithCondition);
            action.conditionName = condition;
            m_scheduledActions.Add(action);
        }

        public void schedule_next_element_with_name(ScheduledAction.Source source, string element) {
            var action = new ScheduledAction(source, ScheduledAction.Type.NextElementWithName);
            action.elementName = element;
            m_scheduledActions.Add(action);
        }

        public void schedule_previous_element_with_name(ScheduledAction.Source source, string element) {
            var action = new ScheduledAction(source, ScheduledAction.Type.PreviousElementWithName);
            action.elementName = element;
            m_scheduledActions.Add(action);
        }

        public void schedule_go_to_specific_instance_element(ScheduledAction.Source source, int elementKey) {
            var action = new ScheduledAction(source, ScheduledAction.Type.GoToSpecificInstanceElement);
            action.elementKey = elementKey;
            m_scheduledActions.Add(action);
        }

        public void schedule_start_experiment(ScheduledAction.Source source) {
            m_scheduledActions.Add(new ScheduledAction(source, ScheduledAction.Type.Start));
        }

        public void schedule_play_experiment(ScheduledAction.Source source) {
            m_scheduledActions.Add(new ScheduledAction(source, ScheduledAction.Type.Play));
        }

        public void schedule_pause_experiment(ScheduledAction.Source source) {
            m_scheduledActions.Add(new ScheduledAction(source, ScheduledAction.Type.Pause));
        }

        public void schedule_stop_experiment(ScheduledAction.Source source) {
            m_scheduledActions.Add(new ScheduledAction(source, ScheduledAction.Type.Stop));
        }

        public void schedule_quit(ScheduledAction.Source source) {
            m_scheduledActions.Add(new ScheduledAction(source, ScheduledAction.Type.Quit));
        }

        public void schedule_modify_action_config(ScheduledAction.Source source, string routineName, string conditionName, string componentName, string newConfigName) {
            var action = new ScheduledAction(source, ScheduledAction.Type.ModifyRoutineActionConfig);
            action.elementName = routineName;
            action.conditionName = conditionName;
            action.componentName = componentName;
            action.configName = newConfigName;
            m_scheduledActions.Add(action);
        }

        public void schedule_update_component_parameter(ScheduledAction.Source source, int componentKey, int configKey, XML.Arg arg) {
            var action = new ScheduledAction(source, ScheduledAction.Type.UpdateComponentParameter);
            action.componentKey = componentKey;
            action.configKey = configKey;
            action.arg = arg;
            m_scheduledActions.Add(action);
        }

        public void schedule_update_connector_parameter(ScheduledAction.Source source, int routineKey, int conditionKey, int connectorKey, XML.Arg arg) {
            var action = new ScheduledAction(source, ScheduledAction.Type.UpdateConnectorParameter);
            action.elementKey = routineKey;
            action.conditionKey = conditionKey;
            action.connectorKey = connectorKey;
            action.arg = arg;
            m_scheduledActions.Add(action);
        }

        public void schedule_component_action_from_gui(ScheduledAction.Source source, int componentKey, int configKey, string actionName) {
            var action = new ScheduledAction(source, ScheduledAction.Type.ComponentActionFromGui);
            action.componentKey = componentKey;
            action.configKey = configKey;
            action.actionName = actionName;
            m_scheduledActions.Add(action);
        }

        private void exp_log(ScheduledAction.Source source, string message) {
            if (source == ScheduledAction.Source.Gui) {
                ExVR.ExpLog().gui(message);
            } else {
                ExVR.ExpLog().command(message);
            }
        }

        public void apply_scheduled_actions() {

            if(m_scheduledActions.Count == 0) {
                return;
            }

            // retrieve and clean actions
            var actions = m_scheduledActions;
            m_scheduledActions = new List<ScheduledAction>();

            int countGoto = 0;
            ScheduledAction lastGotoAction = null;
            ScheduledAction stopAction = null;
            ScheduledAction quitAction = null;
            foreach (var action in actions) {

                if (action.type == ScheduledAction.Type.Stop) {
                    stopAction = action;
                } else if (action.type == ScheduledAction.Type.Quit) {
                    quitAction = action;
                } else if (action.type == ScheduledAction.Type.Next) {
                    ++countGoto;
                    lastGotoAction = action;
                } else if (action.type == ScheduledAction.Type.Previous) {
                    ++countGoto;
                    lastGotoAction = action;
                } else if (action.type == ScheduledAction.Type.NextElementWithName) {
                    ++countGoto;
                    lastGotoAction = action;
                } else if (action.type == ScheduledAction.Type.NextElementWithCondition) {
                    ++countGoto;
                    lastGotoAction = action;
                } else if (action.type == ScheduledAction.Type.PreviousElementWithName) {
                    ++countGoto;
                    lastGotoAction = action;
                } else if (action.type == ScheduledAction.Type.PreviousElementWithCondition) {
                    ++countGoto;
                    lastGotoAction = action;
                } else if (action.type == ScheduledAction.Type.GoToSpecificInstanceElement) {
                    ++countGoto;
                    lastGotoAction = action;
                } else if (action.type == ScheduledAction.Type.ModifyRoutineActionConfig) {

                    exp_log(action.source, "modify_action_config");
                    if (!routines.modify_action_config(action.elementName, action.conditionName, action.componentName, action.configName)) {
                        log_error(string.Format("Cannot apply config {0} from condition {1} in routine {2} with component {3}.", 
                            action.configName,
                            action.conditionName,
                            action.elementName,
                            action.componentName
                        ));
                    }
                } else if (action.type == ScheduledAction.Type.UpdateComponentParameter) {

                    ExVR.Components().update_parameter_from_gui_xml(action.componentKey, action.configKey, action.arg);

                } else if (action.type == ScheduledAction.Type.UpdateConnectorParameter) {

                    Routine routine = routines.get(action.elementKey);
                    if (routine == null) {
                        return;
                    }
                    Condition condition = routine.get_condition_from_key(action.conditionKey);
                    if (condition == null) {
                        return;
                    }
                    var connector = condition.get_connector(action.connectorKey);
                    if (connector != null) {
                        connector.base_update_from_gui(action.arg);
                    }                                        

                } else if (action.type == ScheduledAction.Type.ComponentActionFromGui) {

                    ExVR.Components().action_from_gui(action.componentKey, action.configKey, action.actionName);

                } else if (action.type == ScheduledAction.Type.Start) {
                    exp_log(action.source, "start");
                    start_experiment();
                }else if (action.type == ScheduledAction.Type.Play) {
                    exp_log(action.source, "play");
                    play_experiment();
                }else if (action.type == ScheduledAction.Type.Pause) {
                    exp_log(action.source, "pause");
                    pause_experiment();
                }
            }

            // stop the experiment
            if (stopAction != null) {
                exp_log(stopAction.source, "stop_experiment");
                stop_experiment();
            }

            // quit the program
            if (quitAction != null) {
                exp_log(quitAction.source, "quit");
                GlobalVariables.wantToLeave = true;
#if UNITY_EDITOR
                UnityEditor.EditorApplication.isPlaying = false;
#else
                Application.Quit(1);
#endif
            }

            if(stopAction != null || quitAction != null) {
                // no use to continue
                return;
            }

            // manage goto
            if (countGoto > 1) {
                log_warning(String.Format("To many goto function called during last frame ({0}), only the last one will be executed: {1}", 
                    countGoto.ToString(), 
                    lastGotoAction.type.ToString())
                );
            }

            if (lastGotoAction != null) {

                switch (lastGotoAction.type) {
                    case ScheduledAction.Type.Next:
                        exp_log(lastGotoAction.source, "next");
                        if (!schreduler.next_element()) {
                            log_warning("Cannot go to next element.");
                        }
                        return;
                    case ScheduledAction.Type.Previous:
                        exp_log(lastGotoAction.source, "previous");
                        if (!schreduler.previous_element()) {
                            log_warning("Cannot go to previous element.");
                        }
                        return;
                    case ScheduledAction.Type.NextElementWithName:
                        exp_log(lastGotoAction.source, "next_element_with_name");
                        if (!schreduler.next_element_with_name(lastGotoAction.elementName)) {
                            log_warning(String.Format("Cannot go to next element with name {0}", lastGotoAction.elementName));
                        }
                        return;
                    case ScheduledAction.Type.PreviousElementWithName:
                        exp_log(lastGotoAction.source, "previous_element_with_name");
                        if (!schreduler.previous_element_with_name(lastGotoAction.elementName)) {
                            log_warning(String.Format("Cannot go to previous element with name {0}", lastGotoAction.elementName));
                        }
                        return;
                    case ScheduledAction.Type.NextElementWithCondition:
                        exp_log(lastGotoAction.source, "next_element_with_condition");
                        if (!schreduler.next_element_with_condition(lastGotoAction.conditionName)) {
                            log_warning(String.Format("Cannot go to next element with condition {0}", lastGotoAction.conditionName));
                        }
                        return;
                    case ScheduledAction.Type.PreviousElementWithCondition:
                        exp_log(lastGotoAction.source, "next_element_with_condition");
                        if (!schreduler.previous_element_with_condition(lastGotoAction.conditionName)) {
                            log_warning(String.Format("Cannot go to previous element with condition {0}", lastGotoAction.conditionName));
                        }
                        return;
                    case ScheduledAction.Type.GoToSpecificInstanceElement:
                        exp_log(lastGotoAction.source, "go_to_specific_instance_element");
                        if (!schreduler.go_to_specific_instance_element(lastGotoAction.elementKey)) {
                            log_warning(String.Format("Cannot go to specific element with key {0}", lastGotoAction.elementKey.ToString()));
                        }
                        return;
                }                
            }
        }

#endregion experiment_control

        public void destroy_experiment() {

            log_message("Destroy experiment...");

            if (ExVR.Time().is_experiment_started()) {
                stop_experiment();
            }

            // destroy elements
            routines.clean();
            ISIs.clean();

            m_experimentLoaded = false;

            log_message("Experiment destroyed.");
        }
        
    }
}