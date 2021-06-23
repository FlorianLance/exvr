
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// widgets
#include "ex_item_w.hpp"


namespace tool::ex {

class ExFloatSpinBoxW : public ExItemW<QDoubleSpinBox>{

public:

    ExFloatSpinBoxW() : ExItemW<QDoubleSpinBox>(UiType::Float_spin_box){}
    ExFloatSpinBoxW *init_widget(MinV<qreal> min, V<qreal> value, MaxV<qreal> max, StepV<qreal> singleStep, int decimals, bool enabled = true);
    ExFloatSpinBoxW *init_widget(DsbSettings settings, bool enabled = true);
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
};

}
