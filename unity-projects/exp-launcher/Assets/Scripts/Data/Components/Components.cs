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

using static Ex.ExComponent;

namespace Ex{


    public class Components : MonoBehaviour{


        public Dictionary<Category, List<ExComponent>> componentsPerCategory = new Dictionary<Category, List<ExComponent>>();
        public Dictionary<Type, List<ExComponent>> componentsPerType = new Dictionary<Type, List<ExComponent>>();

        public Dictionary<string, Tuple<Category, Pritority>> Names2Info = null;
        public Dictionary<Category, Transform> Category2Transform = null;

        // sort by priority
        List<ExComponent> sortedComponents = new List<ExComponent>();
        List<ExComponent> reverseSortedComponents = new List<ExComponent>();


        private void log_and_add_to_stacktrace(ExComponent component, ExComponent.Function function, bool start, bool log = false, bool timeExp = false, bool timeElem = false) {

            if (log) {
                ExVR.ExpLog().component(component, function, "", "", timeExp, timeElem);
            }
            ExVR.ExpLog().push_to_strackTrace(new ComponentsManagerTrace(component, function, start));
        }

        public bool generate(XML.Components xmlComponents) {

            // create gameobjects and setup components
            List<ExComponent> components = new List<ExComponent>();
            foreach (XML.Component xmlComponent in xmlComponents.Component) {
                
                Type typeComponent = Type.GetType(string.Format("Ex.{0}Component", xmlComponent.Type));
                if (typeComponent == null) {
                    ExVR.Log().error(string.Format("Error when creating component: {0}", xmlComponent.Type));
                    return false;
                }

                var component = (ExComponent)GO.generate_empty_object(xmlComponent.Name, null, true).AddComponent(typeComponent);
                component.setup_component_object(xmlComponent);
                components.Add(component);
                
                if (!componentsPerType.ContainsKey(typeComponent)) {
                    componentsPerType[typeComponent] = new List<ExComponent>();
                }
                componentsPerType[typeComponent].Add(component);

                if (!componentsPerCategory.ContainsKey(component.category)) {
                    componentsPerCategory[component.category] = new List<ExComponent>();
                }
                componentsPerCategory[component.category].Add(component);
            }

            // sort components by priority
            sortedComponents.Clear();
            reverseSortedComponents.Clear();

            foreach (var component in components) {
                if(component.priority == Pritority.Hight) {
                    sortedComponents.Add(component);
                } else if (component.priority == Pritority.Low) {
                    reverseSortedComponents.Add(component);
                }
            }
            foreach (var component in components) {
                if (component.priority == Pritority.Medium) {
                    sortedComponents.Add(component);
                    reverseSortedComponents.Add(component);
                } 
            }
            foreach (var component in components) {
                if (component.priority == Pritority.Low) {
                    sortedComponents.Add(component);
                } else if (component.priority == Pritority.Hight) {
                    reverseSortedComponents.Add(component);
                }
            }

            // initialize components
            ExVR.ExpLog().component_manager(Function.initialize, true);
            foreach (var component in sortedComponents) {

                if (component.is_function_defined(Function.initialize)) {
                    log_and_add_to_stacktrace(component, Function.initialize, true, true);
                }
                    
                if (!component.base_initialize()) {
                    // if one component not initialized, we stop the experiment generation
                    return false;
                }                    
                          
            }
            ExVR.ExpLog().component_manager(Function.initialize, false);

            return true;
        }

        public void set_current_config(Condition condition) {

            foreach (var action in condition.actions) {
                var component = action.component();
                component.set_current_config(condition, action.config(), action.timeline());
            }
        }

        public void action_from_gui(int componentKey, int configKey, string actionName) {

            ExComponent component = get(componentKey);
            if (component == null) {
                return;                
            }

            if (component.is_function_defined(Function.action_from_gui)) {
                log_and_add_to_stacktrace(component, Function.action_from_gui, true);
                component.base_action_from_gui(configKey, actionName);
                log_and_add_to_stacktrace(component, Function.action_from_gui, false);
            }
        }

