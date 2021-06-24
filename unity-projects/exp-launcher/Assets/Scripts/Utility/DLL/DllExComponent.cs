/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Linq;
using System.ComponentModel;
using System.Collections.Generic;
using System.Runtime.InteropServices;


namespace Ex.DLL{

    public static class CppDllCallbacks{
        
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void StrackTraceCB(string stackTraceMessage);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void LogCB(string message);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void LogErrorCB(string errorMessage);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate long EllapsedTimeExpMsCB();
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate long EllapsedTimeRoutineMsCB();
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate int GetCB(string componentName);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate int IsInitializedCB(int key);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate int IsVisibleCB(int key);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate int IsUpdatingCB(int key);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate int IsClosedCB(int key);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void NextCB();
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void PreviousCB();
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void CloseCB(int key);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void SignalBoolCB(int key, int index, int value);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void SignalIntCB(int key, int index, int value);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void SignalFloatCB(int key, int index, float value);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void SignalDoubleCB(int key, int index, double value);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate void SignalStringCB(int key, int index, string value);

        public static void init_callbacks(){

            StrackTraceCB stackTraceCB = (trace) => {
                ExVR.ExpLog().push_to_strackTrace(new ComponentTrace(trace));
            };
            LogCB logCB = (message) => {
                ExVR.Log().message(message);
            };
            LogErrorCB logErrorCB = (error) => {
                ExVR.Log().error(error);
            };
            EllapsedTimeExpMsCB ellapsedTimeExpMsCB = () => {
                return (int)ExComponent.ellapsed_time_exp_ms();
            };
            EllapsedTimeRoutineMsCB ellapsedTimeRoutineMsCB = () => {
                return (int)ExComponent.ellapsed_time_routine_ms();
            };
            GetCB getCB = (string componentName) => {
                return ExComponent.get(componentName).key;
            };
            IsInitializedCB isInitializedCB = (key) => {
                return 1;
                //return ExComponent.get(key).is_initialized() ? 1 : 0;
            };
            IsVisibleCB isVisibleCB = (key) => {
                return ExComponent.get(key).is_visible() ? 1 : 0;
            };
            IsUpdatingCB isUpdatingCB = (key) => {
                return ExComponent.get(key).is_updating() ? 1 : 0;
            };
            IsClosedCB isClosedCB = (key) => {
                return ExComponent.get(key).is_closed() ? 1 : 0;
            };
            NextCB nextCB = () => {
                ExComponent.next();
            };
            PreviousCB previousCB = () => {
                ExComponent.previous();
            };
            CloseCB closeCB = (key) => {
                //ExComponent.get(key).close();
            };
            SignalBoolCB signalBoolCB = (key, index, value) => {
                ExComponent.get(key).invoke_signal("signal" + (index + 1), (value==1));
            };
            SignalIntCB signalIntCB = (key, index, value) => {
                ExComponent.get(key).invoke_signal("signal" + (index+1), value);
            };
            SignalFloatCB signalFloatCB = (key, index, value) => {
                ExComponent.get(key).invoke_signal("signal" + (index + 1), value);
            };
            SignalDoubleCB signalDoubleCB = (key, index, value) => {
                ExComponent.get(key).invoke_signal("signal" + (index + 1), value);
            };
            SignalStringCB signalStringCB = (key, index, value) => {
                ExComponent.get(key).invoke_signal("signal" + (index + 1), value);
            };

            init_callbacks_ex_component(
                stackTraceCB,
                logCB,
                logErrorCB,
                ellapsedTimeExpMsCB,
                ellapsedTimeRoutineMsCB,
                getCB,
                isInitializedCB,
                isVisibleCB,
                isUpdatingCB,
                isClosedCB,
                nextCB,
                previousCB,
                closeCB,
                signalBoolCB,
                signalIntCB,
                signalFloatCB,
                signalDoubleCB,
                signalStringCB
            );
        }

