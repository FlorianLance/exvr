/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Diagnostics;

namespace Ex.Events{

    public class Signal{

        //bool m_infiniteLoop = false;
        //int m_invokeCount = 0;
        //private Stopwatch m_swInfinityLoop = new Stopwatch();

        public string m_name;

        public void log_error(string error) {
            ExVR.Log().error(String.Format("[SIGNAL] {0} : {1}", m_name, error));
        }

        public event EventHandler<object> ev = delegate { };
        public void invoke(object arg = null) {

            //if (check_infinity_loop()) {
            //    return;
            //}

            ev?.Invoke(this, arg);
        }

        public void reset() {
            ev = delegate { };
        }

        public Signal(string name) {
            m_name = name;
        }

        public string name() {
            return m_name;
        }

        public void remove_listeners() {
            reset();
        }

        //private bool check_infinity_loop() {

        //    if (m_infiniteLoop) {
        //        return true;
        //    }

        //    if (!m_swInfinityLoop.IsRunning) {
        //        m_swInfinityLoop.Start();
        //    }

        //    if (m_swInfinityLoop.Elapsed.TotalMilliseconds < 1000.0 / 90.0) {
        //        m_invokeCount++;

        //        if (m_invokeCount > 2500) {
        //            m_infiniteLoop = true;
        //            m_swInfinityLoop.Stop();
        //            log_error("Signal/Slot infinity loop detected, connection canceled.");
        //            return true;
        //        }
        //    } else {
        //        m_swInfinityLoop.Restart();
        //        m_invokeCount = 0;
        //    }

        //    return false;
        //}
    }
}