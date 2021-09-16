
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "flow_element.hpp"

namespace tool::ex{

class AddFlowElement;
using AddFlowElementUP = std::unique_ptr<AddFlowElement>;

class AddFlowElement : public FlowElement{

public:

    AddFlowElement(Element::Type typeToAdd);

    Element::Type typeToAdd;

private:
    ElementUP add = nullptr;
};

}
