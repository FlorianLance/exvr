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


//#if UNITY_EDITOR
//using UnityEditor;
//namespace Ex{

//    [CustomEditor(typeof(Components))]
//    public class ComponentsEditor : Editor{

//        public override bool RequiresConstantRepaint() {
//            return true;
//        }

//        public override void OnInspectorGUI() {

//            base.OnInspectorGUI();

//            if (!Application.isPlaying) {
//                return;
//            }

//            //EditorGUILayout.LabelField("Current element:");
//            //var currentElementInfo = ExVR.Schreduler().current_element_info();
//            //if (currentElementInfo != null) {
//            //    if (currentElementInfo.type() == FlowElement.FlowElementType.Routine) {

//            //        var routineInfo = (RoutineInfo)currentElementInfo;
//            //        var routine = (Routine)routineInfo.element;
//            //        if (routine != null) {
//            //            EditorGUILayout.LabelField("[Routine] with id " + (currentElementInfo.key()).ToString());
//            //            EditorGUILayout.ObjectField(routine, typeof(Routine), true);

//            //            var condition = routine.current_condition();
//            //            if (condition != null) {
//            //                EditorGUILayout.LabelField("With condition:");
//            //                EditorGUILayout.ObjectField(condition, typeof(Condition), true);
//            //            } else {
//            //                EditorGUILayout.LabelField("...");
//            //            }

//            //        } else {
//            //            EditorGUILayout.LabelField("...");
//            //        }
//            //    } else {

//            //        var isiInfo = (ISIInfo)currentElementInfo;
//            //        var isi = (ISI)isiInfo.element;
//            //        if (isi != null) {
//            //            EditorGUILayout.LabelField("[ISI] with id " + (currentElementInfo.key()).ToString());
//            //            EditorGUILayout.ObjectField(isi, typeof(ISI), true);
//            //        } else {
//            //            EditorGUILayout.LabelField("...");
//            //        }
//            //        //currentCondition = isi.current_condition();
//            //    }
//            //} else {
//            //    EditorGUILayout.LabelField("...");
//            //}
//        }
//    }
//}
//#endif

namespace Ex
{
    public class ComponentInfo{
        public ComponentInfo(Category category, Pritority priority, Reserved reserved) {
            this.category = category;
            this.priority = priority;
            this.reserved = reserved;
        }
        public Category category;
        public Pritority priority;
        public Reserved reserved;
    }

    public class Components : MonoBehaviour{


        public Dictionary<Category, List<ExComponent>> componentsPerCategory = new Dictionary<Category, List<ExComponent>>();
        public static readonly Dictionary<Category, string> Category2Transform = new Dictionary<Category, string> {
            [Category.Audio] = "[C:Audio]",
            [Category.Resource] = "[C:Resource]",
            [Category.Image] = "[C:Image]",
            [Category.Input] = "[C:Input]",
            [Category.Network] = "[C:Network]",
            [Category.Output] = "[C:Output]",
            [Category.Scene] = "[C:Scene]",
            [Category.Script] = "[C:Script]",
            [Category.Environment] = "[C:Environment]",
            [Category.UI] = "[C:UI]",
            [Category.Video] = "[C:Video]",
            [Category.Tracking] = "[C:Tracking]",
            [Category.Text] = "[C:Text]",
            [Category.Model] = "[C:Model]",
            [Category.Avatar] = "[C:Avatar]",
            [Category.Interaction] = "[C:Interaction]",
            [Category.Camera] = "[C:Camera]",
            [Category.Settings] = "[C:Settings]",
            [Category.Cloud] = "[C:Cloud]",
            [Category.Viewer] = "[C:Viewer]"
        };

        private static ComponentInfo gen_info(Category category, Pritority pritority, Reserved reserved) {
            return new ComponentInfo(category, pritority, reserved);
        }

