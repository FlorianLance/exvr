
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <array>
#include <unordered_set>
#include <unordered_map>

namespace tool::ex{

struct RowId{int v;};
struct UiElementKey{int v;};
struct SetKey{int v;};
struct ActionKey{int v;};
struct ConfigKey{int v;};
struct IntervalKey{int v;};
struct TimelineKey{int v;};
struct ConditionKey{int v;};
struct ElementKey{int v;};
struct ComponentKey{int v;};
struct ConnectionKey{int v;};
struct ConnectorKey{int v;};

[[maybe_unused]] static bool operator==(const ComponentKey &l, const ComponentKey &r){
    return  (l.v == r.v);
}
[[maybe_unused]] static bool operator==(const SetKey &l, const SetKey &r){
    return  (l.v == r.v);
}
[[maybe_unused]] static bool operator==(const ElementKey &l, const ElementKey &r){
    return  (l.v == r.v);
}
[[maybe_unused]] static bool operator==(const ConditionKey &l, const ConditionKey &r){
    return  (l.v == r.v);
}



class IdKey{

public :

    enum class Type : int {
        UiItemArgument, Action, Component, Condition, Config, Connection, Element, Interval, Timeline, ButtonElement, Connector, Resource, Set,
        SizeEnum
    };

    IdKey() = delete;
    IdKey(Type type, int id =-1);

    constexpr int operator()() const {
        return m_id;
    }    
    constexpr const char* type_name() const;

    static constexpr const char *get_name(IdKey::Type c) {
        for (auto& p : typeMapping) {
            if (c == std::get<0>(p)) {
                return std::get<1>(p);
            }
        }
        return "";
    }

    static void reset();

private:

    static constexpr std::array<std::pair<Type,const char*>,static_cast<size_t>(Type::SizeEnum)> typeMapping ={{
        // type                    // type_str
        {Type::UiItemArgument,     "UI item argument"},
        {Type::Action,             "Action"},
        {Type::Component,          "Component"},
        {Type::Condition,          "Condition"},
        {Type::Config,             "Config"},
        {Type::Connection,         "Connection"},
        {Type::Element,            "Element"},
        {Type::Interval,           "Interval"},
        {Type::Timeline,           "Timeline"},
        {Type::ButtonElement,      "ButtonElement"},
        {Type::Connector,          "Connector"},
        {Type::Resource,           "Resource"},
        {Type::Set,                "Set"},
    }};

    int &current_id(){
        return currentId[m_type];
    }

    std::unordered_set<int> &current_set(){        
        return keys[m_type];
    }

    static inline std::unordered_map<Type,int> currentId = {};
    static inline std::unordered_map<Type,std::unordered_set<int>> keys = {};

    Type m_type;
    int m_id = -1;
};
}

