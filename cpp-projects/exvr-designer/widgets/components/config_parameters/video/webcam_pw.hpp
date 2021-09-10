
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"

namespace tool::ex {

class WebcamInitConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_sbDeviceId{"device_id"};
    ExSpinBoxW m_sbFPS{"requested_fps"};
    ExSpinBoxW m_sbWidth{"requested_width"};
    ExSpinBoxW m_sbHeight{"requested_height"};


    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Device id: "), m_sbDeviceId()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Requested FPS:"), m_sbFPS()}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Requested width:"), m_sbWidth()}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Requested height:"), m_sbHeight()}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
    }

    void init_and_register_widgets() override{

        add_input_ui(m_sbDeviceId.init_widget(MinV<int>{0}, V<int>{0}, MaxV<int>{32}, StepV<int>{1},  true));
        add_input_ui(m_sbFPS.init_widget(MinV<int>{1}, V<int>{30}, MaxV<int>{120}, StepV<int>{1},  true));
        add_input_ui(m_sbWidth.init_widget(MinV<int>{1}, V<int>{1024}, MaxV<int>{6000}, StepV<int>{1},  true));
        add_input_ui(m_sbHeight.init_widget(MinV<int>{1}, V<int>{768}, MaxV<int>{6000}, StepV<int>{1},  true));
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

class WebcamConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{
    }

    void init_and_register_widgets() override{
    }

    void create_connections() override{
    }

    void late_update_ui() override{
    }
};

}
