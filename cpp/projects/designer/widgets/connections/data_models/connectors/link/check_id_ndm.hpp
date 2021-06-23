
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// nodes
#include "nodes/NodeDataModel.hpp"
using QtNodes::NodeValidationState;

// local
#include "ex_spin_box_w.hpp"
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"


namespace tool::ex {

class CheckIdEmbeddedW : public NodeContainerW<ExSpinBoxW>{
    Q_OBJECT
public:
    void initialize() override;
};

class CheckIdNodeDataModel : public TypedConnectorDataModel<Connector::Type::Check_id, CheckIdEmbeddedW>{
    Q_OBJECT
public slots:
    void compute() override;

public:
    QString portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const override;
};
}
