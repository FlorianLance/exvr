
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <tuple>

// Qt
#include <QWidget>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QScrollArea>
#include <QListWidget>
#include <QMenu>

// local
#include "widgets/list_widget.hpp"
#include "data/components_manager.hpp"
#include "component_widget.hpp"
#include "component_config_dialog.hpp"

namespace tool::ex {



class ComponentsManagerW;
using ComponentsManagerWUP = std::unique_ptr<ComponentsManagerW>;


class ComponentsManagerW : public QFrame{

    Q_OBJECT

public :

    ComponentsManagerW(bool onlyPublicComponents, bool onlyStableComponents);

    ComponentsConfigDialog *component_dialog(ComponentKey componentKey);
    ComponentW *component_widget(ComponentKey componentKey);
    std::pair<int, ComponentW*> component_widget_with_position(ComponentKey componentKey);

    void reset();
    void update_from_components_manager(ComponentsManager *compM);
    void close_all_configs_dialogs();

public slots:        

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void update_component_dialog_with_info(ComponentKey componentKey, ConfigKey configKey, QStringView id, QStringView value);
    void update_style();
    void update_components_to_display();

protected slots:

    void toggle_component_parameters_dialog(ComponentKey componentKey);

    void show_howering_component_custom_menu(QPoint pos, ComponentKey componentKey);
    void show_context_menu(const QPoint &pos);

    void add_new_component(Component::Type type, int id);

    void toggle_component_selection(ComponentKey componentKey);

private:

    void initialize_menues();

signals:

    // component
    void set_component_static_state_signal(ComponentKey componentKey, bool isStatic, bool staticUpdate, bool staticVisibility);
    void update_component_position_signal(ComponentKey componentKey, RowId id);
    void add_component_signal(Component::Type, RowId id);    
    void update_component_name_signal(ComponentKey componentKey, QString name);
    void remove_component_signal(ComponentKey componentKey);
    void duplicate_component_signal(ComponentKey componentKey);
    void identify_component_signal(ComponentKey componentKey);
    // # sort
    void sort_components_by_category_signal();
    void sort_components_by_type_signal();
    void sort_components_by_name_signal();

    // action
    void insert_action_signal(ComponentKey componentKey);
    void insert_action_to_all_selected_routine_conditions_signal(ComponentKey componentKey);
    void insert_action_to_all_routines_conditions_signal(ComponentKey componentKey);
    void remove_action_from_all_selected_routine_conditions_signal(ComponentKey componentKey);
    void remove_action_from_all_routines_conditions_signal(ComponentKey componentKey);

    // arguments
    void arg_updated_signal(ComponentKey componentKey, ConfigKey configKey, QString name, Arg arg, bool initConfig);
    void arg_removed_signal(ComponentKey componentKey, ConfigKey configKey, QString name, bool initConfig);
    void move_arg_up_signal(ComponentKey componentKey, ConfigKey configKey, QString previousName, QString name, bool initConfig);
    void move_arg_down_signal(ComponentKey componentKey, ConfigKey configKey, QString nextName, QString name, bool initConfig);
    void new_arg_signal(ComponentKey componentKey, ConfigKey configKey, QString name, Arg arg, bool initConfig);
    void action_signal(ComponentKey componentKey, ConfigKey configKey, QString name, bool initConfig);

    void ask_for_udapte_signal(int);

    // configs
    void insert_config_in_component_signal(ComponentKey componentKey, RowId id, QString configName);
    void copy_config_from_component_signal(ComponentKey componentKey, RowId id, QString configName);
    void remove_config_from_component_signal(ComponentKey componentKey, RowId id);
    void move_config_in_component_signal(ComponentKey componentKey, RowId from, RowId to);
    void rename_config_in_component_signal(ComponentKey componentKey, RowId id, QString configName);

    // help
    void display_component_help_window_signal(Component::Type type, bool resetWindow = true);

private :

    bool m_onlyPublicComponents = true;
    bool m_onlyStableComponents = true;

    QPoint m_lastPos;

    // menus
    QMenu m_createNewComponentsSubMenu;
    QMenu m_sortComponentsSubMenu;

    ui::ListWidget m_componentsListW;
    std::unordered_map<int, ComponentsConfigDialogUP> m_dialogsW;

    QComboBox m_cbComponentsToDisplay;

};

}
