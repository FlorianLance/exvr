
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


// unity
using UnityEngine;

namespace Ex{

    public class FixationCrossViewerComponent : CanvasWorldSpaceComponent{

        private GameObject m_backgroundGO = null;
        private GameObject m_crossGO = null;
        private Material m_backgroundMat = null;
        private Material m_crossMat = null;

        #region ex_functions
        protected override bool initialize() {
            m_backgroundGO = ExVR.GlobalResources().instantiate_prebab("Components/FixationCross", transform, "Fixation cross");
            m_crossGO       = m_backgroundGO.transform.Find("Cross").gameObject;
            m_backgroundMat = m_backgroundGO.GetComponent<UnityEngine.UI.Image>().material;
            m_crossMat      = m_crossGO.GetComponent<UnityEngine.UI.Image>().material;
            return m_backgroundGO != null;
        }

        protected override void set_visibility(bool visibility) {
            m_backgroundGO.SetActive(visibility);
        }


        // use_eye_camera
        protected override void post_update() {
            update_position();
        }

        public override void update_from_current_config() {

            var bgTr = m_backgroundGO.GetComponent<RectTransform>();

            // size of GO
            var sizeBG = new Vector2(currentC.get<int>("width"), currentC.get<int>("height"));
            bgTr.sizeDelta = sizeBG;
            m_crossGO.GetComponent<RectTransform>().sizeDelta = sizeBG * currentC.get<float>("cross-size-factor");

            // scale
            var sf = currentC.get<float>("scale_factor") * 0.01f;
            bgTr.localScale = new Vector3(
                sf, sf, sf
            );

            // color
            m_backgroundMat.color = currentC.get_color("background-color");
            m_crossMat.color = currentC.get_color("cross-color");

            update_position();
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            update_from_current_config();
            update_position();
        }

        #endregion

        #region private_functions
        public void update_position() {

            var bgTr = m_backgroundGO.GetComponent<RectTransform>();

            m_backgroundGO.transform.position = Vector3.zero;
            m_backgroundGO.transform.rotation = Quaternion.identity;
            bgTr.pivot = new Vector2(0.5f, 0.5f);

            // position/rotation
            if (currentC.get<bool>("use_eye_camera")) {

                // move to head
                Transform camTr = ExVR.Display().cameras().get_eye_camera_transform();
                m_backgroundGO.transform.position = camTr.position + camTr.forward * currentC.get<float>("distance");
                m_backgroundGO.transform.rotation = camTr.rotation;
                m_backgroundGO.transform.eulerAngles += currentC.get_vector3("rotation");
                bgTr.pivot = currentC.get_vector2("pivot");

            } else {
                bgTr.localPosition = currentC.get_vector3("position");
                bgTr.localEulerAngles = currentC.get_vector3("rotation");
            }
        }
    }

    #endregion
}