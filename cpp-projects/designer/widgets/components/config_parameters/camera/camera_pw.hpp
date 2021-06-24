
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_checkbox_w.hpp"

namespace tool::ex {

class CameraInitConfigParametersW : public ConfigParametersW{

public :

    ExRadioButtonW useEye;
    ExRadioButtonW useNeutral;
    ExCheckBoxW cbStartExperiment;
    ExVector3dW position;
    ExVector3dW rotation;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

class CameraConfigParametersW : public ConfigParametersW{

public :

    ExCheckBoxW enableDebugMouseCameraMovements;

    ExRadioButtonW useEye;
    ExRadioButtonW useNeutral;
    ExCheckBoxW cbStartRoutine;
    ExCheckBoxW cbUpdateOn;
    ExVector3dW position;
    ExVector3dW rotation;

    ExVector3dW currentNeutralPosition;
    ExVector3dW currentNeutralRotation;
    QPushButton *copyNeutralToCurrentConfig  = nullptr;

    ExVector3dW currentEyePosition;
    ExVector3dW currentEyeRotation;
    QPushButton *copyEyeToCurrentConfig = nullptr;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void update_with_info(QStringView id, QStringView value) override;
    void create_connections() override;
    void late_update_ui() override;
};

}
