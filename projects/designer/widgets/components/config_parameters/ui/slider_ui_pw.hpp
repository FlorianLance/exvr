
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_text_edit_w.hpp"
#include "ex_combo_box_text_w.hpp"
#include "ex_combo_box_index_w.hpp"
#include "ex_radio_button_w.hpp"
#include "ex_select_color_w.hpp"
#include "ex_line_edit_w.hpp"
#include "ex_vector2d_w.hpp"


namespace tool::ex {

class SliderUiInitConfigParametersW : public ConfigParametersW{

public :

    ExCheckBoxW m_cbHorizontalSlider;

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
    ExCheckBoxW m_followEyeCamera;
    ExVector2dW m_pivot;
    ExFloatSpinBoxW m_distance;

    // textes settings
    TextSubPart m_text1;
    TextSubPart m_text2;
    TextSubPart m_minTxt = TextSubPart(true);
    TextSubPart m_maxTxt = TextSubPart(true);
    TextSubPart m_valueTxt = TextSubPart(true);

    // slider settings
    ExRadioButtonW m_displayMinMax;
    ExRadioButtonW m_displayMinMaxValue;
    ExRadioButtonW m_displaySliderTextes;
    ExRadioButtonW m_displayNothing;
    ExCheckBoxW m_displaySteps;

    ExLineEditW m_sliderText1;
    ExLineEditW m_sliderText2;

    ExSelectColorW m_colBackgound;
    ExSelectColorW m_colHandle;
    ExSelectColorW m_colFillArea;
    ExSelectColorW m_colRestArea;

    ExCheckBoxW m_wholeValue;
    ExCheckBoxW m_randomStart;
    ExFloatSpinBoxW m_minValue;
    ExFloatSpinBoxW m_initialValue;
    ExFloatSpinBoxW m_maxValue;
    ExFloatSpinBoxW m_stepValue;


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
