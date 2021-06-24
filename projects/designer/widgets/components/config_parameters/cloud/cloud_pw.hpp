
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "path_utility.hpp"

namespace tool::ex {

class CloudInitConfigParametersW : public ConfigParametersW{

public :

    ExResourceW m_cloud;
//    ExFloatSpinBoxW m_dsbSize;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {m_cloud()}, LStretch{false}, LMargins{true}, QFrame::Box));
//        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Cube size: "),m_dsbSize()}, LStretch{true}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["cloud"] = m_cloud.init_widget(Resource::Type::Cloud, "Cloud resource: ");
//        m_inputUiElements["size"] = m_dsbSize.init_widget(MinV<qreal>{0.1}, V<qreal>{1.}, MaxV<qreal>{1000.}, StepV<qreal>{0.1},1);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

class CloudConfigParametersW : public ConfigParametersW{

public :

    DefaultTransformSubPart m_transfo;
//    ExSelectColorW m_color;

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget());
//        m_inputUiElements["color"] = m_color.init_widget("Color", Qt::gray);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


}
