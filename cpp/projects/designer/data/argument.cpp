
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "argument.hpp"

using namespace tool::str;
using namespace tool::ex;

std::vector<Arg> Arg::split_value_to_atoms_args() const{

    auto list = split_value();
    std_v1<Arg> args;
    for(auto &v : list){
        Arg arg;
        arg.uiElementKey = uiElementKey;
        arg.m_unityType    = m_unityType;
        arg.m_value        = v;
        arg.m_separator    = "";
        arg.m_sizes        = {};

        arg.generator = generator;
        args.emplace_back(std::move(arg));
    }
    return args;
}

std::array<Arg, 3> Arg::to_transform_args() const{

    auto l = split_value();
    std::array<Arg, 3> args;
    for(auto &arg : args){
        arg.uiElementKey    = uiElementKey;
        arg.m_separator       = m_separator;
        arg.m_sizes           = {3};
    }
    args[0].m_value = l[0] + m_separator + l[1] + m_separator + l[2];
    args[1].m_value = l[3] + m_separator + l[4] + m_separator + l[5];
    args[2].m_value = l[6] + m_separator + l[7] + m_separator + l[8];

    return args;
}

void Arg::init_from_unknow(UiElementKey key, QString v){
    uiElementKey   = key;
    m_unityType    = UnityType::Unknow;
    m_separator    = "";
    m_value        = Convertor::to_str(v);
    m_sizes        = {};
}

void Arg::init_from(QString v){
    m_unityType = UnityType::System_string;
    m_separator = "";
    m_value     = Convertor::to_str(v);
    m_sizes     = {};
}

void Arg::init_from(QStringList list, QString sep){
    m_unityType = UnityType::System_string;
    m_separator = sep;
    m_value     = Convertor::to_str(list,m_separator);
    m_sizes     = {list.length()};
}

void Arg::init_from_bool_str(QString v){
    m_unityType = UnityType::System_boolean;
    m_separator = "";
    m_value     = v;
    m_sizes     = {};
}

void Arg::init_from_int_str(QString v){
    m_unityType = UnityType::System_int32;
    m_separator = "";
    m_value     = v;
    m_sizes     = {};
}

void Arg::init_from_float_str(QString v){
    m_unityType = UnityType::System_single;
    m_separator = "";
    m_value     = v;
    m_sizes     = {};
}

void Arg::init_from_double_str(QString v){
    m_unityType = UnityType::System_double;
    m_separator = "";
    m_value     = v;
    m_sizes     = {};
}

void Arg::init_from_vector3_str(QString v){
    m_unityType = UnityType::System_single;
    m_separator = " ";
    m_value     = v;
    m_sizes     = {3};
}

void Arg::init_from_color_str(QString v){
    m_unityType = UnityType::System_single;
    m_separator = " ";
    m_value     = v;
    m_sizes     = {4};
}

void Arg::init_from_curve_str(QString v, QString sep){
    m_unityType = UnityType::System_single;
    m_separator = sep;
    m_value     = v;
    m_sizes     = {(v.count(m_separator) + 1)};
}

void Arg::init_from_transform_args(Arg tr, Arg rot, Arg sc){

    m_unityType = UnityType::System_single;
    m_separator = " ";
    m_value     = tr.value() + m_separator + rot.value() + m_separator + sc.value();
    m_sizes     = {9};
}


void Arg::init_from_args(std::vector<Arg> args, QString sep, UnityType uType){

    m_unityType = uType;
    m_separator = sep;
    m_value     = "";
    for(size_t ii = 0; ii < args.size(); ++ii){
        m_value += args[ii].m_value;
        if(ii < args.size() -1){
            m_value += m_separator;
        }
    }
    m_sizes = {static_cast<int>(args.size())};
}

Arg Arg::generate_item_ui_arg(UiElementKey uiElementKey, QString name, QString generatorName, UiType associatedUiType, int generatorOrder){
    Arg arg;
    arg.uiElementKey       = uiElementKey;
    arg.name               = name;
    arg.generator.name     = generatorName;
    arg.m_associatedUiType = associatedUiType;
    arg.generator.order    = generatorOrder;
    return arg;
}

Arg Arg::generate_init_ui_arg(UiElementKey uiElementKey, UiType uiType, QString name){
    Arg arg;
    arg.uiElementKey       = uiElementKey;
    arg.m_associatedUiType = uiType;
    arg.name               = name;
    return arg;
}

Arg Arg::generate_from_loaded_xml_values(UiElementKey uiElementKey, UiType uiType, QString name, QString value, QString separator, QVector<int> sizes, UnityType type){
    Arg arg;
    arg.uiElementKey       = uiElementKey;
    arg.m_associatedUiType = uiType;
    arg.name               = name;
    arg.m_value            = value;
    arg.m_separator        = separator;
    arg.m_sizes            = sizes;
    arg.m_unityType        = type;
    return arg;
}

Arg Arg::generate_non_ui_arg(QString value, QString separator){
    Arg arg;
    arg.uiElementKey       = UiElementKey{-1};
    arg.m_associatedUiType = UiType::Non_ui_labels;
    arg.name               = "";
    arg.m_value            = value;
    arg.m_separator        = separator;
    arg.m_sizes            = {value.count(separator)+1};
    arg.m_unityType        = UnityType::System_string;
    return arg;
}

Arg Arg::copy_with_new_element_id(const Arg &argToCopy){
    Arg arg;
    arg.uiElementKey       = UiElementKey{IdKey(IdKey::Type::UiItemArgument)()};
    arg.name               = argToCopy.name;
    arg.m_associatedUiType = argToCopy.m_associatedUiType;
    arg.m_value            = argToCopy.m_value;
    arg.m_separator        = argToCopy.m_separator;
    arg.m_sizes            = argToCopy.m_sizes;
    arg.generator          = argToCopy.generator;
    arg.m_unityType        = argToCopy.m_unityType;
    return arg;
}


