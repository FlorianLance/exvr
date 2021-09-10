
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "path_utility.hpp"

#include <QThread>
#include <QtSerialPort/QSerialPort>


namespace tool::ex {

class SerialPortWriterCommonParameterW : public ConfigParametersW{


public :

    ExLineEditW m_leWritingPort{"port_to_write"};
    ExSpinBoxW m_sbBaudRate{"baud_rate"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Writing port:"), m_leWritingPort()}, LStretch{true}, LMargins{false}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Baud rate:"), m_sbBaudRate()}, LStretch{true}, LMargins{false}));
    }

    void init_and_register_widgets() override{
        add_input_ui(m_leWritingPort.init_widget("COM1"));
        add_input_ui(m_sbBaudRate.init_widget(MinV<int>{0}, V<int>{9600}, MaxV<int>{100000000}, StepV<int>{100}));
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class SerialPortWriterConfigParametersW : public ConfigParametersW{

public :

    ExRadioButtonW m_rbBitsMessage{"bits_mode"};
    ExRadioButtonW m_rbIntMessage{"int_mode"};
    ExRadioButtonW m_rbStringMessage{"string_mode"};

    ExTextEditW m_teMessage{"message"};
    ExCheckBoxW m_cbSendWhendRoutineStarts{"send_new_routine"};
    ExCheckBoxW m_cbSendWhenNewTimelineBlock{"send_new_update_block"};
    ExCheckBoxW m_cbSendWhenEndTimelineBlock{"send_end_update_block"};
    ExCheckBoxW m_cbSendEveryFrame{"send_every_frame"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::VB(), {m_rbBitsMessage(), m_rbIntMessage(), m_rbStringMessage()}, LStretch{true}, LMargins{false}));
        add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("Message to sent:"),  m_teMessage()}, LStretch{false}, LMargins{false}));
        add_widget(ui::F::gen(ui::L::VB(), {m_cbSendWhendRoutineStarts(),
                                                  m_cbSendWhenNewTimelineBlock(),
                                                  m_cbSendWhenEndTimelineBlock(),
                                                  m_cbSendEveryFrame()}, LStretch{true}, LMargins{false}));

    }
    void init_and_register_widgets() override{
        add_input_ui(m_rbBitsMessage.init_widget("Bits message (ex: 0101_0100 0101_0110...)", false));
        add_input_ui(m_rbIntMessage.init_widget("Integers message (ex: 254 13 0 255...)", false));
        add_input_ui(m_rbStringMessage.init_widget("String message (ex: blabla...)", true));
        add_input_ui(m_teMessage.init_widget("..."));
        add_input_ui(m_cbSendWhendRoutineStarts.init_widget("Send message when routine starts ", true));
        add_input_ui(m_cbSendWhenNewTimelineBlock.init_widget("Send message when new update timeline block starts ", false));
        add_input_ui(m_cbSendWhenEndTimelineBlock.init_widget("Send message when update timeline block ends", false));
        add_input_ui(m_cbSendEveryFrame.init_widget("Send message at every frame", false));
    }

    void create_connections() override{

    }
    void late_update_ui() override{}
};

}
