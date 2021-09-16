/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_radio_button_w.hpp"
#include "ex_widgets/ex_line_edit_w.hpp"
#include "ex_widgets/ex_text_edit_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {

class QualisysTrackingInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

    QButtonGroup group1;
    ExRadioButtonW connectToFirstAvailable{"connect_to_first"};
    ExRadioButtonW specifyServer{"connect_to_specific"};
    ExLineEditW hostName{"host_name"};
    ExLineEditW ipAdress{"ip_address"};
};

class QualisysTrackingConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

    TransformSubPart transform{"transform"};
    ExTextEditW objects{"objects"};
};

}
