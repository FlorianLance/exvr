
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
    return config;
}

void Config::swap_arg(QStringView arg1Name, QStringView arg2Name){
    auto &item1 = args[arg1Name];
    auto &item2 = args[arg2Name];
    std::swap(item1.generator->order, item2.generator->order);
}

void Config::update_arg(Arg arg){

    QStringView aName = arg.name;
    if(args.count(aName) != 0){
        args[aName] = std::move(arg);
        return;
    }
    QtLogger::error(QSL("Arg with name ") % name % QSL(" doesn't exists: ") % arg.name % QSL(" ") % arg.value() % QSL(" ") % arg.separator());
}

void Config::add_arg(Arg arg){

    QStringView aName = arg.name;
    if(args.count(aName)==0){
        args[aName] = std::move(arg);
    }else{
        qWarning() << "Config::error: arg " << arg.name << " already added.";
    }
}

void Config::remove_arg(QStringView argName){
    args.erase(argName);
}

