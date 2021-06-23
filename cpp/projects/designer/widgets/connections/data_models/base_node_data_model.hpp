
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QApplication>
#include <QWheelEvent>
#include <QTimer>

// nodes
#include "nodes/NodeDataModel.hpp"

// local
#include "widgets/connections/data_models/data/nodes_data.hpp"

using QtNodes::NodeDataModel;

namespace tool::ex{

class BaseNodeDataModel : public NodeDataModel{           
    Q_OBJECT

public:

    enum class Type {Connector,Component};

    BaseNodeDataModel(Type t) : type(t){}
    virtual ~BaseNodeDataModel() override{}

    QtNodes::NodeValidationState validationState() const override;
    QString validationMessage() const override;

public slots:

    virtual void inputConnectionCreated(const QtNodes::Connection &c)   override{Q_UNUSED(c)}
    virtual void inputConnectionDeleted(const QtNodes::Connection &c)   override{Q_UNUSED(c)}
    virtual void outputConnectionCreated(const QtNodes::Connection &c)  override{Q_UNUSED(c)}
    virtual void outputConnectionDeleted(const QtNodes::Connection &c)  override{Q_UNUSED(c)}
    virtual void wheel_event(QWheelEvent *event){Q_UNUSED(event)}

signals:

    void force_node_update_signal();
    void input_connection_validity_signal(bool state);

protected:

    void set_valid_state();
    void set_invalid_state(QString warning);
    void set_error_state(QString error);

public:

    Type type;
    int key;

    QtNodes::NodeValidationState modelValidationState = QtNodes::NodeValidationState::Valid;
    QString modelValidationMessage;
};
}



