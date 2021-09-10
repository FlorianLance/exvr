
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_pushbutton_w.hpp"
#include "ex_resource_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_line_edit_w.hpp"
#include "ex_combo_box_index_w.hpp"

namespace tool::ex {

class KinectManagerInitConfigParametersW : public ConfigParametersW{

public :

    ExResourceW m_config{"config"};
    ExResourceW m_calib{"calib"};
    ExResourceW m_camera{"camera"};
    ExComboBoxIndexW m_mode{"mode"};
    ExLineEditW m_camarasToUse{"cameras_to_use"};
    ExCheckBoxW m_debugBypassDevice{"debug_bypass"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};


class KinectManagerConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_fps{"fps"};
    ExCheckBoxW m_updateFromCameras{"update_cameras"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};

}
