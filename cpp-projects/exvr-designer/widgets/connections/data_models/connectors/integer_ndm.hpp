
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_spin_box_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class IntegerEmbeddedW : public NodeContainerW<ExSpinBoxW>{
Q_OBJECT
public:
    void initialize() override;
};

class IntegerNodeDataModel : public TypedConnectorDataModel<Connector::Type::Integer, IntegerEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};
}

