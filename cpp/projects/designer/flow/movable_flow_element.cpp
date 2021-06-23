
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "movable_flow_element.hpp"

using namespace tool::ex;

MovableFlowElement::MovableFlowElement(Element *element) : FlowElement (element){
    removeElement    = std::make_unique<RemoveFlowElement>();
    moveLeftElement  = std::make_unique<MoveFlowElement>(true);
    moveRightElement = std::make_unique<MoveFlowElement>(false);
}

void MovableFlowElement::adapt_size_from_name(QFontMetrics fontMetrics){

    FlowElement::adapt_size_from_name(fontMetrics);
    removeElement->adapt_size_from_name(fontMetrics);
    if(canMoveToLeft){
        moveLeftElement->adapt_size_from_name(fontMetrics);
    }
    if(canMoveToRight){
        moveRightElement->adapt_size_from_name(fontMetrics);
    }
}

void MovableFlowElement::compute_position(QPointF topLeft, int loopMaxDeepLevel){

    FlowElement::compute_position(topLeft, loopMaxDeepLevel);
    qreal offset = type() == Element::Type::LoopEnd ? 0.8*areaHeight : 0.;
    qreal heightButtons = uiAreaRect.size().height() / 1.5;
    QSizeF removeSize(removeElement->uiElemRect.width()*0.8, heightButtons);
    removeElement->uiElemRect = QRectF(uiElemRect.center()      + QPointF(-removeSize.width()*0.5, 0.8*areaHeight + 1.2*removeSize.height() + offset),removeSize);

    QSizeF leftSize(moveLeftElement->uiElemRect.width()*0.8, heightButtons);
    moveLeftElement->uiElemRect = QRectF(uiElemRect.center()    + QPointF(-leftSize.width()*1.2, 0.8*areaHeight + offset), leftSize);

    QSizeF rightSize(moveRightElement->uiElemRect.width()*0.8, heightButtons);
    moveRightElement->uiElemRect = QRectF(uiElemRect.center()   + QPointF(0.2*rightSize.width(), 0.8*areaHeight + offset), rightSize);
}

void MovableFlowElement::draw(QPainter &painter, qreal zoomLevel){

    if(!is_selected()){
        return;
    }

    QPen linePen;
    linePen.setWidthF(zoomLevel*1.1);        

    linePen.setColor(display::Colors::flowElements.at(Element::Type::Node).selectedLineBoxColor);
    painter.setPen(linePen);
    painter.drawLine(uiElemRect.center(), removeElement->uiElemRect.center());

    removeElement->draw(painter,zoomLevel);
    if(canMoveToLeft){
        painter.setPen(linePen);
        painter.drawLine(uiElemRect.center(), moveLeftElement->uiElemRect.center());
        moveLeftElement->draw(painter,zoomLevel);
    }
    if(canMoveToRight){
        painter.setPen(linePen);
        painter.drawLine(uiElemRect.center(), moveRightElement->uiElemRect.center());
        moveRightElement->draw(painter,zoomLevel);
    }
}
