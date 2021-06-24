
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
#include "interval.hpp"
#include "connector.hpp"
#include "connection.hpp"
#include "resource.hpp"

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

    // routine
    void routine_selected_signal(ElementKey routineKey);
    // # condition
    void routine_condition_selected_signal(ElementKey routineKey, RowId  conditionTabId);
    void copy_condition_to_signal(ElementKey routineKey, ConditionKey conditionKey);
    // ## actions
    void delete_actions_signal(ElementKey routineKey, ConditionKey conditionKey);
    void fill_actions_signal(ElementKey routineKey, ConditionKey conditionKey);
    void clean_actions_signal(ElementKey routineKey, ConditionKey conditionKey);
    void add_action_signal(ElementKey routineKey, ConditionKey conditionKey, ComponentKey componentKey);
    void delete_action_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey);
    void fill_action_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, bool update, bool visibility);
    void clean_action_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, bool update, bool visibility);
    void move_action_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, RowId id);
    void move_action_up_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey);
    void move_action_down_signal(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey);
    // ### config
    // # config
    void select_config_signal(ElementKey routineKey,ConditionKey conditionKey, ActionKey actionKey, RowId configTabId);
    // ### timeline
    void update_timeline_signal(ElementKey routineKey,ConditionKey conditionKey, double duration, double scale, double uiSize);
    // #### interval
    void add_interval_signal(ElementKey routineKey,ConditionKey conditionKey, ActionKey actionKey, bool updateTimeline, TimelineKey timelineKey, Interval interval);
    void remove_interval_signal(ElementKey routineKey,ConditionKey conditionKey, ActionKey actionKey, bool updateTimeline, TimelineKey timelineKey, Interval interval);
    // ## connections
    void delete_connections_signal(ElementKey routineKey, ConditionKey conditionKey);
    void nodes_connection_created_signal(ElementKey routineKey,ConditionKey conditionKey, Connection *connection);
    void connector_input_connection_validity_signal(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey, bool state);
    // ## connectors
    void show_connector_node_documentation_signal(ElementKey routineKey, ConditionKey conditionKey, ConnectorKey connectorKey);
    void connector_node_created_signal(ElementKey routineKey,ConditionKey conditionKey, Connector *connector);
    void connector_node_modified_signal(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey, QString name, Arg arg);
    void connector_node_moved_signal(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey, QPointF pos);
    void duplicate_connector_node_signal(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey);
    // # components
    void show_component_node_documentation_signal(ComponentKey componentKey);
    void component_node_created_signal(ElementKey routineKey,ConditionKey conditionKey, ComponentKey componentKey, QPointF pos);
    void component_node_moved_signal(ElementKey routineKey,ConditionKey conditionKey, ComponentKey componentKey, QPointF pos);
    // ## components / connectors / connections
    void unselect_nodes_and_connections_signal(ElementKey routineKey,ConditionKey conditionKey, bool doUpdate);
    void delete_nodes_and_connections_signal(ElementKey routineKey, ConditionKey conditionKey,
        std_v1<ConnectorKey> connectorsKey, std_v1<ComponentKey> componentsKey, std_v1<ConnectionKey> connectionsKey, bool doUpdate);
    void select_nodes_and_connections_signal(ElementKey routineKey, ConditionKey conditionKey,
        std_v1<ConnectorKey> connectorsKey, std_v1<ComponentKey> componentsKey, std_v1<ConnectionKey> connectionsKey, bool doUpdate);

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
