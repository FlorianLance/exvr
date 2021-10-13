
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "timeline.hpp"

#include <QDebug>

using namespace tool;
using namespace tool::ex;

bool Timeline::add_interval(const Interval &interval){

    const double totalBefore = sum_intervals();
    intervals.emplace_back(interval);
    merge();
    const double totalAfter = sum_intervals();

    return !almost_equal(totalBefore,totalAfter);
}

bool Timeline::remove_interval(const Interval &intervalToRemove){

    const double totalBefore = sum_intervals();

    std_v1<size_t> idToRemove;
    std_v1<Interval> intervalsToAdd;

    for(size_t ii = 0; ii < intervals.size(); ++ii){
        Interval &interval = intervals[ii];

        bool startInside = interval.inside(intervalToRemove.start);
        bool endInside   = interval.inside(intervalToRemove.end);

        if(startInside && endInside){
            intervalsToAdd.emplace_back(Interval{intervalToRemove.end, interval.end, IntervalKey{-1}});
            interval.end = intervalToRemove.start;
        }else if(startInside){
            interval.end = intervalToRemove.start;
        }else if(endInside){
            interval.start = intervalToRemove.end;
        }else if(intervalToRemove.inside(interval.start) && intervalToRemove.inside(interval.end)){
            idToRemove.emplace_back(ii);
        }
    }

    for(int ii = static_cast<int>(idToRemove.size())-1; ii >= 0; --ii){
        intervals.erase(intervals.begin()+static_cast<int>(idToRemove[static_cast<size_t>(ii)]));
    }

    for(auto &i : intervalsToAdd){
        intervals.emplace_back(std::move(i));
    }

    std::sort(intervals.begin(), intervals.end(), compare_intervals);

    intervals.erase(std::remove_if(intervals.begin(), intervals.end(),[](Interval& i) {
        return (almost_equal<double>(i.length().v,0.)); // put your condition here
    }), intervals.end());

    const double totalAfter = sum_intervals();

    return !almost_equal(totalBefore,totalAfter);
}

void Timeline::cut(SecondsTS max){

    std_v1<size_t> idToRemove;
    for(size_t ii = 0; ii < intervals.size(); ++ii){
        Interval &interval = intervals[ii];
        if(interval.inside(max)){
            interval.end = max;
        }else if(interval.start.v > max.v){
            idToRemove.emplace_back(ii);
        }
    }

    for(int ii = static_cast<int>(idToRemove.size())-1; ii >= 0; --ii){
        intervals.erase(intervals.begin()+static_cast<int>(idToRemove[static_cast<size_t>(ii)]));
    }
}

double Timeline::sum_intervals() const{

    double total = 0.;
    for(const auto &interval : intervals){
        total += interval.length().v;
    }
    return total;
}


void Timeline::fill(SecondsTS length){
    clean();
    intervals.emplace_back(Interval{SecondsTS{0.},length, IntervalKey{-1}});
}

void Timeline::clean(){
    intervals.clear();
}

void Timeline::merge(){

    while(true){

        std_v1<std::pair<size_t,size_t>> collides;

        for(size_t ii = 0; ii < intervals.size(); ++ii){
            for(size_t jj = 0; jj < intervals.size(); ++jj){
                if(ii == jj){
                    continue;
                }
                if(intervals[ii].collide(intervals[jj])){ // merge if collide
                    collides.emplace_back(std::make_pair(ii,jj));
                    break;
                }
            }
            if(collides.size() > 0){
                break;
            }
        }

        if(collides.size() == 0){
            break;
        }

        Interval merged = merge_intervals(intervals[collides[0].first], intervals[collides[0].second]);
        if(collides[0].first < collides[0].second){
            intervals.erase(intervals.begin()+static_cast<int>(collides[0].second));
            intervals.erase(intervals.begin()+static_cast<int>(collides[0].first));
        }else{
            intervals.erase(intervals.begin()+static_cast<int>(collides[0].first));
            intervals.erase(intervals.begin()+static_cast<int>(collides[0].second));
        }
        intervals.emplace_back(merged);
    }

    std::sort(intervals.begin(), intervals.end(), compare_intervals);
}
