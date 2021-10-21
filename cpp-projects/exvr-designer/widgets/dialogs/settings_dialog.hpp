
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDialog>

// local
#include "ui_settings.h"
#include "data/settings.hpp"

namespace tool::ex {

class SettingsDialog : public QDialog{

Q_OBJECT
public:

    SettingsDialog(){

        // set ui
        m_ui.setupUi(this);
        setWindowIcon(QIcon(":/icons/Settings"));

        // define settings dialog ui
        setModal(true);
        setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);

        // settings dialog
        connect(m_ui.pbOk,      &QPushButton::clicked, this,  &QDialog::accept);
        connect(m_ui.pbCancel,  &QPushButton::clicked, this,  &QDialog::reject);
        connect(m_ui.pbReset,   &QPushButton::clicked, this, &SettingsDialog::reset_settings_signal);
        connect(m_ui.rbVrMode, &QRadioButton::clicked, this, &SettingsDialog::update_ui_state);
        connect(m_ui.rbFlatMode, &QRadioButton::clicked, this, &SettingsDialog::update_ui_state);
        connect(m_ui.rbFlatStereoMode, &QRadioButton::clicked, this, &SettingsDialog::update_ui_state);
        connect(m_ui.cbDefinition, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&](int){
            update_ui_state();
        });
        connect(m_ui.cbFullscreen, &QCheckBox::clicked, this, &SettingsDialog::update_ui_state);

        connect(this, &SettingsDialog::finished, this, [&](int result){
            if(result != 1){
                emit settings_canceled_signal();
                return;
            }

            Settings settings;

            // debug
            settings.debug = m_ui.cbDebug->isChecked();
            settings.csharpAddDebugInfo = m_ui.cbCsharpDebugInfo->isChecked();
            settings.catchComponentsExceptions = m_ui.cbCatchComponentsExceptions->isChecked();

            // camera
            settings.neutralX = m_ui.cbNeutralX->isChecked();
            settings.neutralY = m_ui.cbNeutralY->isChecked();
            settings.neutralZ = m_ui.cbNeutralZ->isChecked();
            settings.positionalTracking = m_ui.cbEnablePositionalTracking->isChecked();

            // input
            settings.catchExternalKeyboardKeysEvents = m_ui.cbCatchExternalKeyboardKeysEvents->isChecked();

            // display
            if(m_ui.rbVrMode->isChecked()){
                settings.displayMode = Settings::ExpLauncherDisplayMode::OpenVR;
            }else if(m_ui.rbFlatMode->isChecked()){
                settings.displayMode = Settings::ExpLauncherDisplayMode::Flat;
            }else{
                settings.displayMode = Settings::ExpLauncherDisplayMode::FlatStereo;
            }
            settings.stereoCameraFOV = m_ui.sbStereoFOV->value();
            settings.monitorId = m_ui.sbMonitorId->value();
            settings.fullscreen = m_ui.cbFullscreen->isChecked();
            settings.customWidth = m_ui.sbDefWidth->value();
            settings.customHeight = m_ui.sbDefHeight->value();
            settings.resolutionId = m_ui.cbDefinition->currentIndex();

            emit settings_updated_signal(std::move(settings));

        });
    }

public slots:

    void update_from_settings(Settings *settings){

        // debug
        m_ui.cbDebug->setChecked(settings->debug);
        m_ui.cbCsharpDebugInfo->setChecked(settings->csharpAddDebugInfo);
        m_ui.cbCatchComponentsExceptions->setChecked(settings->catchComponentsExceptions);

        // camera
        m_ui.cbNeutralX->setChecked(settings->neutralX);
        m_ui.cbNeutralY->setChecked(settings->neutralY);
        m_ui.cbNeutralZ->setChecked(settings->neutralZ);
        m_ui.cbEnablePositionalTracking->setChecked(settings->positionalTracking);

        // input
        m_ui.cbCatchExternalKeyboardKeysEvents->setChecked(settings->catchExternalKeyboardKeysEvents);

        // display
        if(settings->displayMode == Settings::ExpLauncherDisplayMode::OpenVR){
            m_ui.rbVrMode->setChecked(true);
        }else if(settings->displayMode == Settings::ExpLauncherDisplayMode::Flat){
            m_ui.rbFlatMode->setChecked(true);
        }else{
            m_ui.rbFlatStereoMode->setChecked(true);
        }
        m_ui.sbStereoFOV->setValue(settings->stereoCameraFOV);
        m_ui.sbMonitorId->setValue(settings->monitorId);
        m_ui.cbFullscreen->setChecked(settings->fullscreen);
        m_ui.cbDefinition->setCurrentIndex(settings->resolutionId);
        m_ui.sbDefWidth->setValue(settings->customWidth);
        m_ui.sbDefHeight->setValue(settings->customHeight);

        update_ui_state();
    }

private slots:


    void update_ui_state(){

        bool custom = m_ui.cbDefinition->currentIndex() == 0;

        if(m_ui.rbVrMode->isChecked()){
            m_ui.sbStereoFOV->setEnabled(false);
            m_ui.sbDefWidth->setEnabled(custom );
            m_ui.sbDefHeight->setEnabled(custom );

        }else if(m_ui.rbFlatMode->isChecked()){
            m_ui.sbStereoFOV->setEnabled(false);

            m_ui.sbDefWidth->setEnabled(custom );
            m_ui.sbDefHeight->setEnabled(custom );
        }else if(m_ui.rbFlatStereoMode->isChecked()){
            m_ui.sbStereoFOV->setEnabled(true);

            m_ui.sbDefWidth->setEnabled(custom);
            m_ui.sbDefHeight->setEnabled(custom);
        }
    }

signals:

    void settings_updated_signal(Settings settings);
    void reset_settings_signal();
    void settings_canceled_signal();

private:

    Ui::SettingsUI m_ui;
};


}
