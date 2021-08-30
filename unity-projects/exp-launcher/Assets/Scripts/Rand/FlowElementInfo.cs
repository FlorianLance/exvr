/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex{

    public class FlowElementInfo{

        protected FlowElement m_element = null;
        protected Interval m_interval;
        protected int m_order;
        protected int m_elementIteration;

        public int key() {
            return m_element.key();
        }

        public FlowElement element() {
            return m_element;
        }

        public Interval interval() {
            return m_interval;
        }
        public FlowElement.FlowElementType type() {
            return m_element.type();
        }

        public string name() {
            return m_element.name;
        }

        public int order() {
            return m_order;
        }

        public int element_iteration() {
            return m_elementIteration;
        }
    }

    public class RoutineInfo : FlowElementInfo{

        private Condition m_condition = null;
        private int m_conditionIteration;

        public RoutineInfo(Routine routine, Condition condition, Interval interval, int order, int elementIteration, int conditionIteration) {
            m_element = routine;
            m_condition = condition;
            m_interval = interval;
            m_order = order;
            m_elementIteration = elementIteration;
            m_conditionIteration = conditionIteration;
        }

        public Condition condition() {
            return m_condition;
        }

        public int condition_iteration() {
            return m_conditionIteration;
        }
    }
    public class ISIInfo : FlowElementInfo{

        private string m_durationStr;
        private int m_durationIteration;

        public ISIInfo(ISI isi, string durationStr, Interval interval, int order, int elementIteration, int durationIteration) {
            m_element = isi;
            m_durationStr = durationStr;
            m_interval = interval;
            m_order = order;
            m_elementIteration = elementIteration;
            m_durationIteration = durationIteration;
        }
        public string duration_str() {
            return m_durationStr;
        }

        public int duration_iteration() {
            return m_durationIteration;
        }
    }
}