
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QListWidget>

// local
#include "config.hpp"
#include "ex_item_w.hpp"

namespace tool::ex {


class ExListLabelsW : public ExItemW<QListWidget>{

public:

    ExListLabelsW() : ExItemW<QListWidget>(UiType::List_labels){}
    ExListLabelsW *init_widget(bool enabled = true);
    std::optional<Arg> generate_init_arg_from_dialog(QStringList othersParameters) override;
    void init_connection(const QString &nameParam) override;
    Arg convert_to_arg() const override;
    void update_from_arg(const Arg &arg) override;
};

}
