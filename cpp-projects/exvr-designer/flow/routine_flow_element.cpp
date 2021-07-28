
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "routine_flow_element.hpp"


using namespace tool::ex;

RoutineFlowElement::RoutineFlowElement(Routine *routine) : MovableFlowElement(routine){
    isARandomizer = routine->isARandomizer;
}

void RoutineFlowElement::adapt_size_from_name(QFontMetrics fontMetrics){
    MovableFlowElement::adapt_size_from_name(fontMetrics);
}

void RoutineFlowElement::compute_position(QPointF topLeft, int loopMaxDeepLevel){
    MovableFlowElement::compute_position(topLeft, loopMaxDeepLevel);
}


void RoutineFlowElement::draw(QPainter &painter, qreal zoomLevel){

    MovableFlowElement::draw(painter, zoomLevel);

    // draw rectangle
    QPen pen;
    pen.setWidthF(zoomLevel*1.1);
    pen.setColor(is_selected() ? colors.selectedLineBoxColor : colors.unselectedLineBoxColor);
    if(!isARandomizer){
        pen.setColor(is_selected() ? colors.selectedLineBoxColor : colors.unselectedLineBoxColor);
    }else{
        pen.setColor(is_selected() ? QColor(140,165,206) : colors.unselectedLineBoxColor);
    }

    painter.setPen(pen);

    if(!isARandomizer){
        painter.setBrush(is_selected() ? colors.selectedFillBoxColor : colors.unselectedFillBoxColor);
    }else{
        painter.setBrush(QColor(140,165,206));
    }
    painter.drawRoundedRect(uiElemRect, zoomLevel*4.,zoomLevel*4., Qt::AbsoluteSize);

    // draw name
    pen.setColor(is_selected() ? colors.selectedTextColor : colors.unselectedTextColor);
    painter.setPen(pen);
    painter.drawText(uiElemRect,  Qt::AlignCenter, m_name);
}

void RoutineFlowElement::update(Element *element){
    FlowElement::update(element);
    isARandomizer = dynamic_cast<Routine*>(element)->isARandomizer;
}
