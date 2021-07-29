/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class FlowElement : MonoBehaviour{

        public enum FlowElementType { Routine, Isi };

        protected FlowElementType m_type;
        protected int m_key = -1;
        protected string m_keyStr;
        protected int m_callsNb = 0;
        protected int m_elementIteration = 0;

        public int key() {return m_key;}        
        public string key_str() {return m_keyStr;}        
        public FlowElementType type() {return m_type;}
        public int element_iteration() { return m_elementIteration; }
        public int calls_nb() {return m_callsNb;}
    }
}