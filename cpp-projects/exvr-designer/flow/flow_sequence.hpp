
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QObject>

// local
// # flow
#include "loop_flow_element.hpp"
#include "routine_flow_element.hpp"
#include "isi_flow_element.hpp"
#include "node_flow_element.hpp"
// # experiment
#include "experiment/experiment.hpp"

namespace tool::ex {

class FlowSequence;
using FlowSequenceUP = std::unique_ptr<FlowSequence>;

class FlowSequence : public QObject{

    Q_OBJECT

public:

    void reset();
    void update_from_experiment(Experiment *exp);
    void check_click_on_elements(QPoint clickPos) noexcept;    
    void draw(QPainter &painter, qreal zoomLevel);

    FlowElement* current_selection() const;

signals:

    void select_element_signal(ElementKey elementKey);
    void unselect_element_signal();
    void add_element_signal(Element::Type type, size_t index);
    void remove_selected_element_signal();
    void move_element_left_signal(size_t id);
    void move_element_right_signal(size_t id);

private:

    size_t flow_position(FlowElement *elem) const;


public:

    std_v1<NodeFlowElement*>        nodesElements;
    std_v1<RoutineFlowElement*>     routinesElements;
    std_v1<IsiFlowElement*>         ISIsElements;
    std_v1<LoopNodeFlowElement*>    loopsStart;
    std_v1<LoopNodeFlowElement*>    loopsEnd;
    std_v1<LoopFlowElementUP>       loopsElements; // not in elements
    std_v1<FlowElementUP>           elements; // all elements
};
}


