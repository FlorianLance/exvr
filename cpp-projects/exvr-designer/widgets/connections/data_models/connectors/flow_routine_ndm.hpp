
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#pragma once

// Qt
#include <QLabel>

// nodes
#include "nodes/NodeDataModel.hpp"
#include "nodes/NodeData.hpp"
using QtNodes::PortType;

// qt-utility
#include "ex_widgets/ex_label_w.hpp"
#include "ex_widgets/ex_line_edit_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {


class StartRoutineNodeDataModel : public TypedConnectorDataModel<Connector::Type::Start_routine, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};

class StopRoutineNodeDataModel : public TypedConnectorDataModel<Connector::Type::Stop_routine, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};

class PreUpdateRoutineNodeDataModel : public TypedConnectorDataModel<Connector::Type::Pre_update_routine, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};

class PostUpdateRoutineNodeDataModel : public TypedConnectorDataModel<Connector::Type::Post_update_routine, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};

class UpdateRoutineNodeDataModel : public TypedConnectorDataModel<Connector::Type::Update_routine, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};

class RoutineConditionEmbeddedW : public NodeContainerW<ExLineEditW>{
    Q_OBJECT
public:
    void initialize() override;
};

class RoutineConditionNodeDataModel : public TypedConnectorDataModel<Connector::Type::Routine_condition, RoutineConditionEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};

}


