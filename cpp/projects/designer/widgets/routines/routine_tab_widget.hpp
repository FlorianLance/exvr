
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "condition_widget.hpp"
#include "data/routine.hpp"

namespace tool::ex{

class RoutineTabW;
using TimelinesRoutineTabWUP = std::unique_ptr<RoutineTabW>;

class RoutineTabW : public QTabWidget{

    Q_OBJECT

public:

    RoutineTabW(Routine *routine);
    ConditionW *current_condition_widget();    

    void reset();
    void close_all_windows();

    void update_from_routine(GUI *gui, Routine *routine);
    void update_from_connector_info(ConditionKey conditionKey, ConnectorKey connectorKey, QStringView id, QStringView value);

    ConditionW *condition_widget(RowId tabId);

    constexpr ElementKey routine_key() const noexcept{return m_routineKey;}

private :

    ElementKey m_routineKey;
};
}
