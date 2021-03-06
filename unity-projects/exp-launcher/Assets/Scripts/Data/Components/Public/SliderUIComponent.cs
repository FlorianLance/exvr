/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

// unity
using UnityEngine;
using UnityEngine.UI;

// TMPro
using TMPro;

namespace Ex{

    public class SliderUIComponent : CanvasWorldSpaceComponent{
        
        private GameObject m_sliderGO = null;
        
        private Slider m_slider = null;
        private TextMeshProUGUI m_descriptionText1 = null;
        private TextMeshProUGUI m_descriptionText2 = null;        
        private TextMeshProUGUI m_sliderText1 = null;
        private TextMeshProUGUI m_sliderText2 = null;
        private TextMeshProUGUI m_sliderValueText = null;

        //private float currentRandValue = 0f;

        private static Dictionary<string, TextAlignmentOptions> m_alignment = null;

        protected override bool initialize() {

            // signals
            add_signal("value updated");
            // slots            
            add_slot("set value", (value) => { set_value((float)value); });
            add_slot("increase", (amout) => { increase((float)amout); });
            add_slot("decrease", (amout) => { decrease((float)amout); });            

            // init gameObjects            
            if (initC.get<bool>("horizontal_slider")) {
                m_sliderGO = ExVR.GlobalResources().instantiate_prebab("Components/HorizontalSliderCamera", transform); 
                m_sliderGO.name = "Horizontal slider";
            } else {
                m_sliderGO = ExVR.GlobalResources().instantiate_prebab("Components/VerticalSliderCamera", transform);
                m_sliderGO.name = "Vertical slider";
            }

            // find sub go
            if (initC.get<bool>("horizontal_slider")) {
            
                m_descriptionText1 = m_sliderGO.transform.Find("TopText").GetComponent<TextMeshProUGUI>();
                m_descriptionText2 = m_sliderGO.transform.Find("BottomText").GetComponent<TextMeshProUGUI>();

                var sliderPanel = m_sliderGO.transform.Find("SliderPanel");
                m_slider = sliderPanel.Find("Slider").GetComponent<Slider>();
                m_sliderValueText = sliderPanel.Find("Slider").Find("SliderValueText").GetComponent<TextMeshProUGUI>();
                m_sliderText1 = sliderPanel.Find("LeftSliderText").GetComponent<TextMeshProUGUI>();
                m_sliderText2 = sliderPanel.Find("RightSliderText").GetComponent<TextMeshProUGUI>();

            } else {

                m_descriptionText1 = m_sliderGO.transform.Find("LeftText").GetComponent<TextMeshProUGUI>();
                m_descriptionText2 = m_sliderGO.transform.Find("RightText").GetComponent<TextMeshProUGUI>();

                var sliderPanel = m_sliderGO.transform.Find("SliderPanel");
                m_slider = sliderPanel.Find("Slider").GetComponent<Slider>();
                m_sliderValueText = sliderPanel.Find("Slider").Find("SliderValueText").GetComponent<TextMeshProUGUI>();
                m_sliderText1 = sliderPanel.Find("TopSliderText").GetComponent<TextMeshProUGUI>();
                m_sliderText2 = sliderPanel.Find("BottomSliderText").GetComponent<TextMeshProUGUI>();
            }
           
            return true;
        }

        protected override void start_routine() {

            float currentValue;
            if (currentC.get<bool>("random_start")) { // random value
                if (currentC.get<bool>("whole")) {
                    currentValue = (float)Random.Range((int)currentC.get<float>("min"), (int)currentC.get<float>("max"));
                } else {
                    currentValue = Random.Range(currentC.get<float>("min"), currentC.get<float>("max"));
                }
            } else { // current value
                currentValue = get_value();
            }

            set_value(currentValue);
        }

        protected override void set_visibility(bool visibility) {
            m_sliderGO.SetActive(visibility);
        }

        public float get_value() {
            return currentC.get<float>("value");
        }

        public void decrease(float amount) {
            set_value(get_value() - amount);
        }

