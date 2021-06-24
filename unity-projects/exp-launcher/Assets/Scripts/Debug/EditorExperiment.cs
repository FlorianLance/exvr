
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#if UNITY_EDITOR

// unity
using UnityEditor;

namespace Ex{


    public class ExperimentMenu{

        [MenuItem("Experiment/Load")]
        static void load_experiment() {

            string instanceFilePath;
            if (System.IO.File.Exists(ExVR.Paths().lastLoadedInstanceFile)) {
                instanceFilePath = ExVR.Paths().lastLoadedInstanceFile;
            } else {
                ExVR.Log().warning("No last loaded instance file found, will try to load default instance file instead.");
                instanceFilePath = ExVR.Paths().defaultInstanceFile;
            }

            ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Load, string.Format("{0}|{1}", ExVR.Paths().expFile, instanceFilePath));
        }
        [MenuItem("Experiment/Start")]
        static void start_experiment() {            
            ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Play);
        }

        [MenuItem("Experiment/Stop")]
        static void stop_experiment() {            
            ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Stop);
        }

        [MenuItem("Experiment/Pause")]
        static void pause_experiment() {            
            ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Pause);
        }

        [MenuItem("Experiment/Next")]
        static void next() {
            ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Next);
        }

        [MenuItem("Experiment/Previous")]
        static void previous() {
            ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Previous);
        }

        [MenuItem("Experiment/Quit")]
        static void quit() {
            ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Quit);
            
        }
    }
}

#endif
