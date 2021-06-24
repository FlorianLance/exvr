
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class DebugManager : MonoBehaviour{

        public GlobalVariables globalVariables = null;
        public DisplayExpInfo displayExpInfos = null;
        public void initialize() {
            globalVariables = transform.Find("Global variables").GetComponent<GlobalVariables>();
            displayExpInfos = GetComponent<DisplayExpInfo>();            
        }
    }
}