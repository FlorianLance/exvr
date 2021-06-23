
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "ex_combo_box_text_w.hpp"
#include "ex_spin_box_w.hpp"

namespace tool::ex {

class ExTimeW : public ExItemW<QWidget>{

public:

    ExTimeW() : ExItemW<QWidget>(UiType::Time){}
    ExTimeW *init_widget(bool enabled = true);
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void set_generator(QString genName) override;

    ExComboBoxTextW typeT;
    ExSpinBoxW frequency;
};
}
