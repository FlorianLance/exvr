
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "movable_flow_element.hpp"
#include "routine.hpp"

namespace tool::ex {

class RoutineFlowElement;
using RoutineFlowElementUP = std::unique_ptr<RoutineFlowElement>;

class RoutineFlowElement : public MovableFlowElement{


public:

    RoutineFlowElement(Routine *routine);
    void adapt_size_from_name(QFontMetrics fontMetrics) override;
    void compute_position(QPointF topLeft, int loopMaxDeepLevel) override;
    void draw(QPainter &painter, qreal zoomLevel) override;
    void update(Element *element) override;
private:

    bool isARandomizer;
};
}