        public static readonly Dictionary<string, ComponentInfo> Names2Info = new Dictionary<string, ComponentInfo> {
            // audio
            ["Ex.MicrophoneComponent"] = gen_info(Category.Audio, Pritority.Medium, Reserved.Public),
            ["Ex.AudioSourceComponent"] = gen_info(Category.Audio, Pritority.Medium, Reserved.Public),
            // input
            ["Ex.JoypadComponent"] = gen_info(Category.Input, Pritority.Hight, Reserved.Public),
            ["Ex.MouseComponent"] = gen_info(Category.Input, Pritority.Hight, Reserved.Public),
            ["Ex.KeyboardComponent"] = gen_info(Category.Input, Pritority.Hight, Reserved.Public),
            // network
            ["Ex.UdpReaderComponent"] = gen_info(Category.Network, Pritority.Hight, Reserved.Public),
            ["Ex.UdpWriterComponent"] = gen_info(Category.Network, Pritority.Hight, Reserved.Public),
            ["Ex.SerialPortWriterComponent"] = gen_info(Category.Network, Pritority.Hight, Reserved.Public),
            ["Ex.ParallelPortWriterComponent"] = gen_info(Category.Network, Pritority.Hight, Reserved.Public),
            // output
            ["Ex.LoggerComponent"] = gen_info(Category.Output, Pritority.Low, Reserved.Public),
            ["Ex.LoggerConditionComponent"] = gen_info(Category.Output, Pritority.Low, Reserved.Public),
            ["Ex.LoggerColumnsComponent"] = gen_info(Category.Output, Pritority.Low, Reserved.Public),
            // camera
            ["Ex.CameraTargetComponent"] = gen_info(Category.Camera, Pritority.Low, Reserved.Public),
            ["Ex.CameraTrajectoryComponent"] = gen_info(Category.Camera, Pritority.Low, Reserved.Public),
            ["Ex.CameraTrajectoryFileComponent"] = gen_info(Category.Camera, Pritority.Low, Reserved.Public),
            ["Ex.CameraComponent"] = gen_info(Category.Camera, Pritority.Low, Reserved.Public),
            ["Ex.FPPAvatarCameraComponent"] = gen_info(Category.Camera, Pritority.Low, Reserved.Closed),
            // scene
            ["Ex.AssetBundleComponent"] = gen_info(Category.Scene, Pritority.Hight, Reserved.Public),
            ["Ex.MultiABComponent"] = gen_info(Category.Scene, Pritority.Hight, Reserved.Public),
            ["Ex.FallingSpheresComponent"] = gen_info(Category.Scene, Pritority.Medium, Reserved.Public),
            ["Ex.MirrorComponent"] = gen_info(Category.Scene, Pritority.Medium, Reserved.Public),
            ["Ex.FlashingDotComponent"] = gen_info(Category.Scene, Pritority.Medium, Reserved.Public),
            ["Ex.MRIComponent"] = gen_info(Category.Scene, Pritority.Medium, Reserved.Public),
            // script
            ["Ex.CSharpScriptComponent"] = gen_info(Category.Script, Pritority.Low, Reserved.Public),
            ["Ex.PythonScriptComponent"] = gen_info(Category.Script, Pritority.Medium, Reserved.Public),
            // UI
            ["Ex.SliderUIComponent"] = gen_info(Category.UI, Pritority.Medium, Reserved.Public),
            // video
            ["Ex.VideoFileComponent"] = gen_info(Category.Video, Pritority.Medium, Reserved.Public),
            ["Ex.VideoFileCameraViewerComponent"] = gen_info(Category.Video, Pritority.Medium, Reserved.Public),
            ["Ex.WebcamComponent"] = gen_info(Category.Video, Pritority.Medium, Reserved.Public),
            ["Ex.VideoSaverComponent"] = gen_info(Category.Video, Pritority.Medium, Reserved.Public),
            // tracking
            ["Ex.SceneScanerComponent"] = gen_info(Category.Tracking, Pritority.Medium, Reserved.LNCO),
            ["Ex.LeapMotionComponent"] = gen_info(Category.Tracking, Pritority.Hight, Reserved.Public),
            ["Ex.LeapMotionTrackingComponent"] = gen_info(Category.Tracking, Pritority.Medium, Reserved.Public),
            ["Ex.LeapMotionArmsDisplayComponent"] = gen_info(Category.Tracking, Pritority.Medium, Reserved.Closed),
            ["Ex.BiopacComponent"] = gen_info(Category.Tracking, Pritority.Hight, Reserved.Public),
            ["Ex.TheraTrainerTrackingComponent"] = gen_info(Category.Tracking, Pritority.Medium, Reserved.Public),
            ["Ex.TheraTrainerPlatformComponent"] = gen_info(Category.Tracking, Pritority.Medium, Reserved.Public),
            ["Ex.KinectManagerComponent"] = gen_info(Category.Tracking, Pritority.Hight, Reserved.LNCO),
            ["Ex.KinectBodyTrackingComponent"] = gen_info(Category.Tracking, Pritority.Hight, Reserved.LNCO),
            ["Ex.OptitrackComponent"] = gen_info(Category.Tracking, Pritority.Hight, Reserved.Public),
            ["Ex.AttachObjectToHandComponent"] = gen_info(Category.Tracking, Pritority.Medium, Reserved.Public),
            ["Ex.QualisysTrackingComponent"] = gen_info(Category.Tracking, Pritority.Hight, Reserved.Public),
            ["Ex.SoncebozSGComponent"] = gen_info(Category.Tracking, Pritority.Hight, Reserved.LNCO),
            ["Ex.FOPRobotComponent"] = gen_info(Category.Tracking, Pritority.Hight, Reserved.LNCO),
            // model
            ["Ex.CubeComponent"] = gen_info(Category.Model, Pritority.Medium, Reserved.Public),
            ["Ex.SphereComponent"] = gen_info(Category.Model, Pritority.Medium, Reserved.Public),
            ["Ex.TorusComponent"] = gen_info(Category.Model, Pritority.Medium, Reserved.Public),
            ["Ex.LinesComponent"] = gen_info(Category.Model, Pritority.Medium, Reserved.Public),
            ["Ex.CylinderComponent"] = gen_info(Category.Model, Pritority.Medium, Reserved.Public),
            ["Ex.LandmarkComponent"] = gen_info(Category.Model, Pritority.Medium, Reserved.Public),
            // cloud
            ["Ex.CloudComponent"] = gen_info(Category.Cloud, Pritority.Medium, Reserved.Public),
            ["Ex.ScanerVideoComponent"] = gen_info(Category.Cloud, Pritority.Medium, Reserved.LNCO),
            // avatar
            ["Ex.HumanoidAvatarComponent"] = gen_info(Category.Avatar, Pritority.Medium, Reserved.Closed),
            ["Ex.HumanoidControllerComponent"] = gen_info(Category.Avatar, Pritority.Low, Reserved.Closed),
            // interaction
            ["Ex.FlagPoleComponent"] = gen_info(Category.Interaction, Pritority.Medium, Reserved.Public),
            ["Ex.MarkToCleanComponent"] = gen_info(Category.Interaction, Pritority.Medium, Reserved.Public),
            ["Ex.TargetToGrabComponent"] = gen_info(Category.Interaction, Pritority.Medium, Reserved.Public),
            // environment
            ["Ex.SkyComponent"] = gen_info(Category.Environment, Pritority.Hight, Reserved.Public),
            // resource
            ["Ex.ImageResourceComponent"] = gen_info(Category.Resource, Pritority.Hight, Reserved.Public),
            ["Ex.PlotResourceComponent"] = gen_info(Category.Resource, Pritority.Hight, Reserved.Public),
            ["Ex.TextResourceComponent"] = gen_info(Category.Resource, Pritority.Hight, Reserved.Public),
            ["Ex.VideoResourceComponent"] = gen_info(Category.Resource, Pritority.Hight, Reserved.Public),
            ["Ex.AudioResourceComponent"] = gen_info(Category.Resource, Pritority.Hight, Reserved.Public),
            ["Ex.DirectoryResourceComponent"] = gen_info(Category.Resource, Pritority.Hight, Reserved.Public),
            // viewer
            ["Ex.FixationCrossViewerComponent"] = gen_info(Category.Viewer, Pritority.Low, Reserved.Public),
            ["Ex.ImageViewerComponent"] = gen_info(Category.Viewer, Pritority.Low, Reserved.Public),
            ["Ex.TextViewerComponent"] = gen_info(Category.Viewer, Pritority.Low, Reserved.Public),
            ["Ex.WebcamViewerComponent"] = gen_info(Category.Viewer, Pritority.Low, Reserved.Public),
            ["Ex.FovSimulatorComponent"] = gen_info(Category.Viewer, Pritority.Hight, Reserved.Public),
            ["Ex.BlendFadeViewerComponent"] = gen_info(Category.Viewer, Pritority.Hight, Reserved.Public)
        };

