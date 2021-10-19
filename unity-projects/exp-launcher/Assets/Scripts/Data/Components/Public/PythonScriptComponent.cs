
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

namespace Ex{

    public class PythonScriptComponent : CppComponent{


        protected override bool initialize() {

            // init DLL
            cppDll = new DLL.PythonScriptComponentDLL();
            cppDll.parent = this;

            // force catch exception for csharp scripts components
            catchExceptions = true;

            // slots
            add_slot("slot1", (arg) => {
                cppDll.call_slot(0, arg);
            });
            add_slot("slot2", (arg) => {
                cppDll.call_slot(1, arg);
            });
            add_slot("slot3", (arg) => {
                cppDll.call_slot(2, arg);
            });
            add_slot("slot4", (arg) => {
                cppDll.call_slot(3, arg);
            });
            // signals
            add_signal("signal1");
            add_signal("signal2");
            add_signal("signal3");
            add_signal("signal4");

            List<string> pathsPython = initC.get_list<string>("paths_python");
            // ...
     
            return cppDll.initialize();
        }
    }
}