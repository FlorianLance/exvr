
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <memory>

// Qt
#include <QThread>
#include <QProcessEnvironment>
#include <QUdpSocket>

// local
#include "utility/path_utility.hpp"
#include "settings.hpp"

namespace tool::ex {


class ExpLauncherProcess : public QProcess{

    Q_OBJECT

public:

    ExpLauncherProcess(QObject *parent = nullptr);
    void start_program(QString command, Settings settings, quint16 readingPort);
    bool isRunning = true;

public slots:



    void read_standard_output();
    void read_error_output();

signals:

    void standard_output_signal(QString);
    void error_output_signal(QString);
};
}
