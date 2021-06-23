
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_vector2d_w.hpp"

using namespace tool;
using namespace tool::ex;

ExVector2dW::ExVector2dW() : ExItemW<QFrame>(UiType::Vector2D){

    w->setFrameShadow(QFrame::Raised);
    w->setFrameShape(QFrame::Shape::NoFrame);

    QHBoxLayout *layout = new QHBoxLayout();
    w->setLayout(layout);
    layout->addWidget(laTitle = ui::W::txt(""));
    ui::L::stretch(layout);
    layout->addWidget(xText = ui::W::txt("x:"));
    layout->addWidget(x());
    layout->addWidget(yText = ui::W::txt("y:"));
    layout->addWidget(y());
    layout->setContentsMargins(0,0,0,0);

    connect(&x, &ExBaseW::ui_change_signal ,this, &ExBaseW::ui_change_signal);
    connect(&y, &ExBaseW::ui_change_signal ,this, &ExBaseW::ui_change_signal);
}

ExVector2dW *ExVector2dW::init_widget(const QString &title, Vector2dSettings settings, bool enabled){
    laTitle->setText(title);
    w->setEnabled(enabled);
    x.init_widget(settings.sX);
    y.init_widget(settings.sY);
    return this;
}

void ExVector2dW::init_connection(const QString &nameParam){
    x.init_connection(nameParam);
    y.init_connection(nameParam);
}


void ExVector2dW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    auto args = arg.split_value_to_atoms_args();
    if(args.size() != 2){
        qWarning() << "Invalid argument value " << arg.value() << " for vector2D widget : " << arg.name ;
        return;
    }

    w->blockSignals(true);

    if(generatorName.length() > 0){

        if(arg.generator.decimals.has_value()){
            const auto value = arg.generator.decimals.value().toInt();
            x.w->setDecimals(value);
            y.w->setDecimals(value);
        }

        if(arg.generator.min.has_value()){
            const auto value = arg.generator.min.value().toDouble();
            x.w->setMinimum(value);
            y.w->setMinimum(value);
        }

        if(arg.generator.max.has_value()){
            const auto value = arg.generator.max.value().toDouble();
            x.w->setMaximum(value);
            y.w->setMaximum(value);
        }

        if(arg.generator.step.has_value()){
            const auto value = arg.generator.step.value().toDouble();
            x.w->setSingleStep(value);
            y.w->setSingleStep(value);
        }
    }

    x.update_from_arg(args[0]);
    y.update_from_arg(args[1]);

    w->blockSignals(false);
}

Arg ExVector2dW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from_args({x.convert_to_arg(),
                        y.convert_to_arg()}, " ", UnityType::System_single);

    // generator
    if(generatorName.length() > 0){
        arg.generator.min        = QString::number(x.w->minimum());
        arg.generator.max        = QString::number(x.w->maximum());
        arg.generator.step = QString::number(x.w->singleStep());
        arg.generator.decimals   = QString::number(x.w->decimals());
    }
    return arg;
}

void ExVector2dW::set_generator(QString genName){

    ExItemW::set_generator(genName);
    x.set_generator(genName);
    y.set_generator(genName);
}

void ExVector2dW::set_decimals(int d){
    x.blockSignals(true);
    y.blockSignals(true);
    x.w->setDecimals(d);
    y.w->setDecimals(d);
    x.blockSignals(false);
    y.blockSignals(false);
}

void ExVector2dW::set_values(geo::Pt2d values){
    x.blockSignals(true);
    y.blockSignals(true);
    x.w->setValue(values.x());
    y.w->setValue(values.y());
    x.blockSignals(false);
    y.blockSignals(false);
}

void ExVector2dW::set_steps(geo::Pt2d steps){
    x.blockSignals(true);
    y.blockSignals(true);
    x.w->setSingleStep(steps.x());
    y.w->setSingleStep(steps.y());
    x.blockSignals(false);
    y.blockSignals(false);
}

void ExVector2dW::set_min(geo::Pt2d min){
    x.blockSignals(true);
    y.blockSignals(true);
    x.w->setMinimum(min.x());
    y.w->setMinimum(min.y());
    x.blockSignals(false);
    y.blockSignals(false);
}

void ExVector2dW::set_max(geo::Pt2d max){
    x.blockSignals(true);
    y.blockSignals(true);
    x.w->setMaximum(max.x());
    y.w->setMaximum(max.y());
    x.blockSignals(false);
    y.blockSignals(false);
}

void ExVector2dW::init_default_tooltip(QString name){
    const QString tooltip = QSL("name: ") % name % QSL("  C# type: ") % from_view(get_tooltip_string(type));
    x.init_tooltip(tooltip);
    y.init_tooltip(tooltip);
}
