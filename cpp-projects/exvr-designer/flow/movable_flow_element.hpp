
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "remove_flow_element.hpp"
#include "move_flow_element.hpp"

namespace tool::ex {

struct MovableFlowElement : public FlowElement{

    MovableFlowElement(Element *element);

    void adapt_size_from_name(QFontMetrics fontMetrics) override;

    void compute_position(QPointF topLeft, int loopMaxDeepLevel) override;

    void draw(QPainter &painter, qreal zoomLevel) override;

    bool canMoveToLeft = true;
    bool canMoveToRight= true;

    RemoveFlowElementUP removeElement   = nullptr;
    MoveFlowElementUP moveLeftElement   = nullptr;
    MoveFlowElementUP moveRightElement  = nullptr;
};
}
