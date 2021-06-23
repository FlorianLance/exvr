
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// local
#include "config_pw.hpp"
#include "ex_resource_w.hpp"

namespace tool::ex {

class ImageResourceInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};


class ImageResourceConfigParametersW : public ConfigParametersW{

public :

    ExResourceW m_image;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
