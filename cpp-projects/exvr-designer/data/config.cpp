
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

void Config::update_arg(QString name, Arg arg){

    if(args.count(name)!=0){
        args[name] = std::move(arg);
        return;
    }
    QtLogger::error(QSL("Arg with name ") % name % QSL(" doesn't exists: ") % arg.name % QSL(" ") % arg.value() % QSL(" ") %
                  QString::number(arg.uiElementKey.v) % QSL(" ") % arg.separator());
}

void Config::add_arg(QString name, Arg arg){

    if(args.count(name)==0){
        args[name] = std::move(arg);
        return;
    }
//    qCritical() << "Arg with name " << name << " already exists " << arg.name << arg.value() << arg.uiElementKey << arg.separator();
}

void Config::remove_arg(QString name){
    args.erase(name);
}

void Config::move_arg_up(QString prevName, QString name){
    auto &item1 = args[name];
    auto &item2 = args[prevName];
    std::swap(item1, item2);
}

void Config::move_arg_down(QString nextName, QString name){
    auto &item1 = args[name];
    auto &item2 = args[nextName];
    std::swap(item1, item2);
}


