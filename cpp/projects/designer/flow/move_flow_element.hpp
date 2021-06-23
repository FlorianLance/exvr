
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

#include "flow/flow_element.hpp"

namespace tool::ex{

class MoveFlowElement;
using MoveFlowElementUP = std::unique_ptr<MoveFlowElement>;

class MoveFlowElement : public FlowElement{

public:

    MoveFlowElement(bool left);

    void draw(QPainter &painter, qreal zoomLevel) override;


    bool isLeft;

private:

    ElementUP move = nullptr;
};

}