        public void update_parameter_from_gui(int componentKey, int configKey, XML.Arg arg) {

            ExComponent component = get(componentKey);
            if(component == null) {
                return;
            }

            // update config arg
            foreach (ComponentConfig config in component.configs) {
                if (config.key == configKey) {
                    if (!config.update_from_xml(arg)) {
                        ExVR.Log().error(string.Format("{0} Update argument {1} with value {2} from config {3} failed.", 
                            component.verbose_name(), 
                            arg.Name, 
                            arg.Value,
                            config.name
                        ));
                        return;
                    }
                }
            }

            // call function only if it's the current config
            if(component.currentC != null) {
                if(component.currentC.key == configKey) {
                    if (component.is_function_defined(Function.update_parameter_from_gui)) {
                        log_and_add_to_stacktrace(component, Function.update_parameter_from_gui, true);
                        component.base_update_parameter_from_gui(configKey, arg);
                        log_and_add_to_stacktrace(component, Function.update_parameter_from_gui, false);
                    }
                }
            }
        }

        public void on_gui() {

            foreach (var component in sortedComponents) {
                if (component.is_function_defined(Function.on_gui)) {
                    if (component.is_updating()) {
                        log_and_add_to_stacktrace(component, Function.on_gui, true);
                        component.base_on_gui();
                        log_and_add_to_stacktrace(component, Function.on_gui, false);
                    }
                }
            }
        }

        public void update() {

            UnityEngine.Profiling.Profiler.BeginSample("[ExVR][ComponentsManager] pre_update");
            foreach (var component in sortedComponents) {
                if (component.is_function_defined(Function.pre_update)) {
                    if (component.is_updating()) {
                        log_and_add_to_stacktrace(component, Function.pre_update, true);
                        component.base_pre_update();
                        log_and_add_to_stacktrace(component, Function.pre_update, false);
                    }
                }
            }
            UnityEngine.Profiling.Profiler.EndSample();

            UnityEngine.Profiling.Profiler.BeginSample("[ExVR][ComponentsManager] update");
            foreach (var component in sortedComponents) {
                if (component.is_function_defined(Function.update)) {
                    if (component.is_updating()) {
                        log_and_add_to_stacktrace(component, Function.update, true);
                        component.base_update();
                        log_and_add_to_stacktrace(component, Function.update, false);
                    }
                }
            }
            UnityEngine.Profiling.Profiler.EndSample();

            UnityEngine.Profiling.Profiler.BeginSample("[ExVR][ComponentsManager] post_update");
            foreach (var component in sortedComponents) {
                if (component.is_function_defined(Function.post_update)) {
                    if (component.is_updating()) {
                        log_and_add_to_stacktrace(component, Function.post_update, true);
                        component.base_post_update();
                        log_and_add_to_stacktrace(component, Function.post_update, false);
                    }
                }
            }
            UnityEngine.Profiling.Profiler.EndSample();
        }

        public void play() {

            ExVR.ExpLog().component_manager(Function.play, true);
            foreach (var component in sortedComponents) {
                if (component.is_function_defined(Function.play)) {
                    if (component.is_updating()) {
                        log_and_add_to_stacktrace(component, Function.play, true, true, true, true);
                        component.base_play();
                        log_and_add_to_stacktrace(component, Function.play, false, true, true, true);
                    }
                }
            }
            ExVR.ExpLog().component_manager(Function.play, false);
        }

        public void pause() {

            ExVR.ExpLog().component_manager(Function.pause, true);
            foreach (var component in sortedComponents) {
                if (component.is_function_defined(Function.pause)) {
                    if (component.is_updating()) {
                        log_and_add_to_stacktrace(component, Function.pause, true, true, true, true);
                        component.base_pause();
                        log_and_add_to_stacktrace(component, Function.pause, false, true, true, true);
                    }
                }
            }
            ExVR.ExpLog().component_manager(Function.pause, false);
        }

        public void start_experiment() {
                        
            ExVR.ExpLog().component_manager(Function.start_experiment, true);

            foreach (var component in sortedComponents) {

                // reset states
                component.currentCondition  = null;
                component.currentRoutine    = null;
                component.currentTimeline   = null;
                component.currentC          = null;

                if (component.is_function_defined(Function.start_experiment)) {
                    log_and_add_to_stacktrace(component, Function.start_experiment, true, true);
                    component.base_start_experiment();
                    log_and_add_to_stacktrace(component, Function.start_experiment, false, true);
                }
            }

            ExVR.ExpLog().component_manager(Function.start_experiment, false);
        }

