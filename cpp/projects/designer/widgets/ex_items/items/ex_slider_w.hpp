
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "qt_str.hpp"
#include "ex_item_w.hpp"

namespace tool::ex {

class ExSliderIntegerW : public ExItemW<QFrame>{

    Q_OBJECT

public:

    ExSliderIntegerW();
    ExSliderIntegerW* init_widget(QString title, MinV<int> min, V<int> value, MaxV<int> max, StepV<int> step);
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;

    void init_default_tooltip(QString name) override;

    QLabel *title = nullptr;
    QLabel *minMax = nullptr;
    QLabel *valueTxt = nullptr;
    QSlider *value = nullptr;
};

class ExSliderFloatW : public ExItemW<QFrame>{

    Q_OBJECT

public:

    ExSliderFloatW();
    ExSliderFloatW *init_widget(QString title, MinV<qreal> min, V<qreal> valueTxt, MaxV<qreal> max, StepV<qreal> step);
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;

    void init_default_tooltip(QString name) override;

    QString value_to_string() const;

    QLabel *title = nullptr;
    QLabel *minMax = nullptr;
    QLabel *valueTxt = nullptr;
    QSlider *value = nullptr;

private:
    int m_nbSteps;
    qreal m_min;
    qreal m_max;
    qreal m_step;
};


}
