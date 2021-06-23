
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

// local
// # data
#include "action.hpp"
// # widgets
#include "ui_action.h"
#include "timeline_widget.hpp"

namespace tool::ex{

class ActionW : public QWidget{

    Q_OBJECT

public :

    ActionW(ElementKey routineKey, ConditionKey conditionKey, Action *action);

    void update_from_action(int id, Action *action, qreal scale, qreal factorSize, SecondsTS max);

    constexpr ElementKey routine_key() const noexcept{return m_routineKey;}
    constexpr ConditionKey condition_key() const noexcept{return m_conditionKey;}
    constexpr ActionKey action_key() const noexcept{return m_actionKey;}

protected:

    void mousePressEvent(QMouseEvent *event) override;

public slots:

    void set_minimized_state(bool state);

private:

    ElementKey m_routineKey;
    ConditionKey m_conditionKey;
    ActionKey m_actionKey;

    // ui
    Ui::ActionW m_ui;
    bool m_minimized = false;

    // widgets
    TimelineW *m_timelineUpdateW     = nullptr;
    TimelineW *m_timelineVisibilityW = nullptr;    
};
}

