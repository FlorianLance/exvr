
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"

namespace tool::ex {

class AudioSourceInitConfigParametersW : public ConfigParametersW{

public :

    AudioSourceInitConfigParametersW();

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
    void update_with_info(QStringView id, QStringView value) override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

class AudioSourceConfigParametersW : public ConfigParametersW{

public :

    AudioSourceConfigParametersW();

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;

};

}
