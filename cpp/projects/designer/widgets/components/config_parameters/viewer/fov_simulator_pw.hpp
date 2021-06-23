
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_float_spin_box_w.hpp"
#include "ex_select_color_w.hpp"

namespace tool::ex {

class FovSimulatorInitConfigParametersW : public ConfigParametersW{

public :

    ExFloatSpinBoxW horizontalFov;
    ExFloatSpinBoxW verticalFov;
    ExFloatSpinBoxW distance;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};


class FovSimulatorConfigParametersW : public ConfigParametersW{
public :


    ExSelectColorW color;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
