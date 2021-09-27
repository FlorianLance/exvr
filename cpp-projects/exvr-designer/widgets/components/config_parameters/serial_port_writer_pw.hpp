
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"

namespace tool::ex {

class SerialPortWriteInitParameterW : public ConfigParametersW{

public :

    SerialPortWriteInitParameterW();

    void insert_widgets() override;
    void init_and_register_widgets() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};


class SerialPortWriterConfigParametersW : public ConfigParametersW{

public :

    SerialPortWriterConfigParametersW();

    void insert_widgets() override;
    void init_and_register_widgets() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

}
