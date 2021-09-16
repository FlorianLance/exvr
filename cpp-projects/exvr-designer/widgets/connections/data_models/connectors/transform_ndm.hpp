
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_transformation_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class TransformEmbeddedW : public NodeContainerW<ExTransformationW>{
    Q_OBJECT
public:
    void initialize() override;
};


class TransformNodeDataModel : public TypedConnectorDataModel<Connector::Type::Transform, TransformEmbeddedW>{
    Q_OBJECT
public slots:
    void compute() override;
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};
}

