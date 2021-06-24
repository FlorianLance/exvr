/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;

namespace Ex.Events{
    public class Slot{

        private System.Action<object> m_action = null;
        private string m_name;

        public void log_error(string error) {
            ExVR.Log().error(string.Format("[SLOT] {0} : {1}", m_name, error));
        }

        public Slot(string name, System.Action<object> action) {
            m_action = action;
            m_name = name;
        }
        public string name() {
            return m_name;
        }

        public void connect(Signal signal) {
            signal.ev += (sender, value) => m_action.Invoke(value);
        }

        public void connect(Signal signal, Func<object, object> convertor) {
            signal.ev += (sender, value) => m_action.Invoke(convertor.Invoke(value));
        }
    }
}
