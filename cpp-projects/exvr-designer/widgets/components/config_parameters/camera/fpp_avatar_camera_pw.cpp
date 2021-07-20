
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "fpp_avatar_camera_pw.hpp"

using namespace tool::ex;

void tool::ex::FPPAvatarCameraInitConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::HB(), {avatar()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
}

void tool::ex::FPPAvatarCameraInitConfigParametersW::init_and_register_widgets(){
    m_inputUiElements["avatar"] = avatar.init_widget(Component::T::Humanoid_avatar, "Avatar");
}

void tool::ex::FPPAvatarCameraInitConfigParametersW::create_connections(){

}

void tool::ex::FPPAvatarCameraInitConfigParametersW::late_update_ui(){

}

void tool::ex::FPPAvatarCameraConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::HB(), {moveNeutralCameraToHead()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {neutralPitch(), neutralYaw(), neutralRoll()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::VB(), {updateEyesCameraFromHead(), updateHeadFromEyesCamera(), doNotUpdate()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::W::horizontal_line());
    add_widget(ui::F::gen(ui::L::HB(), {headTrackingOffsetPos()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {headTrackingOffsetRot()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
}

void tool::ex::FPPAvatarCameraConfigParametersW::init_and_register_widgets(){

    m_inputUiElements["move_neutral_camera_to_head"]  = moveNeutralCameraToHead.init_widget("Move neutral camera to head", true);
    m_inputUiElements["neutral_pitch"]                = neutralPitch.init_widget("Pitch", false);
    m_inputUiElements["neutral_yaw"]                  = neutralYaw.init_widget("Yaw", true);
    m_inputUiElements["neutral_roll"]                 = neutralRoll.init_widget("Roll", false);
    m_inputUiElements["update_eyes_camera_from_head"] = updateEyesCameraFromHead.init_widget("Update eyes camera from avatar head", false);
    m_inputUiElements["update_head_from_eyes_camera"] = updateHeadFromEyesCamera.init_widget("Update avatar head from eyes camera", false);
    m_inputUiElements["no_not_update"]                = doNotUpdate.init_widget("Do nothing", true);

    DsbSettings offsetS{MinV<qreal>{-2.},V<qreal>{0.},MaxV<qreal>{2.},StepV<qreal>{0.01}, 2};
    m_inputUiElements["head_tracking_offset_pos"] = headTrackingOffsetPos.init_widget("Head offset position:", Vector3dSettings{offsetS,offsetS,offsetS});
    headTrackingOffsetPos.x.w->setValue(0);
    headTrackingOffsetPos.y.w->setValue(0.1);
    headTrackingOffsetPos.z.w->setValue(0.1);

    DsbSettings offsetRot{MinV<qreal>{-180.},V<qreal>{0.},MaxV<qreal>{180.},StepV<qreal>{0.1}, 2};
    Vector3dSettings offsetVecRot = {offsetRot,offsetRot,offsetRot};
    m_inputUiElements["head_tracking_offset_rot"] = headTrackingOffsetRot.init_widget("Head offset rotation:", offsetVecRot);

}

void tool::ex::FPPAvatarCameraConfigParametersW::create_connections()
{

}

void tool::ex::FPPAvatarCameraConfigParametersW::late_update_ui()
{

}
