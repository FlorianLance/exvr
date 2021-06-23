
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_curve_x_w.hpp"

// Qt
#include <QSizePolicy>

// Qwt
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_curve_fitter.h>

// base
#include "geometry/point2.hpp"

#include <iostream>

using namespace tool;
using namespace tool::ex;

CurveXW::CurveXW(){

    setCanvasBackground( Qt::gray );
    setAxisScale( QwtPlot::xBottom, 0.0, m_maxSize);
    setAxisScale( QwtPlot::yLeft, -10.0, 10.0);

    QFont axisFont("Times", 8);
    setAxisFont(QwtPlot::xBottom, axisFont);
    setAxisFont(QwtPlot::yLeft, axisFont);

    m_curve.setTitle("");
    m_curve.setPen( Qt::black, 4 );
    m_curve.setRenderHint( QwtPlotItem::RenderAntialiased, true );
    m_curve.setCurveAttribute(QwtPlotCurve::Fitted, false);
    m_curve.setSymbol( nullptr );
    m_curve.attach(this);
}

void CurveXW::CurveXW::set_y_range(qreal min, qreal max, bool autoMinMax){

    m_autoMinMax = autoMinMax;

    if(m_autoMinMax){
        update_y_scale_from_min_max();
    }else{
        if(min < max){
            setAxisScale( QwtPlot::yLeft, min, max);
        }
    }

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveXW::set_line_color(QColor color){
    m_curve.setPen(color, 4);
}

void CurveXW::set_max_size(int maxSize){

    // update max size
    m_maxSize = maxSize;

    // resize x coordinates
    if(static_cast<int>(xCoords.size()) != m_maxSize){
        xCoords.resize(static_cast<size_t>(m_maxSize));
        std::iota(std::begin(xCoords), std::end(xCoords), 0.);
    }

    // resize y coordinates
    if(yCoords.size() > static_cast<size_t>(maxSize)){
        yCoords.erase(std::begin(yCoords), std::begin(yCoords) + static_cast<int>(yCoords.size()) - maxSize);
    }

    setAxisScale( QwtPlot::xBottom, 0.0, m_maxSize);

    m_curve.setSamples(xCoords.data(), yCoords.data(), static_cast<int>(yCoords.size()));

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveXW::clear(){

    yCoords.clear();
    m_curve.setSamples(xCoords.data(), yCoords.data(), static_cast<int>(yCoords.size()));

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveXW::update_y_scale_from_min_max(){

    if(yCoords.size() == 0){
        return;
    }

    const auto [minI, maxI] = std::minmax_element(std::begin(yCoords), std::end(yCoords));

    auto min = *minI;
    auto max = *maxI;
    auto diff = max-min;
    min -= diff * 0.1;
    max += diff * 0.1;
    setAxisScale( QwtPlot::yLeft, min, max );

}


void CurveXW::add_value(qreal value){

    // add value at the end
    yCoords.emplace_back(value);

    // remove first value if set too large
    if(static_cast<int>(yCoords.size()) > m_maxSize){
        yCoords.erase(std::begin(yCoords), std::begin(yCoords)+1);
    }

    // resize x coordinates
    if(static_cast<int>(xCoords.size()) != m_maxSize){
        xCoords.resize(static_cast<size_t>(m_maxSize));
        std::iota(std::begin(xCoords), std::end(xCoords), 0.);
    }

    // update curve
    m_curve.setSamples(xCoords.data(), yCoords.data(), static_cast<int>(yCoords.size()));

    // update auto scale
    if(m_autoMinMax){
        update_y_scale_from_min_max();
    }

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveXW::add_values(const std_v1<double> &yValues){

    if(yValues.size() == 0){
        return;
    }

    // add values at the end
    yCoords.insert(std::end(yCoords), std::begin(yValues), std::end(yValues));

    // remove first values if set too large
    if(static_cast<int>(yCoords.size()) > m_maxSize){
        yCoords.erase(std::begin(yCoords), std::begin(yCoords) + static_cast<int>(yCoords.size()) - m_maxSize);
    }

    // resize x coordinates
    if(static_cast<int>(xCoords.size()) != m_maxSize){
        xCoords.resize(static_cast<size_t>(m_maxSize));
        std::iota(std::begin(xCoords), std::end(xCoords), 0.);
    }

    // update curve
    m_curve.setSamples(xCoords.data(), yCoords.data(), static_cast<int>(yCoords.size()));

    // update auto scale
    if(m_autoMinMax){
        update_y_scale_from_min_max();
    }

    QwtPlot::replot();
    QwtPlot::repaint();
}


CurveXManagerW::CurveXManagerW(){

    auto layout = ui::L::VB();
    setLayout(layout);

    layout->setStretch(0,1);
    layout->setStretch(1,40);
    layout->setStretch(2,1);
    layout->setStretch(3,1);

    layout->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("Title:"), name()}, LStretch{false}, LMargins{false}));
    layout->addWidget(&curve);
    curve.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    layout->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("Min Y:"), minY(), ui::W::txt("Max Y:"), maxY(), automaticMinMax()}, LStretch{true}, LMargins{false}));
    layout->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("Max size:"), sizeMax(), ui::W::txt("Curve color:"), color()}, LStretch{true}, LMargins{false}));
}

