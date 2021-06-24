/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.IO;

// unity
using UnityEngine;
using UnityEngine.UI;

namespace Ex{

    public class VideoSaverComponent : ExComponent{


        private DLL.VideoSaver m_videoSaver = null;

        protected override bool initialize() {

            // init dll
            m_videoSaver = new DLL.VideoSaver();

            // init slots
            add_slot("add frame", (image) => {                
                m_videoSaver.add_frame((ImageContainer)image);
            });

            return m_videoSaver.initialize(initC, key);
        }

        protected override void start_experiment() {
            m_videoSaver.start_experiment();
        }

        protected override void stop_experiment() {
            m_videoSaver.stop_experiment();
        }
    }
}