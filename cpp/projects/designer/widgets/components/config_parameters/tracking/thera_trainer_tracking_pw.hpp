/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "ex_line_edit_w.hpp"
#include "ex_spin_box_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {

class TheraTrainerTrackingInitConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_readingPort;
    ExLineEditW m_readingAddress;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Reading address:"), m_readingAddress()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Reading port:"), m_readingPort()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["read_address"]   = m_readingAddress.init_widget("127.0.0.1");
        m_inputUiElements["read_port"]      = m_readingPort.init_widget(MinV<int>{8000},V<int>{8080}, MaxV<int>{44000}, StepV<int>{1});
    }

    void create_connections() override{}

    void late_update_ui() override{}
};


class TheraTrainerTrackingConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

}
