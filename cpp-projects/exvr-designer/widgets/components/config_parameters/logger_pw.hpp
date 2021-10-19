
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"

namespace tool::ex {

class LoggerInitConfigParametersW : public ConfigParametersW{

public :

    LoggerInitConfigParametersW();

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

class LoggerConfigParametersW : public ConfigParametersW{};

class LoggerColumnsInitConfigParametersW : public ConfigParametersW{

public :

    LoggerColumnsInitConfigParametersW();

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};


class LoggerColumnsConfigParametersW : public ConfigParametersW{};

class LoggerConditionInitConfigParametersW : public ConfigParametersW{

public :

    LoggerConditionInitConfigParametersW();

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};


class LoggerConditionConfigParametersW : public ConfigParametersW{};

}
