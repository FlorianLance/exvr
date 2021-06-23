
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// local
#include "ex_base_w.hpp"

namespace tool::ex {

template<typename widget>
class ExItemW : public ExBaseW{
public:

    ExItemW(UiType t) : ExBaseW(t), w(std::make_unique<widget>()){
    }

    virtual Arg convert_to_arg() const override {
        return Arg::generate_item_ui_arg(UiElementKey{key()}, itemName, generatorName, type, generatorOrder);
    }

    virtual void update_from_arg(const Arg &arg) override{

        key = IdKey(IdKey::Type::UiItemArgument, arg.uiElementKey.v);

        if(generatorName.length() > 0){
            generatorOrder = arg.generator.order;
        }
    }

    virtual void init_tooltip(QString tooltip  = "") override{
        w->setToolTipDuration(-1);
        w->setToolTip(tooltip);
    }

    virtual void init_default_tooltip(QString name) override{
        w->setToolTipDuration(-1);
        w->setToolTip(QSL("name: ") % name % QSL("  C# type: ") % from_view(get_tooltip_string(type)));
    }

    widget *release(){
        return w.release();
    }

    widget * operator()() { return w.get();}

    std::unique_ptr<widget> w = nullptr;
};
}
