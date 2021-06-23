
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_combo_box_text_w.hpp"

using namespace tool;
using namespace tool::ex;

ExComboBoxTextW *ExComboBoxTextW::init_widget(QStringList items, Index index, bool enabled){
    ui::W::init(w.get(), items, enabled);
    if(index.v < w->count()){
        w->setCurrentIndex(index.v);
    }
    return this;
}

void ExComboBoxTextW::init_connection(const QString &nameParam) {
    connect(w.get(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=]{emit ui_change_signal(nameParam);});
}

std::optional<Arg> ExComboBoxTextW::generate_init_arg_from_dialog(QStringList othersParameters){

    GenUIItemDialog genD("Add " % from_view(get_name(type)));
    QLineEdit leText;
    leText.setText("A|B|C");
    genD.add_row("Enter items (using \"|\" as separator)):", &leText);

    if(genD.show_dialog(std::move(othersParameters))){
        if(leText.text().length() == 0){
            return {};
        }
        auto split = leText.text().split("|");
        if(split.count() == 0){
            return {};
        }

        auto arg =Arg::generate_init_ui_arg(UiElementKey{key()}, type, genD.name());
        arg.set_value(split[0]);
        arg.set_separator("");
        arg.generator.info = leText.text();
        return {arg};
    }

    return {};
}

void ExComboBoxTextW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(generatorName.length() > 0){
        if(auto info = arg.generator.info; info.has_value()){
            w->addItems(arg.generator.info.value().split("|"));
        }
    }

    const auto text  = arg.to_string_value();
    if(text.length() > 0){        
        w->setCurrentText(text);        
    }

    w->blockSignals(false);
}

Arg ExComboBoxTextW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(w->currentText());

    // generator
    if(generatorName.length() > 0){
        arg.generator.info = "";
        for(int ii = 0; ii < w->count(); ++ii){
            arg.generator.info.value() += w->itemText(ii);
            if(ii < w->count()-1){
                arg.generator.info.value() += "|";
            }
        }
    }

    return arg;
}
