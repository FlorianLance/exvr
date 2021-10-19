
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Runtime.InteropServices;


namespace Ex.DLL{

    public class PythonScriptComponentDLL : ExComponentDLL{


        #region memory_management

        /// <summary>
        /// PythonComponentDLL default constructor
        /// </summary>
        public PythonScriptComponentDLL() : base() {
        }

        /// <summary>
        /// Allocate DLL memory
        /// </summary>
        protected override void create_DLL_class() {
            _handle = new HandleRef(this, create_python_script_component());
        }

        /// <summary>
        /// Clean DLL memory
        /// </summary>
        protected override void delete_DLL_class() {
            delete_python_script_component(_handle);
        }


        #endregion memory_management    
        #region DllImport

        //// memory management
        [DllImport("exvr-export", EntryPoint = "create_python_script_component", CallingConvention = CallingConvention.Cdecl)]
        static private extern IntPtr create_python_script_component();

        [DllImport("exvr-export", EntryPoint = "delete_python_script_component", CallingConvention = CallingConvention.Cdecl)]
        static private extern void delete_python_script_component(HandleRef pyScript);

        #endregion DllImport        
    }
}
