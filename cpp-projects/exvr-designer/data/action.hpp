
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "id_key.hpp"
#include "forward.hpp"
#include "timeline.hpp"
#include "connection.hpp"

namespace tool::ex {

struct Action;
using ActionUP = std::unique_ptr<Action>;

struct Action{

    Action() = delete;
    Action(Component *component, Config *config, ActionKey id);

    static std::unique_ptr<Action> generate_component_action(Component *component, SecondsTS duration){
        auto action = std::make_unique<Action>(component, component->configs[0].get(), ActionKey{-1});
        action->timelineUpdate     = std::make_unique<Timeline>(Timeline::Type::Update, TimelineKey{-1});
        action->timelineUpdate->add_interval(Interval(SecondsTS{0}, duration,IntervalKey{-1}));
        action->timelineVisibility = std::make_unique<Timeline>(Timeline::Type::Visibility, TimelineKey{-1});
        action->timelineVisibility->add_interval(Interval(SecondsTS{0}, duration,IntervalKey{-1}));
        return action;
    }

    void select_config(RowId  configTabId);

    Config    *config               = nullptr;
    Component *component            = nullptr;    

    TimelineUP timelineUpdate       = nullptr;
    TimelineUP timelineVisibility   = nullptr;

    static ActionUP copy_with_new_element_id(const Action &actionToCopy);

    void update_intervals_with_max_length(SecondsTS maxLength);

    inline QString to_string() const{return QSL("Action(") % QString::number(key()) % QSL(")");}

    IdKey key;

    // ui
    // # graph
    QPointF nodePosition;
    //QSize nodeSize;
    bool nodeUsed = false;
    bool nodeSelected = false;
};


}
