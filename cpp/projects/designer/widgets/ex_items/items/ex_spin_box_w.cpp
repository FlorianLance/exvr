
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_spin_box_w.hpp"

// qt-utility
#include "qt_str.hpp"

using namespace tool;
using namespace tool::ex;


ExSpinBoxW *ExSpinBoxW::init_widget(MinV<int> min, V<int> value, MaxV<int> max, StepV<int> singleStep, bool enabled){
    ui::W::init(w.get(), min,value,max,singleStep,enabled);
    w->setMinimumWidth(30);
    return this;
}


void ExSpinBoxW::init_connection(const QString &nameParam){connect(w.get(), QOverload<int>::of(&QSpinBox::valueChanged), this, [=]{emit ui_change_signal(nameParam);});}

void ExSpinBoxW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(generatorName.length() > 0){
        w->setMinimum(arg.generator.min.value().toInt());
        w->setMaximum(arg.generator.max.value().toInt());
        w->setSingleStep(arg.generator.step.value().toInt());        
    }
    w->setValue(arg.to_int_value());

    w->blockSignals(false);
}

Arg ExSpinBoxW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(w->value());

    // generator
    if(generatorName.length() > 0){
        arg.generator.min        = QString::number(w->minimum());
        arg.generator.max        = QString::number(w->maximum());
        arg.generator.step = QString::number(w->singleStep());
    }
    return arg;
}

