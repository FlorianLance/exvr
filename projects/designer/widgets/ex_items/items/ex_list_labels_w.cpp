/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "ex_list_labels_w.hpp"

using namespace tool::ex;


ExListLabelsW *ExListLabelsW::init_widget(bool enabled){
    w->clear();
    w->setEnabled(enabled);
    return this;
}

std::optional<Arg> ExListLabelsW::generate_init_arg_from_dialog(QStringList othersParameters){
    Q_UNUSED(othersParameters)
    return {};
}

void ExListLabelsW::init_connection(const QString &nameParam){
    connect(w.get(), &QListWidget::itemChanged, this, [=]{emit ui_change_signal(nameParam);});
}

Arg ExListLabelsW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();

    // value
    QStringList list;
    for(int ii = 0; ii < w->count(); ++ii){
        list << w->item(ii)->text();
    }
    arg.init_from(list, "|");

    // generator
    if(generatorName.length() > 0){
        // ...
    }
    return arg;
}

void ExListLabelsW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(generatorName.length() > 0){
        // ...
    }

    w->clear();
    auto labels = arg.split_value();
    for(auto &label : labels){
        w->addItem(label);
    }

    w->blockSignals(false);
}
