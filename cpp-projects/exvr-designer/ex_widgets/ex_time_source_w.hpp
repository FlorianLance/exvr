
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "ex_widgets/ex_combo_box_text_w.hpp"
#include "ex_widgets/ex_spin_box_w.hpp"

namespace tool::ex {

class ExTimeW : public ExItemW<QWidget>{

public:

    ExTimeW(QString name ="");
    ExTimeW *init_widget(bool enabled = true);

    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void set_as_generator() override;

    ExComboBoxTextW typeT = {"type"};
    ExSpinBoxW frequency = {"frequency"};
};
}
