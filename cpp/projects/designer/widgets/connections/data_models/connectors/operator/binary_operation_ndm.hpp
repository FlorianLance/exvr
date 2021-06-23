
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
#include "ex_combo_box_text_w.hpp"
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class BinaryOperationEmbeddedW  : public NodeContainerW<ExComboBoxTextW>{
Q_OBJECT
public:
    void initialize() override;
};

class BinaryOperationNodeDataModel : public TypedConnectorDataModel<Connector::Type::Binary_operation, BinaryOperationEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
    QString caption() const override;
};
}
