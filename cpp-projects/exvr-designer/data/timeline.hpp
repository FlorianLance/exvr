
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <iostream>

// qt-utility
#include "qt_str.hpp"

// local
#include "interval.hpp"

namespace tool::ex {

struct Timeline;
using TimelineUP = std::unique_ptr<Timeline>;

struct Timeline{

    enum Type {Update,Visibility};

    Timeline(Type t, TimelineKey id) : key(IdKey::Type::Timeline, id.v), type(t){
    }

    static TimelineUP copy_with_new_element_id(const Timeline &timelineToCopy){
        TimelineUP timeline = std::make_unique<Timeline>(timelineToCopy.type, TimelineKey{-1});
        for(const auto& interval : timelineToCopy.intervals){
            timeline->intervals.emplace_back(Interval::copy_with_new_element_id(interval));
        }
        return timeline;
    }

    bool add_interval(const Interval &interval);
    bool remove_interval(const Interval &intervalToRemove);
    void cut(SecondsTS max);
    double sum_intervals() const;


    void fill(SecondsTS lenght);
    void clean();

    IdKey key;
    std_v1<Interval> intervals;
    Type type;

    inline QString to_string() const{
        QString v;
        for(const auto &interval : intervals){
            v = v % interval.to_string();
        }
        return v;
    }

private:

    void merge();
};


}
