
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QWidget>
#include <QToolBox>

// local
#include "flow_diagram_widget.hpp"

// # ui
#include "ui_isi.h"
#include "ui_loop.h"
#include "ui_routine.h"

// ui
namespace Ui {
    class RoutineW;
    class IsiW;
    class LoopW;
}

namespace tool::ex {


class ElementViewerW;
using ElementDisplayWUP = std::unique_ptr<ElementViewerW>;

class ElementViewerW : public QWidget{

    Q_OBJECT

public :

    ElementViewerW(QTabWidget *twCurrentElement);
    void reset();

public slots:

    void update_from_current_element(Element *elem);


signals:

    // all
    void update_element_name_signal(ElementKey key, QString name);

    // routine
    void select_routine_condition_signal(ElementKey routineKey, RowId conditionTabId);
    void move_routine_condition_down_signal(ElementKey routineKey, RowId conditionTabId);
    void move_routine_condition_up_signal(ElementKey routineKey, RowId conditionTabId);

    // loop
    void select_loop_set_signal(ElementKey loopKey, QString set);
    void modify_loop_nb_reps_signal(ElementKey loopKey, int nbReps);
    void modify_loop_type_signal(ElementKey loopKey, Loop::Mode mode);
    void modify_loop_set_name_signal(ElementKey loopKey, QString set, RowId idSet);
    void modify_loop_set_occurrencies_nb_signal(ElementKey loopKey, int occurenciesNb, RowId idSet);
    void add_loop_sets_signal(ElementKey loopKey, QString set, RowId idSet);
    void remove_set_signal(ElementKey loopKey, RowId idSet);
    void move_loop_set_up_signal(ElementKey loopKey, RowId idSet);
    void move_loop_set_down_signal(ElementKey loopKey, RowId idSet);
    void load_loop_sets_file_signal(ElementKey loopKey, QString filePath);
    void reload_loop_sets_file_signal(ElementKey loopKey);

    // isi
    void set_isi_randomize_signal(ElementKey isiKey, bool checked);
    void add_isi_interval_signal(ElementKey isiKey, double interval, RowId idInterval);
    void modify_isi_interval_signal(ElementKey isiKey, double interval, RowId idInterval);
    void remove_isi_interval_signal(ElementKey isiKey, RowId idInterval);
    void move_isi_interval_up_signal(ElementKey isiKey, RowId idInterval);
    void move_isi_interval_down_signal(ElementKey isiKey, RowId idInterval);

private:

    void init_routine_ui();
    void init_loop_ui();
    void init_isi_ui();

    void update_loop_ui(Loop *loop);
    void update_routine_ui(Routine *routine);
    void update_isi_ui(Isi *isi);


    // current loop style index
    int m_currentLoopIndex = 0;


    // layout
    QHBoxLayout *m_layout = nullptr;

    // ui
    std::unique_ptr<Ui::RoutineW> m_routineUI   = nullptr;
    std::unique_ptr<Ui::LoopW>    m_loopUI      = nullptr;
    std::unique_ptr<Ui::IsiW>     m_isiUI       = nullptr;

    // widgets
    QWidget m_noSelectionW;
    QWidget m_routineW;
    QWidget m_loopW;
    QWidget m_isiW;
    QTabWidget *m_toolBox = nullptr;

    ElementKey m_currentElementId = {-1};

};
}
