
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
#include "ex_line_edit_w.hpp"


#include "ex_config_w.hpp"

namespace tool::ex {

class AssetBundleInitConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo;
    ExResourceW m_assetBundle;
    ExLineEditW m_leSubObjectName;
    ExCheckBoxW m_displayHierarchy;
    QTextEdit *m_hierarchy = nullptr;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
    void update_with_info(QStringView id, QStringView value) override;
};

class AssetBundleConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
