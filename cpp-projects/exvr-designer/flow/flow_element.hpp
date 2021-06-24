
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <memory>

// Qt
#include <QPainter>
#include <QFontMetrics>
#include <QGraphicsObject>

// local
#include "element.hpp"
#include "settings/display.hpp"

namespace tool::ex {

class FlowElement;
using FlowElementUP = std::unique_ptr<FlowElement>;


class FlowElement : public QObject{


public:

    FlowElement() = default;
    FlowElement(FlowElement&&) = delete;
    FlowElement& operator=(FlowElement&&) = delete;
    FlowElement(const FlowElement&) = delete;
    FlowElement& operator=(const FlowElement&) = delete;
    FlowElement(Element *element);

    virtual void update(Element *element);

    static void define_area_height(qreal height);
    static void define_stretch(qreal stretch);

    virtual void adapt_size_from_name(QFontMetrics fontMetrics);
    virtual void compute_position(QPointF topLeft, int loopMaxDeepLevel);

    virtual void draw(QPainter &painter, qreal zoomLevel);

    inline QString name() const noexcept{return m_name;}
    inline bool is_selected() const noexcept{return m_selected;}
    inline Element::Type type() const noexcept{return m_type;}

    // ui       
    static inline qreal areaHeight = 0.;
    static inline qreal areaStretch = 0.75;
    static inline qreal sizeTxt = 3.;
    QRectF uiAreaRect = QRectF(0., 0., 0., 0.); /**< area rectangle in the display view */
    QRectF uiElemRect = QRectF(0., 0., 0., 0.); /**< rectangle of the element in the display view */
    display::Colors::FlowElement colors;

    ElementKey key;

protected:

    QString m_name;
    Element::Type m_type;
    bool m_selected;
    std_v1<int> m_insideLoopsID;

};

}
