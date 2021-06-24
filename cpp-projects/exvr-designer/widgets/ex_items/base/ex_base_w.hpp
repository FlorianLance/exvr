
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#pragma once

// std
#include <any>

// local
#include "argument.hpp"
#include "qt_ui.hpp"
#include "generation/gen_ui_item_dialog.hpp"

namespace tool::ex {


class ExBaseW : public QObject{
Q_OBJECT
public:
    ExBaseW(UiType t) : type(t), key(IdKey::Type::UiItemArgument, -1){}

    virtual ~ExBaseW(){}
    virtual void init_connection(const QString &nameParam) = 0;
    virtual void update_from_arg(const Arg &arg) = 0;    
    virtual Arg convert_to_arg()const = 0;
    virtual void init_tooltip(QString tooltip) = 0;
    virtual void init_default_tooltip(QString key) = 0;    
    virtual void set_generator(QString genName){
        generatorName = genName;
    }

    virtual void update_from_resources(){}
    virtual void update_from_components(){}


    virtual ExBaseW *init_widget2(std_v1<std::any> parameters){
        Q_UNUSED(parameters)
        return this;
    }

    virtual std::optional<Arg> generate_init_arg_from_dialog(QStringList othersParameters){

        GenUIItemDialog genD(type);
        genD.setMinimumWidth(500);
        genD.setMaximumWidth(900);
        if(genD.show_dialog(othersParameters)){
            return {genD.generate_arg(UiElementKey{key()})};
        }
        return {};
    }


    QString itemName;
    QString generatorName = "";
    int generatorOrder = -1;
    UiType type;
    IdKey key;

signals:

    void ui_change_signal(QString nameParam);
    void action_signal(QString nameAction);

    // test
    void update_from_components_signal();
    void update_from_resources_signal();
};



}


