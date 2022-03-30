
/***********************************************************************************
** exvr-exp                                                                       **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// system
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Ex {
    public class CppElement {

        // log
        // # global
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void LogMessageCB(string message);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void LogWarningCB(string warningMessage);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void LogErrorCB(string errorMessage);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void StrackTraceCB(string stackTraceMessage);
        // # per type
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void LogMessageIdCB(string message, int sType, int sKey);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void LogWarningIdCB(string warningMessage, int sType, int sKey);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void LogErrorIdCB(string errorMessage, int sType, int sKey);

        // component
        // # get
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate int GetCB(string componentName);
        // # states
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate int IsVisibleCB(int key);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate int IsUpdatingCB(int key);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        delegate int IsClosedCB(int key);
        // # signals
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
        // times
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate long EllapsedTimeExpMsCB();
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate long EllapsedTimeRoutineMsCB();
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]

        // commands
        private delegate void NextCB();
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void PreviousCB();
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void CloseCB(int key);

        private static LogMessageCB logMessageCB = null;
        private static LogWarningCB logWarningCB = null;
        private static LogErrorCB logErrorCB = null;
        private static LogMessageIdCB logMessageIdCB = null;
        private static LogWarningIdCB logWarningIdCB = null;
        private static LogErrorIdCB logErrorIdCB = null;
        private static StrackTraceCB stackTraceCB = null;
        private static EllapsedTimeExpMsCB ellapsedTimeExpMsCB = null;
        private static EllapsedTimeRoutineMsCB ellapsedTimeRoutineMsCB = null;
        private static GetCB getCB = null;
        private static CloseCB closeCB = null;
        private static NextCB nextCB = null;
        private static PreviousCB previousCB = null;
        private static IsVisibleCB isVisibleCB = null;
        private static IsUpdatingCB isUpdatingCB = null;
        private static IsClosedCB isClosedCB = null;
        private static SignalBoolCB signalBoolCB = null;
        private static SignalIntCB signalIntCB = null;
        private static SignalFloatCB signalFloatCB = null;
        private static SignalDoubleCB signalDoubleCB = null;
        private static SignalStringCB signalStringCB = null;

        private static readonly string bracesStr = "{0}{1}";
        private static readonly string signalStr = "signal";

        enum SenderT : int {
            GUI = 0, Component = 1, Resource = 2
        };

        static public bool contains(CppDllImport cppDll, Parameters.Container pc, string name) {
            return contains_ex_element(cppDll.getHandle(), (int)pc, name) == 1;
        }

        static public T get<T>(CppDllImport cppDll, Parameters.Container pc, string name) {
            int idC = (int)pc;
            switch (Type.GetTypeCode(typeof(T))) {
                case TypeCode.Boolean:
                    return (T)(object)(get_parameter_int_ex_element(cppDll.getHandle(), idC, name) == 1);
                case TypeCode.Int16:
                    return (T)(object)(get_parameter_int_ex_element(cppDll.getHandle(), idC, name));
                case TypeCode.Int32:
                    return (T)(object)(get_parameter_int_ex_element(cppDll.getHandle(), idC, name));
                case TypeCode.Int64:
                    return (T)(object)(get_parameter_int_ex_element(cppDll.getHandle(), idC, name));
                case TypeCode.Single:
                    return (T)(object)(get_parameter_float_ex_element(cppDll.getHandle(), idC, name));
                case TypeCode.Double:
                    return (T)(object)(get_parameter_double_ex_element(cppDll.getHandle(), idC, name));
                case TypeCode.String:
                    return (T)(object)(get_parameter_string_ex_element(cppDll.getHandle(), idC, name));
            }
            return default(T);
        }

        static public T[] get_array<T>(CppDllImport cppDll, Parameters.Container pc, string name) {

            int idC = (int)pc;
            int size = get_size_parameter_array_ex_element(cppDll.getHandle(), idC, name);
            if (size == 0) {
                return null;
            }

            object array = null;
            switch (Type.GetTypeCode(typeof(T))) {
                case TypeCode.Boolean:
                    ExVR.Log().error("Type not managed for arrays.");
                    break;
                case TypeCode.Int16:
                    array = new int[size];
                    get_parameter_array_int_ex_element(cppDll.getHandle(), idC, name, (int[])array);
                    break;
                case TypeCode.Int32:
                    array = new int[size];
                    get_parameter_array_int_ex_element(cppDll.getHandle(), idC, name, (int[])array);
                    break;
                case TypeCode.Int64:
                    array = new int[size];
                    get_parameter_array_int_ex_element(cppDll.getHandle(), idC, name, (int[])array);
                    break;
                case TypeCode.Single:
                    array = new float[size];
                    get_parameter_array_float_ex_element(cppDll.getHandle(), idC, name, (float[])array);
                    break;
                case TypeCode.Double:
                    array = new double[size];
                    get_parameter_array_double_ex_element(cppDll.getHandle(), idC, name, (double[])array);
                    break;
                case TypeCode.String:
                    ExVR.Log().error("Type not managed for arrays.");
                    break;
            }
            return (T[])array;
        }

        static public void set(CppDllImport cppDll, Parameters.Container pc, string name, bool value) {
            set_parameter_int_ex_element(cppDll.getHandle(), (int)pc, name, value ? 1 : 0);
        }
        static public void set(CppDllImport cppDll, Parameters.Container pc, string name, short value) {
            set_parameter_int_ex_element(cppDll.getHandle(), (int)pc, name, Converter.to_int(value));
        }
        static public void set(CppDllImport cppDll, Parameters.Container pc, string name, int value) {
            set_parameter_int_ex_element(cppDll.getHandle(), (int)pc, name, value);
        }
        static public void set(CppDllImport cppDll, Parameters.Container pc, string name, long value) {
            set_parameter_int_ex_element(cppDll.getHandle(), (int)pc, name, Converter.to_int(value));
        }
        static public void set(CppDllImport cppDll, Parameters.Container pc, string name, float value) {
            set_parameter_float_ex_element(cppDll.getHandle(), (int)pc, name, value);
        }
        static public void set(CppDllImport cppDll, Parameters.Container pc, string name, double value) {
            set_parameter_double_ex_element(cppDll.getHandle(), (int)pc, name, value);
        }
        static public void set(CppDllImport cppDll, Parameters.Container pc, string name, string value) {
            set_parameter_string_ex_element(cppDll.getHandle(), (int)pc, name, value);
        }

        static public void set_array(CppDllImport cppDll, Parameters.Container pc, string name, List<int> value, int length) {
            set_parameter_array_int_ex_element(cppDll.getHandle(), (int)pc, name, value.ToArray(), length);
        }
        static public void set_array(CppDllImport cppDll, Parameters.Container pc, string name, List<float> value, int length) {
            set_parameter_array_float_ex_element(cppDll.getHandle(), (int)pc, name, value.ToArray(), length);
        }
        static public void set_array(CppDllImport cppDll, Parameters.Container pc, string name, List<double> value, int length) {
            set_parameter_array_double_ex_element(cppDll.getHandle(), (int)pc, name, value.ToArray(), length);
        }

        static public void set(CppDllImport cppDll, Parameters.Container pc, Argument arg) {

            if(arg.xml.UiGeneratorType == "Resource") {
                return;
            }

            var tCode = Type.GetTypeCode(arg.type);
            if (arg.xml.Dim == 0) {

                switch (tCode) {
                    case TypeCode.Boolean:
                        set(cppDll, pc, arg.xml.Name, (bool)arg.value);
                        return;
                    case TypeCode.Int16:
                        set(cppDll, pc, arg.xml.Name, (short)arg.value);
                        return;
                    case TypeCode.Int32:
                        set(cppDll, pc, arg.xml.Name, (int)arg.value);
                        return;
                    case TypeCode.Int64:
                        set(cppDll, pc, arg.xml.Name, (long)arg.value);
                        return;
                    case TypeCode.Single:
                        set(cppDll, pc, arg.xml.Name, (float)arg.value);
                        return;
                    case TypeCode.Double:
                        set(cppDll, pc, arg.xml.Name, (double)arg.value);
                        return;
                    case TypeCode.String:
                        set(cppDll, pc, arg.xml.Name, (string)arg.value);
                        return;
                    default:
                        ExVR.Log().warning(string.Format("Type [{0}] not managed for arg [{1}] of dim 0.", tCode.ToString(), arg.xml.Name));
                        return;
                }

            } else if (arg.xml.Dim == 1) {
                string[] sizes = arg.xml.Sizes.Split(' ');
                int length = Converter.to_int(sizes[0]);

                switch (tCode) {
                    case TypeCode.Int32:
                        set_array(cppDll, pc, arg.xml.Name, (List<int>)arg.value, length);
                        return;
                    case TypeCode.Single:
                        set_array(cppDll, pc, arg.xml.Name, (List<float>)arg.value, length);
                        return;
                    case TypeCode.Double:
                        set_array(cppDll, pc, arg.xml.Name, (List<double>)arg.value, length);
                        return;

                    default:
                        ExVR.Log().warning(string.Format("Type [{0}] not managed for arg [{1}] of dim 1.", tCode.ToString(), arg.xml.Name));
                        return;
                }
            } else if (arg.xml.Dim == 2) {
                string[] sizes = arg.xml.Sizes.Split(' ');
                int rows = Converter.to_int(sizes[0]);
                int cols = Converter.to_int(sizes[1]);

                ExVR.Log().warning("Dimension 2 not managed.");
                //set_array(exComponent, container, xmlArg.Name, value, tCode, rows, cols);
            }
        }

        public static void init_callbacks() {

            stackTraceCB = (trace) => {
                ExVR.Log().error("TRACE");
                ExVR.ExpLog().push_to_strackTrace(new ComponentTrace(trace)); 
            };

            logMessageCB = (message) => { ExVR.Log().message(message); };
            logMessageIdCB = (message, sType, sKey) => {

                ExVR.Log().error("MESSAGE");
                switch ((SenderT)sType) {
                    case SenderT.Component:
                        if (ExVR.Components().componentPerKey.ContainsKey(sKey)) {
                            ExVR.Components().componentPerKey[sKey].log_message(message, true);
                        } else {
                            ExVR.Log().error(string.Format("[DLL] Receive message from invalid component key {0} : {1}", sKey, message));
                        }
                        break;
                }
            };

            logWarningCB = (message) => { ExVR.Log().warning(message); };
            logWarningIdCB = (message, sType, sKey) => {
                ExVR.Log().error("WARNING");
                switch ((SenderT)sType) {
                    case SenderT.Component:
                        if (ExVR.Components().componentPerKey.ContainsKey(sKey)) {
                            ExVR.Components().componentPerKey[sKey].log_warning(message, true);
                        } else {
                            ExVR.Log().error(string.Format("[DLL] Receive warning from invalid component key {0} : {1}", sKey, message));
                        }
                        break;
                }
            };

            logErrorCB = (message) => { ExVR.Log().error(message); };
            logErrorIdCB = (message, sType, sKey) => {
                ExVR.Log().error("ERROR");
                switch ((SenderT)sType) {
                    case SenderT.Component:
                        if (ExVR.Components().componentPerKey.ContainsKey(sKey)) {
                            ExVR.Components().componentPerKey[sKey].log_error(message, true);
                        } else {
                            ExVR.Log().error(string.Format("[DLL] Receive error from invalid component key {0} : {1}", sKey, message));
                        }
                        break;
                }
            };

            ellapsedTimeExpMsCB = () => {
                return (int)ExVR.Time().ellapsed_exp_ms();
            };
            ellapsedTimeRoutineMsCB = () => {
                return (int)ExVR.Time().ellapsed_element_ms();
            };
            getCB = (string componentName) => {
                return ExVR.Components().get_from_name(componentName).key;
            };

            isVisibleCB = (key) => {
                var c = ExVR.Components().get_from_key(key);
                if (c != null) {
                    return c.is_visible() ? 1 : 0;
                }
                return 0;
            };
            isUpdatingCB = (key) => {
                var c = ExVR.Components().get_from_key(key);
                if (c != null) {
                    return c.is_updating() ? 1 : 0;
                }
                return 0;
            };
            isClosedCB = (key) => {
                var c = ExVR.Components().get_from_key(key);
                if (c != null) {
                    return c.is_closed() ? 1 : 0;
                }
                return 0;
            };

            nextCB = () => {
                ExVR.Events().command.next();
            };
            previousCB = () => {
                ExVR.Events().command.previous();
            };
            closeCB = (key) => {
                var c = ExVR.Components().get_from_key(key);
                if (c != null) {
                    c.close();
                }
            };

            signalBoolCB = (key, index, value) => {
                var c = ExVR.Components().get_from_key(key);
                if (c != null) {
                    c.invoke_signal(string.Format(bracesStr, signalStr, Converter.to_int(index + 1)), (value == 1));
                }
            };
            signalIntCB = (key, index, value) => {
                var c = ExVR.Components().get_from_key(key);
                if (c != null) {
                    c.invoke_signal(string.Format(bracesStr, signalStr, Converter.to_int(index + 1)), value);
                }
            };
            signalFloatCB = (key, index, value) => {
                var c = ExVR.Components().get_from_key(key);
                if (c != null) {
                    c.invoke_signal(string.Format(bracesStr, signalStr, Converter.to_int(index + 1)), value);
                }
            };
            signalDoubleCB = (key, index, value) => {
                var c = ExVR.Components().get_from_key(key);
                if (c != null) {
                    c.invoke_signal(string.Format(bracesStr, signalStr, Converter.to_int(index + 1)), value);
                }
            };
            signalStringCB = (key, index, value) => {
                var c = ExVR.Components().get_from_key(key);
                if (c != null) {
                    c.invoke_signal(string.Format(bracesStr, signalStr, Converter.to_int(index + 1)), value);
                }
            };

            init_callbacks_ex_element(
                logMessageCB, logWarningCB, logErrorCB,
                logMessageIdCB, logWarningIdCB, logErrorIdCB,
                stackTraceCB,
                ellapsedTimeExpMsCB, ellapsedTimeRoutineMsCB,
                getCB,
                isVisibleCB, isUpdatingCB, isClosedCB,
                nextCB, previousCB, closeCB,
                signalBoolCB, signalIntCB, signalFloatCB, signalDoubleCB, signalStringCB
            );
        }

        [DllImport("exvr-export", EntryPoint = "contains_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern int contains_ex_element(HandleRef exElement, int containerId, string name);

        [DllImport("exvr-export", EntryPoint = "set_parameter_bool_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void set_parameter_bool_ex_element(HandleRef exElement, int containerId, string name, int value);

        [DllImport("exvr-export", EntryPoint = "set_parameter_int_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void set_parameter_int_ex_element(HandleRef exElement, int containerId, string name, int value);

        [DllImport("exvr-export", EntryPoint = "set_parameter_float_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void set_parameter_float_ex_element(HandleRef exElement, int containerId, string name, float value);

        [DllImport("exvr-export", EntryPoint = "set_parameter_double_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void set_parameter_double_ex_element(HandleRef exElement, int containerId, string name, double value);

        [DllImport("exvr-export", EntryPoint = "set_parameter_string_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void set_parameter_string_ex_element(HandleRef exElement, int containerId, string name, string value);


        [DllImport("exvr-export", EntryPoint = "get_parameter_int_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern int get_parameter_int_ex_element(HandleRef exElement, int containerId, string name);

        [DllImport("exvr-export", EntryPoint = "get_parameter_float_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern float get_parameter_float_ex_element(HandleRef exElement, int containerId, string name);

        [DllImport("exvr-export", EntryPoint = "get_parameter_double_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern double get_parameter_double_ex_element(HandleRef exElement, int containerId, string name);

        [DllImport("exvr-export", EntryPoint = "get_parameter_string_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern string get_parameter_string_ex_element(HandleRef exElement, int containerId, string name);


        [DllImport("exvr-export", EntryPoint = "get_size_parameter_array_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern int get_size_parameter_array_ex_element(HandleRef exElement, int containerId, string name);

        [DllImport("exvr-export", EntryPoint = "get_parameter_array_int_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void get_parameter_array_int_ex_element(HandleRef exElement, int containerId, string name, int[] array);

        [DllImport("exvr-export", EntryPoint = "get_parameter_array_float_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void get_parameter_array_float_ex_element(HandleRef exElement, int containerId, string name, float[] array);

        [DllImport("exvr-export", EntryPoint = "get_parameter_array_double_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void get_parameter_array_double_ex_element(HandleRef exElement, int containerId, string name, double[] array);


        [DllImport("exvr-export", EntryPoint = "set_parameter_array_int_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void set_parameter_array_int_ex_element(HandleRef exElement, int containerId, string name, int[] values, int size);

        [DllImport("exvr-export", EntryPoint = "set_parameter_array_float_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void set_parameter_array_float_ex_element(HandleRef exElement, int containerId, string name, float[] values, int size);

        [DllImport("exvr-export", EntryPoint = "set_parameter_array_double_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static public extern void set_parameter_array_double_ex_element(HandleRef exElement, int containerId, string name, double[] values, int size);

        [DllImport("exvr-export", EntryPoint = "init_callbacks_ex_element", CallingConvention = CallingConvention.Cdecl)]
        static private extern void init_callbacks_ex_element(
            [MarshalAs(UnmanagedType.FunctionPtr)] LogMessageCB logMessageCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] LogWarningCB logWarningCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] LogErrorCB logErrorCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] LogMessageIdCB logMessageIdCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] LogWarningIdCB logWarningIdCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] LogErrorIdCB logErrorIdCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] StrackTraceCB strackTraceCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] EllapsedTimeExpMsCB ellapsedTimeExpMsCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] EllapsedTimeRoutineMsCB ellapsedTimeRoutineMsCB,
            [MarshalAs(UnmanagedType.FunctionPtr)] GetCB getCB,
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
}