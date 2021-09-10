
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDesktopServices>
#include <QDirIterator>
#include <QDir>
#include <QListWidget>

// local
#include "config_pw.hpp"
#include "path_utility.hpp"
#include "ex_double_spin_box_w.hpp"

namespace tool::ex {

class ParallelPortWriterInitConfigParametersW : public ConfigParametersW{

public :

    ExCheckBoxW m_x32Mode{"x32_mode"};
    ExCheckBoxW m_int16Mode{"int16_mode"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::VB(),{m_x32Mode(), m_int16Mode()}, LStretch{true}, LMargins{true},QFrame::Box));
    }

    void init_and_register_widgets() override{        
        add_input_ui(m_x32Mode.init_widget("Use x32 dll", false));
        add_input_ui(m_int16Mode.init_widget("Use 16 bits integers as sending values", false));
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

class ParallelPortWriterConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_port{"port"};
    ExDoubleSpinBoxW m_pulseTime{"pulse_time"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Port:"), m_port()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Pulse time:"), m_pulseTime()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    }

    void init_and_register_widgets() override{
        add_input_ui(m_port.init_widget(MinV<int>{0}, V<int>{50000}, MaxV<int>{65535}, StepV<int>{1}));
        add_input_ui(m_pulseTime.init_widget(MinV<qreal>{0.00}, V<qreal>{1.0}, MaxV<qreal>{10.}, StepV<qreal>{0.01}, 2));
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

}
