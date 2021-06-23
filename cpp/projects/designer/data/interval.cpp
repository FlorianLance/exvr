
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "interval.hpp"

using namespace tool;
using namespace tool::ex;

bool Interval::inside(SecondsTS time) const{

    if(almost_equal(time.v,start.v) || almost_equal(time.v,end.v)){
        return true;
    }
    return time.v > start.v && time.v < end.v;
}

bool Interval::collide(Interval interval){
    return (inside(interval.start) || inside(interval.end) || interval.inside(start) || interval.inside(end));
}

Seconds Interval::length() const {
    return Seconds{end.v-start.v};
}



