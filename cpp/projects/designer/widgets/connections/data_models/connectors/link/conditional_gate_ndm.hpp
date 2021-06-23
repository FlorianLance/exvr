
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// nodes
#include "nodes/NodeDataModel.hpp"
#include "nodes/NodeData.hpp"
#include "nodes/Connection.hpp"

using QtNodes::PortType;

// local
#include "ex_checkbox_w.hpp"
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class ConditionalGateEmbeddedW : public NodeContainerW<ExCheckBoxW>{
Q_OBJECT
public:
    void initialize() override;
};


class ConditionalGateNodeDataModel : public TypedConnectorDataModel<Connector::Type::Conditional_gate, ConditionalGateEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};
}
