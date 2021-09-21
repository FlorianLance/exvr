
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "data/id_key.hpp"

// local
#include "forward.hpp"
#include "data/timeline.hpp"
#include "data/connection.hpp"

namespace tool::ex {

struct Action;
using ActionUP = std::unique_ptr<Action>;

struct Action{

    Action() = delete;
    Action(Component *component, Config *config, ActionKey id);

    void select_config(RowId  configTabId);
    void update_intervals_with_max_length(SecondsTS maxLength);

    inline QString to_string() const{return QSL("Action(") % QString::number(key()) % QSL(")");}

    static ActionUP generate_component_action(Component *component, SecondsTS duration);
    static ActionUP copy_with_new_element_id(const Action &actionToCopy);

    void check_integrity();

    IdKey key;

    Config    *config               = nullptr;
    Component *component            = nullptr;

    TimelineUP timelineUpdate       = nullptr;
    TimelineUP timelineVisibility   = nullptr;

    // ui
    // # graph
    QPointF nodePosition;
    //QSize nodeSize;
    bool nodeUsed = false;
    bool nodeSelected = false;
};

static bool operator<(const ActionUP &l, const ActionUP &r){
    if(l->key() == r->key()){
        return false;
    }

    if(l->component->key() == r->component->key()){
        return false;
    }

    return true;
}

static bool operator==(const ActionUP &l, const ActionUP &r){
    return !(l < r) && !(r < l);
}

}
