
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QFileDialog>

// local
#include "config_pw.hpp"
#include "path_utility.hpp"
#include "ex_resource_w.hpp"
#include "ex_resources_list_w.hpp"
#include "ex_line_edit_w.hpp"

#include "ex_config_w.hpp"

namespace tool::ex {

class MultiABInitConfigParametersW : public ConfigParametersW{

public :

    ExResourcesListW abList;

    void insert_widgets() override;
    void init_and_register_widgets() override;
};

class MultiABConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo;
    ExResourceW m_currentAB;
    void insert_widgets() override;
    void init_and_register_widgets() override;
};
}
