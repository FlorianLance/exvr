/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Text;
using System.Collections.Generic;

// unity
using UnityEngine;
using UnityEngine.UI;

namespace Ex{
    public class ExComponent : MonoBehaviour{

        public enum Function{
            initialize,
            start_experiment,
            start_routine,
            set_update_state,
            set_visibility,
            update_parameter_from_gui,
            update_from_current_config,
            action_from_gui,
            pre_update,
            update,
            post_update,
            play,
            pause,
            stop_routine,
            stop_experiment,
            clean,
            slot1,
            slot2,
            slot3,
            slot4,
            slot5,
            on_gui,
            undefined,
            not_defined_in_component
        }

        public enum Category {
            Audio,
            Avatar,
            Camera,
            Environment,
            Image,
            Input,
            Interaction,                        
            Model,
            Network,
            Output,
            Resource,
            Script,
            Scene,
            Settings,
            Text,
            UI,
            Tracking,
            Video,
            Cloud,
            Viewer,
            Undefined
        };

        public enum Pritority { Low, Medium, Hight};
        public enum Reserved {Public, Closed, LNCO};

        public int key = -1; // id component
        public string keyStr;
        public Category category = Category.Undefined;
        public Pritority priority = Pritority.Medium;
        public Function currentFunction = Function.undefined;
        public Dictionary<Function, bool> functionsDefined = null;
        protected bool catchExceptions = false;

        public TimeLine currentTimeline = null;
        public Condition currentCondition = null;
        public Routine currentRoutine = null;

        // events
        protected Events.Connections m_events = null;
        public Events.Connections events() { return m_events; }

        public bool is_function_defined(Function function) {
            return functionsDefined[function];
        }

        protected void add_signal(string name){
            m_events.add_signal(name);
        }

        protected void add_slot(string name, System.Action<object> action) {
            m_events.add_slot(name, action);
        }

        public void invoke_signal(string name, object arg = null) {
            m_events.invoke_signal(name, arg);
        }

        // configs
        public ComponentInitConfig initC = null;
        public ComponentConfig currentC = null; // current config
        public List<ComponentConfig> configs = null;

        // states
        protected bool m_visibility = false; // is visible ?
        protected bool m_updating = false;   // call update function ?
        private bool m_started = false;      // has associated routine started ?
        private bool m_closed = false;       // is closed ? (cannot be enabled anymore until next routine)

        public void set_closed_flag(bool closed) {
            m_closed = closed;
        }

        public void close() {
            ExVR.Components().close(this);
        }

        public bool is_started() {
            return m_started;
        }

        public bool is_visible() {
            return m_visibility;
        }

        public bool is_updating() {
            return m_updating;
        }

        public bool is_closed() {
            return m_closed;
        }

        // Name of the component
        public string component_name() {
            return name;
        }

        public string verbose_name() {

            StringBuilder builder = new StringBuilder();
            builder.AppendFormat(" [From component: [{0}]({1})([{2}])", name, this.GetType().ToString(), currentFunction.ToString());
            if(currentRoutine != null) {
                builder.AppendFormat(", from routine: [{0}] with condition: [{1}]", currentRoutine.name, currentCondition.name);
            }
            builder.AppendFormat(" at time {0}ms ({1}ms)]", ellapsed_time_routine_ms().ToString(), ellapsed_time_exp_ms().ToString());
            return builder.ToString();
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

                lineNb   = frame.GetFileLineNumber();
                columnNb = frame.GetFileColumnNumber();
                fileName = frame.GetFileName();
            }

            var builder = new StringBuilder();
            builder.Append("[EX_COMPONENT ERROR]");
            if(fileName != null) {
                builder.AppendFormat("  [LOCATION] from class [{0}] in function [{1}] in file [{2}] at line ({3}) and column ({4})\n",
                    className, functionName, fileName, lineNb.ToString(), columnNb.ToString());
            } else {
                builder.AppendFormat("  [LOCATION] from class [{0}] in function [{1}]\n",
                    className, functionName);
            }
            builder.AppendFormat("  [MESSAGE] {0}", e.Message);
            log_error(builder.ToString(), true);            
        }

        protected void send_infos_to_gui_init_config(string id, string infos) {
            ExVR.Network().gui_ipc().send_component_infos_to_GUI(keyStr, initC.keyStr, id, infos);
        }
        protected void send_infos_to_gui_current_config(string id, string infos) {
            ExVR.Network().gui_ipc().send_component_infos_to_GUI(keyStr, currentC.keyStr, id, infos);
        }

        public void add_message_to_stack_trace(string message) {
            ExVR.Events().stacktrace.ComponentTrace.Invoke(this, message);
        }

