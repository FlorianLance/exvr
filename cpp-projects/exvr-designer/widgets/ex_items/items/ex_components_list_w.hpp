
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QFrame>
#include <QComboBox>

// local
#include "ex_component_w.hpp"
#include "widgets/list_widget.hpp"


namespace tool::ex{


class ExComponentsListW : public ExItemW<QFrame>{

    Q_OBJECT
public:

    ExComponentsListW();
    ExComponentsListW *init_widget(Component::Type componentType, QString title, bool enabled = true);

    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void update_from_components() override;

private:

    std::optional<Component::Type> m_componentType;

    QPushButton *m_icon =  nullptr;
    QLabel *m_title = nullptr;
    QComboBox *m_componentNames = nullptr;
    QPushButton *m_add = nullptr;
    QPushButton *m_remove = nullptr;
    ui::ListWidget *m_list = nullptr;

    std_v1<int> m_componentsKeys;
};

}
