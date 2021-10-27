
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDialog>

// local
#include "ui_base_component_config_widget.h"
#include "config_widget.hpp"

namespace tool::ex {

class ComponentConfigDialog;
using ComponentsConfigDialogUP = std::unique_ptr<ComponentConfigDialog>;



class ComponentConfigDialog : public QDialog{

    Q_OBJECT

public:

    ComponentConfigDialog(QWidget *parent, Component *component);

    void set_connections();

    void update_from_component(Component *component);
    void update_with_info(ConfigKey configKey, QStringView id, QStringView value);    

private :


    inline ConfigW* get_init_config_widget(){
         return qobject_cast<ConfigW*>(m_ui.vlInitConfig->itemAt(0)->widget());
    }

    inline ConfigW* get_config_widget(int index){
        return qobject_cast<ConfigW*>(m_ui.tabConfigs->widget(index));
    }

    ConfigParametersW *generate_parameters(Component::Type type, bool initConfig);

private slots:

    void show_insert_new_config_dialog();
    void show_duplicate_config_dialog();
    void show_rename_config_dialog();
    void show_reset_config_dialog();

public:

    ComponentKey componentKey;
    Component::Type componentType;

private:

    ConfigW *m_initConfigW = nullptr;

    // dialog
    std::unique_ptr<QDialog> m_modalDialog = nullptr;
    Ui::BaseComponentConfigWidget m_ui;

    Qt::WindowFlags defaultFlags;
    bool pinned = false;
    QWidget *m_parent = nullptr;

    bool m_isUpdating = false;
};


}
