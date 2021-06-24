
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

#include "flow/flow_element.hpp"

namespace tool::ex {


class RemoveFlowElement;
using RemoveFlowElementUP = std::unique_ptr<RemoveFlowElement>;

class RemoveFlowElement : public FlowElement{

public:

    RemoveFlowElement();

    void draw(QPainter &painter, qreal zoomLevel) override;

private :
    ElementUP remove = nullptr;
};

}
