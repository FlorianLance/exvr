

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "scene_scaner_pw.hpp"

using namespace tool::ex;

void SceneScanerInitConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::HB(), {m_kinectManager()}, LStretch{false}, LMargins{true}, QFrame::Box));
}

void SceneScanerInitConfigParametersW::init_and_register_widgets(){
    m_inputUiElements["kinect_manager"] = m_kinectManager.init_widget(Component::Type::Kinect_manager, "Kinect manager component: ");
}

void SceneScanerConfigParametersW::insert_widgets(){
    add_sub_part_widget(m_tr);
    add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Size points: "),m_sizePoints()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(),{m_displayClouds()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(),{m_displayColliders()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(),{m_moveEyeToHeadPosition()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
}

void SceneScanerConfigParametersW::init_and_register_widgets(){

    map_sub_part(m_tr.init_widget("Global model transform", "global_transform"));

    m_inputUiElements["size_points"]       = m_sizePoints.init_widget(MinV<qreal>{0.0001}, V<qreal>{0.0030}, MaxV<qreal>{0.05}, StepV<qreal>{0.0001},4);
    m_inputUiElements["display_clouds"]    = m_displayClouds.init_widget("Display clouds ", true);
    m_inputUiElements["display_colliders"] = m_displayColliders.init_widget("Display colliders ", false);

    m_actionUiElements["move_eye_to_head"] = m_moveEyeToHeadPosition.init_widget("Move eye camera to fit tracked head");
}
