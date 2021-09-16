/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// nodes
#include "nodes/NodeData.hpp"
#include "nodes/NodeDataModel.hpp"
#include "nodes/Connection.hpp"
#include "nodes/FlowScene.hpp"
#include "nodes/FlowView.hpp"
#include "nodes/DataModelRegistry.hpp"
#include "nodes/ConnectionStyle.hpp"

// local
#include "widgets/connections/data_models/base_node_data_model.hpp"
#include "data/component.hpp"
#include "data/action.hpp"


using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;

namespace tool::ex{

class ComponentNodeDataModel : public BaseNodeDataModel {

Q_OBJECT

public:

    ComponentNodeDataModel(int key, Component::Type componentType);

    // caption
    bool captionVisible() const override {
        return true;
    }
    virtual bool portCaptionVisible(PortType, PortIndex) const override {
        return true;
    }
    virtual QString portCaption(PortType, PortIndex) const override;


    void update_name(QString componentName);


    // ports
    unsigned int nPorts(PortType portType) const override;

    // data
    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
    std::shared_ptr<NodeData> outData(PortIndex port) override;
    void setInData(std::shared_ptr<NodeData>, PortIndex) override;

    std_v1<std::pair<Component::Info, std::shared_ptr<ComponentOutData>>> signalsF; // outputData
    std_v1<std::pair<Component::Info, std::weak_ptr<NodeData>>> slotsF; // inputData


    QWidget * embeddedWidget() override { return nullptr; }

    QString caption() const override {
        return m_caption;
    }

    QString name() const override {
        return m_name;
    }

protected:

    QString m_caption;
    QString m_name;
};
}
