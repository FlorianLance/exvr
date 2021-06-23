
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

class ExVector3dW : public ExItemW<QFrame>{

public:

    constexpr static DsbSettings DefautlTraV = {MinV<qreal>{-10000.}, V<qreal>{0}, MaxV<qreal>{10000.}, StepV<qreal>{0.01}, 3};
    constexpr static DsbSettings DefaultRotV = {MinV<qreal>{-10000.}, V<qreal>{0}, MaxV<qreal>{10000.}, StepV<qreal>{0.1},  3};
    constexpr static DsbSettings DefaultScaV = {MinV<qreal>{-10000.}, V<qreal>{1}, MaxV<qreal>{10000.}, StepV<qreal>{0.01}, 3};

    ExVector3dW();
    ExVector3dW *init_widget(const QString &title, Vector3dSettings settings={}, bool enabled=true);
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void set_generator(QString genName) override;

    void set_decimals(int d);
    void set_values(geo::Pt3d values);
    void set_steps(geo::Pt3d steps);
    void set_min(geo::Pt3d min);
    void set_max(geo::Pt3d max);
    void set_enable_state(geo::Pt3<bool> states);

    geo::Pt3d values()const;

    void init_default_tooltip(QString name) override;

public:

    QLabel *laTitle = nullptr;

    QLabel *xText = nullptr;
    QLabel *yText = nullptr;
    QLabel *zText = nullptr;

    ExFloatSpinBoxW x;
    ExFloatSpinBoxW y;
    ExFloatSpinBoxW z;
};

}
