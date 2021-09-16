
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_checkbox_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {


class MirrorInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};


class MirrorConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transform{"transform"};
    ExCheckBoxW m_showFrame{"show_frame"};

    void insert_widgets() override{
        add_sub_part_widget(m_transform);
        add_widget(ui::F::gen(ui::L::HB(), {m_showFrame()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transform.init_widget());
        add_input_ui(m_showFrame.init_widget("Show frame", true));
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

}
