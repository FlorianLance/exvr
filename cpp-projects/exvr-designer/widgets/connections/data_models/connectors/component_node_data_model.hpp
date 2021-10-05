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

    // data
    std::shared_ptr<NodeData> outData(PortIndex port) override;
    void setInData(std::shared_ptr<NodeData>, PortIndex) override;

    // name
    void update_name(QString componentName);


    // widget
    QWidget * embeddedWidget() override { return nullptr; }

public:

    // inputData
    std_v1<std::pair<Component::Info, std::weak_ptr<NodeData>>> slotsF;
    // outputData
    std_v1<std::pair<Component::Info, std::shared_ptr<ComponentOutData>>> signalsF;

};
}
