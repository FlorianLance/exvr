
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_vector3d_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"

namespace tool::ex {

class Vector3EmbeddedW : public NodeContainerW<ExVector3dW>{
Q_OBJECT
public:
    void initialize() override;
};

class Vector3NodeDataModel : public TypedConnectorDataModel<Connector::Type::Vector3, Vector3EmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};
}

