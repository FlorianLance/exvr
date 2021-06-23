
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

// local
#include "ex_label_w.hpp"
#include "ex_line_edit_w.hpp"
#include "ex_config_w.hpp"
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class NextNodeDataModel : public TypedConnectorDataModel<Connector::Type::Next, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class PreviousNodeDataModel : public TypedConnectorDataModel<Connector::Type::Previous, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class StopNodeDataModel : public TypedConnectorDataModel<Connector::Type::Stop, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class PauseNodeDataModel : public TypedConnectorDataModel<Connector::Type::Pause, PlaceHolderEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class NextWithNameEmbeddedW : public NodeContainerW<ExLineEditW>{
Q_OBJECT
public:
    void initialize() override;
};
class NextWithNameNodeDataModel : public TypedConnectorDataModel<Connector::Type::Next_with_name, NextWithNameEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class PreviousWithNameEmbeddedW : public NodeContainerW<ExLineEditW>{
Q_OBJECT
public:
    void initialize() override;
};
class PreviousWithNameNodeDataModel : public TypedConnectorDataModel<Connector::Type::Previous_with_name, PreviousWithNameEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class NextWithCondEmbeddedW : public NodeContainerW<ExLineEditW>{
Q_OBJECT
public:
    void initialize() override;
};
class NextWithCondNodeDataModel : public TypedConnectorDataModel<Connector::Type::Next_with_cond, NextWithCondEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;    
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class PreviousWithCondEmbeddedW : public NodeContainerW<ExLineEditW>{
Q_OBJECT
public:
    void initialize() override;
};
class PreviousWithCondNodeDataModel : public TypedConnectorDataModel<Connector::Type::Previous_with_cond, PreviousWithCondEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class ForceComponentConfigW  : public NodeContainerW<ExConfigW>{
    Q_OBJECT
public:
    void initialize() override;
};

class ForceComponentConfigNodeDataModel : public TypedConnectorDataModel<Connector::Type::Force_component_config, ForceComponentConfigW>{
    Q_OBJECT
public slots:
    void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

}


