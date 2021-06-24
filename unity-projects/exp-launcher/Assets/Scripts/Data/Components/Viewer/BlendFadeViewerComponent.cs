
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


// unity
using UnityEngine;

namespace Ex{
    public class BlendFadeViewerComponent : CanvasWorldSpaceComponent{

        private GameObject m_overlayGo = null;
        private BlendFadeOverlay m_overlay = null;

        protected override bool initialize() {

            m_overlayGo = ExVR.GlobalResources().instantiate_prebab("Components/BlendFadeOverlay", transform, "Blend fade overlay");
            if(m_overlayGo == null) {
                return false;
            }
            m_overlayGo.transform.localScale = new Vector3(0.4f, 0.4f, 0.4f);
            m_overlay = m_overlayGo.GetComponent<BlendFadeOverlay>();
            m_overlay.initialize();

            return true;
        }

        protected override void start_routine() {

            m_overlay.start_color_change(
                currentC.get<bool>("only_blend"),
                currentC.get_color("start_color"), 
                currentC.get_color("end_color"), 
                currentC.get<float>("duration_blend"),
                currentC.get<float>("duration_fade")
            );
        }

        protected override void set_visibility(bool visibility) {
            m_overlayGo.SetActive(visibility);
        }

        protected override void pre_update() {
            m_overlay.update();
            m_overlayGo.transform.position = CameraUtility.eye_camera_position();
        }

        protected override void update() {
            m_overlayGo.transform.position = CameraUtility.eye_camera_position();
        }

        protected override void post_update() {
            m_overlayGo.transform.position = CameraUtility.eye_camera_position();
        }
    }
}

