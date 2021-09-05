/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "ex_line_edit_w.hpp"
#include "ex_spin_box_w.hpp"
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

    TransformSubPart m_transfo;
    ExFloatSpinBoxW m_height;

    ExVector3dW m_offsetPelvisHandGripTr;
    ExVector3dW m_offsetPelvisHandGripRot;

    ExVector3dW m_offsetRightHandGripTr;
    ExVector3dW m_offsetRightHandGripRot;

    ExVector3dW m_offsetLeftHandGripTr;
    ExVector3dW m_offsetLeftHandGripRot;

    ExCheckBoxW m_displayGrips;

    void insert_widgets() override;
    void init_and_register_widgets() override;

    void create_connections() override{

    }

    void late_update_ui() override{}
};

}
