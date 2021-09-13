
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

    ConfigW(Config *config, Component *component, bool initConfig, std::unordered_map<QStringView,Arg> &args);
    void update_from_config(Config *config);


    void update_with_info(QStringView id, QStringView value);
    void reset_args();

    ConfigKey configKey;
    ComponentKey componentKey;
    QString name;

private:

    ConfigParametersW *p = nullptr;
    ConfigParametersW *generate_parameters(Component::Type type, bool initConfig);

    template<typename T1, typename T2>
    ConfigParametersW *gen_params_w(bool initConfig){
        if(initConfig){
            return new T1();
        }else{
            return new T2();
        }
    }
};
}
