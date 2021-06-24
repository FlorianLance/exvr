
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

#include "ex_item_w.hpp"

// Qt
#include <QMouseEvent>

// QWt
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_curve_fitter.h>

// local
#include "ex_double_spin_box_w.hpp"
#include "ex_checkbox_w.hpp"

namespace tool::ex{


class CurveW : public QwtPlot{

    Q_OBJECT
public:

    std_v1<double> xCoords = {0,1};
    std_v1<double> yCoords = {0,1};

    CurveW();
    void mousePressEvent(QMouseEvent *event) override;

signals:

    void point_added_signal();
    void point_removed_signal();

private:

    double minScaleX = 0.;
    double maxScaleX = 1.;

    double minScaleY = 0.;
    double maxScaleY = 1.;

public slots:

    void reset();

    void add_point(double x, double y);
    void set_points(std_v1<double> x, std_v1<double> y);

    void set_first_y(double value);
    void set_last_y(double value);

    void set_fitted_state(bool state);
    void set_title(QString title);
    void set_x_title(QString title);
    void set_y_title(QString title);
    void set_x_range(qreal min, qreal max);
    void set_y_range(qreal min, qreal max);

    void remove_symbol();

private:

    QwtPlotCurve curve;
    bool sort = true;
    bool fitted = true;
};


class ExCurveW : public ExItemW<QFrame>{

public :

    ExCurveW() : ExItemW<QFrame>(UiType::Curve){}
    ExCurveW  *init_widget(QString title, QString xTitle = "x", QString yTitle = "y", geo::Pt2d xRange = {0,1}, geo::Pt2d yRange = {0,1}, bool enabled = true);
    std::optional<Arg> generate_init_arg_from_dialog(QStringList othersParameters) override;
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;

    // curve
    CurveW *curve        = nullptr;
    // actions
    QPushButton *resetB = nullptr;
    QPushButton *addPointB = nullptr;
//    QPushButton *presetSinusB = nullptr;
    // range x    
    ExDoubleSpinBoxW minX;
    ExDoubleSpinBoxW maxX;
    // range y
    ExDoubleSpinBoxW minY;
    ExDoubleSpinBoxW maxY;
    // first/last y
    ExDoubleSpinBoxW firstY;
    ExDoubleSpinBoxW lastY;
    // point to add
    ExDoubleSpinBoxW addX;
    ExDoubleSpinBoxW addY;
    // settings
    ExCheckBoxW fitted;
//    ExCheckBoxW relative;
};


}