        [DllImport("exvr-export", EntryPoint = "init_callbacks_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static private extern void init_callbacks_ex_component(
            [MarshalAs(UnmanagedType.FunctionPtr)] StrackTraceCB strackTraceCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] LogCB logCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] LogErrorCB logErrorCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] EllapsedTimeExpMsCB ellapsedTimeExpMsCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] EllapsedTimeRoutineMsCB ellapsedTimeRoutineMsCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] GetCB getCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] IsInitializedCB isInitializedCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] IsVisibleCB isVisibleCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] IsUpdatingCB isUpdatingCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] IsClosedCB isClosedCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] NextCB nextCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] PreviousCB previousCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] CloseCB closeCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] SignalBoolCB signalBoolCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] SignalIntCB signalIntCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] SignalFloatCB signalFloatCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] SignalDoubleCB signalDoubleCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] SignalStringCB signalStringCB
        );
    }

    public abstract class ExComponentDLL : CppDllImport{

        public enum ParametersContainer { InitConfig=0, CurrentConfig=1, Dynamic=2};

        private ComponentInitConfig m_initConfig = null;
        private ComponentConfig m_currentConfig = null;

        abstract protected override void create_DLL_class();

        protected override void delete_DLL_class() {
            delete_ex_component(_handle);
        }

        public virtual bool initialize(ComponentInitConfig initC, int componentKey) {

            m_initConfig = initC;            

            foreach (KeyValuePair<string, Argument> arg in m_initConfig.args) {
                update_component_from_xml(ParametersContainer.InitConfig, arg.Value.xml, arg.Value.value);
            }

            update_parameter_int_ex_component(_handle, (int)ParametersContainer.Dynamic, "key", componentKey);

            return initialize_ex_component(_handle) == 1 ? true : false;
        }

        public virtual void start_experiment() {
            start_experiment_ex_component(_handle);
        }

        public virtual void stop_experiment() {
            stop_experiment_ex_component(_handle);
        }

        public virtual void start_routine(ComponentConfig config) {

            m_currentConfig = config;
            foreach (KeyValuePair<string, Argument> arg in m_initConfig.args) {
                update_component_from_xml(ParametersContainer.CurrentConfig, arg.Value.xml, arg.Value.value);
            }
            start_routine_ex_component(_handle);
        }

        public virtual void stop_routine() {
            stop_routine_ex_component(_handle);
        }

        public virtual void clean() {
            clean_ex_component(_handle);
        }

        public virtual void play() {
            play_ex_component(_handle);
        }

        public virtual void pause() {
            pause_ex_component(_handle);
        }

        public virtual void update() {
            update_ex_component(_handle);
        }

        public virtual void update_parameter_from_gui(XML.Arg arg) {
            update_component_from_xml(ParametersContainer.CurrentConfig, arg, m_currentConfig.args[arg.Name].value);
        }

        public virtual void add_dynamic_parameter(string name, object value, TypeCode type) {
            update_parameter(ParametersContainer.Dynamic, name, value, type);
        }

        public virtual void set_visibility(bool visible) {
            set_visibility_ex_component(_handle, visible ? 1 : 0);
        }

        public virtual void set_update_state(bool doUpdate) { 
            set_update_state_ex_component(_handle, doUpdate ? 1 : 0);
        }

        public virtual void call_slot(int index, object value) {

            int idC = (int)ParametersContainer.Dynamic;

            if (value is bool) {
                update_parameter_bool_ex_component(_handle, idC, "slot" + index, ((bool)value) ? 1 : 0);
            } else if (value is int) {
                update_parameter_int_ex_component(_handle, idC, "slot" + index, (int)value);
            } else if (value is float) {
                update_parameter_float_ex_component(_handle, idC, "slot" + index, (float)value);
            } else if (value is double) {
                update_parameter_double_ex_component(_handle, idC, "slot" + index, (double)value);
            } else if (value is string) {
                update_parameter_string_ex_component(_handle, idC, "slot" + index, (string)value);
            } else if(value is List<double>) {
                update_parameter_array_double_ex_component(_handle, idC, "slot" + index, ((List<double>)value).ToArray(), ((List<double>)value).Count);
            } else {
                ExVR.Log().error("Type not managed by component.");
                return;
            }
            call_slot_ex_component(_handle, index);
        }

        public bool contains(ParametersContainer container, string name) {
            return contains_ex_component(_handle, (int)container, name) == 1;
        }

        public object get_parameter<T>(ParametersContainer container, string name) {
            int idC = (int)container;
            switch (Type.GetTypeCode(typeof(T))) {
                case TypeCode.Boolean:
                    return get_parameter_int_ex_component(_handle, idC, name) == 1;
                case TypeCode.Int16:
                    return get_parameter_int_ex_component(_handle, idC, name);
                case TypeCode.Int32:
                    return get_parameter_int_ex_component(_handle, idC, name);
                case TypeCode.Int64:
                    return get_parameter_int_ex_component(_handle, idC, name);
                case TypeCode.Single:
                    return get_parameter_float_ex_component(_handle, idC, name);
                case TypeCode.Double:
                    return get_parameter_double_ex_component(_handle, idC, name);
                case TypeCode.String:
                    return get_parameter_string_ex_component(_handle, idC, name);
            }
            return default(T);
        }

        public object get_parameter_1d(ParametersContainer container, string name, TypeCode t) {

            int idC = (int)container;
            int size = get_size_parameter_array_ex_component(_handle, idC, name);
            if (size == 0) {
                return null;
            }
            switch (t) {
                case TypeCode.Boolean:
                    ExVR.Log().error("Type not managed for arrays.");
                    break;
                case TypeCode.Int16:
                    var array1 = new int[size];
                    get_parameter_array_int_ex_component(_handle, idC, name, array1);
                    return array1;
                case TypeCode.Int32:
                    var array2 = new int[size];
                    get_parameter_array_int_ex_component(_handle, idC, name, array2);
                    return array2;
                case TypeCode.Int64:
                    var array3 = new int[size];
                    get_parameter_array_int_ex_component(_handle, idC, name, array3);
                    return array3;
                case TypeCode.Single:
                    var array4 = new float[size];
                    get_parameter_array_float_ex_component(_handle, idC, name, array4);
                    return array4;
                case TypeCode.Double:
                    var array5 = new double[size];
                    get_parameter_array_double_ex_component(_handle, idC, name, array5);
                    return array5;
                case TypeCode.String:
                    ExVR.Log().error("Type not managed for arrays.");
                    break;
            }

            return null;
        }

        public void update_parameter(ParametersContainer container, string name, object value, TypeCode t) {

            int idC = (int)container;
            switch (t) {
                case TypeCode.Boolean:
                    update_parameter_bool_ex_component(_handle, idC, name, ((bool)value) ? 1 : 0);
                    break;
                case TypeCode.Int16:
                    update_parameter_int_ex_component(_handle, idC, name, (int)value);
                    break;
                case TypeCode.Int32:
                    update_parameter_int_ex_component(_handle, idC, name, (int)value);
                    break;
                case TypeCode.Int64:
                    update_parameter_int_ex_component(_handle, idC, name, (int)value);
                    break;
                case TypeCode.Single:
                    update_parameter_float_ex_component(_handle, idC, name, (float)value);
                    break;
                case TypeCode.Double:
                    update_parameter_double_ex_component(_handle, idC, name, (double)value);
                    break;
                case TypeCode.String:
                    update_parameter_string_ex_component(_handle, idC, name, (string)value);
                    break;
            }
        }

        public void update_parameter_1d(ParametersContainer container, string name, List<object> value, int length, TypeCode t) {

            int idC = (int)container;
            switch (t) {
                case TypeCode.Boolean:
                    // ExVR.Log().error("Type not managed for arrays: " + t.ToString() + " "+ name);
                    return;
                case TypeCode.Int16:                    
                    update_parameter_array_int_ex_component(_handle, idC, name, value.Cast<int>().ToArray(), length);
                    break;
                case TypeCode.Int32:
                    update_parameter_array_int_ex_component(_handle, idC, name, value.Cast<int>().ToArray(), length);
                    break;
                case TypeCode.Int64:
                    update_parameter_array_int_ex_component(_handle, idC, name, value.Cast<int>().ToArray(), length);
                    break;
                case TypeCode.Single:
                    update_parameter_array_float_ex_component(_handle, idC, name, value.Cast<float>().ToArray(), length);
                    break;
                case TypeCode.Double:
                    update_parameter_array_double_ex_component(_handle, idC, name, value.Cast<double>().ToArray(), length);
                    break;
                case TypeCode.String:
                    // ExVR.Log().error("Type not managed for arrays: " + t.ToString() + " "+ name);
                    break;
            }
        }

        private void update_component_from_xml(ParametersContainer container, XML.Arg xmlArg, object value) {

            var tCode = Type.GetTypeCode(Type.GetType(xmlArg.Type));
            if (xmlArg.Dim == 0) {
                update_parameter(container, xmlArg.Name, value, tCode);
            } else if (xmlArg.Dim == 1) {
                string[] sizes = xmlArg.Sizes.Split(' ');
                int length = (int)TypeDescriptor.GetConverter(typeof(int)).ConvertFrom(sizes[0]);
                update_parameter_1d(container, xmlArg.Name, (List<object>)value, length, tCode);
            } else if (xmlArg.Dim == 2) {
                //string[] sizes = xmlArg.Sizes.Split(' ');
                //int rows = (int)TypeDescriptor.GetConverter(typeof(int)).ConvertFrom(sizes[0]);
                //int cols = (int)TypeDescriptor.GetConverter(typeof(int)).ConvertFrom(sizes[1]);
                //update_parameter_2d(exComponent, container, xmlArg.Name, value, tCode, rows, cols);
            }
        }


        [DllImport("exvr-export", EntryPoint = "delete_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void delete_ex_component(HandleRef exComponent);

        [DllImport("exvr-export", EntryPoint = "initialize_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern int initialize_ex_component(HandleRef exComponent);

        [DllImport("exvr-export", EntryPoint = "start_experiment_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void start_experiment_ex_component(HandleRef exComponent);

        [DllImport("exvr-export", EntryPoint = "stop_experiment_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void stop_experiment_ex_component(HandleRef exComponent);

        [DllImport("exvr-export", EntryPoint = "start_routine_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void start_routine_ex_component(HandleRef exComponent);

        [DllImport("exvr-export", EntryPoint = "stop_routine_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void stop_routine_ex_component(HandleRef exComponent);

        [DllImport("exvr-export", EntryPoint = "update_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void update_ex_component(HandleRef exComponent);

        [DllImport("exvr-export", EntryPoint = "set_visibility_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void set_visibility_ex_component(HandleRef exComponent, int visible);

        [DllImport("exvr-export", EntryPoint = "set_update_state_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void set_update_state_ex_component(HandleRef exComponent, int doUpdate);

        [DllImport("exvr-export", EntryPoint = "play_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void play_ex_component(HandleRef exComponent);

        [DllImport("exvr-export", EntryPoint = "pause_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void pause_ex_component(HandleRef exComponent);

        [DllImport("exvr-export", EntryPoint = "clean_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void clean_ex_component(HandleRef exComponent);

        [DllImport("exvr-export", EntryPoint = "call_slot_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void call_slot_ex_component(HandleRef exComponent, int index);

        [DllImport("exvr-export", EntryPoint = "contains_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern int contains_ex_component(HandleRef exComponent, int containerId, string name);

        [DllImport("exvr-export", EntryPoint = "update_parameter_bool_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void update_parameter_bool_ex_component(HandleRef exComponent, int containerId, string name, int value);

        [DllImport("exvr-export", EntryPoint = "update_parameter_int_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void update_parameter_int_ex_component(HandleRef exComponent, int containerId, string name, int value);

        [DllImport("exvr-export", EntryPoint = "update_parameter_float_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void update_parameter_float_ex_component(HandleRef exComponent, int containerId, string name, float value);

        [DllImport("exvr-export", EntryPoint = "update_parameter_double_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void update_parameter_double_ex_component(HandleRef exComponent, int containerId, string name, double value);

        [DllImport("exvr-export", EntryPoint = "update_parameter_string_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void update_parameter_string_ex_component(HandleRef exComponent, int containerId, string name, string value);


        [DllImport("exvr-export", EntryPoint = "get_parameter_int_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern int get_parameter_int_ex_component(HandleRef exComponent, int containerId, string name);

        [DllImport("exvr-export", EntryPoint = "get_parameter_float_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern float get_parameter_float_ex_component(HandleRef exComponent, int containerId, string name);

        [DllImport("exvr-export", EntryPoint = "get_parameter_double_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern double get_parameter_double_ex_component(HandleRef exComponent, int containerId, string name);

        [DllImport("exvr-export", EntryPoint = "get_parameter_string_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern string get_parameter_string_ex_component(HandleRef exComponent, int containerId, string name);


        [DllImport("exvr-export", EntryPoint = "get_size_parameter_array_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern int get_size_parameter_array_ex_component(HandleRef exComponent, int containerId, string name);

        [DllImport("exvr-export", EntryPoint = "get_parameter_array_int_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void get_parameter_array_int_ex_component(HandleRef exComponent, int containerId, string name, int[] array);

        [DllImport("exvr-export", EntryPoint = "get_parameter_array_float_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void get_parameter_array_float_ex_component(HandleRef exComponent, int containerId, string name, float[] array);

        [DllImport("exvr-export", EntryPoint = "get_parameter_array_double_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void get_parameter_array_double_ex_component(HandleRef exComponent, int containerId, string name, double[] array);


        [DllImport("exvr-export", EntryPoint = "update_parameter_array_int_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void update_parameter_array_int_ex_component(HandleRef exComponent, int containerId, string name, int[] values, int size);

        [DllImport("exvr-export", EntryPoint = "update_parameter_array_float_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void update_parameter_array_float_ex_component(HandleRef exComponent, int containerId, string name, float[] values, int size);

        [DllImport("exvr-export", EntryPoint = "update_parameter_array_double_ex_component", CallingConvention = CallingConvention.Cdecl)]
        static public extern void update_parameter_array_double_ex_component(HandleRef exComponent, int containerId, string name, double[] values, int size);


       
    }
}
