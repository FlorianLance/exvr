/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;


// unity
using UnityEngine;

namespace Ex {

    public class ElectrodeInfo {
        public string name = "";
        public List<int> pixelsId = new List<int>();
        public double score = 0.0;
    }

    public class TkvEEGComponent : ExComponent {

        private static readonly string eegQualitySignal             = "eeg quality";
        private static readonly string eegQualityValidatedSignal    = "eeg quality validated";        
        private static readonly string cogFeaturesSignal            = "COG features";
        private static readonly string bandsPowersSignal            = "bands powers";

        // network
        private WebsocketClientComponent m_websocketClientC = null;

        // headset
        public bool eegHeadsetDefined = false;
        public string eegHeadsetName;
        // electrodes
        public List<string> electrodesNamesPerId = null;
        public double sampleRateQuality = 0.0;
        public double overallEEGQuality = 0.0;
        public bool electrodesValidity = false;
        private Dictionary<Color32, ElectrodeInfo> m_electrodesInfoPerColor = null;
        private Dictionary<string, ElectrodeInfo> m_electrodesInfoPerName = null;        
        private Texture2D m_electrodesMapT = null;
        private Color32[] m_electrodesMapPixels = null;


        #region ex_functions

        protected override bool initialize() {

            // add slots
            add_slot("send trigger", (triggerName) => {
                m_websocketClientC.send_message("TRIGGER%" + triggerName);
            });
            // add signals
            add_signal(eegQualitySignal);
            add_signal(eegQualityValidatedSignal);
            add_signal(cogFeaturesSignal);
            add_signal(bandsPowersSignal);

            // retrieve websocket client
            m_websocketClientC = initC.get_component<WebsocketClientComponent>("websocket_client_component");
            if (m_websocketClientC == null) {
                log_error("No websocket component set. Initialization aborted");
                return false;
            }

            // retrieve resources
            Texture2D headsetElectrodesQualityImageR = initC.get_resource_image("headset_electrodes_quality_image");
            if(headsetElectrodesQualityImageR != null) {
                // init map
                m_electrodesInfoPerColor = new Dictionary<Color32, ElectrodeInfo>();
            } else {
                log_warning("No electrodes image resource set.");
            }

            string electrodesColorsStr = initC.get_resource_text("electrodes_colors");
            if(electrodesColorsStr != "text_not_found") {
                // init map
                m_electrodesInfoPerName = new Dictionary<string, ElectrodeInfo>();
            } else {
                log_warning("No electrodes colors resource text set.");
            }

            if(m_electrodesInfoPerName != null && m_electrodesInfoPerColor != null) {


                // retrieve correspondances
                foreach (var line in Ex.Text.split(electrodesColorsStr, "\n", false)) {

                    var electrodeInfoStr = Ex.Text.split(line, " ", false);

                    string electrodeName = electrodeInfoStr[0];
                    Color32 electrodeColor = new Color32((byte)Converter.to_int(electrodeInfoStr[1]), 0, 0, 255);

                    var elecInfo = new ElectrodeInfo();
                    elecInfo.name = electrodeName;

                    m_electrodesInfoPerColor[electrodeColor] = elecInfo;
                    m_electrodesInfoPerName[electrodeName] = elecInfo;
                }

                // retrieve pixels per electrode
                m_electrodesMapPixels = headsetElectrodesQualityImageR.GetPixels32();
                for (int idP = 0; idP < m_electrodesMapPixels.Length; ++idP) {
                    if (m_electrodesInfoPerColor.ContainsKey(m_electrodesMapPixels[idP])) {
                        m_electrodesInfoPerColor[m_electrodesMapPixels[idP]].pixelsId.Add(idP);
                    }
                }

                // init image texture
                m_electrodesMapT = new Texture2D(headsetElectrodesQualityImageR.width, headsetElectrodesQualityImageR.height);
                m_electrodesMapT.filterMode = FilterMode.Trilinear;
                m_electrodesMapT.wrapMode = TextureWrapMode.Clamp;
                foreach (var elecInfo in m_electrodesInfoPerName) {
                    var currentElectrodeInfo = elecInfo.Value;
                    foreach (var pId in currentElectrodeInfo.pixelsId) {
                        m_electrodesMapPixels[pId] = new Color32(122, 122, 122, 255);
                    }
                }

                // update texture 2D
                m_electrodesMapT.SetPixels32(m_electrodesMapPixels);
                m_electrodesMapT.Apply();

                invoke_signal("eeg quality", new ImageContainer(m_electrodesMapT, false));

            } else {
                log_warning("Resources must be set for computing EEG quality image.");
            }

            return true;
        }
        protected override void start_experiment() {

            eegHeadsetDefined       = false;
            eegHeadsetName          = "undefined";
            electrodesNamesPerId    = new List<string>();
        }

        protected override void start_routine() {

            m_websocketClientC.connections().get_signal("message read").ev += (sender, value) => {
                var timeMessage = (TimeAny)value;
                parse_message((string)timeMessage.value);
            };
        }

