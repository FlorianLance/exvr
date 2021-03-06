
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_checkbox_w.hpp"
#include "ex_widgets/ex_vector2d_w.hpp"
#include "ex_widgets/ex_float_spin_box_w.hpp"
#include "ex_widgets/ex_radio_button_w.hpp"
#include "ex_widgets/ex_select_color_w.hpp"
#include "ex_widgets/ex_line_edit_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {

class SliderUiInitConfigParametersW : public ConfigParametersW{

public :

    ExCheckBoxW m_cbHorizontalSlider{"horizontal_slider"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

class SliderUiConfigParametersW : public ConfigParametersW{


public:

    QTabWidget *m_tw1 = nullptr;
    QTabWidget *m_tw2 = nullptr;
    QTabWidget *m_text1Tw = nullptr;
    QTabWidget *m_text2Tw = nullptr;
    QTabWidget *m_minTextTw = nullptr;
    QTabWidget *m_maxTextTw = nullptr;
    QTabWidget *m_valueTextTw = nullptr;

    WordSpaceCanvasSubPart m_cameraSettings;
    ExCheckBoxW m_followEyeCamera{"use_eye_camera"};
    ExVector2dW m_pivot{"pivot"};
    ExFloatSpinBoxW m_distance{"distance"};

    // textes settings
    TextSubPart m_text1 {"t1"};
    TextSubPart m_text2 {"t2"};
    TextSubPart m_minTxt {"tmin", true};
    TextSubPart m_maxTxt {"tmax", true};
    TextSubPart m_valueTxt {"tvalue", true};

    // slider settings
    QButtonGroup group1;
    ExRadioButtonW m_displayMinMax{"display_min_max"};
    ExRadioButtonW m_displayMinMaxValue{"display_min_max_value"};
    ExRadioButtonW m_displaySliderTextes{"display_slider_textes_text"};
    ExRadioButtonW m_displayNothing{"display_nothing"};
    ExCheckBoxW m_displaySteps{"display_steps"};

    ExLineEditW m_sliderText1{"slider_text1"};
    ExLineEditW m_sliderText2{"slider_text2"};

    ExSelectColorW m_colBackgound{"background_color"};
    ExSelectColorW m_colHandle{"handle_color"};
    ExSelectColorW m_colFillArea{"fill_area_color"};
    ExSelectColorW m_colRestArea{"rest_area_color"};

    ExCheckBoxW m_wholeValue{"whole"};
    ExCheckBoxW m_randomStart{"random_start"};
    ExFloatSpinBoxW m_minValue{"min"};
    ExFloatSpinBoxW m_initialValue{"value"};
    ExFloatSpinBoxW m_maxValue{"max"};
    ExFloatSpinBoxW m_stepValue{"step"};


public slots:

    void update_ui_value_type(bool whole);
    void update_ui_value_limits(qreal value);

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

};

}
