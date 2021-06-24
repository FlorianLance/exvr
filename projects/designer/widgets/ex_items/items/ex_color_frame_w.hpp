
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

#include "ex_item_w.hpp"

namespace tool::ex{

class ExColorFrameW : public ExItemW<QFrame>{


public :

    ExColorFrameW();
    ExColorFrameW  *init_widget(bool on, bool enabled = true);
    std::optional<Arg> generate_init_arg_from_dialog(QStringList othersParameters) override;
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;

    bool onState = false;
    static const inline QString stateOn  = QSL("background-color:green;");
    static const inline QString stateOff = QSL("background-color:red;");

    void update(bool on);
};
}