        public void start_routine(Condition condition) {

            ExVR.ExpLog().component_manager(Function.start_routine, true);
            foreach (var action in condition.actions) {

                var component = action.component();
                if (component.is_function_defined(Function.start_routine)) {
                    log_and_add_to_stacktrace(component, Function.start_routine, true, true);
                }

                component.base_start_routine();

                if (component.is_function_defined(Function.start_routine)) {
                    log_and_add_to_stacktrace(component, Function.start_routine, false, true);
                }   
            }
            ExVR.ExpLog().component_manager(Function.start_routine, false);
        }

        public void stop_routine(Condition condition) {

            ExVR.ExpLog().component_manager(Function.stop_routine, true);
            foreach (var action in condition.reverseOrderActions) {

                var component = action.component();
                if (component.is_function_defined(Function.stop_routine)) {
                    log_and_add_to_stacktrace(component, Function.stop_routine, true, true);
                }

                component.base_stop_routine();

                if (component.is_function_defined(Function.stop_routine)) {
                    log_and_add_to_stacktrace(component, Function.stop_routine, false, true);
                }
            }
            ExVR.ExpLog().component_manager(Function.stop_routine, false);
        }

        public void stop_experiment() {

            ExVR.ExpLog().component_manager(Function.stop_experiment, true);
            foreach (var component in reverseSortedComponents) {

                if (component.is_function_defined(Function.stop_experiment)) {
                    log_and_add_to_stacktrace(component, Function.stop_experiment, true, true, true, true);
                }

                component.base_stop_experiment();

                if (component.is_function_defined(Function.stop_experiment)) {                    
                    log_and_add_to_stacktrace(component, Function.stop_experiment, false, true, true, true);
                }

                // reset states
                component.currentCondition = null;
                component.currentRoutine = null;
                component.currentTimeline = null;
                component.currentC = null;
            }
            ExVR.ExpLog().component_manager(Function.stop_experiment, false);
        }
        public void close(ExComponent componentToClose) {

            if (!componentToClose.is_closed()) {
                ExVR.Log().message(string.Format("Close component {0} with key {1}.", componentToClose.name, componentToClose.key));
                set_component_states(componentToClose, false, false);
                componentToClose.set_closed_flag(true);                
            } else {
                ExVR.Log().error(string.Format("Component {0} with key {1} already closed.", componentToClose.name, componentToClose.key));
            }            
        }

        public void clean() {
            
            ExVR.ExpLog().component_manager(Function.clean, true);
            foreach (var component in reverseSortedComponents) {

                if (component.is_function_defined(Function.clean)) {
                    ExVR.ExpLog().component(component, Function.clean, "", "", false, false);
                    component.base_clean();
                }

                // destroy gameobject
                Destroy(component.gameObject);
            }
            ExVR.ExpLog().component_manager(Function.clean, false);

            // clean container
            sortedComponents.Clear();
            componentsPerType.Clear();
            componentsPerCategory.Clear();
        }

        public void set_components_states(Condition condition, double time) {

            // component inside condition
            HashSet<int> componentInsideCondition = new HashSet<int>();
            foreach (var action in condition.actions) {

                var component = action.component();
                componentInsideCondition.Add(component.key);

                bool doUpdate   = action.timeline().inside_update_intervals(time);
                bool visibility = action.timeline().inside_visibility_intervals(time);
                set_component_states(component, doUpdate, visibility);
            }

            // component not inside condition
            foreach(var component in reverseSortedComponents) {
                if (!componentInsideCondition.Contains(component.key)) {
                    set_component_states(component, false, false);
                }                
            }
        }

        public void set_every_component_states_to_false() {
            // disable/hide all components if necessary with login
            foreach(var component in reverseSortedComponents) {
                set_component_states(component, false, false);
            }
        }

        public void disable() {

            // force disable/hide all component without logging
            foreach (var component in reverseSortedComponents) {
                component.base_set_update_state(false);
                component.base_set_visibility(false);
            }
        }

