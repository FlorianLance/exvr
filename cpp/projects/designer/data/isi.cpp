

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "isi.hpp"


using namespace tool;
using namespace tool::ex;



IsiUP Isi::copy_with_new_element_id(const Isi &isiToCopy, const QString &newName){

    IsiUP isi = std::make_unique<Isi>(newName, ElementKey{-1});
    isi->randomized = isiToCopy.randomized;
    isi->intervals = isiToCopy.intervals;
    isi->currentIntervalId = isiToCopy.currentIntervalId;
    return isi;
}

void Isi::set_randomize(bool randomize) {
    this->randomized = randomize;
}

void Isi::modify_interval(double value, RowId id){
    intervals[id.v] = value;
}

void Isi::remove_interval(RowId id){
    intervals.erase(intervals.begin()+id.v);
    if(id.v > 0){
        currentIntervalId = to_unsigned(id.v-1);
    }
}

void Isi::add_interval(double value, RowId id){
    intervals.insert(intervals.begin()+ id.v, value);
    currentIntervalId = id.v;
}

void Isi::move_interval_up(RowId id){
    std::swap(intervals[id.v], intervals[id.v-1]);
    currentIntervalId = id.v-1;
}

void Isi::move_interval_down(RowId id){
    std::swap(intervals[id.v], intervals[id.v + 1]);
    currentIntervalId = id.v + 1;
}

QString Isi::str_intervals() const{
    QString str;
    for(const auto& interval : intervals){
        str += QString::number(interval) % QSL(" ");
    }
    if(str.size() > 0){
        str.remove(str.size()-1,1);
    }
    return str;
}
