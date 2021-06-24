
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "qt_ui.hpp"
#include "argument.hpp"


namespace tool::ex {

class BaseGenW : public QWidget{
public:
    virtual void update_arg(Arg &arg) const = 0;
};

class GenSpinboxW : public BaseGenW{

public:

    GenSpinboxW(QString text = "Spin box options");

    QSpinBox min;
    QSpinBox max;
    QSpinBox value;
    QSpinBox step;

    void update_arg(Arg &arg) const override;
};

class SpinboxFloatGenW : public BaseGenW{

public:

    SpinboxFloatGenW();

    QDoubleSpinBox min;
    QDoubleSpinBox max;
    QDoubleSpinBox value;
    QDoubleSpinBox step;
    QSpinBox decimals;

    void update_arg(Arg &arg) const override;
};



class SpinboxDoubleGenW : public BaseGenW{

public:

    SpinboxDoubleGenW(QString text = "Double spin box options");

    QDoubleSpinBox min;
    QDoubleSpinBox max;
    QDoubleSpinBox value;
    QDoubleSpinBox step;
    QSpinBox decimals;

    void update_arg(Arg &arg) const override;
};

class Vector2dGenW : public BaseGenW{

public:

    Vector2dGenW();

    QDoubleSpinBox min;
    QDoubleSpinBox max;
    QDoubleSpinBox valueX;
    QDoubleSpinBox valueY;
    QDoubleSpinBox step;
    QSpinBox decimals;

    void update_arg(Arg &arg) const override;
};

class Vector3dGenW : public BaseGenW{

public:

    Vector3dGenW();

    QDoubleSpinBox min;
    QDoubleSpinBox max;
    QDoubleSpinBox valueX;
    QDoubleSpinBox valueY;
    QDoubleSpinBox valueZ;
    QDoubleSpinBox step;
    QSpinBox decimals;

    void update_arg(Arg &arg) const override;

};

class TransformGenW : public BaseGenW{

public:

    TransformGenW();

    QDoubleSpinBox trValue;
    QDoubleSpinBox trMin;
    QDoubleSpinBox trMax;
    QDoubleSpinBox trStep;
    QSpinBox       trDec;

    QDoubleSpinBox rotValue;
    QDoubleSpinBox rotMin;
    QDoubleSpinBox rotMax;
    QDoubleSpinBox rotStep;
    QSpinBox       rotDec;

    QDoubleSpinBox scValue;
    QDoubleSpinBox scMin;
    QDoubleSpinBox scMax;
    QDoubleSpinBox scStep;
    QSpinBox       scDec;

    void update_arg(Arg &arg) const override;

};

class ResourceGenW : public BaseGenW{
public:

    ResourceGenW();
    QComboBox resourcesTypes;

    void update_arg(Arg &arg) const override;

};

class ComponentGenW : public BaseGenW{
public:

    ComponentGenW();
    QComboBox componentsTypes;

    void update_arg(Arg &arg) const override;

};
}
