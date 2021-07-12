
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

    ComponentsManagerW(bool lncoComponents);

    ComponentConfigDialog *component_dialog(ComponentKey componentKey);
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
    void update_component_position_signal(ComponentKey componentKey, RowId id);
    void add_component_signal(Component::Type, RowId id);    
    void remove_component_signal(ComponentKey componentKey);
    void duplicate_component_signal(ComponentKey componentKey);
    void identify_component_signal(ComponentKey componentKey);
    // # sort
    void sort_components_by_category_signal();
    void sort_components_by_type_signal();
    void sort_components_by_name_signal();



    void ask_for_udapte_signal(int);

private :

    bool m_lncoComponents = false;

    QPoint m_lastPos;

    // menus
    QMenu m_createNewComponentsSubMenu;
    QMenu m_createNewExperimentalComponentsSubMenu;
    QMenu m_sortComponentsSubMenu;

    ui::ListWidget m_componentsListW;
    std::unordered_map<int, ComponentsConfigDialogUP> m_dialogsW;

    QComboBox m_cbComponentsToDisplay;

};

}
