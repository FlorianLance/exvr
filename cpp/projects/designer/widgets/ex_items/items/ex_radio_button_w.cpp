
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_radio_button_w.hpp"

using namespace tool::ex;

void ExRadioButtonW::update_from_arg(const Arg &arg) {
    ExItemW::update_from_arg(arg);

    w->blockSignals(true);
    w->setChecked(arg.to_bool_value());
    w->blockSignals(false);
}

ExRadioButtonW *ExRadioButtonW::init_widget(QString txt, bool checked, bool enabled){
    ui::W::init(w.get(), txt, checked, enabled);
    return this;
}

std::optional<Arg> ExRadioButtonW::generate_init_arg_from_dialog(QStringList ){
    return {};
}

void ExRadioButtonW::init_connection(const QString &nameParam) {
    connect(w.get(), &QRadioButton::toggled, this, [=]{emit ui_change_signal(nameParam);});
}

Arg ExRadioButtonW::convert_to_arg() const {
    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(w->isChecked());
    return arg;
}


