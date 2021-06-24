
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// Qt
#include <QFrame>
#include <QIcon>
#include <QLabel>
#include <QPushButton>

// local
// # data
#include "data/component.hpp"

namespace tool::ex {

class ComponentW;
using ComponentWUP = std::unique_ptr<ComponentW>;

enum class ComponentStyle{
    neutral,
    hover,
    hoverShow,
    show,
};

class ComponentW : public QFrame{
    Q_OBJECT

public :

    ComponentW(Component *component);

    void update_from_component(Component *component);
    void update_style();

public slots:

    void dropEvent(QDropEvent *event) override;

protected:

    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

signals:

    void show_component_custom_menu_signal(QPoint globalPos, ComponentKey key);
    void toggle_selection_component_signal(ComponentKey key);
    void toggle_component_parameters_signal(ComponentKey key);
    void remove_component_signal(ComponentKey key);
    void enter_component_signal(ComponentKey key);
    void leave_component_signal(ComponentKey key);

public :

    // data
    QIcon icon;

    ComponentKey key = {-1};
    Component::Type type;
    Component::Category category;
    bool isStatic= false;

    bool mouseHovering  = false;
    bool showWindow     = false;

protected:

    QPushButton *m_iconButton = nullptr;
    QLabel *m_titleLabel = nullptr;

    ComponentStyle currentStyle = ComponentStyle::neutral;
    const static inline QString componentNeutralStyle   = QSL("QPushButton{background-color:white;}");
    const static inline QString componentShowStyle      = QSL("QPushButton{background-color:rgb(160, 211, 146);}");
    const static inline QString hoverComponentStyle     = QSL("QPushButton{background-color:lightgrey;}");
    const static inline QString hoverComponentShowStyle = QSL("QPushButton{background-color:rgb(211, 235, 205);}");
};

}
