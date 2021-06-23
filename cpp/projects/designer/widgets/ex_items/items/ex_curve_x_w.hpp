
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

#include "ex_item_w.hpp"

// QWt
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

// local
#include "ex_line_edit_w.hpp"
#include "ex_spin_box_w.hpp"
#include "ex_double_spin_box_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_select_color_w.hpp"

namespace tool::ex{


class CurveXW : public QwtPlot{

    Q_OBJECT

public:

    std_v1<double> xCoords;
    std_v1<double> yCoords;

    CurveXW();


public slots:

    void set_y_range(qreal min, qreal max, bool autoMinMax);
    void set_line_color(QColor color);
    void set_max_size(int maxSize);
    void add_value(qreal y);
    void add_values(const std_v1<double> &yValues);
    void clear();

    void update_y_scale_from_min_max();

private:
    QwtPlotCurve m_curve;
    int m_maxSize = 100;
    bool m_autoMinMax = true;

};

class CurveXManagerW : public QWidget{
public:

    CurveXManagerW();

    ExLineEditW name;
    CurveXW curve;
    ExDoubleSpinBoxW minY;
    ExDoubleSpinBoxW maxY;
    ExCheckBoxW automaticMinMax;
    ExSpinBoxW sizeMax;
    ExSelectColorW color;
};


class ExCurveXW : public ExItemW<CurveXManagerW>{

Q_OBJECT
public :

    ExCurveXW() : ExItemW<CurveXManagerW>(UiType::Curve){}
    ExCurveXW  *init_widget(QString title, bool enabled = true);
    std::optional<Arg> generate_init_arg_from_dialog(QStringList othersParameters) override;
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;


signals:

    void name_changed_signal(QString name);

};


}
