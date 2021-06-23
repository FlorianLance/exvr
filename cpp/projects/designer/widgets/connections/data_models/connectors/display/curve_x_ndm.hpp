
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
#include "ex_curve_x_w.hpp"
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class CurveXEmbeddedW : public NodeContainerW<ExCurveXW>{
Q_OBJECT
public:
    void initialize() override;
    bool update_with_info(QStringView value) override;

    QString curveTitle = QSL("Default curve");
};

class CurveXNodeDataModel : public TypedConnectorDataModel<Connector::Type::Curve_x, CurveXEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};
}


