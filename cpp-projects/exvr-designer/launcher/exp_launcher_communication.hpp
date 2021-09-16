
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <memory>

// Qt
#include <QUdpSocket>

// local
#include "utility/path_utility.hpp"

namespace tool::ex {

class ExpLauncherCommunication : public QObject{

    Q_OBJECT

public:

    ExpLauncherCommunication(QObject *parent = nullptr);

    std::unique_ptr<QUdpSocket> readSocket = nullptr;
    std::unique_ptr<QUdpSocket> writeSocket= nullptr;

    quint16 readingPort = 8196;
    quint16 writingPort = 0;

public slots:

    void clean();
    void read_pending_datagrams();

    void send_udp_command(QStringView message);


signals:

    void message_received_signal(QString message);
    void error_signal(QString error);
};
}
