
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

    add_widget(ui::F::gen(ui::L::VB(),{
        ui::F::gen(ui::L::HB(), {moveNeutralCameraToHead()}, LStretch{true}, LMargins{false}, QFrame::NoFrame),
        ui::F::gen(ui::L::HB(), {ui::W::txt("Using axes:"), neutralPitch(), neutralYaw(), neutralRoll()}, LStretch{true}, LMargins{false}, QFrame::NoFrame),
        ui::F::gen(ui::L::HB(), {ui::W::txt("With offset:")}, LStretch{true}, LMargins{false}, QFrame::NoFrame),
        ui::F::gen(ui::L::HB(), {neutralCameraToHeadOffsetPos()}, LStretch{true}, LMargins{false}, QFrame::NoFrame),
        ui::F::gen(ui::L::HB(), {neutralCameraToHeadOffsetRot()}, LStretch{true}, LMargins{false}, QFrame::NoFrame)
    }, LStretch{true}, LMargins{true}, QFrame::Box));


    add_widget(ui::W::horizontal_line());

    add_widget(ui::F::gen(ui::L::VB(), {updateEyesCameraFromHead(), updateHeadFromEyesCamera(), doNotUpdate()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));    
    add_widget(ui::F::gen(ui::L::HB(), {headFromEyesOffsetPos()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {headFromEyesOffsetRot()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
}

void tool::ex::FPPAvatarCameraConfigParametersW::init_and_register_widgets(){

    m_inputUiElements["move_neutral_camera_to_head"]  = moveNeutralCameraToHead.init_widget("Move neutral camera to head", true);
    m_inputUiElements["neutral_pitch"]                = neutralPitch.init_widget("Pitch", false);
    m_inputUiElements["neutral_yaw"]                  = neutralYaw.init_widget("Yaw", true);
    m_inputUiElements["neutral_roll"]                 = neutralRoll.init_widget("Roll", false);
    m_inputUiElements["update_eyes_camera_from_head"] = updateEyesCameraFromHead.init_widget("Update eyes camera from avatar head", false);
    m_inputUiElements["update_head_from_eyes_camera"] = updateHeadFromEyesCamera.init_widget("Update avatar head from eyes camera", false);
    m_inputUiElements["no_not_update"]                = doNotUpdate.init_widget("Do nothing", true);

    DsbSettings offsetS{MinV<qreal>{-2.},V<qreal>{0.1},MaxV<qreal>{2.},StepV<qreal>{0.01}, 2};
    DsbSettings offsetRot{MinV<qreal>{-180.},V<qreal>{0.},MaxV<qreal>{180.},StepV<qreal>{0.1}, 2};
    Vector3dSettings offsetVecPos = {offsetS,offsetS,offsetS};
    Vector3dSettings offsetVecRot = {offsetRot,offsetRot,offsetRot};

    m_inputUiElements["neutral_camera_to_head_offset_pos"] = neutralCameraToHeadOffsetPos.init_widget("Neutral offset position:", offsetVecPos);
    neutralCameraToHeadOffsetPos.x.w->setValue(0);
    m_inputUiElements["neutral_camera_to_head_offset_rot"] = neutralCameraToHeadOffsetRot.init_widget("Neutral offset rotation:", offsetVecRot);

    m_inputUiElements["head_from_eyes_offset_pos"] = headFromEyesOffsetPos.init_widget("Head offset position:", offsetVecPos);
    headFromEyesOffsetPos.x.w->setValue(0);
    headFromEyesOffsetPos.y.w->setValue(0);
    headFromEyesOffsetPos.z.w->setValue(0);
    m_inputUiElements["head_from_eyes_offset_rot"] = headFromEyesOffsetRot.init_widget("Head offset rotation:", offsetVecRot);
}

void tool::ex::FPPAvatarCameraConfigParametersW::create_connections()
{

}

void tool::ex::FPPAvatarCameraConfigParametersW::late_update_ui()
{

}
