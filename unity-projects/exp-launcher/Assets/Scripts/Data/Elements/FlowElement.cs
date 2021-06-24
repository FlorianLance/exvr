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

        public int key() {
            return m_key;
        }        

        public string key_str() {
            return m_keyStr;
        }
        
        public FlowElementType type() {
            return m_type;
        }

        protected FlowElementType m_type;
        protected int m_key = -1;
        protected string m_keyStr;
    }
}