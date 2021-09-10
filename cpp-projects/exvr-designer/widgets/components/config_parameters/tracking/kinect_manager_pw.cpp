

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "kinect_manager_pw.hpp"

using namespace tool::ex;

void KinectManagerInitConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::VB(), {m_config(),m_calib(),m_camera()}, LStretch{false}, LMargins{true}, QFrame::Box));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Cameras mode:"), m_mode()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Cameras id to use:"), m_camarasToUse()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
    add_widget(m_debugBypassDevice());
}

void KinectManagerInitConfigParametersW::init_and_register_widgets(){

    add_input_ui(m_config.init_widget(Resource::Type::Text, "Network file: "));
    add_input_ui(m_calib.init_widget(Resource::Type::Text,  "Calibration file: "));
    add_input_ui(m_camera.init_widget(Resource::Type::Text, "Camera file: "));
    add_input_ui(m_mode.init_widget({"Cloud", "Mesh"}, 0));
    add_input_ui(m_camarasToUse.init_widget("0 1 2 3 4 5 6 7"));
    add_input_ui(m_debugBypassDevice.init_widget("Enable it for testing the experiment without the device", false));
}

void KinectManagerConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::HB(),{m_updateFromCameras(), ui::W::txt("Camera ask frame rate: "), m_fps()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
}

void KinectManagerConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_updateFromCameras.init_widget("Update cameras ", true));
    add_input_ui(m_fps.init_widget(MinV<int>{1}, V<int>{45}, MaxV<int>{90}, StepV<int>{1}));
}
