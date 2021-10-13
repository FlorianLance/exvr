/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class AudioResourceComponent : ExComponent{

        public Texture2D m_texture = null;

        #region ex_functions

        protected override bool initialize() {
            return true;
        }

        #endregion

        #region private_functions
        private void load_audio() {

            var audioData = currentC.get_resource_audio_data("audio");
            // ...
        }

        #endregion
    }
}