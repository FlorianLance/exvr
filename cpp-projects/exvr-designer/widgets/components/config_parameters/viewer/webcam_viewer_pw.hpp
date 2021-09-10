
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


    ExSpinBoxW m_sbDeviceId{"device_id"};
    ExSpinBoxW m_sbFPS{"requested_fps"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};

class WebcamViewerConfigParametersW : public ConfigParametersW{

public :

    EyeRendererSubPart m_eye;

    WordSpaceCanvasSubPart m_cameraSettings;
    ExCheckBoxW m_followEyeCamera{"use_eye_camera"};
    ExCheckBoxW m_cbUseVideoSize{"use_original_size"};
    ExVector2dW m_pivot{"pivot"};
    ExFloatSpinBoxW m_distance{"distance"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
