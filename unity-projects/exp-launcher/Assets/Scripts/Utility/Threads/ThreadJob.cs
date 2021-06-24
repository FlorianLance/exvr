/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections;

namespace Ex{

    public class ThreadedJob{

        private bool m_IsDone = false;
        private object m_Handle = new object();
        private System.Threading.Thread m_Thread = null;

        public bool is_done {
            get {
                bool tmp;
                lock (m_Handle) {
                    tmp = m_IsDone;
                }
                return tmp;
            }
            set {
                lock (m_Handle) {
                    m_IsDone = value;
                }
            }
        }

        public void set_priority(System.Threading.ThreadPriority p) {
            if (m_Thread != null) {
                m_Thread.Priority = p;
            }
        }

        public void start() {
            m_Thread = new System.Threading.Thread(run);
            m_Thread.Start();
        }

        public void stop() {
            if (m_Thread != null) {
                m_Thread.Abort();
                m_Thread.Join();
            }
        }

        protected virtual void ThreadFunction() { }

        protected virtual void OnFinished() { }

        public virtual bool update() {
            if (is_done) {
                OnFinished();
                return true;
            }
            return false;
        }

        IEnumerator wait_for() {
            while (!update()) {
                yield return null;
            }
        }

        private void run() {
            ThreadFunction();
            is_done = true;
        }
    }
}