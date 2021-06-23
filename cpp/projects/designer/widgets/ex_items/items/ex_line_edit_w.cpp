
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_line_edit_w.hpp"

using namespace tool::ex;


ExLineEditW *ExLineEditW::init_widget(QString txt, bool enabled){
    ui::W::init(w.get(), txt, enabled);
    return this;
}

std::optional<Arg> ExLineEditW::generate_init_arg_from_dialog(QStringList othersParameters){

    GenUIItemDialog genD(QSL("Add ") % from_view(get_name(type)));
    QLineEdit leText;
    genD.add_row(QSL("Value:"), &leText);

    if(genD.show_dialog(std::move(othersParameters))){
        Arg arg = Arg::generate_init_ui_arg(UiElementKey{key()}, type, genD.name());
        arg.set_separator("");
        arg.set_value(leText.text());
        return {arg};
    }

    return {};
}

void ExLineEditW::init_connection(const QString &nameParam){connect(w.get(), &QLineEdit::textChanged,this, [=]{emit ui_change_signal(nameParam);});}

void ExLineEditW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(generatorName.length() > 0){
        // ...
    }
    w->setText(arg.to_string_value());

    w->blockSignals(false);
}

Arg ExLineEditW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(w->text());

    // generator
    if(generatorName.length() > 0){
        // ...
    }
    return arg;
}
