
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QSpinBox>
#include <QComboBox>
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>

// nodes
#include "nodes/NodeDataModel.hpp"
#include "nodes/NodeData.hpp"
using QtNodes::PortType;

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class DecimalCounterConfigNodeDataModel : public TypedConnectorDataModel<Connector::Type::Decimal_counter, PlaceHolderEmbeddedW>{

Q_OBJECT

public slots:

void compute() override;
public:
    virtual QString portCaption(PortType, PortIndex) const override;
};
}


