
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "widgets/components/config_parameters/config_pw.hpp"

namespace tool::ex {

class FPPAvatarCameraInitConfigParametersW : public ConfigParametersW{

public :

    FPPAvatarCameraInitConfigParametersW();

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;


private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

class FPPAvatarCameraConfigParametersW : public ConfigParametersW{

public :

    FPPAvatarCameraConfigParametersW();

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;

};

}
