
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

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

    TransformSubPart m_transfo;
    ExSelectColorW m_onColor;
    ExSelectColorW m_offColor;
    ExCheckBoxW m_on;

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
        add_widget(ui::F::gen(ui::L::HB(), {m_on()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("<b>Colors:</b> "), ui::W::txt("ON"), m_onColor(), ui::W::txt("OFF"), m_offColor()}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget("Dot transform","transform"));
        m_inputUiElements["on"]         = m_on.init_widget("On ", false);
        m_inputUiElements["on_color"]   = m_onColor.init_widget("Select ON color", Qt::white);
        m_inputUiElements["off_color"]  = m_offColor.init_widget("Select OFF color", Qt::black);
        m_transfo.tr.set_scale_values({0.1,0.1,0.1});
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

}
