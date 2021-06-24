
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QString>
#include <QVector>
#include <QDebug>

// local
#include "argument.hpp"

namespace tool::ex {


struct Config;
using ConfigUP = std::unique_ptr<Config>;

struct Config{

    Config() = delete;
    Config(const QString &n, ConfigKey id) : name(n), key(IdKey::Type::Config, id.v){
    }

    static ConfigUP copy_with_new_element_id(const Config &configToCopy, const QString &newName);

    void update_arg(QString name, Arg arg);
    void add_arg(QString name, Arg arg);
    void remove_arg(QString name);
    void move_arg_up(QString prevName, QString name);
    void move_arg_down(QString nextName, QString name);

    inline QString to_string() const{return QSL("Config(") % name % QSL("|") % QString::number(key()) % QSL(")");}

    QString name = QSL("standard");
    IdKey key;

    std::map<QString,Arg> args;
};
}
