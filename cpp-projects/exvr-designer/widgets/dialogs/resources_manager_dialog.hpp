
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QDialog>
#include <QFileDialog>

// base
#include "utility/vector_utility.hpp"

// local
#include "resources/resources_manager.hpp"
#include "ui_resources_manager_dialog.h"
#include "ui_resource_type.h"


namespace tool::ex {

class VerticalTextTabWidgetStyle : public QProxyStyle{
    public:
    QSize sizeFromContents(ContentsType type, const QStyleOption* option,const QSize& size, const QWidget* widget) const;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const;
};

class ResourcesManagerDialog : public QDialog{
Q_OBJECT
public:

    ResourcesManagerDialog();
    void update_from_resources_manager(const ResourcesManager *resM);

public slots:

    void update_resources_to_reload();
    void generate_csharp_script();
    void show_section(Resource::Type type);

signals:

    void add_resources_signal(Resource::Type type, QStringList path);
    void update_resource_path_signal(QString currentPath, QString newPath);
    void update_resource_alias_signal(QString currentPath, QString newAlias);

    void resource_selected_signal(Resource::Type type, size_t index);
    void clean_resources_signal(Resource::Type type);
    void remove_resource_signal(Resource::Type type, size_t index);

    void update_reload_resource_code_signal(int code);
private:

    Ui::ResourcesManagerD m_ui;
    std::unordered_map<Resource::Type, std::tuple<Ui::ResourceTypeW,QWidget*>> m_typesW;
    std::unordered_map<Resource::Type, int> m_tabsIdW;


};


}
