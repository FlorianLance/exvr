/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_line_edit_w.hpp"
#include "ex_widgets/ex_spin_box_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {

class TheraTrainerTrackingInitConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_readingPort{"read_port"};
    ExLineEditW m_readingAddress{"read_address"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Reading address:"), m_readingAddress()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Reading port:"), m_readingPort()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    }

    void init_and_register_widgets() override{        
        add_input_ui(m_readingAddress.init_widget("127.0.0.1"));
        add_input_ui(m_readingPort.init_widget(MinV<int>{8000},V<int>{8080}, MaxV<int>{44000}, StepV<int>{1}));
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
