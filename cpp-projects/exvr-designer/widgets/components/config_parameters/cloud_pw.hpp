
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "ex_widgets/ex_resource_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {

class CloudInitConfigParametersW : public ConfigParametersW{

public :

    ExResourceW m_cloud{"cloud"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {m_cloud()}, LStretch{false}, LMargins{true}, QFrame::Box));
    }

    void init_and_register_widgets() override{
        add_input_ui(m_cloud.init_widget(Resource::Type::Cloud, "Cloud resource: "));
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

class CloudConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo{"transform"};

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget());
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


}
