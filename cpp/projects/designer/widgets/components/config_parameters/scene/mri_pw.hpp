
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "path_utility.hpp"
#include "ex_double_spin_box_w.hpp"
#include "ex_radio_button_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_component_w.hpp"
#include "ex_components_list_w.hpp"

namespace tool::ex {

class MriInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

    ExComponentW humanoidController;

    ExComponentW keyboard;
    ExComponentsListW loggersList;

    ExComboBoxTextW triggerKey;

};

class MriConfigParametersW : public ConfigParametersW{

public :

    DefaultTransformSubPart transform;

    ExCheckBoxW goNextWhenTrigger;

    ExRadioButtonW solve;
    ExRadioButtonW dissolve;
    ExRadioButtonW move_table_inside;
    ExRadioButtonW move_table_outside;
    ExRadioButtonW move_table_qualisys;
    ExRadioButtonW nothing;    

    ExDoubleSpinBoxW duration;
    ExDoubleSpinBoxW distance;
    ExCheckBoxW room;
    ExCheckBoxW magnet;

    ExCheckBoxW initQualisysPositions;
    ExCheckBoxW enableQualisysArmsTracking;
    ExVector3dW targetHeadTrOffset;
    ExVector3dW targetHeadRotOffset;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
