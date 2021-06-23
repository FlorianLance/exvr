
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// Qt
#include <QDialog>

// local
#include "routine.hpp"
#include "loop.hpp"
#include "ui_copy_to_conditions.h"
#include "widgets/list_widget.hpp"


namespace tool::ex {

class CopyToConditionDialog : public QDialog{

    Q_OBJECT

public :

    CopyToConditionDialog();

    void update_from_data(ElementKey currentRoutineKey, ConditionKey currentConditionKey, std_v1<Routine*> routines, std_v1<Loop*> loops);

signals:

    void copy_to_conditions_signal(ElementKey routineKey, ConditionKey conditionKey, std_v1<std::pair<ElementKey,ConditionKey>> conditionsToBeEcrased,
                                   bool copyActions, bool copyConnections);

private slots:

    void update_list_from_filters();
    void update_ui_from_conditions_checkboxes();

private:

    Ui::CopyConditionToUiD ui;
    ui::ListWidget *lw = nullptr;

    ElementKey m_currentRoutine;
    ConditionKey m_currentCondition;
    std_v1<std::pair<const Loop* ,std::unique_ptr<ui::ListWidget>>> setsPerLoops;
    std_v1<std::pair<const Routine*,std::unique_ptr<ui::ListWidget>>> conditionsPerRoutines;    
};
}
