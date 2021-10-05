
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_line_edit_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"

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
public:
    void init_ports_caption() override;
};
}
