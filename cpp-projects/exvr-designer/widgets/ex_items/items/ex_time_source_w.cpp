
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_time_source_w.hpp"

using namespace tool::ex;

ExTimeW::ExTimeW(QString name) : ExItemW<QWidget>(UiType::Time, name){
    connect(&typeT, &ExComboBoxTextW::ui_change_signal, this, &ExTimeW::ui_change_signal);
    connect(&frequency, &ExSpinBoxW::ui_change_signal, this, &ExTimeW::ui_change_signal);
}

ExTimeW *ExTimeW::init_widget(bool enabled){

    QStringList items = {"Time since exp", "Time since routine"};
    typeT.init_widget(items, Index{0}, enabled);
    frequency.init_widget(MinV<int>{1}, V<int>{30}, MaxV<int>{90}, StepV<int>{1}, enabled);

    auto l = ui::L::VB();
    l->setContentsMargins(1,1,1,1);
    w->setLayout(l);

    auto h1 = ui::L::VB();
    h1->setContentsMargins(1,1,1,1);
    h1->addWidget(ui::W::txt("Type: "));
    h1->addWidget(typeT());
    auto w1 = new QWidget();
    w1->setLayout(h1);

    auto h2 = ui::L::VB();
    h2->setContentsMargins(1,1,1,1);
    h2->addWidget(ui::W::txt("Max frequency (FPS): "));
    h2->addWidget(frequency());
    auto w2 = new QWidget();
    w2->setLayout(h2);

    l->addWidget(w1);
    l->addWidget(w2);

    return this;
}

void ExTimeW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    auto split = arg.value().split("|");
    if(split.size() < 2){
        return;
    }

    w->blockSignals(true);

    Arg typeA = arg;
    Arg freqA = arg;

    typeA.init_from(split[0]);
    freqA.init_from_int_str(split[1]);

    typeT.update_from_arg(typeA);
    frequency.update_from_arg(freqA);

    w->blockSignals(false);
}

Arg ExTimeW::convert_to_arg() const{

    auto typeA = typeT.convert_to_arg();
    auto freqA = frequency.convert_to_arg();

    QStringList list;
    list << std::move(typeA.value());
    list << std::move(freqA.value());

    typeA.init_from(list, "|");
    return typeA;
}

void ExTimeW::set_as_generator(){
    ExBaseW::set_as_generator();
    typeT.set_as_generator();
    frequency.set_as_generator();
}
