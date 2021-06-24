
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QVector>

// local
#include "node_flow.hpp"
#include "add_flow_element.hpp"

namespace tool::ex {


class NodeFlowElement;
using NodeFlowElementUP = std::unique_ptr<NodeFlowElement>;


class NodeFlowElement : public FlowElement{

public:

    NodeFlowElement(NodeFlow *node);

    void adapt_size_from_name(QFontMetrics fontMetrics) override;
    void draw(QPainter &painter, qreal zoomLevel) override;
    void compute_position(QPointF topLeft, int loopMaxDeepLevel) override;
    void draw_add_buttons(QPainter &painter, qreal zoomLevel);

    AddFlowElementUP addRoutine = nullptr;
    AddFlowElementUP addIsi     = nullptr;
    AddFlowElementUP addLoop    = nullptr;
};
}
