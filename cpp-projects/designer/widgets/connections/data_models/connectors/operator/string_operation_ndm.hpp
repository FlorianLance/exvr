
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
#include "ex_combo_box_text_w.hpp"
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"


namespace tool::ex {

class StringOperationEmbeddedW : public NodeContainerW<ExComboBoxTextW>{
Q_OBJECT
public:
    void initialize() override;
};


class StringOperationNodeDataModel : public TypedConnectorDataModel<Connector::Type::String_operation, StringOperationEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
    QString caption() const override;
    NodeDataType dataType(PortType t, PortIndex i) const override;
    unsigned int nPorts(PortType portType) const override;
};
}


