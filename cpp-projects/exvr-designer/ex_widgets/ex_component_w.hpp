
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

// qt-utility
#include "ex_widgets/ex_item_w.hpp"

// local
#include "data/component.hpp"

namespace tool::ex{

class ExComponentW : public ExItemW<QFrame>{

public:

    ExComponentW(QString name ="");
    ExComponentW *init_widget(tool::ex::Component::Type componentType, QString title, bool enabled = true);

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