        private void set_component_states(ExComponent component, bool doUpdate, bool visibility, bool log = true) {

            if (component.is_closed()) {
                return;
            }

            if (doUpdate != component.is_updating()) {

                if (component.is_started() && log) {
                    ExVR.ExpLog().component(component, Function.set_update_state, component.currentC.name, " -> U=" + doUpdate, true, true);
                }

                if (log && component.is_function_defined(Function.set_update_state)) {
                    log_and_add_to_stacktrace(component, Function.set_update_state, true);
                }

                component.base_set_update_state(doUpdate);

                if (log && component.is_function_defined(Function.set_update_state)) {
                    log_and_add_to_stacktrace(component, Function.set_update_state, false);
                }                
            }
            
            if (visibility != component.is_visible()) {
       
                if (component.is_started() && log) {
                    ExVR.ExpLog().component(component, Function.set_visibility, component.currentC.name, " -> U=" + visibility, true, true);
                }

                if (log && component.is_function_defined(Function.set_visibility)) {
                    log_and_add_to_stacktrace(component, Function.set_visibility, true);
                }

                component.base_set_visibility(visibility);

                if (log && component.is_function_defined(Function.set_visibility)) {
                    log_and_add_to_stacktrace(component, Function.set_visibility, false);
                }
            }
        }

