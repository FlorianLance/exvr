
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public struct CameraSettings{

        public CameraSettings(Camera camera) {
            this.camera = camera;
            defaultBackgroundColor = camera.backgroundColor;
            defaultClearFlags = camera.clearFlags;
        }

        public void reset_default() {
            camera.backgroundColor = defaultBackgroundColor;
            camera.clearFlags = defaultClearFlags;
        }

        public void set_background_color(Color color) {
            camera.backgroundColor = color;
        }

        public void set_clear_flags(CameraClearFlags flags) {
            camera.clearFlags = flags;
        }

        CameraClearFlags defaultClearFlags;
        Color defaultBackgroundColor;
        Camera camera;
    }

}