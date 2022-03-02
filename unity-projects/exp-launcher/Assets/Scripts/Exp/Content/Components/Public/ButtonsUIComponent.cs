
/***********************************************************************************
** exvr-exp                                                                       **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// system
using System.Collections.Generic;

// unity
using UnityEngine;
using UnityEngine.UI;

// TMPro
using TMPro;

namespace Ex {

    public class ButtonsUIComponent : CanvasWorldSpaceComponent {
        
        public GameObject m_buttonsUiGO = null;

        public TextMeshProUGUI m_topText    = null;
        public TextMeshProUGUI m_bottomText = null;
        public TextMeshProUGUI m_leftText   = null;
        public TextMeshProUGUI m_rightText  = null;
        public Transform m_buttonsParent = null;
        public List<GameObject> m_buttonsLine = null;

        public Dictionary<int, Dictionary<int, Button>> m_buttons = null;
        public Dictionary<int, Dictionary<int, TextMeshProUGUI>> m_buttonsText = null;

        //private float currentRandValue = 0f;

        //private static Dictionary<string, TextAlignmentOptions> m_alignment = null;

        protected override bool initialize() {

    
            // signals
            //add_signal("button updated");
            // slots            
            //add_slot("set button", (buttonId) => { });
            //add_slot("next",    (nullArg) => { });
            //add_slot("previous", (nullArg) => {});

            m_buttonsUiGO = ExVR.GlobalResources().instantiate_prebab("Components/ButtonsUI", transform);            
            m_buttonsUiGO.name = "Buttons UI";
            m_buttonsUiGO.GetComponent<UnityEngine.UI.Image>().material = ExVR.GlobalResources().instantiate_default_transparent_mat();

            m_topText       = m_buttonsUiGO.transform.Find("Top text").GetComponent<TextMeshProUGUI>();
            m_topText.text = "...";

            m_bottomText = m_buttonsUiGO.transform.Find("Bottom text").GetComponent<TextMeshProUGUI>();
            m_bottomText.text = "...";

            m_leftText = m_buttonsUiGO.transform.Find("Middle/Left text").GetComponent<TextMeshProUGUI>();
            m_leftText.text = "...";

            m_rightText = m_buttonsUiGO.transform.Find("Middle/Right text").GetComponent<TextMeshProUGUI>();
            m_rightText.text = "...";

            m_buttonsParent = m_buttonsUiGO.transform.Find("Middle/Buttons");



            int nbButtonsH = 2;
            int nbButtonsV = 2;

            m_buttons = new Dictionary<int, Dictionary<int, Button>>(nbButtonsV);
            m_buttonsText = new Dictionary<int, Dictionary<int, TextMeshProUGUI>>(nbButtonsV);
            m_buttonsLine = new List<GameObject>(nbButtonsV);
            for (int ii = 0; ii < nbButtonsV; ++ii) {

                var lineGO = GO.generate_empty_scene_object(string.Format("Line{0}", ii), m_buttonsParent, true);
                lineGO.transform.localPosition = new Vector3(0, 0, -0.01f);
                lineGO.transform.localScale = new Vector3(1, 1, 1);
                var le = lineGO.AddComponent<LayoutElement>();
                le.flexibleWidth = 1f;
                le.flexibleHeight = 1f;

                var hlg = lineGO.AddComponent<HorizontalLayoutGroup>();
                hlg.childControlWidth = true;
                hlg.childControlHeight = true;
                hlg.childScaleWidth = false;
                hlg.childScaleHeight = false;
                hlg.childForceExpandWidth = true;
                hlg.childForceExpandHeight = true;

                m_buttonsLine.Add(lineGO);

                var lineButtons = new Dictionary<int, Button>(nbButtonsH);
                var lineButtonsText = new Dictionary<int, TextMeshProUGUI>(nbButtonsH);
                for (int jj = 0; jj < nbButtonsH; ++jj) {
                    var buttonGO = ExVR.GlobalResources().instantiate_prebab("Common/Button", lineGO.transform, "Button");
                    buttonGO.SetActive(true);
                    buttonGO.transform.localPosition = Vector3.zero;
                    buttonGO.transform.localScale = new Vector3(1, 1, 1);

                    var button = buttonGO.GetComponent<Button>();

                    button.interactable = false;
                    if (jj == 0) {
                        button.interactable = true;
                    }

                    lineButtons.Add(jj, button);
                    lineButtonsText.Add(jj, buttonGO.transform.Find("Text (TMP)").gameObject.GetComponent<TextMeshProUGUI>());
                }
                m_buttons.Add(ii, lineButtons);
                m_buttonsText.Add(ii, lineButtonsText);
            }




            return true;
        }

        protected override void start_routine() {


        }

        protected override void set_visibility(bool visibility) {
            m_buttonsUiGO.SetActive(visibility);
        }

        public override void update_from_current_config() {
            resize_container();
            update_ui();
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            update_from_current_config();
        }


        protected override void post_update() {
            resize_container();
        }


        public void resize_container() {

            m_buttonsUiGO.transform.position = Vector3.zero;
            m_buttonsUiGO.transform.rotation = Quaternion.identity;

            var rTr = m_buttonsUiGO.GetComponent<RectTransform>();
            rTr.pivot = new Vector2(0.5f, 0.5f);

            if (currentC.get<bool>("use_eye_camera")) {

                // move to head
                Transform camTr = ExVR.Display().cameras().get_eye_camera_transform();
                m_buttonsUiGO.transform.position = camTr.position + camTr.forward * currentC.get<float>("distance");
                m_buttonsUiGO.transform.rotation = camTr.rotation;
                m_buttonsUiGO.transform.eulerAngles += currentC.get_vector3("rotation");
                rTr.pivot = currentC.get_vector2("pivot");

            } else {
                rTr.localPosition = currentC.get_vector3("position");
                rTr.localEulerAngles = currentC.get_vector3("rotation");
            }

            rTr.sizeDelta =
                new Vector2(currentC.get<int>("width"), currentC.get<int>("height")
            );

            var sf = currentC.get<float>("scale_factor") * 0.01f;
            rTr.localScale = new Vector3(
                sf, sf, sf
            );
        }

        private void update_ui() {

            // container
            // # background            
            m_buttonsUiGO.GetComponent<UnityEngine.UI.Image>().material.color = currentC.get_color("background_color");

            // textes                        
            currentC.update_text("left_t", m_leftText);
            currentC.update_text("right_t", m_rightText);
            currentC.update_text("top_t", m_topText);
            currentC.update_text("bottom_t", m_bottomText);

            m_leftText.gameObject.SetActive(m_leftText.text.Length > 0);
            m_rightText.gameObject.SetActive(m_rightText.text.Length > 0);
            m_topText.gameObject.SetActive(m_topText.text.Length > 0);
            m_bottomText.gameObject.SetActive(m_bottomText.text.Length > 0);
        }
    }
}