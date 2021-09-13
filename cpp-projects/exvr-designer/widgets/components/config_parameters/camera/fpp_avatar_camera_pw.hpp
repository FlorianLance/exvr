
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_component_w.hpp"

namespace tool::ex {

class FPPAvatarCameraInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

    ExComponentW avatar{"avatar"};
};

class FPPAvatarCameraConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

    ExCheckBoxW moveNeutralCameraToHead{"move_neutral_camera_to_head"};
    ExCheckBoxW neutralPitch{"neutral_pitch"};
    ExCheckBoxW neutralYaw{"neutral_yaw"};
    ExCheckBoxW neutralRoll{"neutral_roll"};
    ExVector3dW neutralCameraToHeadOffsetPos{"neutral_camera_to_head_offset_pos"};
    ExVector3dW neutralCameraToHeadOffsetRot{"neutral_camera_to_head_offset_rot"};

    QButtonGroup group1;
    ExRadioButtonW updateEyesCameraFromHead{"update_eyes_camera_from_head"};
    ExRadioButtonW doNotUpdate{"no_not_update"};
    ExRadioButtonW updateHeadFromEyesCamera{"update_head_from_eyes_camera"};

    ExVector3dW headFromEyesOffsetPos{"head_from_eyes_offset_pos"};
    ExVector3dW headFromEyesOffsetRot{"head_from_eyes_offset_rot"};

};

}
