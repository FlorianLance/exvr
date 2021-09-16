
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <memory>

// Qt
#include <QDialog>
#include <QFileDialog>

// local
#include "experiment/experiment.hpp"
#include "ui_generate_instances_dialog.h"


namespace tool::ex {

class GenerateInstancesDialog;
using GenerateInstancesDialogP = std::unique_ptr<GenerateInstancesDialog>;


class GenerateInstancesDialog : public QDialog{


public:

    GenerateInstancesDialog(std_v1<Routine*> routines){
        m_ui.setupUi(this);

        connect(m_ui.pbCancel, &QPushButton::clicked, this, &GenerateInstancesDialog::close);
        connect(m_ui.pbGenerateFiles, &QPushButton::clicked, this, [&]{

            directoryPath = QFileDialog::getExistingDirectory(nullptr, "Select parent directory for the generated instances");
            if(directoryPath.size() == 0){
                return;
            }

            nbInstances = m_ui.sbNbInstancesFiles->value();
            randomSeed  = static_cast<unsigned int>(m_ui.sbSeed->value());
            baseName    = m_ui.leBaseName->text();
//            pathSelectedInstance = "";
            close();
        });

//         connect(m_ui.pbGenerateSelected, &QPushButton::clicked, this, [&]{

//            pathSelectedInstance = QFileDialog::getSaveFileName(nullptr, "Select instance file");
//            if(pathSelectedInstance.size() == 0){
//                return;
//            }

//            directoryPath = "";
//            close();
//         });
    }


private :

    // dialog
    Ui::GenerateInstanceW m_ui;

public :

    // generates instances randomly
    unsigned int randomSeed = 0;
    int nbInstances = 0;
    QString baseName = "instance_";
    QString directoryPath = "";

    // generate selected instance
//    QString pathSelectedInstance = "";
};
}
