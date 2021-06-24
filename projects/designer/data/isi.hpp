
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <deque>

// base
#include "utility/types_utility.hpp"

// local
#include "element.hpp"
#include "qt_str.hpp"

namespace tool::ex {

struct Isi;
using IsiUP = std::unique_ptr<Isi>;

// TODO
struct Duration{
    double value = 1.0;
};

struct Isi : public Element  {

    Isi() : Element(Type::Isi, "isi"){
    }

    Isi(QString n, ElementKey id) : Element(Type::Isi, n, id.v){
    }

    inline QString to_string() const{return QSL("Isi(") % name() % QSL("|") % QString::number(key()) % QSL(")");}

    static IsiUP copy_with_new_element_id(const Isi &isiToCopy, const QString &newName);


    void set_randomize(bool randomize);

    void add_interval(double value, RowId id);
    void modify_interval(double value, RowId id);
    void remove_interval(RowId id);
    void move_interval_up(RowId id);
    void move_interval_down(RowId id);

    QString str_intervals()const;

    bool randomized;
    std_v1<double> intervals = {1.0};
    size_t currentIntervalId = 0;
};
}
