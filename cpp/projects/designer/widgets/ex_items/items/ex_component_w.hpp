
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <optional>

// Qt
#include <QFrame>
#include <QComboBox>

// local
#include "ex_item_w.hpp"
#include "component.hpp"

namespace tool::ex{


class ExComponentW : public ExItemW<QFrame>{

    Q_OBJECT
public:

    ExComponentW();
    ExComponentW *init_widget(tool::ex::Component::Type componentType, QString title, bool enabled = true);

    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void update_from_components() override;

    QString current_component_name_displayed()const;

private:

    std::optional<tool::ex::Component::Type> m_componentType;

    QPushButton *m_icon =  nullptr;
    QLabel *m_title = nullptr;
    QComboBox *m_componentNames = nullptr;

    int m_currentKey = -1;
};

}
