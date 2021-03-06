
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QFrame>
#include <QComboBox>

// qt-utility
#include "ex_widgets/ex_item_w.hpp"

// local
#include "resources/resource.hpp"

namespace tool::ex{

class ExResourceW : public ExItemW<QFrame>{


public:

    ExResourceW(QString name ="");
    ExResourceW *init_widget(Resource::Type resourceType, QString title, bool enabled = true);

    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void update_from_resources() override;

private:

    Resource::Type m_resourceType;

    QPushButton *m_icon = nullptr;
    QLabel *m_title  = nullptr;
    QComboBox *m_resourcesAlias  = nullptr;
    QPushButton *m_resources = nullptr;

    int m_currentKey = -1;
    std_v1<int> resourcesId;
};

}
