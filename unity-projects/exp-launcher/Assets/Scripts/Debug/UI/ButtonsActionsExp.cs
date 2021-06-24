
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections;

// unity
using UnityEngine;
using UnityEngine.UI;

namespace Ex{

    public class ButtonsActionsExp : MonoBehaviour{

        public enum DebugCameraState
        {
            hidden, minimized, expanded
        };

        public Button bReloadCurrent = null;
        public Button bStop = null;
        public Button bPlay = null;
        public Button bPlayPause = null;
        public Button bPlayAfterTen = null;
        public Button bPause = null;
        public Button bNext = null;
        public Button bPrevious = null;
        public Button bToggleCam = null;
        public Button bFPS = null;

        public GameObject debugIndicator = null;

        public DebugCameraState debugCamState = DebugCameraState.hidden;
        public RuntimeDebugCamera runtimeDebugCamera = null;

        IEnumerator play_in_ten_seconds() {

            bReloadCurrent.gameObject.SetActive(false);
            bStop.gameObject.SetActive(false);
            bPlay.gameObject.SetActive(false);
            bPlayPause.gameObject.SetActive(false);
            bPlayAfterTen.gameObject.SetActive(false);
            bPause.gameObject.SetActive(false);
            bNext.gameObject.SetActive(false);
            bPrevious.gameObject.SetActive(false);

            yield return new WaitForSeconds(10);

            bReloadCurrent.gameObject.SetActive(true);
            bStop.gameObject.SetActive(true);
            bPlay.gameObject.SetActive(true);
            bPlayPause.gameObject.SetActive(true);
            bPlayAfterTen.gameObject.SetActive(true);
            bPause.gameObject.SetActive(true);
            bNext.gameObject.SetActive(true);
            bPrevious.gameObject.SetActive(true);

            ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Play);
        }


        // Use this for initialization
        void Start() {

            bReloadCurrent.onClick.AddListener(() => {
                bReloadCurrent.interactable = false;

                string instanceFilePath;
                if (System.IO.File.Exists(ExVR.Paths().lastLoadedInstanceFile)){
                    instanceFilePath = ExVR.Paths().lastLoadedInstanceFile;
                } else {
                    ExVR.Log().warning("No last loaded instance file found, will try to load default instance file instead.");
                    instanceFilePath = ExVR.Paths().defaultInstanceFile;
                }

                ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Load, string.Format("{0}|{1}", ExVR.Paths().expFile, instanceFilePath));
            });
            bStop.onClick.AddListener(() => {
                ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Stop);
            });

            bPlay.onClick.AddListener(() => {
                ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Play);                
            });
            bPlayPause.onClick.AddListener(() => {
                ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.PlayPause);
            });

            bPlayAfterTen.onClick.AddListener(() => {
                StartCoroutine(play_in_ten_seconds());
            });

            bPause.onClick.AddListener(() => {
                ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Pause);
            });

            bNext.onClick.AddListener(() => {                
                ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Next);
            });

            bPrevious.onClick.AddListener(() => {
                ExVR.Network().send_command_from_exp_launcher(NetworkManager.Command.Previous);
            });

            bToggleCam.onClick.AddListener(() => {
                update_runtime_debug_camera();
            });
 

            bFPS.onClick.AddListener(() => {
                var goG = ExVR.GO().DebugScene.transform.Find("[Graphy]").gameObject;
                goG.SetActive(!goG.activeSelf);
            });

            runtimeDebugCamera.hide();
        }

        private void update_runtime_debug_camera() {

            switch (debugCamState) {
                case DebugCameraState.hidden:
                    debugCamState = DebugCameraState.minimized;
                    runtimeDebugCamera.bottom_left();
                    debugIndicator.SetActive(true);
                    break;
                case DebugCameraState.minimized:
                    debugCamState = DebugCameraState.expanded;
                    runtimeDebugCamera.expand();
                    debugIndicator.SetActive(true);
                    break;
                case DebugCameraState.expanded:
                    debugCamState = DebugCameraState.hidden;
                    runtimeDebugCamera.hide();
                    debugIndicator.SetActive(false);
                    break;
            }
        }

        private void Update() {
            
            if (!ExVR.Experiment().is_loaded()) {
                bReloadCurrent.interactable = true;
                bStop.interactable = false;
                bPlay.interactable = false;
                bPlayPause.interactable = false;
                bPlayAfterTen.interactable = false;
                bPause.interactable = false;
                bNext.interactable = false;
                bPrevious.interactable = false;
            } else {

                if (ExVR.Time().is_experiment_started()) {
                    bStop.interactable = true;
                    bNext.interactable = true;
                    bPrevious.interactable = true;

                    if (ExVR.Time().is_experiment_running()) {
                        bPlay.interactable = false;
                        bPlayAfterTen.interactable = false;
                        bPlayPause.interactable = false;
                        bPause.interactable = true;
                    } else {
                        bPlay.interactable = true;
                        bPlayAfterTen.interactable = true;
                        bPlayPause.interactable = true;
                        bPause.interactable = false;
                    }

                } else {
                    bStop.interactable = false;
                    bNext.interactable = false;
                    bPrevious.interactable = false;
                    bPlay.interactable = true;
                    bPlayAfterTen.interactable = true;
                    bPlayPause.interactable = true;
                }
            }
        }
    }
}
