
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// std
#include <memory>

// Qt
#include <QTabWidget>

// local
#include "routine_tab_widget.hpp"
#include "experiment.hpp"


namespace tool::ex{

class RoutinesManagerTW;
using RoutinesManagerTWUP = std::unique_ptr<RoutinesManagerTW>;


class RoutinesManagerTW : public QTabWidget{

    Q_OBJECT

public :

    RoutinesManagerTW();

    void close_all_windows();

    RoutineTabW* current_routine_widget();
    RoutineTabW *routine_widget(RowId tabId);

public slots:

    void update_from_experiment(Experiment *exp);
    void reset();
    void update_connector_dialog_with_info(ElementKey elementKey, ConditionKey conditionKey, ConnectorKey connectorKey, QStringView id, QStringView value);
};
}
