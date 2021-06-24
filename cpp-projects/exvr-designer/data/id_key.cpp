
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "id_key.hpp"

// std
#include <iostream>

using namespace tool::ex;

IdKey::IdKey(IdKey::Type type, int id) : m_type(type){

    if(id == -1){
        m_id = current_id()++;
    }else{
        m_id = id;
        if(id >= current_id()){
            current_id() = id+1;
        }
    }

    auto &set = current_set();
    if(set.count(m_id) != 0){
        if(m_type != Type::UiItemArgument && m_type != Type::Element && m_type != Type::Interval){// && m_type) != Type::Connector){
            std::cerr << "Id of type " << type_name() << " already exists: " << m_id << "\n";
        }
    }else{
        set.insert(m_id);
    }
}

void IdKey::reset(){

    currentId.clear();
    for (auto& p : typeMapping) {
        currentId[std::get<0>(p)] = 0;
    }

    keys.clear();
    for (auto& p : typeMapping) {
        keys[std::get<0>(p)] = {};
    }
}


constexpr const char *IdKey::type_name() const {
    return get_name(m_type);
}
