
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
