
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_pushbutton_w.hpp"

using namespace tool::ex;

ExPushButtonW *ExPushButtonW::init_widget(QString txt, bool enabled){
    ui::W::init(w.get(), txt, enabled);
    return this;
}

std::optional<Arg> ExPushButtonW::generate_init_arg_from_dialog(QStringList othersParameters){
    Q_UNUSED(othersParameters)
    return {};
}

void ExPushButtonW::init_connection(const QString &nameParam){
    connect(w.get(), &QPushButton::clicked, this, [=]{emit action_signal(nameParam);});
}

void ExPushButtonW::update_from_arg(const Arg &arg){
    Q_UNUSED(arg)
//    w->blockSignals(true);
//    w->blockSignals(false);
}

Arg ExPushButtonW::convert_to_arg() const{
    return Arg{};
}