ExCurveXW *ExCurveXW::init_widget(QString title, bool enabled){

    QwtText titleC(title);

    QFont titleFont("Times", 9, QFont::Bold);
    titleC.setFont(titleFont);
    w->curve.setTitle("");
    w->setEnabled(enabled);

    w->minY.init_widget(MinV<qreal>{-100000.}, V<qreal>{-10.}, MaxV<qreal>{100000}, StepV<qreal>{0.1}, 5);
    w->maxY.init_widget(MinV<qreal>{-100000.}, V<qreal>{10.}, MaxV<qreal>{100000}, StepV<qreal>{0.1}, 5);
    w->automaticMinMax.init_widget("Auto", true);
    w->sizeMax.init_widget(MinV<int>{10}, V<int>{100}, MaxV<int>{5000}, StepV<int>{1});
    w->name.init_widget(QSL("Default curve"));
    w->color.init_widget(QSL("Curve color"), Qt::black);


    return this;
}

std::optional<Arg> ExCurveXW::generate_init_arg_from_dialog(QStringList othersParameters){
    GenUIItemDialog genD(QSL("Add ") % from_view(get_name(type)));
    if(genD.show_dialog(std::move(othersParameters))){
        Arg arg = Arg::generate_init_ui_arg(UiElementKey{key()}, type, genD.name());
        arg.set_separator("");
        arg.set_value("");
        return {arg};
    }
    return {};
}

void ExCurveXW::init_connection(const QString &nameParam){

    w->name.init_connection(QSL("name"));
    w->minY.init_connection(QSL("min_x"));
    w->maxY.init_connection(QSL("max_y"));
    w->automaticMinMax.init_connection(QSL("auto"));
    w->sizeMax.init_connection(QSL("size_max"));
    w->color.init_connection(QSL("color"));

    connect(&w->name, &ExLineEditW::ui_change_signal, this, [&,nameParam]{
        emit ui_change_signal(nameParam);
        emit name_changed_signal(w->name.w->text());
    });
    connect(&w->minY, &ExDoubleSpinBoxW::ui_change_signal, this, [&,nameParam]{
        w->curve.set_y_range(w->minY.w->value(), w->maxY.w->value(), w->automaticMinMax.w->isChecked());
        emit ui_change_signal(nameParam);
    });
    connect(&w->maxY, &ExDoubleSpinBoxW::ui_change_signal, this, [&,nameParam]{
        w->curve.set_y_range(w->minY.w->value(), w->maxY.w->value(), w->automaticMinMax.w->isChecked());
        emit ui_change_signal(nameParam);
    });
    connect(&w->automaticMinMax, &ExCheckBoxW::ui_change_signal, this, [&,nameParam]{
        w->curve.set_y_range(w->minY.w->value(), w->maxY.w->value(), w->automaticMinMax.w->isChecked());
        emit ui_change_signal(nameParam);
    });
    connect(&w->sizeMax, &ExSpinBoxW::ui_change_signal, this, [&,nameParam]{
        w->curve.set_max_size(w->sizeMax.w->value());
        emit ui_change_signal(nameParam);
    });
    connect(&w->color, &ExSelectColorW::ui_change_signal, this, [&,nameParam]{
        w->curve.set_line_color(w->color.current_color());
        emit ui_change_signal(nameParam);
    });
}

void ExCurveXW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    const auto split = arg.value().split("%%");
    if(split.size() < 6){
        return;
    }

    w->blockSignals(true);

    auto nameArg    = arg;
    auto minArg     = arg;
    auto maxArg     = arg;
    auto autoArg    = arg;
    auto sizeMaxArg = arg;
    auto colorArg   = arg;

    nameArg.init_from(split[0]);
    minArg.init_from_double_str(split[1]);
    maxArg.init_from_double_str(split[2]);
    autoArg.init_from_bool_str(split[3]);
    sizeMaxArg.init_from_int_str(split[4]);
    colorArg.init_from_color_str(split[5]);

    w->name.blockSignals(true);
    w->minY.blockSignals(true);
    w->maxY.blockSignals(true);
    w->automaticMinMax.blockSignals(true);
    w->sizeMax.blockSignals(true);
    w->color.blockSignals(true);

    w->name.update_from_arg(nameArg);
    w->minY.update_from_arg(minArg);
    w->maxY.update_from_arg(maxArg);
    w->automaticMinMax.update_from_arg(autoArg);
    w->sizeMax.update_from_arg(sizeMaxArg);
    w->color.update_from_arg(colorArg);

    w->name.blockSignals(false);
    w->minY.blockSignals(false);
    w->maxY.blockSignals(false);
    w->automaticMinMax.blockSignals(false);
    w->sizeMax.blockSignals(false);
    w->color.blockSignals(false);

    w->curve.set_y_range(w->minY.w->value(), w->maxY.w->value(), w->automaticMinMax.w->isChecked());    
    w->curve.set_max_size(w->sizeMax.w->value());
    w->curve.set_line_color(w->color.current_color());

    w->blockSignals(false);

    emit name_changed_signal(w->name.w->text());
}

Arg ExCurveXW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();

    const auto nameA = w->name.convert_to_arg();
    const auto minA = w->minY.convert_to_arg();
    const auto maxA = w->maxY.convert_to_arg();        
    const auto autoA = w->automaticMinMax.convert_to_arg();
    const auto sizeMaxA = w->sizeMax.convert_to_arg();
    const auto colorA = w->color.convert_to_arg();
    arg.init_from({nameA.value(),minA.value(),maxA.value(),autoA.value(),sizeMaxA.value(),colorA.value()},"%%");
    return arg;
}

#include "moc_ex_curve_x_w.cpp"

