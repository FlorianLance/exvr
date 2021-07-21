
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

    ExComponentW avatar;
};

class FPPAvatarCameraConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

    ExCheckBoxW moveNeutralCameraToHead;
    ExCheckBoxW neutralPitch;
    ExCheckBoxW neutralYaw;
    ExCheckBoxW neutralRoll;
    ExVector3dW neutralCameraToHeadOffsetPos;
    ExVector3dW neutralCameraToHeadOffsetRot;

    ExRadioButtonW updateEyesCameraFromHead;

    ExRadioButtonW doNotUpdate;

    ExRadioButtonW updateHeadFromEyesCamera;
    ExVector3dW headFromEyesOffsetPos;
    ExVector3dW headFromEyesOffsetRot;

};

}
