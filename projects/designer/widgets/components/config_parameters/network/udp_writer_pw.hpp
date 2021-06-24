
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

class UdpWriterInitConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_sbWritingPort;
    ExLineEditW m_leWritingIpAdress;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Writing port:"), m_sbWritingPort()}, LStretch{true}, LMargins{false}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Writing IP adress (or hostname):"), m_leWritingIpAdress()}, LStretch{true}, LMargins{false}));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["writing_port"]       = m_sbWritingPort.init_widget( MinV<int>{0}, V<int>{8060}, MaxV<int>{100000}, StepV<int>{1});
        m_inputUiElements["writing_address"]  = m_leWritingIpAdress.init_widget("127.0.0.1");
    }


    void create_connections() override{}
    void late_update_ui() override{}
};


class UdpWriterConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

}
