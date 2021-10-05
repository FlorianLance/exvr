
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"

namespace tool::ex {

class RealsToVector2NodeDataModel : public TypedConnectorDataModel<Connector::Type::Reals_to_vec2, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};
}
