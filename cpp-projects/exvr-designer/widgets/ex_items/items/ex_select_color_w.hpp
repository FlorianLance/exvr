
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QColorDialog>

// local
#include "config.hpp"
#include "ex_item_w.hpp"

namespace tool::ex {


class ExSelectColorW : public ExItemW<QPushButton>{

    Q_OBJECT

public:

    ExSelectColorW();
    ~ExSelectColorW() override;

    QColor current_color() const;

    ExSelectColorW *init_widget(QString dialogName, QColor color, bool enabled = true);
    std::optional<Arg> generate_init_arg_from_dialog(QStringList othersParameters) override;
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;

public slots:

    void close();

private :

    QColorDialog m_colDialog;
};

}
