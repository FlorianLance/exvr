
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "node_flow_element.hpp"


using namespace tool::ex;

NodeFlowElement::NodeFlowElement(NodeFlow *node) : FlowElement(node){

    addRoutine = std::make_unique<AddFlowElement>(Element::Type::Routine);
    addIsi     = std::make_unique<AddFlowElement>(Element::Type::Isi);
    addLoop    = std::make_unique<AddFlowElement>(Element::Type::Loop);
}


void NodeFlowElement::adapt_size_from_name(QFontMetrics fontMetrics){

    QRect rect = fontMetrics.boundingRect(name());
    qreal minAreaWidth = 0.4*rect.width();
    qreal maxAreaWidth = 0.8*rect.width();
    qreal areaWidth = minAreaWidth + areaStretch*(maxAreaWidth - minAreaWidth);

    qreal min = std::min(0.6*areaWidth, 0.8*areaHeight);
    uiElemRect = QRectF(QPointF(0.,0.), QSizeF(min, min));
    uiAreaRect = QRectF(QPointF(0.,0.), QSizeF(areaWidth, areaHeight));
}

void NodeFlowElement::draw(QPainter &painter, qreal zoomLevel){

    // draw ellipse
    QPen pen;
    pen.setWidthF(zoomLevel*1.1);
    pen.setColor(is_selected() ? colors.selectedLineBoxColor : colors.unselectedLineBoxColor);
    painter.setPen(pen);
    painter.setBrush(is_selected() ? colors.selectedFillBoxColor : colors.unselectedFillBoxColor);
    painter.drawEllipse(uiElemRect);

    if(is_selected()){
        draw_add_buttons(painter,zoomLevel);
    }
}

void NodeFlowElement::compute_position(QPointF topLeft, int loopMaxDeepLevel){

    FlowElement::compute_position(topLeft, loopMaxDeepLevel);
    qreal heightButtons = uiAreaRect.size().height() / 2.;
    qreal heightOffset  = heightButtons/2.;
    qreal widthButton = uiAreaRect.size().width()*2.75;
    qreal posXButtons = uiElemRect.center().x()-0.5*widthButton;
    addRoutine->uiElemRect = QRectF(QPointF(posXButtons, uiAreaRect.y() + areaHeight + heightOffset), QSizeF(widthButton, heightButtons));
    addLoop->uiElemRect    = QRectF(QPointF(posXButtons, uiAreaRect.y() + areaHeight + heightButtons + 2*heightOffset), QSizeF(widthButton, heightButtons));
    addIsi->uiElemRect     = QRectF(QPointF(posXButtons, uiAreaRect.y() + areaHeight + 2*heightButtons + 3*heightOffset), QSizeF(widthButton, heightButtons));
}

void NodeFlowElement::draw_add_buttons(QPainter &painter, qreal zoomLevel){

    QPen pen;
    pen.setColor(display::Colors::flowElements.at(Element::Type::Node).selectedLineBoxColor);
    pen.setWidthF(zoomLevel*1.1);
    painter.setPen(pen);

    QLineF line(addIsi->uiElemRect.center(), QPointF(uiElemRect.center().x(),  uiElemRect.bottom()));
    painter.drawLine(line);

    pen.setColor(display::Colors::flowElements.at(Element::Type::Routine).selectedLineBoxColor);
    painter.setPen(pen);
    painter.setBrush(display::Colors::flowElements.at(Element::Type::Routine).selectedFillBoxColor);
    painter.drawRoundedRect(addRoutine->uiElemRect, zoomLevel*4.,zoomLevel*4., Qt::AbsoluteSize);

    pen.setColor(display::Colors::flowElements.at(Element::Type::Loop).selectedLineBoxColor);
    painter.setPen(pen);
    painter.setBrush(display::Colors::flowElements.at(Element::Type::Loop).selectedFillBoxColor);
    painter.drawRoundedRect(addLoop->uiElemRect, zoomLevel*4.,zoomLevel*4., Qt::AbsoluteSize);

    pen.setColor(display::Colors::flowElements.at(Element::Type::Isi).selectedLineBoxColor);
    painter.setPen(pen);
    painter.setBrush(display::Colors::flowElements.at(Element::Type::Isi).selectedFillBoxColor);
    painter.drawRoundedRect(addIsi->uiElemRect, zoomLevel*4.,zoomLevel*4., Qt::AbsoluteSize);

    pen.setColor(display::Colors::flowElements.at(Element::Type::Routine).selectedTextColor);
    painter.setPen(pen);
    painter.drawText(addRoutine->uiElemRect,    Qt::AlignCenter, "routine");

    pen.setColor(display::Colors::flowElements.at(Element::Type::Loop).selectedTextColor);
    painter.setPen(pen);
    painter.drawText(addLoop->uiElemRect,       Qt::AlignCenter, "loop");

    pen.setColor(display::Colors::flowElements.at(Element::Type::Isi).selectedTextColor);
    painter.setPen(pen);
    painter.drawText(addIsi->uiElemRect,        Qt::AlignCenter, "ISI");
}
