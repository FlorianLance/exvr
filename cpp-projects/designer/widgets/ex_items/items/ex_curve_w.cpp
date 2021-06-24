
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_curve_w.hpp"

// Qwt
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_curve_fitter.h>


using namespace tool;
using namespace tool::ex;


CurveW::CurveW(){

    setCanvasBackground( Qt::gray );

    QFont axisFont("Calibri", 8);
    setAxisFont(QwtPlot::xBottom,   axisFont);
    setAxisFont(QwtPlot::yLeft,     axisFont);

    curve.setTitle("");
    curve.setPen( Qt::black, 4 );
    curve.setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve.setCurveAttribute(QwtPlotCurve::Fitted, fitted);
    curve.setSymbol( new QwtSymbol(
        QwtSymbol::Ellipse,
        QBrush(Qt::yellow),
        QPen(Qt::red, 2),
        QSize(4, 4))
    );

    setAxisScale( QwtPlot::xBottom, minScaleX, maxScaleX);
    setAxisScale( QwtPlot::yLeft,   minScaleY, maxScaleY);

    QwtSplineCurveFitter *fitter = new QwtSplineCurveFitter();
    fitter->setFitMode(QwtSplineCurveFitter::FitMode::Spline);
    curve.setCurveFitter(fitter);

    curve.setRawSamples(xCoords.data(), yCoords.data(), static_cast<int>(xCoords.size()));
    curve.attach(this);

    QwtPlot::replot();
    QwtPlot::repaint();
}


void CurveW::set_title(QString title){

    QwtText t(title);
    QFont font("Calibri", 10);
    font.setBold(true);
    t.setFont(font);
    setTitle(t);
}

void CurveW::set_x_title(QString title){

    QwtText t(title);
    QFont font("Calibri", 9);
    font.setBold(false);
    t.setFont(font);

    setAxisTitle(QwtPlot::xBottom, t);
}

void CurveW::set_y_title(QString title){

    QwtText t(title);
    QFont font("Calibri", 9);
    font.setBold(false);
    t.setFont(font);

    setAxisTitle(QwtPlot::yLeft, t);
}

