
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_pushbutton_w.hpp"
#include "ex_component_w.hpp"

namespace tool::ex {

class SceneScanerInitConfigParametersW : public ConfigParametersW{

public :

    ExComponentW m_kinectManager;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};


class SceneScanerConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_tr;
    ExFloatSpinBoxW m_sizePoints;
    ExCheckBoxW m_displayClouds;
    ExCheckBoxW m_displayColliders;
    ExPushButtonW m_moveEyeToHeadPosition;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};

}
