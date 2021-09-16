
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#pragma once

// Qt
#include <QLabel>

// nodes
#include "nodes/NodeDataModel.hpp"
#include "nodes/NodeData.hpp"
using QtNodes::PortType;

// qt-utility
#include "ex_widgets/ex_label_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {


class StartRoutineNodeDataModel : public TypedConnectorDataModel<Connector::Type::Start_routine, PlaceHolderEmbeddedW>{

Q_OBJECT
public slots:

void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class StopRoutineNodeDataModel : public TypedConnectorDataModel<Connector::Type::Stop_routine, PlaceHolderEmbeddedW>{

Q_OBJECT
public slots:

void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class PreUpdateRoutineNodeDataModel : public TypedConnectorDataModel<Connector::Type::Pre_update_routine, PlaceHolderEmbeddedW>{

Q_OBJECT
public slots:

void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class PostUpdateRoutineNodeDataModel : public TypedConnectorDataModel<Connector::Type::Post_update_routine, PlaceHolderEmbeddedW>{

Q_OBJECT
public slots:

void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};


class UpdateRoutineNodeDataModel : public TypedConnectorDataModel<Connector::Type::Update_routine, PlaceHolderEmbeddedW>{

Q_OBJECT
public slots:

void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};





}


