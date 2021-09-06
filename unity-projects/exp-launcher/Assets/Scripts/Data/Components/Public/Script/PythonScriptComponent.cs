
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

namespace Ex{

    public class PythonScriptComponent : ExComponent{

        private DLL.PythonScript m_python = null;

        protected override bool initialize() {

            // force catch exception for csharp scripts components
            catchExceptions = true;

            // slots
            add_slot("slot1", (arg) => {
                m_python.call_slot(0, arg);
            });
            add_slot("slot2", (arg) => {
                m_python.call_slot(1, arg);
            });
            add_slot("slot3", (arg) => {
                m_python.call_slot(2, arg);
            });
            add_slot("slot4", (arg) => {
                m_python.call_slot(3, arg);
            });
            // signals
            add_signal("signal1");
            add_signal("signal2");
            add_signal("signal3");
            add_signal("signal4");

            List<string> pathsPython = initC.get_list<string>("paths_python");
            m_python = new DLL.PythonScript();            
            return m_python.initialize(initC, key);
        }

        protected override void start_experiment() {
            m_python.start_experiment();
        }

        protected override void start_routine() {
            m_python.start_routine(currentC);
        }

        protected override void update() {
            m_python.update();
        }

        protected override void set_update_state(bool doUpdate) {
            m_python.set_update_state(doUpdate);
        }

        protected override void set_visibility(bool visibility) {
            m_python.set_visibility(visibility);
        }

        public override void play() {
            m_python.play();
        }

        public override void pause() {
            m_python.pause();
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            m_python.update_parameter_from_gui(updatedArgName);
        }

        protected override void stop_routine() {
            m_python.stop_routine();
        }

        protected override void stop_experiment() {
            m_python.stop_experiment();
        }

        protected override void clean() {
            m_python.clean();
        }
    }
}