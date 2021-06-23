
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "move_flow_element.hpp"

using namespace tool::ex;


MoveFlowElement::MoveFlowElement(bool left)  : isLeft(left), move(std::make_unique<Element>(Element::Type::MoveElement, "move")) {

    m_name          = move->name();
    m_type          = move->type;
    key             = ElementKey{move->key()};
    m_selected      = move->is_selected();
    m_insideLoopsID = move->insideLoopsID;
    colors = display::Colors::flowElements.at(m_type);
}

void MoveFlowElement::draw(QPainter &painter, qreal zoomLevel){

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
    painter.drawText(uiElemRect,  Qt::AlignCenter, isLeft ? "<" : ">");
}
