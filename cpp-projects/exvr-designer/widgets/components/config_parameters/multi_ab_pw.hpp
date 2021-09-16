
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// local
#include "ex_widgets/ex_resources_list_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {

class MultiABInitConfigParametersW : public ConfigParametersW{

public :

    ExResourcesListW abList{"ab_list"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
};

class MultiABConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo{"transform"};
    ExResourceW m_currentAB{"ab_alias"};
    void insert_widgets() override;
    void init_and_register_widgets() override;
};
}
