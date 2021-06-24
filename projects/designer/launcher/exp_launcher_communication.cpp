

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "exp_launcher_communication.hpp"

// Qt
#include <QWidget>

// qt-utility
#include "qt_logger.hpp"

using namespace tool::ex;

void ExpLauncherCommunication::clean(){

    if(readSocket){
        readSocket->close();
        readSocket = nullptr;
    }
    if(writeSocket){
        writeSocket->close();
        writeSocket = nullptr;
    }
}

ExpLauncherCommunication::ExpLauncherCommunication(QObject *parent){

    Q_UNUSED(parent)

    // initialize reading socket
    readSocket  = std::make_unique<QUdpSocket>();
    connect(readSocket.get(), &QUdpSocket::readyRead, this, &ExpLauncherCommunication::read_pending_datagrams);
    connect(readSocket.get(), QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),[=](QAbstractSocket::SocketError){
        emit error_signal(QSL("[IPC] Socket error\n"));
    });

    bool success = false;
    for(; readingPort < 8216; ++readingPort){
        success = readSocket->bind(QHostAddress::LocalHost, readingPort, QAbstractSocket::ReuseAddressHint);
        if(success){
            QtLogger::message(QSL("[IPC] UDP read port connected: ") % QString::number(readingPort));
            break;
        }
    }
    if(!success){
        QtLogger::error(QSL("[IPC] UDP port error: ") % QString::number(readingPort));
    }

    // initialize writing socket
    writeSocket  = std::make_unique<QUdpSocket>();
}

void ExpLauncherCommunication::read_pending_datagrams(){

    bool readDatagram = true;
    QHostAddress sender;
    quint16 senderPort;

    while (readDatagram){

        if(readSocket->state() == QAbstractSocket::BoundState){
            readDatagram = readSocket->hasPendingDatagrams();
        }else{
            readDatagram = false;
        }

        if(!readDatagram){
            return;
        }

        QByteArray datagram;
        datagram.resize(static_cast<int>(readSocket->pendingDatagramSize()));

        auto size = readSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        if(size > 0){
            emit message_received_signal(QString(datagram));
        }else{
            emit error_signal(QSL("[IPC] Error while reading udp packet.\n"));
        }
    }
}

void ExpLauncherCommunication::send_udp_command(QStringView message){
    if(writingPort == 0){
        return;
    }
    writeSocket->writeDatagram(message.toUtf8(), QHostAddress::LocalHost, writingPort);
}

#include "moc_exp_launcher_communication.cpp"
