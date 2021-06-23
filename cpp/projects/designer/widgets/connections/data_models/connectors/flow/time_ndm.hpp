
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "ex_time_source_w.hpp"
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class TimeEmbeddedW  : public NodeContainerW<ExTimeW>{
Q_OBJECT
public:
    void initialize() override;
    bool set_text_value(QStringView value) override;
};

class TimeNodeDataModel : public TypedConnectorDataModel<Connector::Type::Time, TimeEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString caption() const override;
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;

};

}

