
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// base
#include "geometry/point3.hpp"

// widgets
#include "ex_float_spin_box_w.hpp"

namespace tool::ex {

class ExVector2dW : public ExItemW<QFrame>{

public:

    ExVector2dW();
    ExVector2dW *init_widget(const QString &title, Vector2dSettings settings={}, bool enabled=true);
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void set_generator(QString genName) override;

    void set_decimals(int d);
    void set_values(geo::Pt2d values);
    void set_steps(geo::Pt2d steps);
    void set_min(geo::Pt2d min);
    void set_max(geo::Pt2d max);

    void init_default_tooltip(QString name) override;


public:

    QLabel *laTitle = nullptr;

    QLabel *xText = nullptr;
    QLabel *yText = nullptr;

    ExFloatSpinBoxW x;
    ExFloatSpinBoxW y;
};

}
