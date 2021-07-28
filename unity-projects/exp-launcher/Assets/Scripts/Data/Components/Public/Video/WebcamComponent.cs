/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class WebcamComponent : ExComponent{

        private WebCamTexture m_webcamTexture = null;
        private int updateCounter = 0;


        protected override bool initialize() {

            add_signal("new frame");
            add_slot("pause", (nullArg) => { pause(); });
            add_slot("play", (nullArg) => { play(); });
            

            WebCamDevice[] devices = WebCamTexture.devices;
            if (devices.Length == 0) {
                log_error("No device available.");
                return false;
            }

            int id = initC.get<int>("device_id");
            if (id >= devices.Length) {
                log_error("Invalid id device.");
                return false;
            }
            m_webcamTexture = new WebCamTexture(devices[id].name);
            m_webcamTexture.requestedWidth  = initC.get<int>("requested_width");
            m_webcamTexture.requestedHeight = initC.get<int>("requested_height");
            m_webcamTexture.requestedFPS    = initC.get<int>("requested_fps");        
            m_webcamTexture.Play();

            return true;
        }

        protected override void start_experiment() {
            m_webcamTexture.Play();
        }

        protected override void start_routine() {
            updateCounter = 0;
        }

        protected override void update() {

            if (!m_webcamTexture.isPlaying) {
                return;
            }

            var currentTime = time().ellapsed_element_ms();
            double deltaTime = 1000.0 / initC.get<int>("requested_fps");
            if (currentTime / deltaTime > updateCounter) {
                ++updateCounter;
                invoke_signal("new frame", new ImageContainer(m_webcamTexture));
            }
        }

        public override void pause() {
            m_webcamTexture.Pause();
        }

        public override void play() {
            m_webcamTexture.Play();
        }

        protected override void stop_experiment() {
            m_webcamTexture.Stop();
        }
    }
}