        // sort by priority
        [SerializeField]
        private List<ExComponent> sortedComponents = new List<ExComponent>();
        private List<ExComponent> reverseSortedComponents = new List<ExComponent>();
        public Dictionary<Type, List<ExComponent>> componentsPerType = new Dictionary<Type, List<ExComponent>>();

        public bool generate(XML.Components xmlComponents) {

            // create gameobjects and setup components
            List<ExComponent> components = new List<ExComponent>();

            // remove every previous category
            foreach (Transform child in transform) {
                DestroyImmediate(child.gameObject);
            }

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
                    ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.initialize, true, true);
                }
                    
                if (!component.base_initialize()) {
                    // if one component not initialized, we stop the experiment generation
                    return false;
                }                    
                          
            }
            ExVR.ExpLog().component_manager(Function.initialize, false);

            return true;
        }

        public void action_from_gui(int componentKey, int configKey, string actionName) {

            ExComponent component = get(componentKey);
            if (component == null) {
                return;                
            }

            if (component.is_function_defined(Function.action_from_gui)) {
                ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.action_from_gui, true);
                component.base_action_from_gui(configKey, actionName);
                ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.action_from_gui, false);
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
                        ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.update_parameter_from_gui, true);
                        component.base_update_parameter_from_gui(configKey, arg);
                        ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.update_parameter_from_gui, false);
                    }
                }
            }
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
                    ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.start_experiment, true, true);
                    component.base_start_experiment();
                    ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.start_experiment, false, true);
                }
            }

            ExVR.ExpLog().component_manager(Function.start_experiment, false);
        }


        public void stop_experiment() {

            ExVR.ExpLog().component_manager(Function.stop_experiment, true);
            foreach (var component in reverseSortedComponents) {

                if (component.is_function_defined(Function.stop_experiment)) {
                    ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.stop_experiment, true, true, true, true);
                }

                component.base_stop_experiment();

                if (component.is_function_defined(Function.stop_experiment)) {
                    ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.stop_experiment, false, true, true, true);
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

        public void update_states_from_time(Condition condition, double time) {

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


        public void set_component_states(ExComponent component, bool doUpdate, bool visibility, bool log = true) {

            if (component.is_closed()) {
                return;
            }

            if (doUpdate != component.is_updating()) {

                if (component.is_started() && log) {
                    ExVR.ExpLog().component(component, Function.set_update_state, component.currentC.name, " -> U=" + doUpdate, true, true);
                }

                if (log && component.is_function_defined(Function.set_update_state)) {
                    ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.set_update_state, true);
                }

                component.base_set_update_state(doUpdate);

                if (log && component.is_function_defined(Function.set_update_state)) {
                    ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.set_update_state, false);
                }                
            }
            
            if (visibility != component.is_visible()) {
       
                if (component.is_started() && log) {
                    ExVR.ExpLog().component(component, Function.set_visibility, component.currentC.name, " -> U=" + visibility, true, true);
                }

                if (log && component.is_function_defined(Function.set_visibility)) {
                    ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.set_visibility, true);
                }

                component.base_set_visibility(visibility);

                if (log && component.is_function_defined(Function.set_visibility)) {
                    ExVR.ExpLog().log_and_add_to_stacktrace(component, Function.set_visibility, false);
                }
            }
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
