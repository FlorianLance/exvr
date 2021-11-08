/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "serial_port_reader_pw.hpp"


// qt-utility
#include "ex_widgets/ex_line_edit_w.hpp"
#include "ex_widgets/ex_spin_box_w.hpp"
#include "ex_widgets/ex_radio_button_w.hpp"
#include "ex_widgets/ex_checkbox_w.hpp"
#include "ex_widgets/ex_text_edit_w.hpp"
#include "ex_widgets/ex_double_spin_box_w.hpp"

using namespace tool::ex;

struct SerialPortReaderInitParameterW::Impl{
    ExLineEditW leReaderPort{"port_to_read"};
};

SerialPortReaderInitParameterW::SerialPortReaderInitParameterW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void SerialPortReaderInitParameterW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Reader port:"), m_p->leReaderPort()}, LStretch{true}, LMargins{false}));
}

void SerialPortReaderInitParameterW::init_and_register_widgets(){
    add_input_ui(m_p->leReaderPort.init_widget("COM1"));
}


struct SerialPortReaderConfigParametersW::Impl{

    QButtonGroup group1;
    ExRadioButtonW rbIntMessage{"int_mode"};
    ExRadioButtonW rbStringMessage{"string_mode"};
};

SerialPortReaderConfigParametersW::SerialPortReaderConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void SerialPortReaderConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::VB(), {m_p->rbIntMessage(), m_p->rbStringMessage()}, LStretch{true}, LMargins{false}));
}


void SerialPortReaderConfigParametersW::init_and_register_widgets(){

    add_inputs_ui(
        ExRadioButtonW::init_group_widgets(m_p->group1,
        {&m_p->rbIntMessage, &m_p->rbStringMessage},
        {
            "Integers message",
            "String message"
        },
        {
            true, false}
        )
    );
}

