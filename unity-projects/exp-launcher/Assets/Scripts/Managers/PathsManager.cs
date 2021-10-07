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

        public string expLauncherExeFile;
        public string expLauncherMainDir;
        public string expLauncherDataDir;
        public string expLauncherMonoDir;
        public string expLauncherTempGeneratedDir;

        public string designerMainDir;
        public string designerDataTempDir;
        public string designerTempExpFile;
        public string designerDefaultInstanceFile;
        public string designerLogDir;

        public string lastLoadedInstanceFile = "";


        public void initialize() {

            expLauncherDataDir = Application.dataPath;
            var platform = Application.platform;
            if (platform == RuntimePlatform.WindowsPlayer || platform == RuntimePlatform.WindowsEditor) {
                expLauncherMainDir = expLauncherDataDir + "/..";
                expLauncherExeFile = expLauncherMainDir + "/ExVR-exp.exe";
            } else if (platform == RuntimePlatform.LinuxPlayer) {
                //expLauncherMainDir = ...; 
                //expLauncherExeFile = ...;
            }
            else if (platform == RuntimePlatform.OSXPlayer) {
                //expLauncherMainDir = ...;
                //expLauncherExeFile = ...;
            }
            expLauncherMonoDir = expLauncherMainDir + "/mono-scripting";
            expLauncherTempGeneratedDir = expLauncherMainDir + "/temp_generated";
            if (!Directory.Exists(expLauncherTempGeneratedDir)) {
                Directory.CreateDirectory(expLauncherTempGeneratedDir);
            }

#if UNITY_EDITOR
            designerMainDir             = string.Format("{0}/../../cpp-projects/_build/bin/exvr-designer", expLauncherMainDir);
            designerDataTempDir         = string.Format("{0}/data/temp", designerMainDir);
            designerTempExpFile         = string.Format("{0}/data/temp/exp.xml", designerMainDir);                        
            designerLogDir              = string.Format("{0}/logs", designerMainDir);
            designerDefaultInstanceFile = string.Format("{0}/data/temp/debug-instance.xml", designerMainDir);
#else
            designerMainDir             = expLauncherMainDir + "/..";
            designerDataTempDir         = designerMainDir + "/data/temp";
            designerTempExpFile         = designerMainDir + "/data/temp/exp.xml";           
            designerLogDir              = designerMainDir + "/logs";
            designerDefaultInstanceFile = designerMainDir + "/data/temp/debug-instance.xml";
#endif

            if (!File.Exists(designerTempExpFile)) {                
                designerTempExpFile         = expLauncherMainDir + "/exp.xml";
                designerDefaultInstanceFile = expLauncherMainDir + "/debug-instance.xml";
            }
        }


    }
}