
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "element.hpp"

namespace tool::ex {

    struct NodeFlow;
    using NodeFlowUP = std::unique_ptr<NodeFlow>;

    /**
     * @brief Non-data element used only with by the flow but still take place in experiment
     */
    struct NodeFlow : public Element{

        NodeFlow() : Element(Type::Node, "node"){
        }
    };


}
