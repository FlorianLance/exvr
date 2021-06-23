
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_vector2d_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_radio_button_w.hpp"

namespace tool::ex {


class BlendFadeViewerInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override {}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};


class BlendFadeViewerConfigParametersW : public ConfigParametersW{

public:

    ExRadioButtonW onlyBlend;
    ExRadioButtonW blendAndFade;

    ExSelectColorW startColor;
    ExSelectColorW endColor;

    ExFloatSpinBoxW durationBlend;
    ExFloatSpinBoxW durationFade;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
