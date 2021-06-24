
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_text_edit_w.hpp"

using namespace tool::ex;


ExTextEditW::ExTextEditW() : ExItemW<QTextEdit>(UiType::Text_edit) {}

ExTextEditW *ExTextEditW::init_widget(QString txt, bool enabled){
    ui::W::init(w.get(), txt, enabled);
    return this;
}

std::optional<Arg> ExTextEditW::generate_init_arg_from_dialog(QStringList othersParameters){

    GenUIItemDialog genD(QSL("Add ") % from_view(get_name(type)));
    QTextEdit teText;
    genD.add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("Text:"), &teText},  LStretch{false},LMargins{false}, QFrame::NoFrame));

    if(genD.show_dialog(std::move(othersParameters))){
        Arg arg = Arg::generate_init_ui_arg(UiElementKey{key()}, type, genD.name());
        arg.set_separator("");
        arg.set_value(teText.toPlainText());
        return {arg};
    }

    return {};
}

void ExTextEditW::init_connection(const QString &nameParam){connect(w.get(), &QTextEdit::textChanged,this, [=]{emit ui_change_signal(nameParam);});}

void ExTextEditW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(arg.generator.name.length() > 0){
        // ...
    }
    w->setText(arg.to_string_value());

    w->blockSignals(false);
}

Arg ExTextEditW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(w->toPlainText());

    // generator
    if(generatorName.length() > 0){
        // ...
    }
    return arg;
}
