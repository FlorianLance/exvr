
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <utility>

// nodes
#include "nodes/DataModelRegistry.hpp"
#include "nodes/TypeConverter.hpp"
using QtNodes::DataModelRegistry;

// base
#include "utility/vector_utility.hpp"

// local
#include "connector.hpp"
#include "connectors/connector_node_data_model.hpp"
#include "connectors/component/component_node_data_model.hpp"

namespace tool::ex {

class DataNodeModels{
public:

    // init styles
    static inline QString FlowViewStyleStr = "";
    static inline QString ConnectionStyleStr = "";
    static inline QString NodeStyleStr = "";

    static inline QtNodes::NodeStyle generatorStyle;
    static inline QtNodes::NodeStyle convertorStyle;
    static inline QtNodes::NodeStyle functionStyle;
    static inline QtNodes::NodeStyle componentStyle;
    static inline QtNodes::NodeStyle operatorStyle;
    static inline QtNodes::NodeStyle actionStyle;
    static inline QtNodes::NodeStyle displayStyle;
    static inline QtNodes::NodeStyle eventStyle;
    static inline QtNodes::NodeStyle flowStyle;
    static inline QtNodes::NodeStyle linkStyle;

    static void initialize();

    template<Connector::Category C>


    static std_v1<std::pair<QString,QString>> get_connectors(){

        const auto& types = Connector::types_with_category<C>();
        std_v1<std::pair<QString, QString>> connectors;
        for (const auto &type : types) {
            connectors.emplace_back(std::make_pair(from_view(Connector::get_name(type)),from_view(Connector::get_caption(type))));
        }
        return connectors;
    }

    static std::unique_ptr<ConnectorNodeDataModel> generate_connector_data_model(Connector *connector);
    static std::unique_ptr<ComponentNodeDataModel> generate_component_data_model(Component *component);
    static inline std::shared_ptr<DataModelRegistry> registry = nullptr;
};

}
