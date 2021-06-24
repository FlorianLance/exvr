
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_combo_box_index_w.hpp"

using namespace tool::ex;

void ExComboBoxIndexW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(generatorName.length() > 0){
        if(auto info = arg.generator.info; info.has_value()){
            w->addItems(arg.generator.info.value().split("|"));

        }
    }
    w->setCurrentIndex(arg.to_int_value());

    w->blockSignals(false);
}

Arg ExComboBoxIndexW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(w->currentIndex());

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

ExComboBoxIndexW *ExComboBoxIndexW::init_widget(QStringList items, int index, bool enabled){

    ui::W::init(w.get(), items, enabled);
    if(index < w->count()){
        w->setCurrentIndex(index);
    }
    return this;
}

void ExComboBoxIndexW::init_connection(const QString &nameParam) {
    connect(w.get(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=]{emit ui_change_signal(nameParam);});
}

std::optional<Arg> ExComboBoxIndexW::generate_init_arg_from_dialog(QStringList othersParameters){

    GenUIItemDialog genD(QSL("Add ") % from_view(get_name(type)));
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
        auto arg = Arg::generate_init_ui_arg(UiElementKey{key()}, type, genD.name());
        arg.generator.info = leText.text();
        arg.set_value(split[0]);
        arg.set_separator("");
        return {arg};
    }

    return {};
}
