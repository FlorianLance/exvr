

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "add_flow_element.hpp"

using namespace tool::ex;

AddFlowElement::AddFlowElement(Element::Type typeToAdd) : add(std::make_unique<Element>(Element::Type::AddElement, "add")){

    this->typeToAdd = typeToAdd;
    m_name      = add->name();
    m_type      = add->type;
    key         = ElementKey{add->key()};
    m_selected  = add->is_selected();
    m_insideLoopsID = add->insideLoopsID;
    colors = display::Colors::flowElements.at(m_type);
}