        public void initialize() {

            Names2Info = new Dictionary<string, Tuple<Category, Pritority>>();
            // audio
            Names2Info["Ex.MicrophoneComponent"]            = new Tuple<Category, Pritority>(Category.Audio,       Pritority.Medium);
            Names2Info["Ex.AudioSourceComponent"]           = new Tuple<Category, Pritority>(Category.Audio,       Pritority.Medium);
            // image
            // input
            Names2Info["Ex.JoypadComponent"]                = new Tuple<Category, Pritority>(Category.Input,       Pritority.Hight);
            Names2Info["Ex.MouseComponent"]                 = new Tuple<Category, Pritority>(Category.Input,       Pritority.Hight);
            Names2Info["Ex.KeyboardComponent"]              = new Tuple<Category, Pritority>(Category.Input,       Pritority.Hight);
            // network
            Names2Info["Ex.UdpReaderComponent"]             = new Tuple<Category, Pritority>(Category.Network,     Pritority.Hight);
            Names2Info["Ex.UdpWriterComponent"]             = new Tuple<Category, Pritority>(Category.Network,     Pritority.Hight);
            Names2Info["Ex.SerialPortWriterComponent"]      = new Tuple<Category, Pritority>(Category.Network,     Pritority.Hight);
            Names2Info["Ex.ParallelPortWriterComponent"]    = new Tuple<Category, Pritority>(Category.Network,     Pritority.Hight);
            // output
            Names2Info["Ex.LoggerComponent"]                = new Tuple<Category, Pritority>(Category.Output,      Pritority.Low);
            Names2Info["Ex.LoggerConditionComponent"]       = new Tuple<Category, Pritority>(Category.Output,      Pritority.Low);
            Names2Info["Ex.LoggerColumnsComponent"]         = new Tuple<Category, Pritority>(Category.Output,      Pritority.Low);            
            // camera
            Names2Info["Ex.CameraTargetComponent"]          = new Tuple<Category, Pritority>(Category.Camera,      Pritority.Low);
            Names2Info["Ex.CameraTrajectoryComponent"]      = new Tuple<Category, Pritority>(Category.Camera,      Pritority.Low);
            Names2Info["Ex.CameraTrajectoryFileComponent"]  = new Tuple<Category, Pritority>(Category.Camera,      Pritority.Low);
            Names2Info["Ex.CameraComponent"]                = new Tuple<Category, Pritority>(Category.Camera,      Pritority.Low);
            // scene
            Names2Info["Ex.AssetBundleComponent"]           = new Tuple<Category, Pritority>(Category.Scene,       Pritority.Hight);
            Names2Info["Ex.MultiABComponent"]               = new Tuple<Category, Pritority>(Category.Scene,       Pritority.Hight);            
            Names2Info["Ex.FallingSpheresComponent"]        = new Tuple<Category, Pritority>(Category.Scene,       Pritority.Medium);
            Names2Info["Ex.MirrorComponent"]                = new Tuple<Category, Pritority>(Category.Scene,       Pritority.Medium);            
            Names2Info["Ex.FlashingDotComponent"]           = new Tuple<Category, Pritority>(Category.Scene,       Pritority.Medium);
            Names2Info["Ex.MRIComponent"]                   = new Tuple<Category, Pritority>(Category.Scene,       Pritority.Medium);
            // script
            Names2Info["Ex.CSharpScriptComponent"]          = new Tuple<Category, Pritority>(Category.Script,      Pritority.Low);
            Names2Info["Ex.PythonScriptComponent"]          = new Tuple<Category, Pritority>(Category.Script,      Pritority.Medium);
            // UI
            Names2Info["Ex.SliderUIComponent"]              = new Tuple<Category, Pritority>(Category.UI,          Pritority.Medium);
            // video
            Names2Info["Ex.VideoFileComponent"]             = new Tuple<Category, Pritority>(Category.Video,       Pritority.Medium);
            Names2Info["Ex.VideoFileCameraViewerComponent"] = new Tuple<Category, Pritority>(Category.Video,       Pritority.Medium);            
            Names2Info["Ex.WebcamComponent"]                = new Tuple<Category, Pritority>(Category.Video,       Pritority.Medium);            
            Names2Info["Ex.VideoSaverComponent"]            = new Tuple<Category, Pritority>(Category.Video,       Pritority.Medium);
            // tracking
            Names2Info["Ex.DuoTrackingComponent"]           = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Medium);
            Names2Info["Ex.SceneScanerComponent"]           = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Medium);
            Names2Info["Ex.LeapMotionComponent"]            = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Hight);
            Names2Info["Ex.LeapMotionTrackingComponent"]    = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Medium);
            Names2Info["Ex.LeapMotionArmsDisplayComponent"] = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Medium);
            Names2Info["Ex.BiopacComponent"]                = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Hight);            
            Names2Info["Ex.TheraTrainerTrackingComponent"]  = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Medium);
            Names2Info["Ex.TheraTrainerPlatformComponent"]  = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Medium);
            Names2Info["Ex.KinectManagerComponent"]         = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Hight);
            Names2Info["Ex.KinectBodyTrackingComponent"]    = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Hight);
            Names2Info["Ex.OptitrackComponent"]             = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Hight);
            Names2Info["Ex.AttachObjectToHandComponent"]    = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Medium);
            Names2Info["Ex.QualisysTrackingComponent"]      = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Hight);
            Names2Info["Ex.SoncebozSGComponent"]            = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Hight);
            Names2Info["Ex.FOPRobotComponent"]              = new Tuple<Category, Pritority>(Category.Tracking,    Pritority.Hight);
            // model
            Names2Info["Ex.CubeComponent"]                  = new Tuple<Category, Pritority>(Category.Model,       Pritority.Medium);
            Names2Info["Ex.SphereComponent"]                = new Tuple<Category, Pritority>(Category.Model,       Pritority.Medium);
            Names2Info["Ex.TorusComponent"]                 = new Tuple<Category, Pritority>(Category.Model,       Pritority.Medium);
            Names2Info["Ex.LinesComponent"]                 = new Tuple<Category, Pritority>(Category.Model,       Pritority.Medium);
            Names2Info["Ex.CylinderComponent"]              = new Tuple<Category, Pritority>(Category.Model,       Pritority.Medium);
            Names2Info["Ex.LandmarkComponent"]              = new Tuple<Category, Pritority>(Category.Model,       Pritority.Medium);            
            // cloud
            Names2Info["Ex.CloudComponent"]                 = new Tuple<Category, Pritority>(Category.Cloud,       Pritority.Medium);
            Names2Info["Ex.ScanerVideoComponent"]           = new Tuple<Category, Pritority>(Category.Cloud,       Pritority.Medium);
            // avatar
            Names2Info["Ex.HumanoidControllerComponent"]    = new Tuple<Category, Pritority>(Category.Avatar,      Pritority.Low);
            // interaction
            Names2Info["Ex.MarkToCleanComponent"]           = new Tuple<Category, Pritority>(Category.Interaction, Pritority.Medium);
            Names2Info["Ex.TargetToGrabComponent"]          = new Tuple<Category, Pritority>(Category.Interaction, Pritority.Medium);
            // environment
            Names2Info["Ex.SkyComponent"]                   = new Tuple<Category, Pritority>(Category.Environment, Pritority.Hight);
            // resource
            Names2Info["Ex.ImageResourceComponent"]         = new Tuple<Category, Pritority>(Category.Resource, Pritority.Hight);
            Names2Info["Ex.PlotResourceComponent"]          = new Tuple<Category, Pritority>(Category.Resource, Pritority.Hight);
            Names2Info["Ex.TextResourceComponent"]          = new Tuple<Category, Pritority>(Category.Resource, Pritority.Hight);
            Names2Info["Ex.VideoResourceComponent"]         = new Tuple<Category, Pritority>(Category.Resource, Pritority.Hight);
            Names2Info["Ex.AudioResourceComponent"]         = new Tuple<Category, Pritority>(Category.Resource, Pritority.Hight);
            Names2Info["Ex.DirectoryResourceComponent"]     = new Tuple<Category, Pritority>(Category.Resource, Pritority.Hight);            
            // viewer
            Names2Info["Ex.FixationCrossViewerComponent"]   = new Tuple<Category, Pritority>(Category.Viewer, Pritority.Low);
            Names2Info["Ex.ImageViewerComponent"]           = new Tuple<Category, Pritority>(Category.Viewer, Pritority.Low);
            Names2Info["Ex.TextViewerComponent"]            = new Tuple<Category, Pritority>(Category.Viewer, Pritority.Low);
            Names2Info["Ex.WebcamViewerComponent"]          = new Tuple<Category, Pritority>(Category.Viewer, Pritority.Low);
            Names2Info["Ex.FovSimulatorComponent"]          = new Tuple<Category, Pritority>(Category.Viewer, Pritority.Hight);
            Names2Info["Ex.BlendFadeViewerComponent"]       = new Tuple<Category, Pritority>(Category.Viewer, Pritority.Hight);
            

            Transform top = ExVR.GO().Components.transform;
            Category2Transform = new Dictionary<Category, Transform>();
            Category2Transform[Category.Audio]         = top.Find("[C:Audio]");
            Category2Transform[Category.Resource]      = top.Find("[C:Resource]");
            Category2Transform[Category.Image]         = top.Find("[C:Image]");
            Category2Transform[Category.Input]         = top.Find("[C:Input]");
            Category2Transform[Category.Network]       = top.Find("[C:Network]");
            Category2Transform[Category.Output]        = top.Find("[C:Output]");
            Category2Transform[Category.Scene]         = top.Find("[C:Scene]");
            Category2Transform[Category.Script]        = top.Find("[C:Script]");
            Category2Transform[Category.Environment]   = top.Find("[C:Environment]");
            Category2Transform[Category.UI]            = top.Find("[C:UI]");
            Category2Transform[Category.Video]         = top.Find("[C:Video]");
            Category2Transform[Category.Tracking]      = top.Find("[C:Tracking]");
            Category2Transform[Category.Text]          = top.Find("[C:Text]");
            Category2Transform[Category.Model]         = top.Find("[C:Model]");
            Category2Transform[Category.Avatar]        = top.Find("[C:Avatar]");
            Category2Transform[Category.Interaction]   = top.Find("[C:Interaction]");
            Category2Transform[Category.Camera]        = top.Find("[C:Camera]");
            Category2Transform[Category.Settings]      = top.Find("[C:Settings]");
            Category2Transform[Category.Cloud]         = top.Find("[C:Cloud]");
            Category2Transform[Category.Viewer]        = top.Find("[C:Viewer]");
        }

        public ExComponent get(int componentKey) {

            foreach (var component in sortedComponents) {
                if (component.key == componentKey) {
                    return component;
                }
            }
            return null;
        }

        public ExComponent get(string componentName) {

            foreach (var component in sortedComponents) {
                if (component.name == componentName) {
                    return component;
                }
            }
            return null;
        }

        public int count() {
            return sortedComponents.Count;
        }

        public List<ExComponent> get_all() {

            List<ExComponent> componentsList = new List<ExComponent>(count());
            foreach (var component in sortedComponents) {
                componentsList.Add(component);
            }
            return componentsList;
        }

        public List<ExComponent> get_all(ExComponent.Category type) {

            List<ExComponent> componentsWithType = new List<ExComponent>();
            foreach (var component in sortedComponents) {
                if (component.category == type) {
                    componentsWithType.Add(component);
                }
            }

            return componentsWithType;
        }

        public T get<T>(string componentName) where T : ExComponent {
            return (T)get(componentName);
        }

        public ExComponent get(string componentName, string componentTypeStr) {
            string fullTypeStr = string.Concat("Ex.",componentTypeStr);
            foreach (var component in sortedComponents) {
                if(component.GetType().ToString() == fullTypeStr) {
                    if(component.name == componentName) {
                        return component;
                    }
                }
            }
            return null;
        }

        public List<T> get_all<T>() where T : ExComponent {

            List<T> components = new List<T>();
            foreach (ExComponent component in get_all()) {
                if (component.GetComponent<T>()) {
                    components.Add((T)component);
                }
            }

            return components;
        }
    }
}
