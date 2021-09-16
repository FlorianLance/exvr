
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

class StringAnyEmbeddedW : public NodeContainerW<ExLineEditW>{
Q_OBJECT
public:
    void initialize() override;
};

class StringAnyNodeDataModel : public TypedConnectorDataModel<Connector::Type::String_any, StringAnyEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
    QString portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const override;
};
}
