
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "data/isi.hpp"
#include "movable_flow_element.hpp"

namespace tool::ex {

class IsiFlowElement;
using IsiFlowElementUP = std::unique_ptr<IsiFlowElement>;

class IsiFlowElement : public MovableFlowElement{


public:

    IsiFlowElement(Isi *isi);

    IsiFlowElement(IsiFlowElement&&) = delete;
    IsiFlowElement& operator=(IsiFlowElement&&) = delete;
    IsiFlowElement(const IsiFlowElement&) = delete;
    IsiFlowElement& operator=(const IsiFlowElement&) = delete;

    // element virtual
    void adapt_size_from_name(QFontMetrics fontMetrics) override;
    void compute_position(QPointF topLeft, int loopMaxDeepLevel) override;
    void draw(QPainter &painter,qreal zoomLevel) override;
};
}
