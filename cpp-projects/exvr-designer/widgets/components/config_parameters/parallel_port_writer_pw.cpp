

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "parallel_port_writer_pw.hpp"

// qt-utility
#include "ex_widgets/ex_checkbox_w.hpp"
#include "ex_widgets/ex_double_spin_box_w.hpp"
#include "ex_widgets/ex_spin_box_w.hpp"

using namespace tool::ex;

struct ParallelPortWriterInitConfigParametersW::Impl{
    ExCheckBoxW int16Mode{"int16_mode"};
};

struct ParallelPortWriterConfigParametersW::Impl{
    ExSpinBoxW port{"port"};
    ExDoubleSpinBoxW pulseTime{"pulse_time"};
};


ParallelPortWriterInitConfigParametersW::ParallelPortWriterInitConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void ParallelPortWriterInitConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::VB(),{m_p->int16Mode()}, LStretch{false}, LMargins{true},QFrame::NoFrame));
}

void ParallelPortWriterInitConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_p->int16Mode.init_widget("Use 16 bits integers as sending values", false));
}

ParallelPortWriterConfigParametersW::ParallelPortWriterConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void ParallelPortWriterConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Port:"), m_p->port()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Pulse time:"), m_p->pulseTime()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
}

void ParallelPortWriterConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_p->port.init_widget(MinV<int>{0}, V<int>{50000}, MaxV<int>{65535}, StepV<int>{1}));
    add_input_ui(m_p->pulseTime.init_widget(MinV<qreal>{0.00}, V<qreal>{1.0}, MaxV<qreal>{10.}, StepV<qreal>{0.01}, 2));
}
