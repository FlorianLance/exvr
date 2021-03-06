
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "routines_manager_tab_widget.hpp"

// Qt
#include <QStringBuilder>

// base
#include "utility/benchmark.hpp"

// local
#include "experiment/global_signals.hpp"


using namespace tool::ex;

RoutinesManagerTW::RoutinesManagerTW() {

    setObjectName("Routines tab widget");

    // background-color: rgb(0,100,0);
    // background-color: rgb(230,230,230);
    // background-color: rgb(0,128,0);
    // background-color: rgb(255,255,255);

    tabBar()->setStyleSheet(
        "QTabBar::tab:selected:hover {\
            color: rgb(0,128,0);\
        }\
        QTabBar::tab:!selected:hover{\
            color: rgb(0,128,0);\
        }\
        QTabBar::tab:selected{\
            color: rgb(0,128,0);\
        }\
        QTabBar::tab:!selected{\
            color: rgb(0,0,0);\
        }\
    ");

    connect(this, &RoutinesManagerTW::currentChanged, this, [&]{

        int rowId  = currentIndex();
        if(rowId  > -1){
            auto routineW = routine_widget(RowId{rowId});
            if(routineW != nullptr){
                emit GSignals::get()->routine_selected_signal(routineW->routine_key());
            }
        }
    });
}

void RoutinesManagerTW::close_all_windows(){

    for(int idTab = 0; idTab < count(); ++idTab){
        routine_widget(RowId{idTab})->close_all_windows();
    }
}

void RoutinesManagerTW::reset(){

    BlockSignalsGuard guard;

    while(count() > 0){
        qobject_cast<RoutineTabW*>(widget(0))->reset();
        delete widget(0);
    }
}

void RoutinesManagerTW::update_connector_dialog_with_info(ElementKey elementKey, ConditionKey conditionKey, ConnectorKey connectorKey, QStringView id, QStringView value){
    for(int ii = 0; ii < count(); ++ii){
        auto rw = routine_widget(RowId{ii});
        if(rw->routine_key() == elementKey){
            rw->update_from_connector_info(conditionKey, connectorKey, id, value);
            break;
        }
    }
}

RoutineTabW *RoutinesManagerTW::current_routine_widget(){
    if(int id = currentIndex(); id > -1){
        return qobject_cast<RoutineTabW*>(widget(id));
    }
    return nullptr;
}

void RoutinesManagerTW::update_from_experiment(Experiment *exp){

    const auto signalsState = GSignals::get()->signalsBlocked();
    GSignals::get()->blockSignals(true);

    bool display = false;

    Bench::start("RoutinesManagerTW update_from_experiment 1"sv, display);

        // remove inused routines
        int size = count();
        if(size > 0){
            for(int ii = size-1; ii >= 0; --ii){
                ElementKey rKey = qobject_cast<RoutineTabW*>(widget(ii))->routine_key();
                if(!exp->get_element_from_type_and_id<Routine>(rKey)){
                    delete widget(ii);
                }
            }
        }

    Bench::stop();
    Bench::start("RoutinesManagerTW update_from_experiment 2"sv, display);

        // add new routines
        size = count();
        auto routines = exp->get_elements_from_type<Routine>();
        for(size_t ii = 0; ii < routines.size(); ++ii){
            bool found = false;
            for(int jj = 0; jj < size; ++jj){
                if(routines[ii]->key() == qobject_cast<RoutineTabW*>(widget(jj))->routine_key().v){
                    found = true;
                    break;
                }
            }

            if(!found){
                // conditions
                addTab(new RoutineTabW(routines[ii]), "");
            }
        }

    Bench::stop();
    Bench::start("RoutinesManagerTW update_from_experiment 3"sv, display);

        // reorder
        for(int ii = 0; ii < to_signed(routines.size()); ++ii){
            for(int jj = 0; jj< count(); ++jj){
                if(qobject_cast<RoutineTabW*>(widget(jj))->routine_key().v == routines[to_unsigned(ii)]->key()){
                    if(ii != jj){
                        tabBar()->moveTab(jj,ii);
                    }
                    break;
                }
            }
        }

    Bench::stop();
    Bench::start("RoutinesManagerTW update_from_experiment 4"sv, display);

        int lastRoutineKey = exp->lastRoutineSelected != nullptr ? exp->lastRoutineSelected->key() : -1;

        // update routines timelines
        for(int idTab = 0; idTab < count(); ++idTab){
            auto routine  = routines[to_unsigned(idTab)];
            auto routineW = routine_widget(RowId{idTab});

            Bench::start("RoutinesManagerTW update_from_experiment 41"sv, display);
                QString txt = routine->name() % QSL(" (") % QString::number(routine->conditions.size()) % QSL(")");
                if(tabText(idTab) != txt){
                    setTabText(idTab, txt);
                }
            Bench::stop();
            if((routine->is_selected()) || (lastRoutineKey == routine->key())){
                Bench::start("RoutinesManagerTW update_from_experiment 42"sv, display);
                    if(currentIndex() != idTab){
                        setCurrentIndex(idTab);
                    }
                Bench::stop();
                Bench::start("RoutinesManagerTW update_from_experiment 43"sv, display);
                    routineW->update_from_routine(exp->gui(), routine);
                Bench::stop();
            }
        }

    Bench::stop();

    GSignals::get()->blockSignals(signalsState);
}

RoutineTabW *RoutinesManagerTW::routine_widget(RowId tabId){
    return qobject_cast<RoutineTabW*>(widget(tabId.v));
}



#include "moc_routines_manager_tab_widget.cpp"