void CurveW::set_x_range(qreal min, qreal max){

    minScaleX = min;
    maxScaleX = max;

    // erase values < minScaleX
    int count = 0;
    for(const auto &x : xCoords){
        if(x < minScaleX){
            ++count;
        }
    }

    if(count > 0){
        xCoords.erase(std::begin(xCoords), std::begin(xCoords) + count);
        yCoords.erase(std::begin(yCoords), std::begin(yCoords) + count);
    }

    // erase values > maxScaleX
    int start = -1;
    for(size_t ii = 0; ii < xCoords.size(); ++ii){
        if(xCoords[ii] > maxScaleX){
            start = static_cast<int>(ii);
            break;
        }
    }

    if(start > -1){
        xCoords.erase(std::begin(xCoords) + start, std::end(xCoords));
        yCoords.erase(std::begin(yCoords) + start, std::end(yCoords));
    }

    // set first and last x values
    if(xCoords.size() >= 2){
        xCoords[0] = minScaleX;
        xCoords[xCoords.size()-1] = maxScaleX;
    }else if(xCoords.size() == 1){

        if(std::abs(minScaleX-xCoords[0]) < std::abs(maxScaleX-xCoords[0])){
            yCoords = {yCoords[0], maxScaleY};
        }else{
            yCoords = {minScaleY, yCoords[0]};
        }
        xCoords = {minScaleX, maxScaleX};

    }else{
        xCoords = {minScaleX, maxScaleX};
        yCoords = {minScaleY, maxScaleY};
    }

    setAxisScale( QwtPlot::xBottom, minScaleX, maxScaleX);
    if(xCoords.size() > 1){
        curve.setRawSamples(xCoords.data(), yCoords.data(), static_cast<int>(xCoords.size()));
    }

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveW::set_y_range(qreal min, qreal max){

    if(min > max){
        min = max - 0.01;
    }

    minScaleY = min;
    maxScaleY = max;

    for(auto &y: yCoords){
        if(y < minScaleY){
            y = minScaleY;
        }
        if(y > maxScaleY){
            y = maxScaleY;
        }
    }

    setAxisScale( QwtPlot::yLeft, minScaleY, maxScaleY);
    if(xCoords.size() > 1){
        curve.setRawSamples(xCoords.data(), yCoords.data(), static_cast<int>(xCoords.size()));
    }

    QwtPlot::replot();
    QwtPlot::repaint();
}


void CurveW::mousePressEvent(QMouseEvent *event){

    if(!canvas()->geometry().contains(event->pos())){
        return;
    }

    auto pos = event->pos()-canvas()->pos();
    QPointF pt(
        1.*pos.x()/canvas()->width(),
        1. - 1.*pos.y()/canvas()->height()
    );

    const auto diffScaleX = maxScaleX - minScaleX;
    const auto diffScaleY = maxScaleY - minScaleY;
    const auto rPosX      = minScaleX + pt.x()*diffScaleX;
    const auto rPosY      = minScaleY + pt.y()*diffScaleY;

    if(event->button() == Qt::MouseButton::LeftButton){

        for(size_t ii = 0; ii < xCoords.size(); ++ii){

            if(xCoords[ii] > rPosX){
                xCoords.insert(std::begin(xCoords) + static_cast<int>(ii), rPosX);
                yCoords.insert(std::begin(yCoords) + static_cast<int>(ii), rPosY);
                break;
            }
        }

        emit point_added_signal();

    }else if(event->button() == Qt::MouseButton::RightButton){

        double min = 0.1;
        int index = -1;

        for(size_t ii = 0; ii < xCoords.size(); ++ii){

            const auto &px = (xCoords[ii]-minScaleX)/diffScaleX;
            const auto &py = (yCoords[ii]-minScaleY)/diffScaleY;
            double dist = geo::norm(geo::Pt2<double>{pt.x()-px, pt.y()-py});
            if(dist < min){
                min = dist;
                index = static_cast<int>(ii);
            }
        }

        if(index > -1 && index != 0 && (index < static_cast<int>(xCoords.size())-1)){
            xCoords.erase(std::begin(xCoords) + index);
            yCoords.erase(std::begin(yCoords) + index);
        }

        emit point_removed_signal();
    }

    curve.setRawSamples(xCoords.data(), yCoords.data(), static_cast<int>(xCoords.size()));
    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveW::reset(){

    xCoords = {minScaleX, maxScaleX};
    yCoords = {minScaleY, maxScaleY};
    curve.setRawSamples(xCoords.data(), yCoords.data(), static_cast<int>(xCoords.size()));

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveW::add_point(double x, double y){

    size_t id = 0;
    for(size_t ii = 0; ii < xCoords.size(); ++ii){
        if(x < xCoords[ii]){
            id = ii;
            break;
        }
    }
    xCoords.insert(std::begin(xCoords) + id, x);
    yCoords.insert(std::begin(yCoords) + id, y);

    curve.setRawSamples(xCoords.data(), yCoords.data(), static_cast<int>(xCoords.size()));

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveW::set_points(std_v1<double> x, std_v1<double> y){

    xCoords = x;
    yCoords = y;
    curve.setRawSamples(xCoords.data(), yCoords.data(), static_cast<int>(xCoords.size()));

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveW::set_first_y(double value){

    yCoords[0] = value;
    curve.setRawSamples(xCoords.data(), yCoords.data(), static_cast<int>(xCoords.size()));

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveW::set_last_y(double value){

    yCoords[yCoords.size()-1] = value;
    curve.setRawSamples(xCoords.data(), yCoords.data(), static_cast<int>(xCoords.size()));

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveW::set_fitted_state(bool state){

    fitted = state;
    curve.setCurveAttribute(QwtPlotCurve::Fitted, state);

    QwtPlot::replot();
    QwtPlot::repaint();
}

void CurveW::remove_symbol(){

    curve.setSymbol(nullptr);

    QwtPlot::replot();
    QwtPlot::repaint();
}


ExCurveW *ExCurveW::init_widget(QString title, QString xTitle, QString yTitle, geo::Pt2d xRange, geo::Pt2d yRange, bool enabled){

    // generate widgets
    curve = new CurveW();
    auto f1  = ui::F::gen_frame(ui::L::HB(), {{ui::W::txt("<b>Range X axis:</b>"),1}},   0, LMarginsD{0,0,0,0,2});
    auto f2  = ui::F::gen_frame(ui::L::HB(), { {ui::W::txt("min"),1}, {minX(), 10}, {ui::W::txt("max"),1}, {maxX(),10}},   0, LMarginsD{0,0,0,0,2});
    auto f3  = ui::F::gen_frame(ui::L::HB(), {{ui::W::txt("<b>Range Y axis:</b>"),1}},   0, LMarginsD{0,0,0,0,2});
    auto f4  = ui::F::gen_frame(ui::L::HB(), { {ui::W::txt("min"),1}, {minY(), 10}, {ui::W::txt("max"),1}, {maxY(),10}},   0, LMarginsD{0,0,0,0,2});
    auto f5  = ui::F::gen_frame(ui::L::HB(), {{ui::W::txt("<b>Y values:</b>"),1}},   0, LMarginsD{0,0,0,0,2});
    auto f6  = ui::F::gen_frame(ui::L::HB(), {{ui::W::txt("first"),1},{firstY(),10}, {ui::W::txt("last"),1},{lastY(), 10}},  0, LMarginsD{0,0,0,0,2});
    auto f7  = ui::F::gen_frame(ui::L::HB(), {{ui::W::txt("<b>Add specific point:</b>"),1}},   0, LMarginsD{0,0,0,0,2});
    auto f8  = ui::F::gen_frame(ui::L::HB(), { {ui::W::txt("X"),1}, {addX(), 10}, {ui::W::txt("Y"),1}, {addY(),10}},   0, LMarginsD{0,0,0,0,2});
    auto f9  = ui::F::gen_frame(ui::L::HB(), {{addPointB  = new QPushButton("Add point"),1}, {resetB  = new QPushButton("Reset points"),2}},  0, LMarginsD{0,0,0,0,2});
    auto f10 = ui::F::gen_frame(ui::L::HB(), {{ui::W::txt("<b>Others:</b>"),1}},   0, LMarginsD{0,0,0,0,2});
    auto f11 = ui::F::gen_frame(ui::L::HB(), {{fitted(),1}},  0, LMarginsD{0,0,0,0,2});
    auto f12 = ui::F::gen_frame(ui::L::HB(), {{ui::W::txt("<b>Infos:</b>"),1}},   0, LMarginsD{0,0,0,0,2});
    auto f13 = ui::F::gen_frame(ui::L::HB(), {{ui::W::txt("Add point with left click"),1}},  0, LMarginsD{0,0,0,0,2});
    auto f14 = ui::F::gen_frame(ui::L::HB(), {{ui::W::txt("Remove point with right click"),1}},  0, LMarginsD{0,0,0,0,2});
    auto fControl = ui::F::gen_frame(ui::L::VB(), {f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14},
            LStretchD{}, LMarginsD{4,4,4,4}, QFrame::Shape::Box);

    // init widets
    auto diffRangeX = xRange.y() - xRange.x();
    auto diffRangeY = yRange.y() - yRange.x();
    // # range
    minX.init_widget(MinV<qreal>{-100000.}, V<qreal>{xRange.x()}, MaxV<qreal>{100000.}, StepV<qreal>{diffRangeX*0.01}, 3);
    maxX.init_widget(MinV<qreal>{-100000.}, V<qreal>{xRange.y()}, MaxV<qreal>{100000.}, StepV<qreal>{diffRangeX*0.01}, 3);
    minY.init_widget(MinV<qreal>{-100000.}, V<qreal>{yRange.x()}, MaxV<qreal>{100000.}, StepV<qreal>{diffRangeY*0.01}, 3);
    maxY.init_widget(MinV<qreal>{-100000.}, V<qreal>{yRange.y()}, MaxV<qreal>{100000.}, StepV<qreal>{diffRangeY*0.01}, 3);
    minX.editFinishedSignal = false;
    maxX.editFinishedSignal = false;
    minY.editFinishedSignal = false;
    maxY.editFinishedSignal = false;
    // # first/last
    firstY.init_widget(MinV<qreal>{-100000.}, V<qreal>{yRange.x()}, MaxV<qreal>{100000.}, StepV<qreal>{diffRangeY*0.01}, 3);
    lastY.init_widget(MinV<qreal>{-100000.},  V<qreal>{yRange.y()}, MaxV<qreal>{100000.}, StepV<qreal>{diffRangeY*0.01}, 3);
    // # add
    addX.init_widget(MinV<qreal>{-100000.}, V<qreal>{diffRangeX*0.5}, MaxV<qreal>{100000.}, StepV<qreal>{diffRangeY*0.01}, 3);
    addY.init_widget(MinV<qreal>{-100000.},  V<qreal>{diffRangeX*0.5}, MaxV<qreal>{100000.}, StepV<qreal>{diffRangeY*0.01}, 3);
    // # actions
    resetB->setMinimumWidth(150);
    fitted.init_widget("fitted ", true);

    // add widgets to layout
    auto mainL = new QHBoxLayout();
    w->setLayout(mainL);
    mainL->addWidget(ui::F::gen(ui::L::HB(), {curve}, LStretch{false}, LMargins{false}, QFrame::Box));
    mainL->addWidget(fControl);
    mainL->setStretch(0, 3);
    mainL->setStretch(1, 1);

    resetB->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    // # curve
    curve->set_title(title);
    curve->set_x_title(xTitle);
    curve->set_y_title(yTitle);
    curve->set_x_range(xRange.x(), xRange.y());
    curve->set_y_range(yRange.x(), yRange.y());
    curve->set_points({xRange.x(), xRange.y()}, {yRange.x(), yRange.y()});


    w->setEnabled(enabled);

    return this;
}

std::optional<Arg> ExCurveW::generate_init_arg_from_dialog(QStringList othersParameters){
    GenUIItemDialog genD(QSL("Add ") % from_view(get_name(type)));
    if(genD.show_dialog(std::move(othersParameters))){
        auto arg = Arg::generate_init_ui_arg(UiElementKey{key()}, type, genD.name());
        arg.set_separator("");
        arg.set_value("");
        return {arg};
    }
    return {};
}

void ExCurveW::init_connection(const QString &nameParam){

    minX.init_connection(QSL("min_x"));
    maxX.init_connection(QSL("max_x"));
    minY.init_connection(QSL("min_y"));
    maxY.init_connection(QSL("max_y"));
    firstY.init_connection(QSL("first_y"));
    lastY.init_connection(QSL("last_y"));
    fitted.init_connection(QSL("fitted"));

    connect(&fitted, &ExCheckBoxW::ui_change_signal, this, [&,nameParam]{
        curve->set_fitted_state(fitted.w->isChecked());
        emit ui_change_signal(nameParam);
    });
    connect(curve, &CurveW::point_added_signal, this, [=]{
        emit ui_change_signal(nameParam);
    });
    connect(curve, &CurveW::point_removed_signal, this, [=]{
        emit ui_change_signal(nameParam);
    });
    connect(&minX,  &ExDoubleSpinBoxW::ui_change_signal, this, [&,nameParam]{

        minX.blockSignals(true);
        if(minX.w->value() > maxX.w->value()){
           minX.w->setValue(maxX.w->value()-0.01);
        }
        minX.blockSignals(false);

        curve->set_x_range(minX.w->value(), maxX.w->value());
        emit ui_change_signal(nameParam);
    });
    connect(&maxX,  &ExDoubleSpinBoxW::ui_change_signal, this, [&,nameParam]{

        maxX.blockSignals(true);
        if(minX.w->value() > maxX.w->value()){
           maxX.w->setValue(minX.w->value()+0.01);
        }
        maxX.blockSignals(false);

        curve->set_x_range(minX.w->value(), maxX.w->value());
        emit ui_change_signal(nameParam);
    });
    connect(&minY,  &ExDoubleSpinBoxW::ui_change_signal, this, [&,nameParam]{

        minY.blockSignals(true);
        if(minY.w->value() > maxY.w->value()){
           minY.w->setValue(maxY.w->value()-0.01);
        }
        minY.blockSignals(false);

        firstY.blockSignals(true);
        firstY.blockSignals(true);
        const auto diff = maxY.w->value() - minY.w->value();
        firstY.w->setRange(minY.w->value(), maxY.w->value());
        lastY.w->setRange(minY.w->value(), maxY.w->value());
        firstY.w->setSingleStep(diff*0.01);
        lastY.w->setSingleStep(diff*0.01);
        firstY.blockSignals(false);
        firstY.blockSignals(false);

        curve->set_y_range(minY.w->value(), maxY.w->value());
        emit ui_change_signal(nameParam);
    });
    connect(&maxY,  &ExDoubleSpinBoxW::ui_change_signal, this, [&,nameParam]{

        maxY.blockSignals(true);
        if(minY.w->value() > maxY.w->value()){
           maxY.w->setValue(minY.w->value()+0.01);
        }
        maxY.blockSignals(false);

        firstY.blockSignals(true);
        lastY.blockSignals(true);

        const auto diff = maxY.w->value() - minY.w->value();
        firstY.w->setRange(minY.w->value(), maxY.w->value());
        lastY.w->setRange(minY.w->value(), maxY.w->value());        
        firstY.w->setSingleStep(diff*0.01);
        lastY.w->setSingleStep(diff*0.01);

        addX.w->setRange(minX.w->value(), maxX.w->value());
        addY.w->setRange(minY.w->value(), maxY.w->value());
        addX.w->setSingleStep(diff*0.01);
        addY.w->setSingleStep(diff*0.01);

        firstY.blockSignals(false);
        lastY.blockSignals(false);

        curve->set_y_range(minY.w->value(), maxY.w->value());
        emit ui_change_signal(nameParam);
    });
    connect(&firstY,  &ExDoubleSpinBoxW::ui_change_signal, this, [&,nameParam]{
        double v = firstY.w->value();
        if(v < minY.w->value()){
            v = minY.w->value();
        }
        if(v > maxY.w->value()){
            v = maxY.w->value();
        }
        curve->set_first_y(v);
        emit ui_change_signal(nameParam);
    });
    connect(&lastY,  &ExDoubleSpinBoxW::ui_change_signal, this, [&,nameParam]{
        double v = lastY.w->value();
        if(v < minY.w->value()){
            v = minY.w->value();
        }
        if(v > maxY.w->value()){
            v = maxY.w->value();
        }
        curve->set_last_y(v);
        emit ui_change_signal(nameParam);
    });

    connect(addPointB,    &QPushButton::clicked,   this, [&]{
        curve->add_point(addX.w->value(), addY.w->value());
    });

    connect(resetB,    &QPushButton::clicked,   this, [&]{

        firstY.blockSignals(true);
        lastY.blockSignals(true);
        firstY.w->setValue(minY.w->value());
        lastY.w->setValue(maxY.w->value());
        firstY.blockSignals(false);
        lastY.blockSignals(false);

        curve->reset();
    });
}

void ExCurveW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    auto pts = arg.to_curve_value();

    if(pts.first.size() < 2){
        pts.first = {0,1};
    }
    if(pts.second.size() < 2){
        pts.second = {0,1};
    }

    auto minXV = minX.w->value();
    auto maxXV = maxX.w->value();

    auto minYV = minY.w->value();
    auto maxYV = maxY.w->value();

    for(const auto & v : pts.first){
        if(v < minXV){
            minXV = v;
        }
        if(v > maxXV){
            maxXV = v;
        }
    }

    for(const auto & v : pts.second){
        if(v < minYV){
            minYV = v;
        }
        if(v > maxYV){
            maxYV = v;
        }
    }

    auto diffX = maxXV - minXV;
    auto diffY = maxYV - minYV;

    minX.blockSignals(true);
    maxX.blockSignals(true);
    minY.blockSignals(true);
    maxY.blockSignals(true);
    firstY.blockSignals(true);
    lastY.blockSignals(true);

    minX.w->setValue(minXV);
    maxX.w->setValue(maxXV);
    minY.w->setValue(minYV);
    maxY.w->setValue(maxYV);
    firstY.w->setValue(pts.second[0]);
    lastY.w->setValue(pts.second[pts.second.size()-1]);

    minX.w->setSingleStep(diffX*0.01);
    maxX.w->setSingleStep(diffX*0.01);
    minY.w->setSingleStep(diffY*0.01);
    maxY.w->setSingleStep(diffY*0.01);
    firstY.w->setSingleStep(diffY*0.01);
    lastY.w->setSingleStep(diffY*0.01);

    firstY.blockSignals(false);
    lastY.blockSignals(false);
    minY.blockSignals(false);
    maxY.blockSignals(false);
    minX.blockSignals(false);
    maxX.blockSignals(false);

    curve->set_x_range(minXV, maxXV);
    curve->set_y_range(minYV, maxYV);
    curve->set_points(std::move(pts.first), std::move(pts.second));

    w->blockSignals(false);
}

Arg ExCurveW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from_curve(&curve->xCoords, &curve->yCoords, " ");
    return arg;
}

#include "moc_ex_curve_w.cpp"

