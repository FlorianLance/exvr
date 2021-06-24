
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class GoExplorer : MonoBehaviour{

        [Header("Settings")]
        [Rename("Gui")]
        public GameObject GuiSettings = null;
        [Rename("Network")]
        public GameObject NetworkSettings = null;
        [Rename("VR")]
        public GameObject VRSettings = null;
        [Rename("Events")]
        public GameObject EventsSettings = null;
        [Rename("Audio")]
        public GameObject AudioSettings = null;
        [Rename("Paths")]
        public GameObject PathsSettings = null;
        [Rename("Scripting")]
        public GameObject ScriptingSettings = null;
        [Rename("Log")]
        public GameObject LogSettings = null;

        [Header("Experiment content")]
        public GameObject Experiment = null;
        public GameObject Routines = null;
        public GameObject Components = null;
        public GameObject ISIs = null;
        public GameObject Connectors = null;

        [Header("Debug")]
        [Rename("Scene")]
        public GameObject DebugScene = null;
        [Rename("UI")]
        public GameObject DebugUI = null;
        [Rename("Editor camera")]
        public GameObject DebugEditorCamera = null;
        [Rename("Content")]
        public GameObject DebugContent = null;

        [Header("Global")]
        [Rename("Scene")]
        public GameObject GlobalScene = null;
        [Rename("Lights")]
        public GameObject GlobalLights = null;

        public GameObject instantiate(GameObject go, Transform parent = null, bool worldSpace = false) {
            return Instantiate(go, parent, worldSpace);
        }
    }
}