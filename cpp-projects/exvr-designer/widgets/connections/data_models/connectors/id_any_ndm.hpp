
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
#include "ex_widgets/ex_spin_box_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class IdAnyEmbeddedW : public NodeContainerW<ExSpinBoxW>{
Q_OBJECT
public:
    void initialize() override;
};

class IdAnyNodeDataModel : public TypedConnectorDataModel<Connector::Type::Id_any, IdAnyEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
    QString portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const override;
};
}
