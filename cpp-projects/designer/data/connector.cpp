
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "connector.hpp"

// Qt
#include <QDebug>

using namespace tool::ex;

ConnectorUP Connector::copy_with_new_element_id(const Connector &connectorToCopy){
    ConnectorUP connector = std::make_unique<Connector>(
        ConnectorKey{-1}, connectorToCopy.type, connectorToCopy.name, connectorToCopy.pos, connectorToCopy.arg
    );
    connector->inputValidity = connectorToCopy.inputValidity;
    return connector;
}