        public void increase(float amount) {
            set_value(get_value() + amount);
        }


        // use_eye_camera
        protected override void pre_update() {
            resize_container();
        }

        protected override void update_parameter_from_gui(string updatedArgName) {

            // regenerate random value
            float currentValue = get_value();
            if (updatedArgName == "random_start") {                
                if (currentC.get<bool>("random_start")) {                    
                    if (currentC.get<bool>("whole")) {
                        currentValue = (float)Random.Range((int)currentC.get<float>("min"), (int)currentC.get<float>("max"));
                    } else {
                        currentValue = Random.Range(currentC.get<float>("min"), currentC.get<float>("max"));
                    }
                }
            }

            set_value(currentValue);
        }


        public void resize_container() {

            m_sliderGO.transform.position = Vector3.zero;
            m_sliderGO.transform.rotation = Quaternion.identity;

            var rTr = m_sliderGO.GetComponent<RectTransform>();
            rTr.pivot = new Vector2(0.5f, 0.5f);

            if (currentC.get<bool>("use_eye_camera")) {

                // move to head
                Transform camTr = ExVR.Display().cameras().get_eye_camera_transform();
                m_sliderGO.transform.position = camTr.position + camTr.forward * currentC.get<float>("distance");
                m_sliderGO.transform.rotation = camTr.rotation;
                m_sliderGO.transform.eulerAngles += currentC.get_vector3("rotation");
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


        public void set_value(float value) {

            bool whole = currentC.get<bool>("whole");
            float min = currentC.get<float>("min");
            float max = currentC.get<float>("max");

            // update sliders min/max according to whole
            m_slider.wholeNumbers = whole;
            m_slider.minValue = !whole ? min : (int)min;
            m_slider.maxValue = !whole ? max : (int)max;

            // clamp value according to min/max
            if (value < m_slider.minValue) {
                value = m_slider.minValue;
            }
            if (value > m_slider.maxValue) {
                value = m_slider.maxValue;
            }

            // update value
            currentC.set("value", value);

            // update slider value
            var previousValue = m_slider.value;
            m_slider.value = !whole ? value : (int)value;

            // update text ui
            currentC.update_text("t1", m_descriptionText1);
            currentC.update_text("t2", m_descriptionText2);
            currentC.update_text("tmin", m_sliderText1);
            currentC.update_text("tmax", m_sliderText2);
            currentC.update_text("tvalue", m_sliderValueText);

            // update textures according to display option
            if (currentC.get<bool>("display_min_max")) {
                m_sliderText1.text = (!whole ? min : (int)min).ToString();
                m_sliderText2.text = (!whole ? max : (int)max).ToString();
                m_sliderValueText.text = "";
            } else if (currentC.get<bool>("display_min_max_value")) {
                m_sliderText1.text = (!whole ? min : (int)min).ToString();
                m_sliderText2.text = (!whole ? max : (int)max).ToString();
                m_sliderValueText.text = (!whole ? value : (int)value).ToString();
            } else if (currentC.get<bool>("display_slider_textes_text")) {
                m_sliderText1.text = currentC.get<string>("slider_text1");
                m_sliderText2.text = currentC.get<string>("slider_text2");
                m_sliderValueText.text = "";
            } else {
                m_sliderText1.text = "";
                m_sliderText2.text = "";
                m_sliderValueText.text = "";
            }

            // slider
            m_sliderGO.GetComponent<UnityEngine.UI.Image>().color = currentC.get_color("background_color");
            m_slider.transform.Find("Fill Area").Find("Fill").GetComponent<UnityEngine.UI.Image>().color = currentC.get_color("fill_area_color");
            m_slider.transform.Find("Handle Slide Area").Find("Handle").GetComponent<UnityEngine.UI.Image>().color = currentC.get_color("handle_color");
            m_slider.transform.Find("Background").GetComponent<UnityEngine.UI.Image>().color = currentC.get_color("rest_area_color");

            // send updated slider value
            invoke_signal("value updated", m_slider.value);
        }
    }
}