        public void log_message(string message, bool verbose = false) {
            if (verbose) {
                ExVR.Log().message(string.Concat(message, verbose_name()), true);
            } else {
                ExVR.Log().message(message, false);
            }            
        }

        public void log_warning(string warning, bool verbose = true) {
            if (verbose) {
                ExVR.Log().warning(string.Concat(warning, verbose_name()), true);
            } else {
                ExVR.Log().warning(warning, false);
            }
        }

        public void log_error(string error, bool verbose = true) {
            if (verbose) {
                ExVR.Log().error(string.Concat(error, verbose_name()), true);
            } else {
                ExVR.Log().error(error, false);
            }
        }

        static public double previous_frame_duration_ms() {
            return ExVR.Time().previous_frame_duration_ms();
        }

        static public double frame_start_time_since_experiment_ms() {
            return ExVR.Time().frame_start_time_since_experiment_ms();
        }

        static public long frame_id() {
            return ExVR.Time().frame_id();
        }

        static public double ellapsed_time_exp_ms() {
            return ExVR.Time().ellapsed_time_exp_ms();
        }

        static public double ellapsed_time_routine_ms() {
            return ExVR.Time().ellapsed_time_element_ms();
        }

        static public double ellapsed_time_frame_ms() {
            return ExVR.Time().ellapsed_time_frame_ms();
        }

        static public List<ExComponent> get_all(string category) {
            Category type;
            if (System.Enum.TryParse(category, false, out type)) {
                return get_all(type);
            }
            return new List<ExComponent>();
        }

        static public List<ExComponent> get_all(Category type) {
            return ExVR.Components().get_all(type);
        }

        static public ExComponent get(int key) {
            return ExVR.Components().get(key);
        }

        static public ExComponent get(string name) {
            return ExVR.Components().get(name);
        }

        static public List<T> get<T>() where T : ExComponent {
            return ExVR.Components().get_all<T>();
        }

        static public T get<T>(string name) where T : ExComponent {
            return ExVR.Components().get<T>(name);
        }        

        // ######### TEST

