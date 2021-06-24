
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_resource_w.hpp"
#include "ex_select_color_w.hpp"
#include "ex_text_edit_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_radio_button_w.hpp"
#include "ex_vector2d_w.hpp"

namespace tool::ex {

class TextViewerInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};


class TextViewerConfigParametersW : public ConfigParametersW{
public :

    EyeRendererSubPart m_eye;

    QTabWidget m_tw;
    QTabWidget m_textTw;

    WordSpaceCanvasSubPart m_cameraSettings;
    ExCheckBoxW m_followEyeCamera;
    ExVector2dW m_pivot;
    ExFloatSpinBoxW m_distance;
    ExSelectColorW m_backgroundColor;

    TextSubPart m_text;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
