
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "component_node_data_model.hpp"

#include "widgets/connections/data_models/data/nodes_data.hpp"

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


    m_captionVisibility = true;

    nbPorts[static_cast<int>(PortType::In)]   = static_cast<unsigned int>(slotsF.size());
    nbPorts[static_cast<int>(PortType::Out)]  = static_cast<unsigned int>(signalsF.size());
    nbPorts[static_cast<int>(PortType::None)] = 0;

    inPortsInfo.resize(slotsF.size());
    for(size_t ii = 0; ii < slotsF.size(); ++ii){
        inPortsInfo[ii].caption = from_view(slotsF[ii].first.functionName)
            % QSL(" (") % from_view(ConnectionNode::get_name(slotsF[ii].first.argType)) % QSL(")");

        inPortsInfo[ii].type = generate_node_data_type(slotsF[ii].first.argType);
        inPortsInfo[ii].captionVisibility = true;
    }

    outPortsInfo.resize(signalsF.size());
    for(size_t ii = 0; ii < signalsF.size(); ++ii){
        outPortsInfo[ii].caption = from_view(signalsF[ii].first.functionName)
            % QSL(" (") % from_view(ConnectionNode::get_name(signalsF[ii].first.argType)) % QSL(")");

        outPortsInfo[ii].type = generate_node_data_type(signalsF[ii].first.argType);
        outPortsInfo[ii].captionVisibility = true;
    }
}

void ComponentNodeDataModel::update_name(QString componentName){
    m_name      = componentName % QSL("_component");
    m_caption   = componentName;
}

void ComponentNodeDataModel::setInData(std::shared_ptr<QtNodes::NodeData> nodeData, PortIndex port){

    const auto id = static_cast<size_t>(port);
    if(id < slotsF.size()){
        slotsF[id].second = nodeData;
    }
}

std::shared_ptr<QtNodes::NodeData> ComponentNodeDataModel::outData(QtNodes::PortIndex port){

    const auto id = static_cast<size_t>(port);
    if(id < signalsF.size()){
        return signalsF[id].second;
    }
    return nullptr;
}

