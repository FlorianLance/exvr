/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.IO;

// unity
using UnityEngine;

namespace Ex{

    public class PathsManager : MonoBehaviour{

        public string exeFile;

        public string unityMainDir;
        public string unityDataDir;

        public string expDir;
        public string expFile;
        public string defaultInstanceFile;

        public string lastLoadedInstanceFile = "";

        public string logDir;

        public string monoDir;
        
        public void initialize() {

            unityDataDir = Application.dataPath;
            var platform = Application.platform;
            if (platform == RuntimePlatform.WindowsPlayer || platform == RuntimePlatform.WindowsEditor) {
                unityMainDir = unityDataDir + "/..";
                exeFile      = unityMainDir + "/ExVR-exp.exe";
            } else if (platform == RuntimePlatform.LinuxPlayer) {
                //unityMainDir = unityDataDir + "/../.."; 
                //exeFile = unityMainDir + "/ExVR-exp.exe";
            } else if (platform == RuntimePlatform.OSXPlayer) {
                //unityMainDir = unityDataDir + "/../..";
                //exeFile = unityMainDir + "/ExVR-exp.exe";
            }
            monoDir = unityDataDir + "/../mono-scripting";

#if UNITY_EDITOR
            string config   = "release";// ExVR.GuiSettings().designerDebugBuild ? "debug" : "release";
            expDir          = string.Format("{0}/../../../build/bin/{1}/designer/data/temp", unityDataDir, config);
            expFile         = string.Format("{0}/../../../build/bin/{1}/designer/data/temp/exp.xml", unityDataDir, config);            
            defaultInstanceFile    = string.Format("{0}/../../../build/bin/{1}/designer/data/temp/debug-instance.xml", unityDataDir, config);
            logDir          = string.Format("{0}/../../../build/bin/{1}/designer/logs", unityDataDir, config);
#else
            expDir  = unityDataDir + "/../../data/temp";
            expFile = unityDataDir + "/../../data/temp/exp.xml";
            defaultInstanceFile = unityDataDir + "/../../data/temp/debug-instance.xml";  
            logDir = unityDataDir + "/../../logs";
#endif

            if (!File.Exists(expFile)) {                
                expDir              = unityDataDir;
                expFile             = unityDataDir + "/exp.xml";
                defaultInstanceFile = unityDataDir + "/debug-instance.xml";
            }
        }
    }
}