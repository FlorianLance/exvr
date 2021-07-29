
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Text;

// unity
using UnityEngine;
using UnityEngine.UI;

namespace Ex{

    public class DisplayExpInfo : MonoBehaviour {


        public Text tState = null;
        public Text tTime = null;
        public Text tCurrElement = null;
        public Text tComponents = null;
        GuiSettingsManager guiSettings = null;

        // Use this for initialization
        void Start() {

            guiSettings = ExVR.GuiSettings();
            if (guiSettings != null) {
                set_debug_mode(guiSettings.debug);
            }
        }

        public void set_debug_mode(bool enabled) {
            transform.Find("Top UI").gameObject.SetActive(enabled);
        }

        void Update() {

            Scheduler schreduler = ExVR.Schreduler();

            
            var interval = schreduler.current_interval();
            if (interval != null) {
                tTime.text = String.Format("( {0} / {1}s) {2}s )",
                    Math.Round(ExVR.Time().ellapsed_element_s(), 2).ToString("#.00"),
                    Math.Round(interval.tEndS, 2).ToString("#.00"),
                    Math.Round(ExVR.Time().ellapsed_exp_s(), 2).ToString("#.00")
                );
            } else {
                tTime.text = "(0/0s) 0s";
            }

            var info = schreduler.current_element_info();

            if (schreduler.current_element_info() != null) {

                var currentElemenStrBuilder = new StringBuilder();

                if (info.type() == FlowElement.FlowElementType.Routine) {
                    var routineInfo = (RoutineInfo)info;
                    currentElemenStrBuilder.Append("Routine: ");
                    currentElemenStrBuilder.AppendFormat("<color=#00ff00ff>{0}</color> Id: <color=#00ff00ff>{1}</color> Cond: <color=#00ff00ff>{2}</color>",
                        routineInfo.name(),
                        routineInfo.key().ToString(),
                        routineInfo.condition().name
                    );
                } else {
                    var isiInfo = (ISIInfo)info;
                    currentElemenStrBuilder.Append("ISI: ");
                    currentElemenStrBuilder.AppendFormat("<color=#00ff00ff>{0}</color> Id: <color=#00ff00ff>{1}</color> Cond: <color=#00ff00ff>{2}</color>",
                        isiInfo.name(),
                        isiInfo.key().ToString(),
                        isiInfo.duration_str()
                    );
                }

                tCurrElement.text = currentElemenStrBuilder.ToString();
            } else {
                tCurrElement.text = "None";
            }

            if (ExVR.Time().is_experiment_started()) {

                if (ExVR.Time().is_paused()) {
                    tState.text = "Paused";
                } else {
                    tState.text = "Running";
                }
            }else {  
                tState.text = "Stopped";
            }

            var allComponents = ExVR.Components().get_all();
            int componentsInitialized = 0;
            int componentsUpdating = 0;
            int componentsVisible = 0;
            foreach (ExComponent component in allComponents) {

                ++componentsInitialized;
                if (component.is_updating()) {
                    ++componentsUpdating;
                }
                if (component.is_visible()) {
                    ++componentsVisible;
                }
            }

            var componentStrBuilder = new StringBuilder();
            componentStrBuilder.AppendFormat("<color=#00ff00ff>{0}</color> components initialized out of <color=#00ff00ff>{1}</color> loaded\n", 
                componentsInitialized.ToString(), 
                allComponents.Count.ToString()
            );
            componentStrBuilder.AppendFormat("<color=#00ff00ff>{0}</color> updating\n", componentsUpdating.ToString());
            componentStrBuilder.AppendFormat("<color=#00ff00ff>{0}</color> visible", componentsVisible.ToString());
            tComponents.text = componentStrBuilder.ToString();
        }
    }
}
