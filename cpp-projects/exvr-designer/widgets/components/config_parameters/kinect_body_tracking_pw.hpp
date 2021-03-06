
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "ex_widgets/ex_component_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {

class KinectBodyTrackingInitConfigParametersW : public ConfigParametersW{

public :


    ExComponentW m_kinectManager{"kinect_manager"};

    void insert_widgets() override{

        add_widget(ui::F::gen(ui::L::HB(), {m_kinectManager()}, LStretch{false}, LMargins{true}, QFrame::Box));
    }

    void init_and_register_widgets() override{
        add_input_ui(m_kinectManager.init_widget(Component::Type::Kinect_manager, "Kinect manager component: "));
    }

    void create_connections() override{
    }

    void late_update_ui() override{}
};


class KinectBodyTrackingConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_tr {"global_transform"};

    void insert_widgets() override{
        add_sub_part_widget(m_tr);
    }

    void init_and_register_widgets() override{
        map_sub_part(m_tr.init_widget("Global model transform"));
    }

    void create_connections() override{
        // ...
    }


    void late_update_ui() override{}
};

}
