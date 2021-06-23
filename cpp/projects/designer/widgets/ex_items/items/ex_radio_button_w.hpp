
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

#include "ex_item_w.hpp"

namespace tool::ex{

class ExRadioButtonW : public ExItemW<QRadioButton>{
Q_OBJECT
public:

    ExRadioButtonW() : ExItemW<QRadioButton>(UiType::Radio_button){}
    ExRadioButtonW *init_widget(QString txt, bool checked, bool enabled = true);
    std::optional<Arg> generate_init_arg_from_dialog(QStringList othersParameters) override;
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
};
}
