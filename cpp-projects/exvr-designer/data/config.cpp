
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "config.hpp"

// qt-utility
#include "qt_logger.hpp"

using namespace tool::ex;

ConfigUP Config::copy_with_new_element_id(const Config &configToCopy, const QString &newName){

    ConfigUP config = std::make_unique<Config>(newName, ConfigKey{-1});
    for(const auto &arg : configToCopy.args){ // create a new element id for each arg when we duplicate
        config->args[arg.first] = Arg::copy_with_new_element_id(arg.second);
    }

//    for(auto &arg : config->args){
//        config->argsByName[arg.second.name] = &arg.second;
//    }

    return config;
}

//void Config::swap_arg(UiElementKey arg1Key, UiElementKey arg2Key){
void Config::swap_arg(QStringView arg1Name, QStringView arg2Name){
//    auto &item1 = args[arg1Key];
//    auto &item2 = args[arg2Key];
    auto &item1 = args[arg1Name];
    auto &item2 = args[arg2Name];
    std::swap(item1.generator.order, item2.generator.order);
}

void Config::update_arg(Arg arg){

//    auto key = arg.uiElementKey;
    QStringView aName = arg.name;
//    if(args.count(key) != 0){
//        args[key] = std::move(arg);
//        return;
//    }
    if(args.count(aName) != 0){
        args[aName] = std::move(arg);
        return;
    }
    QtLogger::error(QSL("Arg with name ") % name % QSL(" doesn't exists: ") % arg.name % QSL(" ") % arg.value() % QSL(" ") % arg.separator());
//    QtLogger::error(QSL("Arg with name ") % name % QSL(" doesn't exists: ") % arg.name % QSL(" ") % arg.value() % QSL(" ") %
//                  QString::number(arg.uiElementKey.v) % QSL(" ") % arg.separator());
}

void Config::add_arg(Arg arg){

//    auto key = arg.uiElementKey;
    QStringView aName = arg.name;
    if(args.count(aName)==0){
        args[aName] = std::move(arg);
    }else{
        qWarning() << "Config::error: arg " << arg.name << " already added.";
    }

//    if(args.count(key)==0){
//        args[key] = std::move(arg);
//        argsByName[args[key].name] = &args[key];
//    }else{
//        qWarning() << "Config::error: arg " << arg.name << " already added.";
//    }
}

//void Config::remove_arg(UiElementKey argKey){
void Config::remove_arg(QStringView argName){
//    argsByName.erase(args[argKey].name);
//    args.erase(argKey);
    args.erase(argName);
}