        protected override void clean() {
            if (m_electrodesMapT != null) {
                Destroy(m_electrodesMapT);
                m_electrodesMapT = null;
            }
        }


        #endregion

        #region private_functions


        void parse_message(string message) {

            string[] strList = Ex.Text.split(message, " ", true);
            if (strList.Length == 0) {
                return;
            }

            string idMess = strList[0];

            if (idMess == "HEADSET" && !eegHeadsetDefined) {
                eegHeadsetName = strList[1];
                int nbElectrodes = strList.Length - 2;
                electrodesNamesPerId = new List<string>(nbElectrodes);
                for (int idE = 0; idE < nbElectrodes; ++idE) {
                    electrodesNamesPerId.Add(strList[2 + idE]);
                }
                eegHeadsetDefined = true;
            } else if (idMess == "EM_EEG_QUA") {

                //Debug.Log("-> " + message);
                sampleRateQuality = Converter.to_double(strList[1]);
                overallEEGQuality = Converter.to_double(strList[2]);

                int nbElectrodes = strList.Length - 4;
                if (nbElectrodes != electrodesNamesPerId.Count) {
                    log_error("Invalid number of electrodes.");
                    return;
                }

                int nbNoSignal = 0;
                int nbBad = 0;
                int nbPoor = 0;
                int nbOk = 0;
                int nbGood = 0;
                for (int idE = 0; idE < nbElectrodes; ++idE) {

                    var currentElectrodeName = electrodesNamesPerId[idE];
                    var currentElectrodeInfo = m_electrodesInfoPerName[currentElectrodeName];
                    currentElectrodeInfo.score = Converter.to_int(strList[4 + idE]);

                    if (currentElectrodeInfo.score == 1) {  // BAD
                        ++nbBad;
                    } else if (currentElectrodeInfo.score == 2) { // POOR
                        ++nbPoor;
                    } else if (currentElectrodeInfo.score == 3) { // OK?
                        ++nbOk;
                    } else if (currentElectrodeInfo.score == 4) { // GOOD
                        ++nbGood;
                    } else { // NO SIGNAL
                        ++nbNoSignal;
                    }

                    if (m_electrodesMapPixels != null) {
                        foreach (var pId in currentElectrodeInfo.pixelsId) {
                            if (currentElectrodeInfo.score == 1) {  // BAD
                                m_electrodesMapPixels[pId] = new Color32(255, 0, 0, 255);
                            } else if (currentElectrodeInfo.score == 2) { // POOR
                                m_electrodesMapPixels[pId] = new Color32(255, 187, 0, 255);
                            } else if (currentElectrodeInfo.score == 3) { // OK?
                                m_electrodesMapPixels[pId] = new Color32(187, 255, 0, 255);
                            } else if (currentElectrodeInfo.score == 4) { // GOOD
                                m_electrodesMapPixels[pId] = new Color32(0, 255, 0, 255);
                            } else { // NO SIGNAL
                                m_electrodesMapPixels[pId] = new Color32(122, 122, 122, 255);
                            }
                        }
                    }
                }

                // send eeg quality image
                if (m_electrodesMapPixels != null) {
                    m_electrodesMapT.SetPixels32(m_electrodesMapPixels);
                    m_electrodesMapT.Apply();
                    invoke_signal(eegQualitySignal, new ImageContainer(m_electrodesMapT, false));
                }

                bool qualityValidated = false;
                int eegQualityRequirments = initC.get<int>("eeg_quality_requirments");
                if (eegQualityRequirments == 0) {
                    qualityValidated = (nbGood + nbOk + nbPoor) == nbElectrodes;
                } else if (eegQualityRequirments == 1) {
                    qualityValidated = (nbGood + nbOk) == nbElectrodes;
                } else if (eegQualityRequirments == 2) {
                    qualityValidated = nbGood == nbElectrodes;
                }

                // send eeg quality                    
                invoke_signal(eegQualityValidatedSignal, qualityValidated);

            } else if (idMess == "COG_FEAT") {

                invoke_signal(cogFeaturesSignal, new StringAny("arousal",           Converter.to_double(strList[2])));
                invoke_signal(cogFeaturesSignal, new StringAny("mentalAlterness",   Converter.to_double(strList[3])));
                invoke_signal(cogFeaturesSignal, new StringAny("mentalFatigue",     Converter.to_double(strList[4])));
                invoke_signal(cogFeaturesSignal, new StringAny("valence",           Converter.to_double(strList[5])));

            } else if (idMess == "BAND_POW") {

                for (int idS = 2; idS < strList.Length; idS += 7) {
                    var idE         = Converter.to_int(strList[idS + 0]);
                    var theta       = Converter.to_double(strList[idS + 1]);
                    var alpha       = Converter.to_double(strList[idS + 2]);
                    var betaL       = Converter.to_double(strList[idS + 3]);
                    var betaH       = Converter.to_double(strList[idS + 4]);
                    var gamma       = Converter.to_double(strList[idS + 5]);
                    var fullBeta    = Converter.to_double(strList[idS + 6]);

                    string electrodeName = electrodesNamesPerId[idE];
                    invoke_signal(bandsPowersSignal, new StringAny(string.Format("{0}_theta",    electrodeName), theta));
                    invoke_signal(bandsPowersSignal, new StringAny(string.Format("{0}_alpha",    electrodeName), alpha));
                    invoke_signal(bandsPowersSignal, new StringAny(string.Format("{0}_betaL",    electrodeName), betaL));
                    invoke_signal(bandsPowersSignal, new StringAny(string.Format("{0}_betaH",    electrodeName), betaH));
                    invoke_signal(bandsPowersSignal, new StringAny(string.Format("{0}_gamma",    electrodeName), gamma));
                    invoke_signal(bandsPowersSignal, new StringAny(string.Format("{0}_fulLBeta", electrodeName), fullBeta));
                }

            } else if (idMess == "TRIGGER_EVENT") {

                string[] subSplit = Ex.Text.split(message, "#", true);

                foreach (var split in subSplit) {

                    var values = Ex.Text.split(split, " ", true);
                    var idField = values[0];

                    if (idField == "EVENT_BEFORE_BAND_POW") {
                        var subValues = Ex.Text.split(split, "%", true);
                        for (int idS                = 1; idS < subValues.Length; ++idS) {
                            var bpS                 = Ex.Text.split(subValues[idS], " ", true);
                            var idE                 = Converter.to_int(   bpS[0]);
                            var theta               = Converter.to_double(bpS[1]);
                            var alpha               = Converter.to_double(bpS[2]);
                            var betaL               = Converter.to_double(bpS[3]);
                            var betaH               = Converter.to_double(bpS[4]);
                            var gamma               = Converter.to_double(bpS[5]);
                            var fullBeta            = Converter.to_double(bpS[6]);
                            string electrodeName    = electrodesNamesPerId[idE];
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("bef_trig_{0}_theta",    electrodeName), theta));
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("bef_trig_{0}_alpha",    electrodeName), alpha));
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("bef_trig_{0}_betaL",    electrodeName), betaL));
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("bef_trig_{0}_betaH",    electrodeName), betaH));
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("bef_trig_{0}_gamma",    electrodeName), gamma));
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("bef_trig_{0}_fulLBeta", electrodeName), fullBeta));
                        }
                    }else if (idField == "EVENT_AFTER_BAND_POW") {
                        var subValues = Ex.Text.split(split, "%", true);
                        for (int idS = 1; idS < subValues.Length; ++idS) {
                            var bpS                 = Ex.Text.split(subValues[idS], " ", true);
                            var idE                 = Converter.to_int(bpS[0]);
                            var theta               = Converter.to_double(bpS[1]);
                            var alpha               = Converter.to_double(bpS[2]);
                            var betaL               = Converter.to_double(bpS[3]);
                            var betaH               = Converter.to_double(bpS[4]);
                            var gamma               = Converter.to_double(bpS[5]);
                            var fullBeta            = Converter.to_double(bpS[6]);
                            string electrodeName    = electrodesNamesPerId[idE];
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("aft_trig_{0}_theta",    electrodeName), theta));
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("aft_trig_{0}_alpha",    electrodeName), alpha));
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("aft_trig_{0}_betaL",    electrodeName), betaL));
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("aft_trig_{0}_betaH",    electrodeName), betaH));
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("aft_trig_{0}_gamma",    electrodeName), gamma));
                            invoke_signal(bandsPowersSignal, new StringAny(string.Format("aft_trig_{0}_fulLBeta", electrodeName), fullBeta));
                        }
                    } else if (idField == "EVENT_BEFORE_COG_FEAT") {

                        var arousal         = Converter.to_double(values[2]);
                        var mentalAlterness = Converter.to_double(values[3]);
                        var mentalFatigue   = Converter.to_double(values[4]);
                        var valence         = Converter.to_double(values[5]);

                        invoke_signal(cogFeaturesSignal, new StringAny("bef_trig_arousal",           arousal));
                        invoke_signal(cogFeaturesSignal, new StringAny("bef_trig_mentalAlterness",   mentalAlterness));
                        invoke_signal(cogFeaturesSignal, new StringAny("bef_trig_mentalFatigue",     mentalFatigue));
                        invoke_signal(cogFeaturesSignal, new StringAny("bef_trig_valence",           valence));

                    } else if (idField == "EVENT_AFTER_COG_FEAT") {

                        var arousal         = Converter.to_double(values[2]);
                        var mentalAlterness = Converter.to_double(values[3]);
                        var mentalFatigue   = Converter.to_double(values[4]);
                        var valence         = Converter.to_double(values[5]);

                        invoke_signal(cogFeaturesSignal, new StringAny("aft_trig_arousal", arousal));
                        invoke_signal(cogFeaturesSignal, new StringAny("aft_trig_mentalAlterness", mentalAlterness));
                        invoke_signal(cogFeaturesSignal, new StringAny("aft_trig_mentalFatigue", mentalFatigue));
                        invoke_signal(cogFeaturesSignal, new StringAny("aft_trig_valence", valence));
                    }
                }   
            }
        }
        #endregion
    }
}
