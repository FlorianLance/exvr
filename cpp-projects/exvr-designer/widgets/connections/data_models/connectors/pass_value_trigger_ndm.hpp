
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDebug>

// nodes
#include "nodes/NodeDataModel.hpp"
#include "nodes/NodeData.hpp"
using QtNodes::PortType;

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"


namespace tool::ex {

class PassValueTriggerNodeDataModel : public TypedConnectorDataModel<Connector::Type::Pass_value_trigger, PlaceHolderEmbeddedW>{

Q_OBJECT

public slots:

    void compute() override;
public:

    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};
}

