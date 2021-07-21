
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

namespace Ex{

    public class BaseCompiledCSharpComponent : MonoBehaviour{

        public ExComponent p = null;

        public ComponentConfig current_config()     { return p.current_config(); }
        public ComponentInitConfig init_config()    { return p.init_config(); }
        public Routine current_routine()            { return p.currentRoutine; }
        public Condition current_condition()        { return p.currentCondition; }

        public Routine get_routine(string routineName) {
            return ExVR.Routines().get(routineName);
        }

        public bool is_visible()        { return p.is_visible(); }
        public bool is_updating()       { return p.is_updating(); }
        public bool is_closed()         { return p.is_closed(); }

        public void next()      { ExComponent.next(); }
        public void previous()  { Ex.ExComponent.previous(); }
        public void close() { ExVR.Components().close(p);}
        public void stop()      { ExComponent.force_stop_experiment(); }


        public void invoke_signal1(object value) {
            p.invoke_signal("signal1", value);
        }
        public void invoke_signal2(object value) {
            p.invoke_signal("signal2", value);
        }
        public void invoke_signal3(object value) {
            p.invoke_signal("signal3", value);
        }
        public void invoke_signal4(object value) {
            p.invoke_signal("signal4", value);
        }

        public List<ExComponent> get_all(string category) {
            
            ExComponent.Category type;
            if (System.Enum.TryParse(category, false, out type)) {
                return get_all(type);
            }
            return new List<ExComponent>();
        }

        public T get_csharp_script<T>(string name) where T : BaseCompiledCSharpComponent {
            var component = get(name);
            if (component != null) {
                if (component.GetType().ToString() == "Ex.CSharpScriptComponent") {
                    return (T)(((CSharpScriptComponent)component).compiled());
                } else {
                    ExVR.Log().error(string.Format("Component {0} is not a CSharp script.", name));
                }
            }
            return null;
        }

        public List<ExComponent> get_all(ExComponent.Category type) {
            return ExVR.Components().get_all(type);
        }

        public ExComponent get(int key) {
            return ExVR.Components().get(key);
        }

        public ExComponent get(string name) {
            return ExVR.Components().get(name);
        }

        public List<T> get<T>() where T : ExComponent {
            return ExVR.Components().get_all<T>();
        }

        public T get<T>(string name) where T : ExComponent {
            return ExVR.Components().get<T>(name);
        }
        public long frame_id() {
            return ExVR.Time().frame_id();
        }

        public double ellapsed_time_exp_ms() {
            return ExComponent.ellapsed_time_exp_ms();
        }

        public double ellapsed_time_routine_ms() {
            return ExComponent.ellapsed_time_routine_ms();
        }

        public double ellapsed_time_frame_ms() {
            return ExComponent.ellapsed_time_frame_ms();
        }

        public void log_message(string message, bool verbose = false) {
            p.log_message(message, verbose);
        }

        public void log_warning(string warning, bool verbose = true) {
            p.log_warning(warning, verbose);
        }

        public void log_error(string error, bool verbose = true) {
            p.log_error(error, verbose);
        }

        // ExComponent functions
        // # main functions
        public virtual bool initialize() { return true; }        
        
        public virtual void start_experiment() { }

        public virtual void pre_start_routine() { }
        public virtual void start_routine() { }
        public virtual void post_start_routine() { }
        public virtual void update() { }
        public virtual void stop_routine() { }
        public virtual void stop_experiment() { }
        public virtual void play() { }
        public virtual void pause() { }
        public virtual void set_update_state(bool doUpdate) { }
        public virtual void set_visibility(bool visible) { }

        // # for advanced users 
        public virtual void clean() { }
        public virtual void on_gui() { }
        public virtual void pre_update() { }
        public virtual void post_update() { }
        public virtual void update_parameter_from_gui(XML.Arg arg) { }
        public virtual void update_from_current_config() { }
        public virtual void action_from_gui(bool initConfig, string action) { }

