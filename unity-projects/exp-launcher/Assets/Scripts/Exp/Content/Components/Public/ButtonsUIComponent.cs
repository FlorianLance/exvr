
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
        public TextMeshProUGUI m_bottonText = null;
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

            m_topText       = m_buttonsUiGO.transform.Find("Top text").GetComponent<TextMeshProUGUI>();
            m_topText.text = "...";
            return true;
            //m_bottonText    = m_buttonsUiGO.transform.Find("Bottom text").GetComponent<TextMeshProUGUI>();
            //m_leftText      = m_buttonsUiGO.transform.Find("Middle/Left text").GetComponent<TextMeshProUGUI>();
            //m_rightText     = m_buttonsUiGO.transform.Find("Middle/Right text").GetComponent<TextMeshProUGUI>();
            //m_buttonsParent = m_buttonsUiGO.transform.Find("Middle/Buttons");

            

            //int nbButtonsH = 5;
            //int nbButtonsV = 3;

            //m_buttons     = new Dictionary<int, Dictionary<int, Button>>(nbButtonsV);
            //m_buttonsText = new Dictionary<int, Dictionary<int, TextMeshProUGUI>>(nbButtonsV);
            //m_buttonsLine = new List<GameObject>(nbButtonsV);
            //for(int ii = 0; ii < nbButtonsV; ++ii) {

            //    var lineGO = GO.generate_empty_scene_object(string.Format("Line{}", ii), m_buttonsParent, true);
            //    var le = lineGO.AddComponent<LayoutElement>();
            //    le.flexibleWidth  = 1f;
            //    le.flexibleHeight = 1f;

            //    var hlg = lineGO.AddComponent<HorizontalLayoutGroup>();
            //    hlg.childControlWidth       = true;
            //    hlg.childControlHeight      = true;
            //    hlg.childScaleWidth         = false;
            //    hlg.childScaleHeight        = false;
            //    hlg.childForceExpandWidth   = true;
            //    hlg.childForceExpandHeight  = true;

            //    m_buttonsLine.Add(lineGO);

            //    var lineButtons     = new Dictionary<int, Button>(nbButtonsH);
            //    var lineButtonsText = new Dictionary<int, TextMeshProUGUI>(nbButtonsH);
            //    for (int jj = 0; jj < nbButtonsH; ++jj) {                    
            //        var buttonGO = ExVR.GlobalResources().instantiate_prebab("Components/Button", lineGO.transform);
            //        lineButtons.Add(jj, buttonGO.GetComponent<Button>());
            //        lineButtonsText.Add(jj, buttonGO.transform.Find("Text (TMP)").gameObject.GetComponent<TextMeshProUGUI>());
            //    }
            //    m_buttons.Add(ii, lineButtons);
            //    m_buttonsText.Add(ii, lineButtonsText);
            //}




            return true;
        }

        //protected override void start_routine() {

        //    float currentValue;
        //    if (currentC.get<bool>("random_start")) { // random value
        //        if (currentC.get<bool>("whole")) {
        //            currentValue = (float)Random.Range((int)currentC.get<float>("min"), (int)currentC.get<float>("max") + 1);
        //        } else {
        //            currentValue = Random.Range(currentC.get<float>("min"), currentC.get<float>("max"));
        //        }
        //    } else { // current value
        //        currentValue = get_value();
        //    }

        //    set_value(currentValue);
        //}

        //protected override void set_visibility(bool visibility) {
        //    m_sliderGO.SetActive(visibility);
        //}

        //public float get_value() {
        //    return currentC.get<float>("value");
        //}

        //public void decrease(float amount) {
        //    set_value(get_value() - amount);
        //}

        //public void increase(float amount) {
        //    set_value(get_value() + amount);
        //}


        //// use_eye_camera
        //protected override void pre_update() {
        //    resize_container();
        //}

        //protected override void update_parameter_from_gui(string updatedArgName) {

        //    // regenerate random value
        //    float currentValue = get_value();
        //    if (updatedArgName == "random_start") {
        //        if (currentC.get<bool>("random_start")) {
        //            if (currentC.get<bool>("whole")) {
        //                currentValue = (float)Random.Range((int)currentC.get<float>("min"), (int)currentC.get<float>("max"));
        //            } else {
        //                currentValue = Random.Range(currentC.get<float>("min"), currentC.get<float>("max"));
        //            }
        //        }
        //    }

        //    set_value(currentValue);
        //}


        //public void resize_container() {

        //    m_sliderGO.transform.position = Vector3.zero;
        //    m_sliderGO.transform.rotation = Quaternion.identity;

        //    var rTr = m_sliderGO.GetComponent<RectTransform>();
        //    rTr.pivot = new Vector2(0.5f, 0.5f);

        //    if (currentC.get<bool>("use_eye_camera")) {

        //        // move to head
        //        Transform camTr = ExVR.Display().cameras().get_eye_camera_transform();
        //        m_sliderGO.transform.position = camTr.position + camTr.forward * currentC.get<float>("distance");
        //        m_sliderGO.transform.rotation = camTr.rotation;
        //        m_sliderGO.transform.eulerAngles += currentC.get_vector3("rotation");
        //        rTr.pivot = currentC.get_vector2("pivot");

        //    } else {
        //        rTr.localPosition = currentC.get_vector3("position");
        //        rTr.localEulerAngles = currentC.get_vector3("rotation");
        //    }

        //    rTr.sizeDelta =
        //        new Vector2(currentC.get<int>("width"), currentC.get<int>("height")
        //    );

        //    var sf = currentC.get<float>("scale_factor") * 0.01f;
        //    rTr.localScale = new Vector3(
        //        sf, sf, sf
        //    );
        //}


        //public void set_value(float value) {

        //    bool whole = currentC.get<bool>("whole");
        //    float min = currentC.get<float>("min");
        //    float max = currentC.get<float>("max");

        //    // update sliders min/max according to whole
        //    m_slider.wholeNumbers = whole;
        //    m_slider.minValue = !whole ? min : (int)min;
        //    m_slider.maxValue = !whole ? max : (int)max;

        //    // clamp value according to min/max
        //    if (value < m_slider.minValue) {
        //        value = m_slider.minValue;
        //    }
        //    if (value > m_slider.maxValue) {
        //        value = m_slider.maxValue;
        //    }

        //    // update value
        //    currentC.set("value", value);

        //    // update slider value
        //    var previousValue = m_slider.value;
        //    m_slider.value = !whole ? value : (int)value;

        //    // update text ui
        //    currentC.update_text("t1", m_descriptionText1);
        //    currentC.update_text("t2", m_descriptionText2);
        //    currentC.update_text("tmin", m_sliderText1);
        //    currentC.update_text("tmax", m_sliderText2);
        //    currentC.update_text("tvalue", m_sliderValueText);

        //    // update textures according to display option
        //    if (currentC.get<bool>("display_min_max")) {
        //        m_sliderText1.text = (!whole ? min : (int)min).ToString();
        //        m_sliderText2.text = (!whole ? max : (int)max).ToString();
        //        m_sliderValueText.text = "";
        //    } else if (currentC.get<bool>("display_min_max_value")) {
        //        m_sliderText1.text = (!whole ? min : (int)min).ToString();
        //        m_sliderText2.text = (!whole ? max : (int)max).ToString();
        //        m_sliderValueText.text = (!whole ? value : (int)value).ToString();
        //    } else if (currentC.get<bool>("display_slider_textes_text")) {
        //        m_sliderText1.text = currentC.get<string>("slider_text1");
        //        m_sliderText2.text = currentC.get<string>("slider_text2");
        //        m_sliderValueText.text = "";
        //    } else {
        //        m_sliderText1.text = "";
        //        m_sliderText2.text = "";
        //        m_sliderValueText.text = "";
        //    }

        //    // slider
        //    m_sliderGO.GetComponent<UnityEngine.UI.Image>().color = currentC.get_color("background_color");
        //    m_slider.transform.Find("Fill Area").Find("Fill").GetComponent<UnityEngine.UI.Image>().color = currentC.get_color("fill_area_color");
        //    m_slider.transform.Find("Handle Slide Area").Find("Handle").GetComponent<UnityEngine.UI.Image>().color = currentC.get_color("handle_color");
        //    m_slider.transform.Find("Background").GetComponent<UnityEngine.UI.Image>().color = currentC.get_color("rest_area_color");

        //    // send updated slider value
        //    invoke_signal("value updated", m_slider.value);
        //}
    }
}