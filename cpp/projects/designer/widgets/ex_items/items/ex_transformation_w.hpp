
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
#include "ex_line_edit_w.hpp"

namespace tool::ex {

class ExTransformationW : public ExItemW<QFrame>{

    constexpr static Vector3dSettings DefaultTranVec    = {ExVector3dW::DefautlTraV,ExVector3dW::DefautlTraV,ExVector3dW::DefautlTraV};
    constexpr static Vector3dSettings DefaultRotVec     = {ExVector3dW::DefaultRotV,ExVector3dW::DefaultRotV,ExVector3dW::DefaultRotV};
    constexpr static Vector3dSettings DefaultScaVec     = {ExVector3dW::DefaultScaV,ExVector3dW::DefaultScaV,ExVector3dW::DefaultScaV};

public:

    ExTransformationW();
    ExTransformationW *init_widget(const QString &title, Vector3dSettings transS = DefaultTranVec, Vector3dSettings rotationS = DefaultRotVec, Vector3dSettings scaleS = DefaultScaVec, bool enabled = true);

    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void set_generator(QString genName) override;

    void set_from_transform(ExTransformationW *tr);
    void set_enable_state(bool enableTranslation, bool enableRotation, bool enableScale);

    void set_trans_decimals(int d);
    void set_trans_min(geo::Pt3<qreal> m);
    void set_trans_max(geo::Pt3<qreal> m);
    void set_trans_steps(geo::Pt3<qreal> s);
    void set_trans_values(geo::Pt3<qreal> v);

    void set_rotation_decimals(int d);
    void set_rotation_min(geo::Pt3<qreal> m);
    void set_rotation_max(geo::Pt3<qreal> m);
    void set_rotation_steps(geo::Pt3<qreal> s);
    void set_rotation_values(geo::Pt3<qreal> v);

    void set_scale_decimals(int d);
    void set_scale_min(geo::Pt3<qreal> m);
    void set_scale_max(geo::Pt3<qreal> m);
    void set_scale_steps(geo::Pt3<qreal> s);
    void set_scale_values(geo::Pt3<qreal> v);

public:

    QLabel *name = nullptr;
    ExFloatSpinBoxW trX, trY, trZ;
    ExFloatSpinBoxW rotX, rotY, rotZ;
    ExFloatSpinBoxW scX, scY, scZ;

private:

    QGridLayout *layout = nullptr;
};

}
