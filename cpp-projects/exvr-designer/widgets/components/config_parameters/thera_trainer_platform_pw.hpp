/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// qt-utility
#include "ex_widgets/ex_vector3d_w.hpp"
#include "ex_widgets/ex_checkbox_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {

class TheraTrainerPlatformInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

class TheraTrainerPlatformConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo{"transform"};
    ExFloatSpinBoxW m_height{"height"};

    ExVector3dW m_offsetPelvisHandGripTr{"offset_pelvis_pos"};
    ExVector3dW m_offsetPelvisHandGripRot{"offset_pelvis_rot"};

    ExVector3dW m_offsetRightHandGripTr{"offset_right_grip_pos"};
    ExVector3dW m_offsetRightHandGripRot{"offset_right_grip_rot"};

    ExVector3dW m_offsetLeftHandGripTr{"offset_left_grip_pos"};
    ExVector3dW m_offsetLeftHandGripRot{"offset_left_grip_rot"};

    ExCheckBoxW m_displayGrips{"display_targets"};

    void insert_widgets() override;
    void init_and_register_widgets() override;

    void create_connections() override{

    }

    void late_update_ui() override{}
};

}
