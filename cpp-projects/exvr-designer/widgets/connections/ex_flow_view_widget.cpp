
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_flow_view_widget.hpp"

// base
#include "utility/benchmark.hpp"

using namespace tool::ex;



void ExFlowView::paintEvent(QPaintEvent *event){
    QtNodes::FlowView::paintEvent(event);
}

void ExFlowView::resizeEvent(QResizeEvent *event){
    QtNodes::FlowView::resizeEvent(event);
}

void ExFlowView::wheelEvent(QWheelEvent *event){

    // propagate wheel event to embedded widget
    if(hoveredNode){
        for(const auto &node : scene()->nodes()){
            if(node.second->nodeGeometry().hovered()){
                dynamic_cast<BaseNodeDataModel*>(node.second->nodeDataModel())->wheel_event(event);
                return;
            }
        }
        return;
    }

    QPoint delta = event->angleDelta();
    if (delta.y() == 0){
        event->ignore();
        return;
    }

    const auto d = delta.y() / std::abs(delta.y());

    if (d > 0.0){
        if(scaleLvl < maxScaleLvl){
            scaleUp();
            ++scaleLvl;
        }
    }else{
        if(scaleLvl > 0){
            scaleDown();
            --scaleLvl;
        }
    }
}


void ExFlowView::mousePressEvent(QMouseEvent *event){

    auto scenePos = mapToScene(event->pos());
    if(event->button()== Qt::MouseButton::LeftButton){
        leftClick = true;
        p = scenePos;
    }

    FlowView::mousePressEvent(event);
    emit mouse_pressed_event_signal(event);
}

void ExFlowView::mouseReleaseEvent(QMouseEvent *event){

    leftClick = false;
    FlowView::mouseReleaseEvent(event);
    emit mouse_release_event_signal(event);
}

void ExFlowView::mouseMoveEvent(QMouseEvent *event){

    Bench::start("ExFlowView mouseMoveEvent"sv);
    FlowView::mouseMoveEvent(event);
    Bench::stop();

    // check if mouse hovering a node
    hoveredNode = nullptr;
    for(const auto &node : scene()->nodes()){
        if(node.second->nodeGeometry().hovered()){
            hoveredNode = node.second.get();
            break;
        }
    }
    // check if mouse hovering a connection
    hoveredConnection = nullptr;
    for(const auto &connection : scene()->connections()){
        if(connection.second->connectionGeometry().hovered()){
            hoveredConnection = connection.second.get();
            break;
        }
    }
}


void ExFlowView::keyPressEvent(QKeyEvent *event){

    switch (event->key()) {
        case Qt::Key::Key_Control:
            controlPressed = true;
            break;
    }
    FlowView::keyPressEvent(event);
}

void ExFlowView::keyReleaseEvent(QKeyEvent *event){

    switch (event->key()) {
        case Qt::Key::Key_Delete:
            emit delete_selection_signal();
            return;
        case Qt::Key::Key_Control:
            controlPressed = false;
            break;
    }
    FlowView::keyReleaseEvent(event);
}

void ExFlowView::contextMenuEvent(QContextMenuEvent *event){
    BaseNodeDataModel *nodeModelUnderMouse = hoveredNode ? dynamic_cast<BaseNodeDataModel*>(hoveredNode->nodeDataModel()) : nullptr;
    emit open_context_menu_signal(event->globalPos(), mapToScene(event->pos()), nodeModelUnderMouse, hoveredConnection);
}
