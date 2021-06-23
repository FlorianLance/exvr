
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_slider_w.hpp"

using namespace tool;
using namespace tool::ex;



ExSliderIntegerW::ExSliderIntegerW() : ExItemW<QFrame>(UiType::Slider_integer){

    w->setFrameShadow(QFrame::Raised);
    w->setFrameShape(QFrame::Shape::NoFrame);

    QHBoxLayout *layout = new QHBoxLayout();
    w->setLayout(layout);
    layout->addWidget(title = new QLabel());
    layout->addWidget(minMax = new QLabel());
    layout->addWidget(value = new QSlider());
    value->setOrientation(Qt::Horizontal);
    layout->addWidget(valueTxt = new QLabel());

    layout->setContentsMargins(2,2,2,2);
    layout->setSpacing(2);
}

ExSliderIntegerW *ExSliderIntegerW::init_widget(QString titleV, MinV<int> minV, V<int> valueV, MaxV<int> maxV, StepV<int> stepV){
    title->setText(titleV);
    ui::W::init(value, minV, valueV, maxV, stepV);
    valueTxt->setText(QString::number(valueV.v));
    minMax->setText(QSL("[") % QString::number(minV.v) % QSL(" : ") % QString::number(maxV.v) % QSL("]"));
    return this;
}

void ExSliderIntegerW::init_connection(const QString &nameParam){
    connect(value, &QSlider::valueChanged, this, [&](int value){
        valueTxt->setText(QString::number(value));
        emit ui_change_signal(nameParam);
    });
}

void ExSliderIntegerW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(generatorName.length() > 0){

        if(arg.generator.min.has_value()){
            value->setMinimum(arg.generator.min.value().toInt());
        }

        if(arg.generator.max.has_value()){
            value->setMaximum(arg.generator.max.value().toInt());
        }

        if(arg.generator.step.has_value()){
            value->setSingleStep(arg.generator.step.value().toInt());
        }
    }

    int valueV = arg.to_int_value();
    value->setValue(valueV);
    minMax->setText(QSL("[") % QString::number(value->minimum()) % QSL(" : ") % QString::number(value->maximum()) % QSL("]"));
    valueTxt->setText(QString::number(valueV));

    w->blockSignals(false);
}

Arg ExSliderIntegerW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(value->value());

    // generator
    if(generatorName.length() > 0){
        arg.generator.min   = QString::number(value->minimum());
        arg.generator.max   = QString::number(value->maximum());
        arg.generator.step  = QString::number(value->singleStep());
    }

    return arg;
}

void ExSliderIntegerW::init_default_tooltip(QString name){

    const QString tooltip = QSL("name: ") % name % QSL("  C# type: ") % from_view(get_tooltip_string(type));
    title->setToolTipDuration(-1);
    title->setToolTip(tooltip);
    minMax->setToolTipDuration(-1);
    minMax->setToolTip(tooltip);
    valueTxt->setToolTipDuration(-1);
    valueTxt->setToolTip(tooltip);
    value->setToolTipDuration(-1);
    value->setToolTip(tooltip);
}

ExSliderFloatW::ExSliderFloatW() : ExItemW<QFrame>(UiType::Slider_double){

    w->setFrameShadow(QFrame::Raised);
    w->setFrameShape(QFrame::Shape::NoFrame);

    QHBoxLayout *layout = new QHBoxLayout();
    w->setLayout(layout);
    layout->addWidget(title = new QLabel());
    layout->addWidget(minMax = new QLabel());
    layout->addWidget(value = new QSlider());
    value->setOrientation(Qt::Horizontal);
    layout->addWidget(valueTxt = new QLabel());
}

ExSliderFloatW *ExSliderFloatW::init_widget(QString titleV, MinV<qreal> minV, V<qreal> valueV, MaxV<qreal> maxV, StepV<qreal> stepV){

    title->setText(titleV);

    m_min = minV.v;
    m_max = maxV.v;
    m_step = stepV.v;

    const qreal diff = (m_max-m_min);
    m_nbSteps = static_cast<int>(diff/m_step);
    ui::W::init(value, MinV<int>{0}, V<int>{static_cast<int>((valueV.v-m_min)/diff*m_nbSteps)}, MaxV<int>{m_nbSteps},  StepV<int>{1});
    minMax->setText(QSL("[") % QString::number(minV.v) % QSL(" : ") % QString::number(maxV.v) % QSL("]"));
    valueTxt->setText(QString::number(valueV.v));

    return this;
}

QString ExSliderFloatW::value_to_string() const {
    qreal dVal = m_min + (1.0*value->value()/m_nbSteps) * (m_max-m_min);
    return QString::number(dVal);
}

void ExSliderFloatW::init_connection(const QString &nameParam){

    connect(value, &QSlider::valueChanged, this, [&](int value){
        qreal dVal = m_min + (1.0*value/m_nbSteps) * (m_max-m_min);
        valueTxt->setText(QString::number(dVal));
        emit ui_change_signal(nameParam);
    });
}

void ExSliderFloatW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    qreal valueV = arg.to_double_value();

    if(generatorName.length() > 0){

        if(arg.generator.min.has_value()){
            m_min = arg.generator.min.value().toDouble();
        }

        if(arg.generator.max.has_value()){
            m_max = arg.generator.max.value().toDouble();
        }

        if(arg.generator.step.has_value()){
            m_step = arg.generator.step.value().toDouble();
        }

        m_nbSteps = static_cast<int>((m_max-m_min)/m_step);
    }

    ui::W::init(value, MinV<int>{0}, V<int>{static_cast<int>((valueV/m_max)*m_nbSteps)}, MaxV<int>{m_nbSteps},  StepV<int>{1});
    minMax->setText(QSL("[") % QString::number(m_min) % QSL(" : ") % QString::number(m_max) % QSL("]"));
    valueTxt->setText(QString::number(valueV));

    w->blockSignals(false);

}

Arg ExSliderFloatW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(static_cast<float>(m_min + (1.0*value->value()/m_nbSteps) * (m_max-m_min)));

    // generator
    if(generatorName.length() > 0){
        arg.generator.min   = QString::number(m_min);
        arg.generator.max   = QString::number(m_max);
        arg.generator.step  = QString::number(m_step);
    }

    return arg;
}

void ExSliderFloatW::init_default_tooltip(QString name){

    const QString tooltip = QSL("name: ") % name % QSL("  C# type: ") % from_view(get_tooltip_string(type));
    title->setToolTipDuration(-1);
    title->setToolTip(tooltip);
    minMax->setToolTipDuration(-1);
    minMax->setToolTip(tooltip);
    valueTxt->setToolTipDuration(-1);
    valueTxt->setToolTip(tooltip);
    value->setToolTipDuration(-1);
    value->setToolTip(tooltip);
}

#include "moc_ex_slider_w.cpp"
