
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// nodes
#include "nodes/NodeDataModel.hpp"
#include "nodes/NodeData.hpp"
using QtNodes::PortType;

// local
#include "ex_curve_w.hpp"
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class VariableDelayFEmbeddedW : public NodeContainerW<ExCurveW>{
Q_OBJECT
public:
    void initialize() override;
};

class VariableDelayNodeDataModel : public TypedConnectorDataModel<Connector::Type::Variable_delay, VariableDelayFEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
};
}


