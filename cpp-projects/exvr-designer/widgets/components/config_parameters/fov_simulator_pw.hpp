
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_float_spin_box_w.hpp"
#include "ex_widgets/ex_select_color_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {

class FovSimulatorInitConfigParametersW : public ConfigParametersW{

public :

    ExFloatSpinBoxW horizontalFov{"horizontal_fov"};
    ExFloatSpinBoxW verticalFov{"vertical_fov"};
    ExFloatSpinBoxW distance{"distance"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};


class FovSimulatorConfigParametersW : public ConfigParametersW{
public :


    ExSelectColorW color{"color"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
