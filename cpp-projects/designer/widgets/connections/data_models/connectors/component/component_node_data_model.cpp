
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "component_node_data_model.hpp"
#include "connections/data_models/data/nodes_data.hpp"

using namespace tool::ex;

ComponentNodeDataModel::ComponentNodeDataModel(int key, Component::Type componentType): BaseNodeDataModel(Type::Component){

    this->key = key;

    for(const auto &cSignal : Component::get_signals(componentType)){
        signalsF.emplace_back(std::make_pair(
            Component::Info{
                std::get<1>(cSignal),
                std::get<2>(cSignal),
                std::get<3>(cSignal),
            },
            std::make_shared<ComponentOutData>())
        );
    }

    for(const auto &cSlot : Component::get_slots(componentType)){
        std::weak_ptr<NodeData> wPtr;
        slotsF.emplace_back(std::make_pair(
            Component::Info{
                std::get<1>(cSlot),
                std::get<2>(cSlot),
                std::get<3>(cSlot),
            },
            wPtr)
        );
    }
}

void ComponentNodeDataModel::update_name(QString componentName){
    m_name      = componentName + "_component";
    m_caption   = componentName;
}

unsigned int tool::ex::ComponentNodeDataModel::nPorts(QtNodes::PortType portType) const {

    switch (portType){
    case PortType::In:
        return static_cast<unsigned int>(slotsF.size());
    case PortType::Out:
        return static_cast<unsigned int>(signalsF.size());
    case PortType::None:
        break;
    }
    return 0;
}

QtNodes::NodeDataType tool::ex::ComponentNodeDataModel::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const {

    auto id = static_cast<size_t>(portIndex);
    if(portType == PortType::In){
        return generate_node_data_type(slotsF[id].first.argType);
    }else if(portType == PortType::Out){        
        return generate_node_data_type(signalsF[id].first.argType);
    }

    return NodeDataType();
}

QString ComponentNodeDataModel::portCaption(PortType t, PortIndex i ) const{

    auto id = static_cast<size_t>(i);
    if(t == PortType::In){
        if(id < slotsF.size()){
            return from_view(slotsF[id].first.functionName) % QSL(" (") + from_view(ConnectionNode::get_name(slotsF[id].first.argType)) % QSL(")");
        }
    }else if(t == PortType::Out){
        if(id < signalsF.size()){
            return from_view(signalsF[id].first.functionName) % QSL(" (") + from_view(ConnectionNode::get_name(signalsF[id].first.argType)) % QSL(")");
        }
    }
    return "";
}

void ComponentNodeDataModel::setInData(std::shared_ptr<QtNodes::NodeData> nodeData, PortIndex port){

    auto id = static_cast<size_t>(port);
    if(id < slotsF.size()){
        slotsF[id].second = nodeData;
    }
}

std::shared_ptr<QtNodes::NodeData> ComponentNodeDataModel::outData(QtNodes::PortIndex port){

    auto id = static_cast<size_t>(port);
    if(id < signalsF.size()){
        return signalsF[id].second;
    }
    return nullptr;
}

