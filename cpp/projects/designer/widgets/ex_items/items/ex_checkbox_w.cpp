
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_checkbox_w.hpp"

using namespace tool::ex;

ExCheckBoxW *ExCheckBoxW::init_widget(QString txt, bool checked, bool enabled){
    ui::W::init(w.get(), txt, checked, enabled);
    return this;
}

std::optional<Arg> ExCheckBoxW::generate_init_arg_from_dialog(QStringList othersParameters){

    GenUIItemDialog genD(QSL("Add ") % from_view(get_name(type)));
    if(genD.show_dialog(std::move(othersParameters))){
        auto arg = Arg::generate_init_ui_arg(UiElementKey{key()}, type, genD.name());
        arg.set_value(QSL("False"));
        arg.set_separator("");
        return {arg};
    }
    return {};
}

void ExCheckBoxW::init_connection(const QString &nameParam){
    connect(w.get(), &QCheckBox::stateChanged, this, [=]{emit ui_change_signal(nameParam);});
}

void ExCheckBoxW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(generatorName.length() > 0){
        if(arg.generator.info.has_value()){
            w->setText(arg.generator.info.value());
        }
    }
    w->setChecked(arg.to_bool_value());

    w->blockSignals(false);
}

Arg ExCheckBoxW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(w->isChecked());

    // generator
    if(generatorName.length() > 0){
        arg.generator.info = w->text();
    }
    return arg;
}
