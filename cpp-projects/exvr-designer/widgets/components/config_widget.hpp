
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QWidget>

// std
#include <memory>

// local
#include "component.hpp"
#include "config_pw.hpp"

namespace tool::ex {

class ConfigW : public QWidget{

    Q_OBJECT // necessary for a cast in another class

public:

    ConfigW(Config *config, ConfigParametersW *parametersW);

    void update_from_config(Config *config);

    ConfigParametersW *p = nullptr;

    int key;
    QString name;
};
}
