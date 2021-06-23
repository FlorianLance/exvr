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

class FopRobotInitConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW  m_readingPort;
    ExLineEditW m_readingAddress;

    ExSpinBoxW  m_writingPort;
    ExLineEditW m_writingAddress;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Reading address:"), m_readingAddress()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Reading port:"),    m_readingPort()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Writing address:"), m_writingAddress()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Writing port:"),    m_writingPort()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["read_address"]       = m_readingAddress.init_widget("127.0.0.1");
        m_inputUiElements["read_port"]          = m_readingPort.init_widget(MinV<int>{0},V<int>{5554}, MaxV<int>{44000}, StepV<int>{1});
        m_inputUiElements["write_address"]      = m_writingAddress.init_widget("127.0.0.1");
        m_inputUiElements["write_port"]         = m_writingPort.init_widget(MinV<int>{0},V<int>{5555}, MaxV<int>{44000}, StepV<int>{1});
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class FopRobotConfigParametersW : public ConfigParametersW{

public :

    ExRadioButtonW m_delayControl;
    ExRadioButtonW m_forceControl;
    ExRadioButtonW m_testTouch;
    ExRadioButtonW m_positionControl;
    ExRadioButtonW m_none;

    ExSpinBoxW m_delay;
    ExFloatSpinBoxW m_forceRatio;

    void insert_widgets() override{

        add_widget(ui::F::gen(ui::L::VB(),{
                ui::W::txt("Action to do:"),
                m_delayControl(),
                m_forceControl(),
                m_testTouch(),
                m_positionControl(),
                m_none()
            }, LStretch{true}, LMargins{false},QFrame::NoFrame)
        );

        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Delay:"),       m_delay()},        LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Force ratio:"), m_forceRatio()},   LStretch{true}, LMargins{false},QFrame::NoFrame));
    }

    void init_and_register_widgets() override{

        m_inputUiElements["delay_control"]      = m_delayControl.init_widget("Delay control", true);
        m_inputUiElements["force_control"]      = m_forceControl.init_widget("Force control", false);
        m_inputUiElements["test_touch"]         = m_testTouch.init_widget("Test touch", false);
        m_inputUiElements["position_control"]   = m_positionControl.init_widget("Position control", false);
        m_inputUiElements["none"]               = m_none.init_widget("None", false);

        m_inputUiElements["delay"]              = m_delay.init_widget(MinV<int>{0}, V<int>{500}, MaxV<int>{5000}, StepV<int>{1});
        m_inputUiElements["force_ratio"]        = m_forceRatio.init_widget(MinV<qreal>{0.f}, V<qreal>{1.f}, MaxV<qreal>{10000.f}, StepV<qreal>{0.01f}, 2);

    }

    void create_connections() override{}
    void late_update_ui() override{}
};

}
