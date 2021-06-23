
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

#include "ex_item_w.hpp"

namespace tool::ex{

class ExSpinBoxW : public ExItemW<QSpinBox>{

public:

    ExSpinBoxW() : ExItemW<QSpinBox>(UiType::Spin_box){}
    ExSpinBoxW *init_widget(MinV<int> min, V<int> value, MaxV<int> max, StepV<int> singleStep, bool enabled = true);
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
};

}
