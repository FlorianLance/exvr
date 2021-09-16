
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// base
#include "utility/types_utility.hpp"

// qt-utility
#include "qt_str.hpp"
#include "data/id_key.hpp"

namespace tool::ex {

struct Interval{

    Interval(): key(IdKey::Type::Interval, -1){}
    Interval(SecondsTS tS, SecondsTS tE, IntervalKey id) : key(IdKey::Type::Interval, id.v), start(tS), end(tE){}

    static Interval copy_with_new_element_id(const Interval &intervalToCopy){
        return Interval(intervalToCopy.start, intervalToCopy.end, IntervalKey{-1});
    }

    bool inside(SecondsTS time) const;
    bool collide(Interval interval);
    Seconds length() const;

    IdKey key;
    SecondsTS start{0.};
    SecondsTS end{0.};

    void merge(const Interval &i){
        start = SecondsTS{std::min(start.v, i.start.v)};
        end   = SecondsTS{std::max(end.v,   i.end.v)};
    }

    inline QString to_string() const{return QSL("[") % QString::number(start.v) % QSL(", ") % QString::number(end.v) % QSL("]");}
};

    [[maybe_unused]] static Interval merge_intervals(const Interval &i1, const Interval &i2){
        return Interval(SecondsTS{std::min(i1.start.v,i2.start.v)},
                        SecondsTS{std::max(i1.end.v, i2.end.v)}, IntervalKey{i1.key()});
    }

    [[maybe_unused]] static bool compare_intervals(const Interval &i1, const Interval &i2){
        if(almost_equal(i1.start.v,i2.start.v)){
            return i1.end.v < i2.end.v;
        }
        return i1.start.v < i2.start.v;
    }

}
