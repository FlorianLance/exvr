
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// nodes
#include "nodes/NodeDataModel.hpp"
#include "nodes/Connection.hpp"
using QtNodes::NodeValidationState;

// qt-utility
#include "ex_widgets/ex_checkbox_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"


namespace tool::ex {

class BooleanEmbeddedW : public NodeContainerW<ExCheckBoxW>{
Q_OBJECT
public:
    void initialize() override;
};


class BooleanNodeDataModel : public TypedConnectorDataModel<Connector::Type::Boolean, BooleanEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
    void setInData(std::shared_ptr<QtNodes::NodeData> nodeData, PortIndex port) override;
    void inputConnectionCreated(const QtNodes::Connection &c) override;
    void inputConnectionDeleted(const QtNodes::Connection &c) override;
public:
    void init_ports_caption() override;
};
}
