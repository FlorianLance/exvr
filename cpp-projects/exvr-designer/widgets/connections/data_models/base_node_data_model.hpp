
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

struct PortInfo{
    bool captionVisibility;
    QString caption;
    QtNodes::NodeDataType type;
};

namespace tool::ex{

class BaseNodeDataModel : public NodeDataModel{           
    Q_OBJECT

public:

    enum class Type {Connector,Component};

    BaseNodeDataModel(Type t) : type(t){}
    virtual ~BaseNodeDataModel() override{}

    QtNodes::NodeValidationState validationState() const override;
    QString validationMessage() const override;

    const QString &name() const override {return m_name;}
    const QString &caption() const override { return m_caption;}

    unsigned int nPorts(QtNodes::PortType portType) const override{ return nbPorts[static_cast<int>(portType)];}
    const QString &portCaption(QtNodes::PortType t, QtNodes::PortIndex i ) const override;
    const QtNodes::NodeDataType &dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const override;
    bool portCaptionVisible(QtNodes::PortType portType, QtNodes::PortIndex index) const override;
    virtual bool captionVisible() const override{ return m_captionVisibility;};

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

protected:

    QString m_caption;
    QString m_name;

    std::vector<unsigned int> nbPorts = {0,0,0};
    std::vector<PortInfo> inPortsInfo;
    std::vector<PortInfo> outPortsInfo;
    bool m_captionVisibility;

};
}