        public static void set_component_config<T>(string routineName, string conditionName, string componentName, string configToUse) where T : ExComponent {

            // parse everything just in case there is routines/conditions/components/configs with the same names
            foreach(var routine in ExVR.Routines().get_all()) {
                if(routine.name == routineName) {
                    foreach(var condition in routine.get_conditions()) {
                        if(condition.name == conditionName) {
                            foreach(var action in condition.actions) {
                                if(action.component().name == componentName) {
                                    //action.component().configs;
                                    foreach(var config in action.component().configs) {
                                        if(config.name == configToUse) {

                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }                        
        }

        // ######### END TEST

        // Send an event for moving to the next flow element
        public static void next() {
            ExVR.Events().command.NextElementEvent.Invoke();
        }

        // Send an event for moving to the previous flow element
        public static void previous() {
            ExVR.Events().command.PreviousElementEvent.Invoke();
        }

        public static void pause_experiment() {
            ExVR.Events().command.PauseExperimentEvent.Invoke();
        }

        public static void force_stop_experiment() {
            ExVR.Events().command.StopExperimentEvent.Invoke();            
        }        

        public static void next_element_with_name(string elementName){
            ExVR.Events().command.NextElementWithNameEvent.Invoke(elementName);
        }

        public static void previous_element_with_name(string elementName) {
            ExVR.Events().command.PreviousElementWithNameEvent.Invoke(elementName);
        }

        public static void next_element_with_condition(string elementName) {
            ExVR.Events().command.NextElementWithConditionEvent.Invoke(elementName);
        }

        public static void previous_element_with_condition(string elementName) {
            ExVR.Events().command.PreviousElementWithConditionEvent.Invoke(elementName);
        }

        public static void modify_routine_action_config(string routineName, string conditionName, string componentName, string newConfigName) {
            ExVR.Events().command.ModifyRoutineActionConfigEvent.Invoke(routineName, conditionName, componentName, newConfigName);
        }

        public ComponentInitConfig init_config() {
            return initC;
        }

        public ComponentConfig current_config() {
            if(currentC == null) {
                log_error("No current config set, check if component has been added to this condition.");
            }
            return currentC;
        }
        public ComponentConfig get_config(string configName) {

            foreach (ComponentConfig config in configs) {
                if (config.name == configName) {
                    return config;
                }
            }
            return null;
        }

        public ComponentConfig get_config(int configKey) {

            foreach (ComponentConfig config in configs) {
                if (config.key == configKey) {
                    return config;
                }
            }
            return null;
        }

        // setup component, parent, layer, configurations...
        public void setup_component_object(XML.Component xmlComponent) {

            // set members
            gameObject.name = xmlComponent.Name;
            key             = xmlComponent.Key;
            keyStr = Converter.to_string(xmlComponent.Key);
            catchExceptions = ExVR.GuiSettings().catchComponentsExceptions;

            string typeStr = string.Format("Ex.{0}Component", xmlComponent.Type);
            if (Components.Names2Info.ContainsKey(typeStr)) {
                category = Components.Names2Info[typeStr].category;
                priority = Components.Names2Info[typeStr].priority;
            } else {
                category = Category.Scene;
                log_error("Component doesn't belong to a category.");
            }
            tag = string.Format("{0}Component", category.ToString());

            // set parent
            if (Ex.ExVR.Components().Category2Transform.ContainsKey(category)) {
                transform.SetParent(Ex.ExVR.Components().Category2Transform[category]);
            } else {
                log_error( string.Format("GameObject type {0} is not available in components hierarchy.", category.ToString()));
            }

            var parentConfigs = new GameObject("Configs");            
            parentConfigs.transform.SetParent(transform);

            // init config
            var initConfigGo = new GameObject();
            initConfigGo.transform.SetParent(parentConfigs.transform);
            initC = initConfigGo.AddComponent<ComponentInitConfig>();
            initC.initialize(xmlComponent.InitConfig);           

            // conditions config
            configs = new List<ComponentConfig>(xmlComponent.Configs.Config.Count);
            foreach (XML.Config xmlConfig in xmlComponent.Configs.Config) {

                var configGo = new GameObject();
                configGo.transform.SetParent(parentConfigs.transform);

                var componentConfig = configGo.AddComponent<ComponentConfig>();
                componentConfig.initialize(xmlConfig);
                configs.Add(componentConfig);
            }

            // look for defined functions in child class
            Type derivedType = this.GetType();
            functionsDefined = new Dictionary<Function, bool>();
            // # private
            var flagPrivate = System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic;
            functionsDefined[Function.initialize] = (derivedType.GetMethod("initialize", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.start_experiment] = (derivedType.GetMethod("start_experiment", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.start_routine] = (derivedType.GetMethod("start_routine", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.set_update_state] = (derivedType.GetMethod("set_update_state", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.set_visibility] = (derivedType.GetMethod("set_visibility", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.update_parameter_from_gui] = (derivedType.GetMethod("update_parameter_from_gui", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.action_from_gui] = (derivedType.GetMethod("action_from_gui", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.pre_update] = (derivedType.GetMethod("pre_update", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.update] = (derivedType.GetMethod("update", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.post_update] = (derivedType.GetMethod("post_update", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.stop_routine] = (derivedType.GetMethod("stop_routine", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.stop_experiment] = (derivedType.GetMethod("stop_experiment", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.clean] = (derivedType.GetMethod("clean", flagPrivate).DeclaringType == derivedType);
            functionsDefined[Function.on_gui] = (derivedType.GetMethod("on_gui", flagPrivate).DeclaringType == derivedType);
            // # public
            var flagPublic = System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.Public;
            functionsDefined[Function.play] = (derivedType.GetMethod("play", flagPublic).DeclaringType == derivedType);
            functionsDefined[Function.pause] = (derivedType.GetMethod("pause", flagPublic).DeclaringType == derivedType);
            functionsDefined[Function.update_from_current_config] = (derivedType.GetMethod("update_from_current_config", flagPublic).DeclaringType == derivedType);

            // init events
            m_events = new Events.Connections(name);
        }

        public void set_current_config(Condition condition, ComponentConfig config, TimeLine timeline) {

            currentCondition = condition;
            currentRoutine = currentCondition.parent_routine();
            currentTimeline = timeline;
            currentC = config;

            // select eye to render if parameter exists
            int layer = Layers.Default;
            if (currentC.has("eye_to_render")) {
                string renderEyes = currentC.get<string>("eye_to_render");
                if (renderEyes == "Left eye") {
                    layer = Layers.LeftEye;
                } else if (renderEyes == "Right eye") {
                    layer = Layers.RightEye;
                }
            }
            gameObject.layer = layer;
            foreach (Transform tr in gameObject.GetComponentInChildren<Transform>(true)) {
                tr.gameObject.layer = layer;
            }
        }

        // Initialize the component, called only once at the beginning of the experiment, will call child initialize
        public virtual bool base_initialize() {            

            currentFunction = Function.initialize;
            try {
                if (!initialize()) {
                    log_error("Initialization failed. ");
                    return false;
                }
            } catch (Exception e) {
                display_exception(e);
                return false;
            }

            return true; 
        }

        // This function is called only once at the beggining of an experiment 
        public void base_start_experiment() {
            
            currentFunction = Function.start_experiment;

            if (catchExceptions) {
                try {
                    start_experiment();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                start_experiment();
            }      
        }

        // This function is called only once at the end of an experiment 
        public void base_stop_experiment() {
    
            currentFunction = Function.stop_experiment;
            if (catchExceptions) {
                try {
                    stop_experiment();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                stop_experiment();
            }

            // disable the closing state
            m_closed = false;
        }

        // Start the component if inside current routine, called every time at the timeline beggining of an associated routine, will call child start      
        public void base_start_routine() {

            m_started = true;
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

        // Stop the component, called every time at the timeline end of an associated routine, will call child stop
        public void base_stop_routine() {

            m_started = false;
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

        // Called several times per frame if component inside timeline
        public void base_on_gui() {

            currentFunction = Function.on_gui;
            if (catchExceptions) {
                try {
                    on_gui();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                on_gui();
            }
        }

        // Called at every frame if component inside timeline, will call child pre_update
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

        // Called at every frame if component inside timeline, will call child update
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

        // Called at every frame if component inside timeline, will call child post_update
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

        public void base_clean() {

            currentFunction = Function.clean;
            if (catchExceptions) {
                try {
                    clean();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                clean();
            }
        }

        // Play command from the GUI, will resumed if on pause, will call child play
        public void base_play() {

            currentFunction = Function.play;
            if (catchExceptions) {
                try {
                    play();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                play();
            }
        }

        // Pause command from the GUI, will pause if on play, will call child pause
        public void base_pause() {

            currentFunction = Function.pause;
            if (catchExceptions) {
                try {
                    pause();
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                pause();
            }
        }

        // Update the parameters from GUI
        public void base_update_parameter_from_gui(int configKey, XML.Arg arg) {

            currentFunction = Function.update_parameter_from_gui;
            if (catchExceptions) {
                try {
                    update_parameter_from_gui(arg);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                update_parameter_from_gui(arg);
            }                
        }

        public void base_action_from_gui(int configKey, string action) {

            currentFunction = Function.action_from_gui;
            if (initC.key == configKey) {

                if (catchExceptions) {
                    try {
                        action_from_gui(true, action);
                    } catch (Exception e) {
                        display_exception(e);
                    }
                } else {
                    action_from_gui(true, action);
                }

            } else {
                if (currentC != null) {
                    if (currentC.key == configKey) {

                        if (catchExceptions) {
                            try {
                                action_from_gui(false, action);
                            } catch (Exception e) {
                                display_exception(e);
                            }
                        } else {
                            action_from_gui(false, action);
                        }
                    }
                }
            }
        }

        public void base_set_visibility(bool visibility) {
            
            m_visibility = visibility;
            currentFunction = Function.set_visibility;

            if (catchExceptions) {
                try {
                    set_visibility(m_visibility);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                set_visibility(m_visibility);
            }
        }

        public void base_set_update_state(bool doUpdate) {

            m_updating = doUpdate;

            currentFunction = Function.set_update_state;                   
            if (catchExceptions) {
                try {
                    set_update_state(m_updating);
                } catch (Exception e) {
                    display_exception(e);
                }
            } else {
                set_update_state(m_updating);
            }
        }       
        
        protected virtual bool initialize() {
            return true; 
        }
        protected virtual void start_experiment() {
        }
        protected virtual void stop_experiment() {
        }
        protected virtual void start_routine() {
        }
        protected virtual void stop_routine() {
        }
        protected virtual void on_gui() {
        }
        protected virtual void pre_update() {
        }
        protected virtual void update() {
        }
        protected virtual void post_update() {
        }
        public virtual void update_from_current_config() {
        }
        protected virtual void update_parameter_from_gui(XML.Arg arg) {
        }
        protected virtual void action_from_gui(bool initConfig, string action) {
        }
        protected virtual void set_visibility(bool visible) {
        }
        protected virtual void set_update_state(bool doUpdate) {
        }        
        public virtual void play() {
        }
        public virtual void pause() {
        }
        protected virtual void clean() {
        }
    }

    public class CanvasWorldSpaceComponent : ExComponent{

        public override bool base_initialize() {

            var canvas = gameObject.AddComponent<Canvas>();
            gameObject.AddComponent<CanvasScaler>();
            gameObject.AddComponent<GraphicRaycaster>();
            canvas.renderMode = RenderMode.WorldSpace;

            return base.base_initialize();
        }
    }
}