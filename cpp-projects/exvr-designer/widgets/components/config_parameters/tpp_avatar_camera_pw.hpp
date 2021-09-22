
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "widgets/components/config_parameters/config_pw.hpp"

namespace tool::ex {

class TPPAvatarCameraInitConfigParametersW : public ConfigParametersW{

public :

    TPPAvatarCameraInitConfigParametersW();

    void insert_widgets() override;
    void init_and_register_widgets() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

class TPPAvatarCameraConfigParametersW : public ConfigParametersW{

public :

    TPPAvatarCameraConfigParametersW();

    void insert_widgets() override;
    void init_and_register_widgets() override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;

};

}
