
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QWheelEvent>
#include <QMenu>

// nodes
#include "nodes/FlowView.hpp"
#include "nodes/FlowScene.hpp"
#include "nodes/Node.hpp"


// local
#include "data_models/base_node_data_model.hpp"

namespace tool::ex {

class ExFlowView : public QtNodes::FlowView{

Q_OBJECT

public :

    ExFlowView(QtNodes::FlowScene *scene) : QtNodes::FlowView(scene){
    }


    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

signals:

    void open_context_menu_signal(QPoint pos, QPointF mappedPos, BaseNodeDataModel *nodeModelUnderMouse, QtNodes::Connection *connectionUnderMouse);
    void delete_selection_signal();

    void mouse_pressed_event_signal(QMouseEvent *event);
    void mouse_release_event_signal(QMouseEvent *event);

private:


    int scaleLvl = 3;
    const int maxScaleLvl = 8;

    bool leftClick = false;

    bool controlPressed = false;

    QPointF p;
    int minX = -1000;
    int maxX = 1000;

    QtNodes::Node* hoveredNode = nullptr;
    QtNodes::Connection *hoveredConnection = nullptr;

};
}
