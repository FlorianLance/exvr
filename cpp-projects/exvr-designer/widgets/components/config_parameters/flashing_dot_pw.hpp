
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_select_color_w.hpp"
#include "ex_widgets/ex_checkbox_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {

class FlashingDotInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

class FlashingDotConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo {"transform"};
    ExSelectColorW m_onColor{"on_color"};
    ExSelectColorW m_offColor{"off_color"};
    ExCheckBoxW m_on{"on"};

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
        add_widget(ui::F::gen(ui::L::HB(), {m_on()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("<b>Colors:</b> "), ui::W::txt("ON"), m_onColor(), ui::W::txt("OFF"), m_offColor()}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget("Dot transform"));        
        add_input_ui(m_on.init_widget("On ", false));
        add_input_ui(m_onColor.init_widget("Select ON color", Qt::white));
        add_input_ui(m_offColor.init_widget("Select OFF color", Qt::black));
        m_transfo.set_scale_values({0.1,0.1,0.1});
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

}
