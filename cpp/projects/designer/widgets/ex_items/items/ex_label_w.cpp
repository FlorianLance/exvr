
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_label_w.hpp"


using namespace tool::ex;



ExLabelW *ExLabelW::init_widget(QString txt, bool enabled){
    ui::W::init_label(w.get(), txt, enabled);
    return this;
}

std::optional<Arg> ExLabelW::generate_init_arg_from_dialog(QStringList othersParameters){

    GenUIItemDialog genD(QSL("Add ") % from_view(get_name(type)));
    QLineEdit leText;
    genD.add_row(QSL("Value:"), &leText);

    if(genD.show_dialog(std::move(othersParameters))){
        Arg arg = Arg::generate_init_ui_arg(UiElementKey{key()}, type, genD.name());
        arg.set_value(leText.text());
        arg.set_separator("");
        return {arg};
    }

    return {};
}

void ExLabelW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(generatorName.length() > 0){
        // ...
    }
    w->setText(arg.to_string_value());

    w->blockSignals(false);
}

Arg ExLabelW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(w->text());

    // generator
    if(generatorName.length() > 0){
        // ...
    }

    return arg;
}

void ExLabelW::init_connection(const QString &nameParam){
    Q_UNUSED(nameParam)
}
