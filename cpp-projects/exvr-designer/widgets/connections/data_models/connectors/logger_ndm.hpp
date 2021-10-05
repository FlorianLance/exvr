
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"

namespace tool::ex {

class LoggerNodeDataModel : public TypedConnectorDataModel<Connector::Type::Logger, PlaceHolderEmbeddedW>{
public:
    void init_ports_caption() override;
};
}


