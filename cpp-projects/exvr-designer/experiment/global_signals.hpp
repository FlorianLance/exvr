
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <memory>

// Qt
#include <QObject>

// local
#include "data/interval.hpp"
#include "data/connector.hpp"
#include "data/connection.hpp"
#include "data/loop.hpp"
#include "resources/resource.hpp"

namespace tool::ex{

class GSignals : public QObject{
    Q_OBJECT
public:

    static void init();
    static GSignals *get();

signals:

    // ui
    void show_resources_manager_dialog_signal(Resource::Type type = Resource::Type::SizeEnum);
    void show_documentation_signal();
    void show_about_signal();
    void show_settings_dialog_signal();
    void show_benchmark_dialog_signal();
    void toggle_mode_signal();
    void toggle_follow_condition_mode_signal();

    // state
    void exp_launcher_state_updated_signal(ExpLauncherState state, QStringView infos);
    void exp_state_updated_signal(ExpState state, QStringView infos);

    // info
    void component_info_update_signal(ComponentKey componentKey, ConfigKey configKey, QStringView id, QStringView value);
    void connector_info_update_signal(ElementKey elementKey, ConditionKey conditionKey, ConnectorKey connectorKey, QStringView uiName, QStringView value);

    // elements
    void update_element_name_signal(ElementKey key, QString name);
    // # loops
    void select_loop_set_signal(ElementKey loopKey, QString set);
    void modify_loop_nb_reps_signal(ElementKey loopKey, int nbReps);
    void modify_loop_n_signal(ElementKey loopKey, int nbReps);
    void modify_loop_type_signal(ElementKey loopKey, Loop::Mode mode);
    void modify_loop_set_name_signal(ElementKey loopKey, QString set, RowId idSet);
    void modify_loop_set_occurrencies_nb_signal(ElementKey loopKey, int occurenciesNb, RowId idSet);
    void add_loop_sets_signal(ElementKey loopKey, QString set, RowId idSet);
    void remove_set_signal(ElementKey loopKey, RowId idSet);
    void move_loop_set_up_signal(ElementKey loopKey, RowId idSet);
    void move_loop_set_down_signal(ElementKey loopKey, RowId idSet);
    void load_loop_sets_file_signal(ElementKey loopKey, QString filePath);
    void reload_loop_sets_file_signal(ElementKey loopKey);
    // # isi
    void set_isi_randomize_signal(ElementKey isiKey, bool checked);
    void add_isi_interval_signal(ElementKey isiKey, double interval, RowId idInterval);
    void modify_isi_interval_signal(ElementKey isiKey, double interval, RowId idInterval);
    void remove_isi_interval_signal(ElementKey isiKey, RowId idInterval);
    void move_isi_interval_up_signal(ElementKey isiKey, RowId idInterval);
    void move_isi_interval_down_signal(ElementKey isiKey, RowId idInterval);
    // # routine
    void set_routine_as_randomizer_signal(ElementKey routineKey, bool isARandomizer);
    void routine_selected_signal(ElementKey routineKey);
    void select_routine_condition_signal(ElementKey routineKey, RowId conditionTabId);
    void move_routine_condition_down_signal(ElementKey routineKey, RowId conditionTabId);
    void move_routine_condition_up_signal(ElementKey routineKey, RowId conditionTabId);
    // ## condition
    void routine_condition_selected_signal(ElementKey routineKey, RowId  conditionTabId);
    void copy_condition_to_signal(ElementKey routineKey, ConditionKey conditionKey);
    // ### actions
    void delete_actions_signal(ElementKey routineKey, ConditionKey conditionKey);
    void fill_actions_signal(ElementKey routineKey, ConditionKey conditionKey);
    void clean_actions_signal(ElementKey routineKey, ConditionKey conditionKey);    
    void add_action_signal(ElementKey routineKey, ConditionKey conditionKey, ComponentKey componentKey, std::optional<ConfigKey> ConfigKey, bool fillUpdate, bool fillVisibility);
    void delete_action_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey);
    void fill_action_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, bool update, bool visibility);
    void clean_action_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, bool update, bool visibility);
    void move_action_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, RowId id);
    void move_action_up_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey);
    void move_action_down_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey);
    void insert_action_to_selected_routine_signal(ComponentKey componentKey);
    void insert_action_to_all_selected_routine_conditions_signal(ComponentKey componentKey);
    void insert_action_to_all_routines_conditions_signal(ComponentKey componentKey, std::optional<ConfigKey> ConfigKey, bool fillUpdate, bool fillVisibility);
    void insert_action_with_details_signal(ComponentKey componentKey);
    void remove_action_from_all_selected_routine_conditions_signal(ComponentKey componentKey);
    void remove_action_from_all_routines_conditions_signal(ComponentKey componentKey);
    // #### timeline
    void update_timeline_signal(ElementKey routineKey,ConditionKey conditionKey, double duration, double scale, double uiSize);
    // ##### interval
    void add_interval_signal(ElementKey routineKey,ConditionKey conditionKey, ActionKey actionKey, bool updateTimeline, TimelineKey timelineKey, Interval interval);
    void remove_interval_signal(ElementKey routineKey,ConditionKey conditionKey, ActionKey actionKey, bool updateTimeline, TimelineKey timelineKey, Interval interval);
    // ### connections / connectors / nodes
    void delete_connections_signal(ElementKey routineKey, ConditionKey conditionKey);
    void nodes_connection_created_signal(ElementKey routineKey,ConditionKey conditionKey, Connection *connection);
    void connector_input_connection_validity_signal(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey, bool state);
    void show_connector_node_documentation_signal(ElementKey routineKey, ConditionKey conditionKey, ConnectorKey connectorKey);
    void connector_node_created_signal(ElementKey routineKey,ConditionKey conditionKey, Connector *connector);
    void connector_node_modified_signal(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey, QString name, Arg arg);
    void connector_node_moved_signal(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey, QPointF pos);
    void duplicate_connector_node_signal(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey);
    void component_node_created_signal(ElementKey routineKey,ConditionKey conditionKey, ComponentKey componentKey, QPointF pos);
    void component_node_moved_signal(ElementKey routineKey,ConditionKey conditionKey, ComponentKey componentKey, QPointF pos);
    void unselect_nodes_and_connections_signal(ElementKey routineKey,ConditionKey conditionKey, bool doUpdate);
    void delete_nodes_and_connections_signal(ElementKey routineKey, ConditionKey conditionKey,
        std_v1<ConnectorKey> connectorsKey, std_v1<ComponentKey> componentsKey, std_v1<ConnectionKey> connectionsKey, bool doUpdate);
    void select_nodes_and_connections_signal(ElementKey routineKey, ConditionKey conditionKey,
        std_v1<ConnectorKey> connectorsKey, std_v1<ComponentKey> componentsKey, std_v1<ConnectionKey> connectionsKey, bool doUpdate);

    // # components
    void show_component_node_documentation_signal(ComponentKey componentKey);
    void display_component_help_window_signal(Component::Type type, bool resetWindow = true);
    void component_name_changed_signal(ComponentKey componentKey, QString name);
    void sort_components_by_category_signal();
    void sort_components_by_type_signal();
    void sort_components_by_name_signal();
    void update_component_position_signal(ComponentKey componentKey, RowId position);
    void add_component_signal(Component::Type type, RowId position);
    void show_component_custom_menu_signal(QPoint globalPos, ComponentKey key);
    void toggle_selection_component_signal(ComponentKey key);
    void toggle_component_parameters_signal(ComponentKey key);
    void remove_component_signal(ComponentKey key);
    void duplicate_component_signal(ComponentKey componentKey);
    void enter_component_signal(ComponentKey key);
    void leave_component_signal(ComponentKey key);
    void show_component_informations_signal(ComponentKey componentKey);
    // ## config
    void select_action_config_signal(ElementKey routineKey,ConditionKey conditionKey, ActionKey actionKey, RowId configTabId);
    void insert_config_signal(ComponentKey componentKey, RowId id, QString name);
    void copy_config_signal(ComponentKey componentKey, RowId id, QString name);
    void remove_config_signal(ComponentKey componentKey, RowId id);
    void select_config_signal(ComponentKey componentKey, RowId id);
    void move_config_signal(ComponentKey componentKey, RowId from, RowId to);
    void rename_config_signal(ComponentKey componentKey, RowId id, QString name);
    // ### args
    void new_arg_signal(ComponentKey componentKey, ConfigKey configKey, Arg arg, bool initConfig);
    void arg_updated_signal(ComponentKey componentKey, ConfigKey configKey, Arg arg, bool initConfig);
    void arg_removed_signal(ComponentKey componentKey, ConfigKey configKey, QStringView argName, bool initConfig);
    void swap_arg_signal(ComponentKey componentKey, ConfigKey configKey, QStringView argName1, QStringView argName2, bool initConfig);
    void action_signal(ComponentKey componentKey, ConfigKey configKey, QStringView actionName, bool initConfig);

    void ask_for_udapte_signal(int);

private:
    static inline std::unique_ptr<GSignals> m_signals = nullptr;
};

class BlockSignalsGuard{
public:
    BlockSignalsGuard(){
        currentState = GSignals::get()->signalsBlocked();
        GSignals::get()->blockSignals(true);
    }

    ~BlockSignalsGuard(){
        GSignals::get()->blockSignals(currentState);
    }
private:
    bool currentState;
};
}
