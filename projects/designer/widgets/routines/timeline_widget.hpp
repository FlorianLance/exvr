/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/
#pragma once

// Qt
#include <QTimer>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

// base
#include "utility/vector_utility.hpp"

// local
#include "timeline.hpp"

namespace tool::ex{

class TimelineW : public QWidget{

    Q_OBJECT

    public :

    TimelineW(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, Timeline *timeline, bool drawAxe, bool updateTimeline);

    QRectF interval_to_rect(const Interval &i)const;
    Interval rect_to_interval(const QRectF &r) const;

    void update_from_timeline(Timeline *timeline, qreal m_scale, qreal m_factorSize, SecondsTS max);

    constexpr ElementKey routine_key() const noexcept{return m_routineKey;}
    constexpr ConditionKey condition_key() const noexcept{return m_conditionKey;}
    constexpr ActionKey action_key() const noexcept{return m_actionKey;}
    constexpr TimelineKey timeline_key() const noexcept{return m_timelineKey;}

protected:

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

public :

    Timeline::Type type;

private:

    ElementKey m_routineKey;
    ConditionKey m_conditionKey;
    ActionKey m_actionKey;
    TimelineKey m_timelineKey;

    bool m_drawAxe = false;
    bool m_updateTimeline = false;
    bool m_clickOn = false;

    Qt::MouseButton m_currentButtonPressed;
    QPoint m_currentMousePos;

    static constexpr qreal m_widthOffset = 50.;
    static constexpr qreal m_widthPart = 100;

    qreal m_scale = 1.0;
    qreal m_factorSize = 1.0;
    qreal m_widthTotal;
    qreal m_timelineWidth;
    SecondsTS m_maxLength{10.};   

    QRectF timelineR;
    QRectF leftTextPartR;
    QRectF rightPartR;
    QRectF rightTopIntervalsR;
    QRectF rightBottomAxisR;

    std_v1<QRectF> m_elementsPartsAreas;
    std_v1<QRectF> m_intervalsAreas;


};
}

