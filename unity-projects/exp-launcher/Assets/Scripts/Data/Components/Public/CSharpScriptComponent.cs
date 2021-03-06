
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;

namespace Ex{
    
    public class CSharpScriptComponent : ExComponent{

        Type runtimeType = null;
        BaseCompiledCSharpComponent compiledComponent = null;

        public BaseCompiledCSharpComponent compiled() {
            return compiledComponent;
        }



        // once per loading
        protected override bool initialize() {

            // force catch exception for csharp scripts components
            catchExceptions = true;

            // args
            string className = initC.get<string>("component_class_name");

            // retrieve type
            var assembly = CSharpScriptResource.get_compiled_assembly();
            if (assembly == null) {
                log_error(string.Concat("No assembly available, cannot instantiate class Ex.", className));
                return false;
            }
            runtimeType = assembly.GetType(string.Concat("Ex.", className));
            if (runtimeType == null) {
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
            functionsDefined[Function.clean] = (runtimeType.GetMethod("clean", flagPublic).DeclaringType == runtimeType);

            functionsDefined[Function.start_experiment] = (runtimeType.GetMethod("start_experiment", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.stop_experiment] = (runtimeType.GetMethod("stop_experiment", flagPublic).DeclaringType == runtimeType);

            functionsDefined[Function.set_current_config] = (runtimeType.GetMethod("set_current_config", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.update_from_current_config] = (runtimeType.GetMethod("update_from_current_config", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.pre_start_routine] = (runtimeType.GetMethod("pre_start_routine", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.start_routine] = (runtimeType.GetMethod("start_routine", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.post_start_routine] = (runtimeType.GetMethod("post_start_routine", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.stop_routine] = (runtimeType.GetMethod("stop_routine", flagPublic).DeclaringType == runtimeType);

            functionsDefined[Function.on_gui] = (runtimeType.GetMethod("on_gui", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.pre_update] = (runtimeType.GetMethod("pre_update", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.update] = (runtimeType.GetMethod("update", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.post_update] = (runtimeType.GetMethod("post_update", flagPublic).DeclaringType == runtimeType);

            functionsDefined[Function.set_update_state] = (runtimeType.GetMethod("set_update_state", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.set_visibility] = (runtimeType.GetMethod("set_visibility", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.play] = (runtimeType.GetMethod("play", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.pause] = (runtimeType.GetMethod("pause", flagPublic).DeclaringType == runtimeType);

            functionsDefined[Function.update_parameter_from_gui] = (runtimeType.GetMethod("update_parameter_from_gui", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.action_from_gui] = (runtimeType.GetMethod("action_from_gui", flagPublic).DeclaringType == runtimeType);

            functionsDefined[Function.slot1] = (runtimeType.GetMethod("slot1", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.slot2] = (runtimeType.GetMethod("slot2", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.slot3] = (runtimeType.GetMethod("slot3", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.slot4] = (runtimeType.GetMethod("slot4", flagPublic).DeclaringType == runtimeType);
            functionsDefined[Function.slot5] = (runtimeType.GetMethod("slot5", flagPublic).DeclaringType == runtimeType);

            //if (functionsDefined[Function.initialize]) {
            // catchExceptions
            if (!compiledComponent.initialize()) {
                log_error("Error during CSharp script initialization, component will be disactivated.");
                return false;
            }
            //}

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
        protected override void clean() {
            compiledComponent.clean();
        }

        // once per experiment
        protected override void start_experiment() {compiledComponent.start_experiment();}
        protected override void stop_experiment() {compiledComponent.stop_experiment();}

        // once per routine
        protected override void set_current_config(string configName) { }
        public override void update_from_current_config() { compiledComponent.update_from_current_config(); }
        protected override void pre_start_routine() { compiledComponent.pre_start_routine(); }
        protected override void start_routine() { compiledComponent.start_routine(); }
        protected override void post_start_routine() { compiledComponent.post_start_routine(); }
        protected override void stop_routine() { compiledComponent.stop_routine(); }

        // every frame or more
        protected override void on_gui() { compiledComponent.on_gui(); }
        protected override void pre_update() {compiledComponent.pre_update();}
        protected override void update() {compiledComponent.update();}
        protected override void post_update() {compiledComponent.post_update();}

        // several times per routine
        protected override void set_visibility(bool visibility) {compiledComponent.set_visibility(visibility);}
        protected override void set_update_state(bool doUpdate) {compiledComponent.set_update_state(doUpdate);}
        public override void play() { compiledComponent.play(); }
        public override void pause() { compiledComponent.pause(); }

        // from gui
        protected override void action_from_gui(bool initConfig, string action) {compiledComponent.action_from_gui(initConfig, action);}
        protected override void update_parameter_from_gui(string updatedArgName) {compiledComponent.update_parameter_from_gui(updatedArgName);}
    }
}

