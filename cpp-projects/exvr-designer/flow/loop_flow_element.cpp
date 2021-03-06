
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "loop_flow_element.hpp"

// Qt
#include <QFile>
#include <QTextStream>


using namespace tool::ex;

LoopFlowElement::LoopFlowElement(Loop *loop) : FlowElement(loop){
    squareSizeArrow = 5.;
}

void LoopFlowElement::draw(QPainter &painter, qreal zoomLevel){

    size_t level = m_insideLoopsID.size()+1;
    QSizeF sizeArrow(squareSizeArrow*zoomLevel, squareSizeArrow*zoomLevel);

    QPen linePen;

    linePen.setColor(is_selected() ? colors.selectedLineBoxColor : colors.unselectedLineBoxColor);
    linePen.setWidthF(zoomLevel * 1.);

    QPen boxPen;
    boxPen.setWidthF(zoomLevel*1.1);
    boxPen.setColor(is_selected() ? colors.selectedLineBoxColor : colors.unselectedLineBoxColor);

    QPointF right    = endLoopNode->uiElemRect.center() - QPointF(0., endLoopNode->uiElemRect.height()*0.5);
    QPointF topRight = QPointF(endLoopNode->uiElemRect.center().x(),  (level)*FlowElement::areaHeight);
    QPointF topLeft  = QPointF(startLoopNode->uiElemRect.center().x(), (level)*FlowElement::areaHeight);
    QPointF left     = startLoopNode->uiElemRect.center() - QPointF(0., sizeArrow.height() + startLoopNode->uiElemRect.height()*0.5);
    QPointF topMiddle= (topLeft + topRight)*0.5;

    QPolygonF loopLine({right, topRight, topLeft, left});

    linePen.setStyle(Qt::DashLine);
    painter.setPen(linePen);
    painter.drawPolyline(loopLine);

    QPolygonF arrow;
    arrow << left - QPointF(sizeArrow.width()*0.5,0.);
    arrow << left + QPointF(0., sizeArrow.height());
    arrow << left + QPointF(sizeArrow.width()*0.5,0.);
    arrow << left - QPointF(sizeArrow.width()*0.5,0.);

    linePen.setStyle(Qt::SolidLine);
    painter.setPen(linePen);
    painter.drawPolyline(arrow);

    QPainterPath path;
    path.addPolygon(arrow);
    uiElemRect = QRectF(QPointF(topMiddle.x() - uiElemRect.width()*0.5, topMiddle.y() - uiElemRect.height()*0.5),
                        uiElemRect.size());

    // draw rectangle
    painter.setPen(boxPen);
    painter.setBrush(is_selected() ? colors.selectedFillBoxColor : colors.unselectedFillBoxColor);
    painter.drawRoundedRect(uiElemRect, zoomLevel*2.,zoomLevel*2., Qt::AbsoluteSize);

    // draw name
    QPen textPen;
    textPen.setWidthF(zoomLevel*1.1);
    textPen.setColor(is_selected() ?  colors.selectedTextColor : colors.unselectedTextColor);
    painter.setPen(textPen);
    painter.drawText(uiElemRect,     Qt::AlignCenter, name());
}

LoopNodeFlowElement::LoopNodeFlowElement(LoopNode *loopNode) : MovableFlowElement(loopNode){
}

void LoopNodeFlowElement::adapt_size_from_name(QFontMetrics fontMetrics){

    MovableFlowElement::adapt_size_from_name(fontMetrics);

    const QRect rect = fontMetrics.boundingRect("LOOP");
    const qreal minAreaWidth = 0.4*rect.width();
    const qreal maxAreaWidth = 0.8*rect.width();
    const qreal areaWidth = minAreaWidth + areaStretch*(maxAreaWidth - minAreaWidth);

    const qreal min = std::min(0.6*areaWidth, 0.8*areaHeight);
    uiElemRect = QRectF(QPointF(0.,0.), QSizeF(min, min));
    uiAreaRect = QRectF(QPointF(0.,0.), QSizeF(areaWidth, areaHeight));
}

void LoopNodeFlowElement::draw(QPainter &painter, qreal zoomLevel){

    MovableFlowElement::draw(painter, zoomLevel);

    // draw rectangle
    QPen pen;
    pen.setWidthF(zoomLevel*1.1);
    pen.setColor(is_selected() ? colors.selectedLineBoxColor : colors.unselectedLineBoxColor);

    painter.setPen(pen);
    painter.setBrush(is_selected() ? colors.selectedFillBoxColor : colors.unselectedFillBoxColor);
    painter.drawRect(uiElemRect);
}

