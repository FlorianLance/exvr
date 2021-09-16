
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_checkbox_w.hpp"

// local
#include "ex_widgets/ex_resources_list_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {

class PlotResourceInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};


class PlotResourceConfigParametersW : public ConfigParametersW{

public :

    ExResourceW m_plot{"plot"};
    ExCheckBoxW m_randomSelection{"random"};
    ExResourcesListW m_plotsList{"plots_list"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
