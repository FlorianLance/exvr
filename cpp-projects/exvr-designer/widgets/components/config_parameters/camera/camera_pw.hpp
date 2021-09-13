
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

    QButtonGroup group1;
    ExRadioButtonW useEye {"use_eye"};
    ExRadioButtonW useNeutral {"use_neutral"};
    ExCheckBoxW cbStartExperiment {"start_experiment"};
    ExVector3dW position {"position"};
    ExVector3dW rotation {"rotation"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

class CameraConfigParametersW : public ConfigParametersW{

public :

    ExCheckBoxW enableDebugMouseCameraMovements {"debug_camera"};

    QButtonGroup group1;
    ExRadioButtonW useEye {"use_eye"};
    ExRadioButtonW useNeutral {"use_neutral"};
    ExCheckBoxW cbStartRoutine {"start_routine"};
    ExCheckBoxW cbUpdateOn {"update_on"};


    QPushButton *copyNeutralToCurrentConfig  = nullptr;
    QPushButton *copyEyeToCurrentConfig = nullptr;
    ExVector3dW position {"position"};
    ExVector3dW rotation {"rotation"};
    ExVector3dW currentNeutralPosition {"neutral_position"};
    ExVector3dW currentNeutralRotation {"neutral_rotaiton"};
    ExVector3dW currentEyePosition {"eye_rotaiton"};
    ExVector3dW currentEyeRotation {"eye_rotaiton"};


    void insert_widgets() override;
    void init_and_register_widgets() override;
    void update_with_info(QStringView id, QStringView value) override;
    void create_connections() override;
    void late_update_ui() override;
};

}
