
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

namespace tool::ex {


class FixationCrossViewerInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};


class FixationCrossViewerConfigParametersW : public ConfigParametersW{

public:

    EyeRendererSubPart m_eye;
    WordSpaceCanvasSubPart m_cameraSettings;
    ExCheckBoxW m_followEyeCamera;
    ExCheckBoxW m_useImageSize;
    ExVector2dW m_pivot;
    ExFloatSpinBoxW m_distance;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
