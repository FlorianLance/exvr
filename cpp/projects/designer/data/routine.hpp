
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "qt_logger.hpp"

// local
#include "element.hpp"
#include "condition.hpp"
#include "qt_str.hpp"

namespace tool::ex {

struct Routine;
using RoutineUP = std::unique_ptr<Routine>;

struct Routine : public Element {

    Routine(QString n, int id);

    static RoutineUP copy_with_new_element_id(const Routine &routineToCopy, const QString &newName);

    void select_condition(ConditionKey conditionKey);
    void move_condition_down(RowId id);
    void move_condition_up(RowId id);

    void create_nodes_connection(ConditionKey conditionKey, Connection *connection);
    void delete_nodes_connection(ConditionKey conditionKey, ConnectionKey connectionKey);

    void create_connector_node(ConditionKey conditionKey, Connector *connector);
    void move_connector_node(ConditionKey conditionKey, ConnectorKey connectorKey, QPointF pos);
    void duplicate_connector_node(ConditionKey conditionKey, ConnectorKey connectorKey);
    void modify_connector(ConditionKey conditionKey, ConnectorKey connectorKey, QString connectorName, Arg arg);
    void set_connector_input_connection_validity(ConditionKey conditionKey, ConnectorKey connectorKey, bool state);

    void fill_actions_from_condition(ConditionKey conditionKey);
    void clean_actions_from_condition(ConditionKey conditionKey);
    void delete_actions_from_condition(ConditionKey conditionKey);

    Condition *get_condition(ConditionKey conditionKey) const;

    QString to_string() const;

    std_v1<ConditionUP> conditions;
    std_v1<ConditionUP> ghostsConditions; // condition that could be restored
};

}
