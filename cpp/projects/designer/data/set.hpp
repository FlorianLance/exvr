
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QString>

// local
#include "id_key.hpp"

namespace tool::ex {

struct Set{

    Set(QString name, SetKey id) : key(IdKey::Type::Set, id.v), name(name){
    }

    static Set copy_with_new_element_id(const Set &setToCopy){
        Set set(setToCopy.name, SetKey{-1});
        set.occurencies = setToCopy.occurencies;
        return set;
    }

    IdKey key;
    QString name;
    size_t occurencies = 1;
};

[[maybe_unused]] static bool operator==(const Set &l, const Set &r){
    return  (l.name  == r.name);
}


}
