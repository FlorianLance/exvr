
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

class UdpReaderInitConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_sbReadingPort{"reading_port"};
    ExLineEditW m_leReadingIpAdress{"reading_address"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Reading port:"), m_sbReadingPort()}, LStretch{true}, LMargins{false}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Reading IP adress (or hostname):"), m_leReadingIpAdress()}, LStretch{true}, LMargins{false}));
    }

    void init_and_register_widgets() override{        
        add_input_ui(m_sbReadingPort.init_widget( MinV<int>{0}, V<int>{8060}, MaxV<int>{100000}, StepV<int>{1}));
        add_input_ui(m_leReadingIpAdress.init_widget("127.0.0.1"));
    }


    void create_connections() override{}
    void late_update_ui() override{}
};


class UdpReaderConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

}
