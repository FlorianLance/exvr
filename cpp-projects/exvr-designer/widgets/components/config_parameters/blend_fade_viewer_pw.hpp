
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_select_color_w.hpp"
#include "ex_widgets/ex_float_spin_box_w.hpp"
#include "ex_widgets/ex_radio_button_w.hpp"

// local
#include "config_pw.hpp"

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

    QButtonGroup group1;
    ExRadioButtonW onlyBlend{"only_blend"};
    ExRadioButtonW blendAndFade{"blend_and_fade"};

    ExSelectColorW startColor{"start_color"};
    ExSelectColorW endColor{"end_color"};

    ExFloatSpinBoxW durationBlend{"duration_blend"};
    ExFloatSpinBoxW durationFade{"duration_fade"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
