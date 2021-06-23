

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "thera_trainer_platform_pw.hpp"

using namespace tool::ex;


void TheraTrainerPlatformConfigParametersW::insert_widgets() {
    add_sub_part_widget(m_transfo);
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Pelvis height (m): "), m_height()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Offsets: ")}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_displayGrips()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_offsetPelvisHandGripTr()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_offsetPelvisHandGripRot()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_offsetRightHandGripTr()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_offsetRightHandGripRot()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_offsetLeftHandGripTr()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_offsetLeftHandGripRot()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
}

void TheraTrainerPlatformConfigParametersW::init_and_register_widgets(){

    map_sub_part(m_transfo.init_widget());

    DsbSettings offsetP{MinV<qreal>{-2.},V<qreal>{0.},MaxV<qreal>{2.},StepV<qreal>{0.01}, 2};
    DsbSettings offsetR{MinV<qreal>{-360.},V<qreal>{0.},MaxV<qreal>{360.},StepV<qreal>{1}, 2};
    m_inputUiElements["height"]                 = m_height.init_widget(MinV<qreal>{0.5},V<qreal>{1.},MaxV<qreal>{1.5},StepV<qreal>{0.01}, 2);
    m_inputUiElements["display_targets"]        = m_displayGrips.init_widget("Display humanoid targets: ", false);
    m_inputUiElements["offset_pelvis_pos"]      = m_offsetPelvisHandGripTr.init_widget("Pelvis pos:", Vector3dSettings{offsetP,offsetP,offsetP});
    m_inputUiElements["offset_pelvis_rot"]      = m_offsetPelvisHandGripRot.init_widget("Pelvis rot:", Vector3dSettings{offsetR,offsetR,offsetR});
    m_inputUiElements["offset_right_grip_pos"]  = m_offsetRightHandGripTr.init_widget("Right hand grip pos:", Vector3dSettings{offsetP,offsetP,offsetP});
    m_inputUiElements["offset_right_grip_rot"]  = m_offsetRightHandGripRot.init_widget("Right hand grip rot:", Vector3dSettings{offsetR,offsetR,offsetR});
    m_inputUiElements["offset_left_grip_pos"]   = m_offsetLeftHandGripTr.init_widget("Left hand grip pos:", Vector3dSettings{offsetP,offsetP,offsetP});
    m_inputUiElements["offset_left_grip_rot"]   = m_offsetLeftHandGripRot.init_widget("Left hand grip rot:", Vector3dSettings{offsetR,offsetR,offsetR});
}