        // # slots
        public virtual void slot1(object value) { }
        public virtual void slot2(object value) { }
        public virtual void slot3(object value) { }
        public virtual void slot4(object value) { }
        public virtual void slot5(IdAny idValue){ }
    }
    
    public class CSharpScriptComponent : ExComponent{

        Type runtimeType = null;
        BaseCompiledCSharpComponent compiledComponent = null;

        public BaseCompiledCSharpComponent compiled() {
            return compiledComponent;
        }

        protected override bool initialize() {

            // force catch exception for csharp scripts components
            catchExceptions = true;

            // args
            string className   = initC.get<string>("component_class_name");

            // retrieve type
            var assembly = CSharpScriptResource.get_compiled_assembly();
            if(assembly == null) {
                log_error(string.Concat("No assembly available, cannot instantiate class Ex.", className));
                return false;
            }
            runtimeType = assembly.GetType(string.Concat("Ex.", className));
            if(runtimeType == null) {
                log_error(string.Concat("Cannot instantiate class Ex.", className));
                return false;
            }

            // generate component and add it to gameObject
            compiledComponent = (BaseCompiledCSharpComponent)gameObject.AddComponent(runtimeType);
            compiledComponent.p = gameObject.GetComponent<CSharpScriptComponent>();

            // rewrite functions defined dictionary for looking into runtime type
            functionsDefined = new Dictionary<Function, bool>();
            var flagPublic = System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.Public;
            functionsDefined[Function.initialize] = (runtimeType.GetMethod("initialize", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.start_experiment] = (runtimeType.GetMethod("start_experiment", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.pre_start_routine] = (runtimeType.GetMethod("pre_start_routine", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.start_routine] = (runtimeType.GetMethod("start_routine", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.post_start_routine] = (runtimeType.GetMethod("post_start_routine", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.set_update_state] = (runtimeType.GetMethod("set_update_state", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.set_visibility] = (runtimeType.GetMethod("set_visibility", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.update_parameter_from_gui] = (runtimeType.GetMethod("update_parameter_from_gui", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.action_from_gui] = (runtimeType.GetMethod("action_from_gui", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.pre_update] = (runtimeType.GetMethod("pre_update", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.update] = (runtimeType.GetMethod("update", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.post_update] = (runtimeType.GetMethod("post_update", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.stop_routine] = (runtimeType.GetMethod("stop_routine", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.stop_experiment] = (runtimeType.GetMethod("stop_experiment", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.clean] = (runtimeType.GetMethod("clean", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.on_gui] = (runtimeType.GetMethod("on_gui", flagPublic).DeclaringType == runtimeType);            
            functionsDefined[Function.play] = (runtimeType.GetMethod("play", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.pause] = (runtimeType.GetMethod("pause", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.update_from_current_config] = (runtimeType.GetMethod("update_from_current_config", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.slot1] = (runtimeType.GetMethod("slot1", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.slot2] = (runtimeType.GetMethod("slot2", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.slot3] = (runtimeType.GetMethod("slot3", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.slot4] = (runtimeType.GetMethod("slot4", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.slot5] = (runtimeType.GetMethod("slot5", flagPublic).DeclaringType == runtimeType);

            if (functionsDefined[Function.initialize]) {
                // catchExceptions
                if (!compiledComponent.initialize()) {
                    log_error("Error during CSharp script initialization, component will be disactivated.");
                    return false;
                }
            }

            // slots
            add_slot("slot1", (value) => {

                if (functionsDefined[Function.slot1]) {

                    currentFunction = Function.slot1;

                    if (catchExceptions) {
                        try {
                            compiledComponent.slot1(value);
                        } catch (Exception e) {
                            display_exception(e);
                        }
                    } else {
                        compiledComponent.slot1(value);
                    }
                }
            });
            add_slot("slot2", (value) => {

                if (functionsDefined[Function.slot2]) {

                    currentFunction = Function.slot2;

                    if (catchExceptions) {
                        try {
                            compiledComponent.slot2(value);
                        } catch (Exception e) {
                            display_exception(e);
                        }
                    } else {
                        compiledComponent.slot2(value);
                    }
                }
            });
            add_slot("slot3", (value) => {

                if (functionsDefined[Function.slot3]) {

                    currentFunction = Function.slot3;

                    if (catchExceptions) {
                        try {
                            compiledComponent.slot3(value);
                        } catch (Exception e) {
                            display_exception(e);
                        }
                    } else {
                        compiledComponent.slot3(value);
                    }
                }
            });
            add_slot("slot4", (value) => {

                if (functionsDefined[Function.slot4]) {

                    currentFunction = Function.slot4;

                    if (catchExceptions) {
                        try {
                            compiledComponent.slot4(value);
                        } catch (Exception e) {
                            display_exception(e);
                        }
                    } else {
                        compiledComponent.slot4(value);
                    }
                }
            });
            add_slot("slot5", (value) => {

                if (functionsDefined[Function.slot5]) {

                    currentFunction = Function.slot5;

                    if (catchExceptions) {
                        try {
                            compiledComponent.slot5((IdAny)value);
                        } catch (Exception e) {
                            display_exception(e);
                        }
                    } else {
                        compiledComponent.slot5((IdAny)value);
                    }
                }
            });

            // signals
            add_signal("signal1");
            add_signal("signal2");
            add_signal("signal3");
            add_signal("signal4");

            return true;
        }

        protected override void start_experiment() {
            if (functionsDefined[Function.start_experiment]) {
                compiledComponent.start_experiment();
            }
        }

        protected override void stop_experiment() {
            if (functionsDefined[Function.stop_experiment]) {
                compiledComponent.stop_experiment();
            }
        }

        protected override void pre_start_routine() {
            if (functionsDefined[Function.pre_start_routine]) {
                compiledComponent.pre_start_routine();
            }
        }

        protected override void start_routine() {
            if (functionsDefined[Function.start_routine]) {
                compiledComponent.start_routine();
            }
        }

        protected override void post_start_routine() {
            if (functionsDefined[Function.post_start_routine]) {
                compiledComponent.post_start_routine();
            }
        }

        protected override void stop_routine() {
            if (functionsDefined[Function.stop_routine]) {
                compiledComponent.stop_routine();
            }
        }

        protected override void on_gui() {
            if (functionsDefined[Function.on_gui]) {
                compiledComponent.on_gui();
            }
        }

        protected override void pre_update() {
            if (functionsDefined[Function.pre_update]) {
                compiledComponent.pre_update();
            }
        }

        protected override void update() {
            if (functionsDefined[Function.update]) {
                compiledComponent.update();
            }
        }

        protected override void post_update() {
            if (functionsDefined[Function.post_update]) {
                compiledComponent.post_update();
            }
        }

        protected override void set_visibility(bool visibility) {
            if (functionsDefined[Function.set_visibility]) {
                compiledComponent.set_visibility(visibility);
            }
        }

        protected override void set_update_state(bool doUpdate) {
            if (functionsDefined[Function.set_update_state]) {
                compiledComponent.set_update_state(doUpdate);
            }
        }

        protected override void clean() {
            if (functionsDefined[Function.clean]) {
                compiledComponent.clean();
            }
        }

        public override void play() {
            if (functionsDefined[Function.play]) {
                compiledComponent.play();
            }
        }

        public override void pause() {
            if (functionsDefined[Function.pause]) {
                compiledComponent.pause();
            }
        }

        public override void update_from_current_config() {
            if (functionsDefined[Function.update_from_current_config]) {
                compiledComponent.update_from_current_config();
            }
        }

        protected override void action_from_gui(bool initConfig, string action) {
            if (functionsDefined[Function.action_from_gui]) {
                compiledComponent.action_from_gui(initConfig, action);
            }
        }

        protected override void update_parameter_from_gui(XML.Arg arg) {
            if (functionsDefined[Function.update_parameter_from_gui]) {
                compiledComponent.update_parameter_from_gui(arg);
            }
        }

    }
}

