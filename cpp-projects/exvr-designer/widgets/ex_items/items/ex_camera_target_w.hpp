
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QGridLayout>

// local
// # data
#include "config.hpp"
// # utility
#include "qt_str.hpp"
// # widgets
#include "ex_vector3d_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_select_color_w.hpp"
#include "ex_curve_w.hpp"

namespace tool::ex {

class ExCameraTargetW : public ExItemW<QFrame>{

public:

    ExCameraTargetW();
    ExCameraTargetW *init_widget(bool enabled = true);
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void set_generator(QString genName) override;

    ExBaseW *init_widget2(std_v1<std::any> parameters) override;

public:

    ExCheckBoxW displayCamera;
    ExCheckBoxW sphericInterpolation;
    ExFloatSpinBoxW time;
    ExVector3dW translation;
    ExVector3dW rotation;
    ExSelectColorW color;
    ExCurveW speed;
};

}
