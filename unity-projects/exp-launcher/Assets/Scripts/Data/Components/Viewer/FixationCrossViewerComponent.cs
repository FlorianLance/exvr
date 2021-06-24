
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


// unity
using UnityEngine;

namespace Ex{

    public class FixationCrossViewerComponent : CanvasWorldSpaceComponent{

        private GameObject m_fixationCrossGO = null;
        public Texture2D m_texture = null;

        private int m_currentImageWidth = 500;
        private int m_currentImageHeight = 500;

        protected override bool initialize() {
            m_fixationCrossGO = ExVR.GlobalResources().instantiate_prebab("Components/FixationCross", transform, "Fixation cross");
            return m_fixationCrossGO != null;
        }

        protected override void start_routine() {
            resize_image();
        }

        protected override void set_visibility(bool visibility) {
            m_fixationCrossGO.SetActive(visibility);
        }

        protected override void update_parameter_from_gui(XML.Arg arg) {
            resize_image();
        }

        // use_eye_camera
        protected override void pre_update() {
            resize_image();
        }

        public void resize_image() {
            
            m_fixationCrossGO.transform.position = Vector3.zero;
            m_fixationCrossGO.transform.rotation = Quaternion.identity;

            var rTr = m_fixationCrossGO.GetComponent<RectTransform>();
            rTr.pivot = new Vector2(0.5f, 0.5f);

            if (currentC.get<bool>("use_eye_camera")) {

                // move to head
                Transform camTr = ExVR.Display().cameras().get_eye_camera_transform();
                m_fixationCrossGO.transform.position = camTr.position + camTr.forward * currentC.get<float>("distance");
                m_fixationCrossGO.transform.rotation = camTr.rotation;
                m_fixationCrossGO.transform.eulerAngles += currentC.get_vector3("rotation");
                rTr.pivot = currentC.get_vector2("pivot");

            } else {
                rTr.localPosition = currentC.get_vector3("position");
                rTr.localEulerAngles = currentC.get_vector3("rotation");
            }

            rTr.sizeDelta = ((currentC.get<bool>("use_original_size")) ?
                        new Vector2(m_currentImageWidth, m_currentImageHeight) :
                        new Vector2(currentC.get<int>("width"), currentC.get<int>("height"))
            );

            var sf = currentC.get<float>("scale_factor") * 0.01f;
            rTr.localScale = new Vector3(
                sf, sf, sf
            );
        }

    }
}