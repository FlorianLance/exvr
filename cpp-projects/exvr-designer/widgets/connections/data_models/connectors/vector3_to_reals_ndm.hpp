
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"

namespace tool::ex {

class Vector3ToRealsNodeDataModel : public TypedConnectorDataModel<Connector::Type::Vec3_to_reals, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};
}
