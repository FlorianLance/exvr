
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// nodes
#include "nodes/NodeDataModel.hpp"
using QtNodes::NodeValidationState;

// qt-utility
#include "ex_widgets/ex_line_edit_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"


namespace tool::ex {

class CheckStrEmbeddedW : public NodeContainerW<ExLineEditW>{
    Q_OBJECT
public:
    void initialize() override;
};

class CheckStrNodeDataModel : public TypedConnectorDataModel<Connector::Type::Check_str, CheckStrEmbeddedW>{
    Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};
}
