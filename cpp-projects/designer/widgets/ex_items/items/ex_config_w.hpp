
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
#include "ex_item_w.hpp"
#include "component.hpp"

namespace tool::ex{


class ExConfigW : public ExItemW<QFrame>{

    Q_OBJECT
public:

    ExConfigW();
    ExConfigW *init_widget(bool enabled = true);

    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void update_from_components() override;

    QString display()const;

private:

    void update_components_list_widget();
    void update_configs_list_widget();

    QLineEdit *m_routineName = nullptr;
    QLineEdit *m_conditionName = nullptr;

    QLabel *m_routineTitle = nullptr;
    QLabel *m_conditionTitle = nullptr;
    QLabel *m_componentTitle = nullptr;
    QLabel *m_configTitle = nullptr;

//    QComboBox *m_routineNames = nullptr;
//    QComboBox *m_conditionNames = nullptr;
    QComboBox *m_componentNames = nullptr;
    QComboBox *m_configNames = nullptr;

    QString m_currentRoutineName;
    QString m_currentConditionName;

//    int m_currentRoutineKey = -1;
//    int m_currentConditionKey = -1;
    ComponentKey m_currentComponentKey = {-1};
    ConfigKey m_currentConfigKey = {-1};
};

}
