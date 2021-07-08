
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
#include "widgets/list_widget.hpp"
#include "ex_resource_w.hpp"

namespace tool::ex{


class ExResourcesListW : public ExItemW<QFrame>{

    Q_OBJECT
public:

    ExResourcesListW();
    ExResourcesListW *init_widget(Resource::Type resourceType, QString title, bool enabled = true);

    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void update_from_resources() override;

private:

    std::optional<Resource::Type> m_resourceType;

    QPushButton *m_icon =  nullptr;
    QLabel *m_title = nullptr;
    QComboBox *m_resourcesAliases = nullptr;
    QPushButton *m_add = nullptr;
    QPushButton *m_remove = nullptr;
    ui::ListWidget *m_list = nullptr;

    std_v1<int> m_resourcesKeys;
};

}
