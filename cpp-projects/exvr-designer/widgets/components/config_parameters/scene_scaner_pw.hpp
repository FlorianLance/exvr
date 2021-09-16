
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_pushbutton_w.hpp"
#include "ex_widgets/ex_float_spin_box_w.hpp"
#include "ex_widgets/ex_checkbox_w.hpp"

// local
#include "ex_widgets/ex_component_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {

class SceneScanerInitConfigParametersW : public ConfigParametersW{

public :

    ExComponentW m_kinectManager{"kinect_manager"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};


class SceneScanerConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_tr{"global_transform"};
    ExFloatSpinBoxW m_sizePoints{"size_points"};
    ExCheckBoxW m_displayClouds{"display_clouds"};
    ExCheckBoxW m_displayColliders{"display_colliders"};
    ExPushButtonW m_moveEyeToHeadPosition{"move_eye_to_head"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};

}
