
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "isi_flow_element.hpp"


using namespace tool::ex;

IsiFlowElement::IsiFlowElement(Isi *isi) : MovableFlowElement(isi){
}

void IsiFlowElement::adapt_size_from_name(QFontMetrics fontMetrics){
    MovableFlowElement::adapt_size_from_name(fontMetrics);
}

void IsiFlowElement::compute_position(QPointF topLeft, int loopMaxDeepLevel){
    MovableFlowElement::compute_position(topLeft, loopMaxDeepLevel);
}

void IsiFlowElement::draw(QPainter &painter, qreal zoomLevel){

    MovableFlowElement::draw(painter, zoomLevel);

    // draw rectangle
    QPen pen;
    pen.setWidthF(zoomLevel*1.2);
    pen.setColor(is_selected() ? colors.selectedLineBoxColor : colors.unselectedLineBoxColor);
    painter.setPen(pen);
    painter.setBrush(is_selected() ? colors.selectedFillBoxColor : colors.unselectedFillBoxColor);
    painter.drawRoundedRect(uiElemRect, zoomLevel*4.,zoomLevel*4., Qt::AbsoluteSize);

    // draw name
    pen.setColor(is_selected() ? colors.selectedTextColor : colors.unselectedTextColor);    
    painter.setPen(pen);
    painter.drawText(uiElemRect,  Qt::AlignCenter, m_name);
}

