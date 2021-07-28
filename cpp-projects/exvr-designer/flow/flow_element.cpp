
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "flow_element.hpp"


using namespace tool::ex;


void FlowElement::define_area_height(qreal height){
    areaHeight = height;
}

void FlowElement::define_stretch(qreal stretch){
    areaStretch = stretch;
}

void FlowElement::adapt_size_from_name(QFontMetrics fontMetrics){

    QRect rect = fontMetrics.boundingRect(name());
    qreal minAreaWidth = 1.2*rect.width();
    qreal maxAreaWidth = 1.7*rect.width();
    qreal areaWidth = minAreaWidth + areaStretch*(maxAreaWidth - minAreaWidth);
    uiElemRect = QRectF(QPointF(0.,0.), QSizeF(0.9*areaWidth, 0.8*areaHeight));
    uiAreaRect = QRectF(QPointF(0.,0.), QSizeF(areaWidth, areaHeight));
}

void FlowElement::compute_position(QPointF topLeft, int loopMaxDeepLevel){

    uiAreaRect = QRectF(topLeft, uiAreaRect.size());
    QPointF midRect(topLeft.x() + uiAreaRect.width()*0.5, loopMaxDeepLevel*FlowElement::areaHeight + uiAreaRect.height()*0.5);
    uiElemRect = QRectF(QPointF(midRect.x()-uiElemRect.width() * 0.5,midRect.y()-uiElemRect.height() * 0.5), uiElemRect.size());
}

void FlowElement::draw(QPainter &painter, qreal zoomLevel){
    Q_UNUSED(painter)
    Q_UNUSED(zoomLevel)    
}


FlowElement::FlowElement(Element *element) :
    key(ElementKey{element->key()}), m_name(element->name()), m_type(element->type),
    m_selected(element->is_selected()), m_insideLoopsID(element->insideLoopsID){

    colors = display::Colors::flowElements.at(m_type);
}

void FlowElement::update(Element *element){
    key             = ElementKey{element->key()};
    m_name          = element->name();
    m_type          = element->type;       
    m_selected      = element->is_selected();
    m_insideLoopsID = element->insideLoopsID;
}
