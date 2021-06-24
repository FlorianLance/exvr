
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"

#include "ex_vector2d_w.hpp"

namespace tool::ex {

class WebcamViewerInitConfigParametersW : public ConfigParametersW{

public :


    ExSpinBoxW m_sbDeviceId;
    ExSpinBoxW m_sbFPS;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};

class WebcamViewerConfigParametersW : public ConfigParametersW{

public :

    EyeRendererSubPart m_eye;

    WordSpaceCanvasSubPart m_cameraSettings;
    ExCheckBoxW m_followEyeCamera;
    ExCheckBoxW m_cbUseVideoSize;
    ExVector2dW m_pivot;
    ExFloatSpinBoxW m_distance;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
