
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QFileDialog>

// qt-utility
#include "ex_widgets/ex_checkbox_w.hpp"
#include "ex_widgets/ex_line_edit_w.hpp"

// local
#include "ex_widgets/ex_resource_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {

class AssetBundleInitConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo{"init_transform"};
    ExResourceW m_assetBundle {"asset_bundle"};
    ExLineEditW m_leSubObjectName{"name_sub_object"};
    ExCheckBoxW m_displayHierarchy{"display_hierarchy"};
    QTextEdit *m_hierarchy = nullptr;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
    void update_with_info(QStringView id, QStringView value) override;
};

class AssetBundleConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo{"transform"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
