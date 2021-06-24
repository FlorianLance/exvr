
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

    ExLineEditW m_leWritingPort;
    ExSpinBoxW m_sbBaudRate;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Writing port:"), m_leWritingPort()}, LStretch{true}, LMargins{false}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Baud rate:"), m_sbBaudRate()}, LStretch{true}, LMargins{false}));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["port_to_write"] = m_leWritingPort.init_widget("COM1");
        m_inputUiElements["baud_rate"]     = m_sbBaudRate.init_widget(MinV<int>{0}, V<int>{9600}, MaxV<int>{100000000}, StepV<int>{100});
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class SerialPortWriterConfigParametersW : public ConfigParametersW{

public :

    ExRadioButtonW m_rbBitsMessage;
    ExRadioButtonW m_rbIntMessage;
    ExRadioButtonW m_rbStringMessage;

    ExTextEditW m_teMessage;
    ExCheckBoxW m_cbSendWhendRoutineStarts;
    ExCheckBoxW m_cbSendWhenNewTimelineBlock;
    ExCheckBoxW m_cbSendWhenEndTimelineBlock;
    ExCheckBoxW m_cbSendEveryFrame;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::VB(), {m_rbBitsMessage(), m_rbIntMessage(), m_rbStringMessage()}, LStretch{true}, LMargins{false}));
        add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("Message to sent:"),  m_teMessage()}, LStretch{false}, LMargins{false}));
        add_widget(ui::F::gen(ui::L::VB(), {m_cbSendWhendRoutineStarts(),
                                                  m_cbSendWhenNewTimelineBlock(),
                                                  m_cbSendWhenEndTimelineBlock(),
                                                  m_cbSendEveryFrame()}, LStretch{true}, LMargins{false}));

    }
    void init_and_register_widgets() override{
        m_inputUiElements["bits_mode"]              = m_rbBitsMessage.init_widget("Bits message (ex: 0101_0100 0101_0110...)", false);
        m_inputUiElements["int_mode"]               = m_rbIntMessage.init_widget("Integers message (ex: 254 13 0 255...)", false);
        m_inputUiElements["string_mode"]            = m_rbStringMessage.init_widget("String message (ex: blabla...)", true);
        m_inputUiElements["message"]                = m_teMessage.init_widget("...");
        m_inputUiElements["send_new_routine"]       = m_cbSendWhendRoutineStarts.init_widget("Send message when routine starts ", true);
        m_inputUiElements["send_new_update_block"]  = m_cbSendWhenNewTimelineBlock.init_widget("Send message when new update timeline block starts ", false);
        m_inputUiElements["send_end_update_block"]  = m_cbSendWhenEndTimelineBlock.init_widget("Send message when update timeline block ends", false);
        m_inputUiElements["send_every_frame"]       = m_cbSendEveryFrame.init_widget("Send message at every frame", false);
    }

    void create_connections() override{

    }
    void late_update_ui() override{}
};

}
