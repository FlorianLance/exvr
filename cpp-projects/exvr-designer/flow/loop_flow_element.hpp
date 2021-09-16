
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "data/loop.hpp"
#include "movable_flow_element.hpp"

namespace tool::ex {


class LoopFlowElement;
using LoopFlowElementUP = std::unique_ptr<LoopFlowElement>;

class LoopNodeFlowElement;
using LoopNodeFlowElementUP = std::unique_ptr<LoopNodeFlowElement>;


class LoopFlowElement : public FlowElement{


public:

    LoopFlowElement(Loop *loop);

    // element virtual
    void draw(QPainter &painter, qreal zoomLevel) override;

    // associated nodes
    LoopNodeFlowElement *startLoopNode = nullptr;
    LoopNodeFlowElement *endLoopNode   = nullptr;

    qreal squareSizeArrow = 5.;

};

class LoopNodeFlowElement : public MovableFlowElement{


public:

    LoopNodeFlowElement(LoopNode *loopNode);

    void adapt_size_from_name(QFontMetrics fontMetrics) override;

    void draw(QPainter &painter,qreal zoomLevel) override;

    // aossciated loop
    LoopFlowElement *loopElement = nullptr;

};
}
