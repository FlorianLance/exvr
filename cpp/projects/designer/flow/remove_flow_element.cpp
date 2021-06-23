

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "remove_flow_element.hpp"

using namespace tool::ex;

RemoveFlowElement::RemoveFlowElement() : remove(std::make_unique<Element>(Element::Type::RemoveElement, "remove")) {
    m_name    = remove->name();
    m_type    = remove->type;
    key       = ElementKey{remove->key()};
    m_selected = remove->is_selected();
    m_insideLoopsID = remove->insideLoopsID;
    colors = display::Colors::flowElements.at(m_type);
}

void RemoveFlowElement::draw(QPainter &painter, qreal zoomLevel){

    // draw rectangle
    QPen pen;
    pen.setWidthF(zoomLevel*1.1);
    pen.setColor(colors.selectedLineBoxColor);
    painter.setPen(pen);
    painter.setBrush(colors.selectedFillBoxColor);
    painter.drawRoundedRect(uiElemRect, zoomLevel*4.,zoomLevel*4., Qt::AbsoluteSize);

    // draw name
    pen.setColor(colors.selectedTextColor);
    painter.setPen(pen);
    painter.drawText(uiElemRect,  Qt::AlignCenter, "X");
}
