
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDialog>

// local
#include "ui_generate_instances_dialog.h"

namespace tool::ex {

class GenerateInstancesDialog : public QDialog{

public:

    GenerateInstancesDialog();

public slots:

    void show_dialog();

private :

    // dialog
    Ui::GenerateInstanceW m_ui;

public :

    bool useBaseName = false;
    bool useManual   = false;
    unsigned int randomSeed = 0;
    int nbInstances = 0;
    int startId = 0;
    QString baseName = "instance_";
    QStringList manualNames;
    QString directoryPath = "";
};
}
