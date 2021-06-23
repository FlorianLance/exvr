
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_color_frame_w.hpp"

using namespace tool;
using namespace tool::ex;

ExColorFrameW::ExColorFrameW() : ExItemW<QFrame>(UiType::Color_frame){
    w->setMinimumSize(QSize(20,20));
}

ExColorFrameW *ExColorFrameW::init_widget(bool on, bool enabled){
    onState = on;
    ui::W::init(w.get(), onState, enabled);
    return this;
}

std::optional<Arg> ExColorFrameW::generate_init_arg_from_dialog(QStringList othersParameters){
    // no generative
    Q_UNUSED(othersParameters)
    return {};
}

void ExColorFrameW::update_from_arg(const Arg &arg){
    ExItemW::update_from_arg(arg);

    w->blockSignals(true);
    update(arg.to_bool_value());
    w->blockSignals(false);
}

Arg ExColorFrameW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(onState);

    // generator
    if(generatorName.length() > 0){
        // ...
    }
    return arg;
}

void ExColorFrameW::update(bool on){
    if(onState == on){
        return;
    }
    w->setStyleSheet((onState = on) ? stateOn : stateOff);
}

void ExColorFrameW::init_connection(const QString &nameParam){
    // no events
    Q_UNUSED(nameParam)
}
