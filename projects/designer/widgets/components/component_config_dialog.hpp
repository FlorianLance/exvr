
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

class ComponentsConfigDialog;
using ComponentsConfigDialogUP = std::unique_ptr<ComponentsConfigDialog>;



class ComponentsConfigDialog : public QDialog{

    Q_OBJECT

public:

    ComponentsConfigDialog(QWidget *parent);

    void init(Component *component);

    void update_from_component(Component *component);
    void update_with_info(ConfigKey configKey, QStringView id, QStringView value);

signals:

//    // static
//    void static_state_changed_signal(bool isStatic, bool staticUpdate, bool staticVisiblity);

    // name
    void name_changed_signal(QString name);    

    // args
    void arg_updated_signal(ConfigKey configKey, QString name, Arg arg, bool initConfig);
    void move_arg_up_signal(ConfigKey configKey, QString previousName, QString name, bool initConfig);
    void move_arg_down_signal(ConfigKey configKey, QString nextName, QString name, bool initConfig);
    void arg_removed_signal(ConfigKey configKey, QString name, bool initConfig);
    void new_arg_signal(ConfigKey configKey, QString name, Arg arg, bool initConfig);
    void action_signal(ConfigKey configKey, QString name, bool initConfig);

    // config
    void insert_config_signal(RowId id, QString name);
    void copy_config_signal(RowId id, QString name);
    void remove_config_signal(RowId id);
    void move_config_signal(RowId from, RowId to);
    void rename_config_signal(RowId id, QString name);

    // help
    void display_component_help_window_signal(Component::Type type, bool resetWindow = true);

private :


    inline ConfigW* get_init_config_widget(){
         return qobject_cast<ConfigW*>(m_ui.vlInitConfig->itemAt(0)->widget());
    }

    inline ConfigW* get_config_widget(int index){
        return qobject_cast<ConfigW*>(m_ui.tabConfigs->widget(index));
    }

    ConfigParametersW *generate_parameters(Component::Type type, bool initConfig);

public:

    int key;

private:

    ConfigW *m_initConfigW = nullptr;

    // dialog
    Ui::BaseComponentConfigWidget m_ui;

    Qt::WindowFlags defaultFlags;
    bool pinned = false;
    QWidget *m_parent = nullptr;

template<typename T>
static ConfigParametersW *gen_params_w(){

        auto w = new T();

        // sub widgets
        w->insert_widgets();
        w->init_and_register_widgets();
        w->create_connections();
        w->end_stretch();

        return w;
    }
};


}
