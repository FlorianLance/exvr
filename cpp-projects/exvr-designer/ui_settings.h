/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsUI
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *content;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QRadioButton *rbVrMode;
    QRadioButton *rbFlatMode;
    QRadioButton *rbFlatStereoMode;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QSpinBox *sbMonitorId;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QCheckBox *cbFullscreen;
    QSpacerItem *horizontalSpacer_7;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QComboBox *cbDefinition;
    QFrame *line;
    QLabel *label;
    QSpinBox *sbDefWidth;
    QLabel *label_2;
    QSpinBox *sbDefHeight;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *sbStereoFOV;
    QSpacerItem *horizontalSpacer_6;
    QWidget *tabTracking;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_4;
    QGridLayout *gridLayout_4;
    QCheckBox *cbNeutralX;
    QCheckBox *cbNeutralZ;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_5;
    QCheckBox *cbNeutralY;
    QCheckBox *cbEnablePositionalTracking;
    QSpacerItem *verticalSpacer_3;
    QWidget *tabInputs;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *cbCatchExternalKeyboardKeysEvents;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabDebug;
    QVBoxLayout *verticalLayout_4;
    QWidget *gbCSharp;
    QGridLayout *gridLayout;
    QCheckBox *cbCsharpDebugInfo;
    QCheckBox *cbDebug;
    QCheckBox *cbCatchComponentsExceptions;
    QSpacerItem *verticalSpacer_4;
    QFrame *bottomButttons;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pbReset;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbOk;
    QPushButton *pbCancel;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *SettingsUI)
    {
        if (SettingsUI->objectName().isEmpty())
            SettingsUI->setObjectName("SettingsUI");
        SettingsUI->resize(577, 251);
        SettingsUI->setSizeGripEnabled(false);
        verticalLayout = new QVBoxLayout(SettingsUI);
        verticalLayout->setObjectName("verticalLayout");
        content = new QWidget(SettingsUI);
        content->setObjectName("content");
        gridLayout_2 = new QGridLayout(content);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        tabWidget = new QTabWidget(content);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame = new QFrame(tab);
        frame->setObjectName("frame");
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        rbVrMode = new QRadioButton(frame);
        rbVrMode->setObjectName("rbVrMode");
        rbVrMode->setChecked(true);

        horizontalLayout->addWidget(rbVrMode);

        rbFlatMode = new QRadioButton(frame);
        rbFlatMode->setObjectName("rbFlatMode");
        rbFlatMode->setChecked(false);

        horizontalLayout->addWidget(rbFlatMode);

        rbFlatStereoMode = new QRadioButton(frame);
        rbFlatStereoMode->setObjectName("rbFlatStereoMode");
        rbFlatStereoMode->setEnabled(true);

        horizontalLayout->addWidget(rbFlatStereoMode);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_2->addWidget(frame);

        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 0));
        horizontalLayout_5 = new QHBoxLayout(widget_2);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(widget_2);
        label_7->setObjectName("label_7");

        horizontalLayout_5->addWidget(label_7);

        sbMonitorId = new QSpinBox(widget_2);
        sbMonitorId->setObjectName("sbMonitorId");
        sbMonitorId->setMinimum(1);
        sbMonitorId->setMaximum(10);

        horizontalLayout_5->addWidget(sbMonitorId);

        label_9 = new QLabel(widget_2);
        label_9->setObjectName("label_9");

        horizontalLayout_5->addWidget(label_9);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_2->addWidget(widget_2);

        widget_6 = new QWidget(tab);
        widget_6->setObjectName("widget_6");
        widget_6->setMinimumSize(QSize(0, 0));
        horizontalLayout_6 = new QHBoxLayout(widget_6);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(widget_6);
        label_8->setObjectName("label_8");

        horizontalLayout_6->addWidget(label_8);

        cbFullscreen = new QCheckBox(widget_6);
        cbFullscreen->setObjectName("cbFullscreen");
        cbFullscreen->setEnabled(true);
        cbFullscreen->setChecked(true);

        horizontalLayout_6->addWidget(cbFullscreen);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        verticalLayout_2->addWidget(widget_6);

        widget_3 = new QWidget(tab);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(widget_3);
        label_6->setObjectName("label_6");

        horizontalLayout_3->addWidget(label_6);

        cbDefinition = new QComboBox(widget_3);
        cbDefinition->addItem(QString());
        cbDefinition->addItem(QString());
        cbDefinition->addItem(QString());
        cbDefinition->addItem(QString());
        cbDefinition->addItem(QString());
        cbDefinition->setObjectName("cbDefinition");
        cbDefinition->setEnabled(true);

        horizontalLayout_3->addWidget(cbDefinition);

        line = new QFrame(widget_3);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_3->addWidget(line);

        label = new QLabel(widget_3);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        sbDefWidth = new QSpinBox(widget_3);
        sbDefWidth->setObjectName("sbDefWidth");
        sbDefWidth->setEnabled(false);
        sbDefWidth->setMinimum(600);
        sbDefWidth->setMaximum(10000);
        sbDefWidth->setValue(1920);

        horizontalLayout_3->addWidget(sbDefWidth);

        label_2 = new QLabel(widget_3);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        sbDefHeight = new QSpinBox(widget_3);
        sbDefHeight->setObjectName("sbDefHeight");
        sbDefHeight->setEnabled(false);
        sbDefHeight->setMinimum(400);
        sbDefHeight->setMaximum(10000);
        sbDefHeight->setValue(1080);

        horizontalLayout_3->addWidget(sbDefHeight);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(widget_3);

        widget_5 = new QWidget(tab);
        widget_5->setObjectName("widget_5");
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget_5);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        sbStereoFOV = new QSpinBox(widget_5);
        sbStereoFOV->setObjectName("sbStereoFOV");
        sbStereoFOV->setEnabled(false);
        sbStereoFOV->setMinimum(30);
        sbStereoFOV->setMaximum(120);
        sbStereoFOV->setValue(60);

        horizontalLayout_4->addWidget(sbStereoFOV);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_2->addWidget(widget_5);

        tabWidget->addTab(tab, QString());
        tabTracking = new QWidget();
        tabTracking->setObjectName("tabTracking");
        verticalLayout_3 = new QVBoxLayout(tabTracking);
        verticalLayout_3->setObjectName("verticalLayout_3");
        widget_4 = new QWidget(tabTracking);
        widget_4->setObjectName("widget_4");
        gridLayout_4 = new QGridLayout(widget_4);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        cbNeutralX = new QCheckBox(widget_4);
        cbNeutralX->setObjectName("cbNeutralX");

        gridLayout_4->addWidget(cbNeutralX, 2, 0, 1, 1);

        cbNeutralZ = new QCheckBox(widget_4);
        cbNeutralZ->setObjectName("cbNeutralZ");

        gridLayout_4->addWidget(cbNeutralZ, 2, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 2, 3, 1, 1);

        label_5 = new QLabel(widget_4);
        label_5->setObjectName("label_5");

        gridLayout_4->addWidget(label_5, 1, 0, 1, 4);

        cbNeutralY = new QCheckBox(widget_4);
        cbNeutralY->setObjectName("cbNeutralY");
        cbNeutralY->setChecked(true);

        gridLayout_4->addWidget(cbNeutralY, 2, 1, 1, 1);

        cbEnablePositionalTracking = new QCheckBox(widget_4);
        cbEnablePositionalTracking->setObjectName("cbEnablePositionalTracking");
        cbEnablePositionalTracking->setChecked(true);

        gridLayout_4->addWidget(cbEnablePositionalTracking, 0, 0, 1, 4);


        verticalLayout_3->addWidget(widget_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        tabWidget->addTab(tabTracking, QString());
        tabInputs = new QWidget();
        tabInputs->setObjectName("tabInputs");
        verticalLayout_5 = new QVBoxLayout(tabInputs);
        verticalLayout_5->setObjectName("verticalLayout_5");
        widget = new QWidget(tabInputs);
        widget->setObjectName("widget");
        verticalLayout_6 = new QVBoxLayout(widget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        cbCatchExternalKeyboardKeysEvents = new QCheckBox(widget);
        cbCatchExternalKeyboardKeysEvents->setObjectName("cbCatchExternalKeyboardKeysEvents");

        verticalLayout_6->addWidget(cbCatchExternalKeyboardKeysEvents);


        verticalLayout_5->addWidget(widget);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        tabWidget->addTab(tabInputs, QString());
        tabDebug = new QWidget();
        tabDebug->setObjectName("tabDebug");
        verticalLayout_4 = new QVBoxLayout(tabDebug);
        verticalLayout_4->setObjectName("verticalLayout_4");
        gbCSharp = new QWidget(tabDebug);
        gbCSharp->setObjectName("gbCSharp");
        gridLayout = new QGridLayout(gbCSharp);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        cbCsharpDebugInfo = new QCheckBox(gbCSharp);
        cbCsharpDebugInfo->setObjectName("cbCsharpDebugInfo");

        gridLayout->addWidget(cbCsharpDebugInfo, 2, 0, 1, 1);

        cbDebug = new QCheckBox(gbCSharp);
        cbDebug->setObjectName("cbDebug");
        cbDebug->setEnabled(true);
        cbDebug->setChecked(true);

        gridLayout->addWidget(cbDebug, 0, 0, 1, 1);

        cbCatchComponentsExceptions = new QCheckBox(gbCSharp);
        cbCatchComponentsExceptions->setObjectName("cbCatchComponentsExceptions");
        cbCatchComponentsExceptions->setChecked(true);

        gridLayout->addWidget(cbCatchComponentsExceptions, 1, 0, 1, 1);


        verticalLayout_4->addWidget(gbCSharp);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        tabWidget->addTab(tabDebug, QString());

        gridLayout_2->addWidget(tabWidget, 1, 0, 1, 1);


        verticalLayout->addWidget(content);

        bottomButttons = new QFrame(SettingsUI);
        bottomButttons->setObjectName("bottomButttons");
        bottomButttons->setFrameShape(QFrame::StyledPanel);
        bottomButttons->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(bottomButttons);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pbReset = new QPushButton(bottomButttons);
        pbReset->setObjectName("pbReset");

        horizontalLayout_2->addWidget(pbReset);

        horizontalSpacer = new QSpacerItem(147, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pbOk = new QPushButton(bottomButttons);
        pbOk->setObjectName("pbOk");

        horizontalLayout_2->addWidget(pbOk);

        pbCancel = new QPushButton(bottomButttons);
        pbCancel->setObjectName("pbCancel");

        horizontalLayout_2->addWidget(pbCancel);


        verticalLayout->addWidget(bottomButttons);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SettingsUI);

        tabWidget->setCurrentIndex(0);
        cbDefinition->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(SettingsUI);
    } // setupUi

    void retranslateUi(QDialog *SettingsUI)
    {
        SettingsUI->setWindowTitle(QCoreApplication::translate("SettingsUI", "Settings", nullptr));
        label_3->setText(QCoreApplication::translate("SettingsUI", "<html><head/><body><p><span style=\" font-weight:600;\">Display mode</span></p></body></html>", nullptr));
        rbVrMode->setText(QCoreApplication::translate("SettingsUI", "VR", nullptr));
        rbFlatMode->setText(QCoreApplication::translate("SettingsUI", "Flat", nullptr));
        rbFlatStereoMode->setText(QCoreApplication::translate("SettingsUI", "Flat stereoscopic", nullptr));
        label_7->setText(QCoreApplication::translate("SettingsUI", "<html><head/><body><p><span style=\" font-weight:600;\">Monitor to use</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("SettingsUI", "(may crash if monitor doesn't exist)", nullptr));
        label_8->setText(QCoreApplication::translate("SettingsUI", "<b>Fullscreen</b>", nullptr));
        cbFullscreen->setText(QString());
        label_6->setText(QCoreApplication::translate("SettingsUI", "<html><head/><body><p><span style=\" font-weight:600;\">Screen resolution</span></p></body></html>", nullptr));
        cbDefinition->setItemText(0, QCoreApplication::translate("SettingsUI", "Custom", nullptr));
        cbDefinition->setItemText(1, QCoreApplication::translate("SettingsUI", "1280x1024", nullptr));
        cbDefinition->setItemText(2, QCoreApplication::translate("SettingsUI", "1920x1080", nullptr));
        cbDefinition->setItemText(3, QCoreApplication::translate("SettingsUI", "1920x1200", nullptr));
        cbDefinition->setItemText(4, QCoreApplication::translate("SettingsUI", "2560x1440", nullptr));

        label->setText(QCoreApplication::translate("SettingsUI", "<html><head/><body><p><span style=\" font-weight:600;\">Custom </span>width</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsUI", "height", nullptr));
        label_4->setText(QCoreApplication::translate("SettingsUI", "<html><head/><body><p><span style=\" font-weight:600;\">Cameras FOV\302\260</span> (only for stereoscopic mode)</p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SettingsUI", "Display", nullptr));
        cbNeutralX->setText(QCoreApplication::translate("SettingsUI", "X axis (Pitch)", nullptr));
        cbNeutralZ->setText(QCoreApplication::translate("SettingsUI", "Z axis (Roll)", nullptr));
        label_5->setText(QCoreApplication::translate("SettingsUI", "When clicking on play, define HMD current rotation as the neutral for:", nullptr));
        cbNeutralY->setText(QCoreApplication::translate("SettingsUI", "Y axis (Yaw)", nullptr));
        cbEnablePositionalTracking->setText(QCoreApplication::translate("SettingsUI", "Enable positional tracking", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTracking), QCoreApplication::translate("SettingsUI", "Tracking", nullptr));
        cbCatchExternalKeyboardKeysEvents->setText(QCoreApplication::translate("SettingsUI", "Catch keyboard  keys events even with no focus", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabInputs), QCoreApplication::translate("SettingsUI", "Inputs", nullptr));
        cbCsharpDebugInfo->setText(QCoreApplication::translate("SettingsUI", "Debug info in C# scripts  \n"
"(for getting files/lines/columns during errors, may be slower)", nullptr));
        cbDebug->setText(QCoreApplication::translate("SettingsUI", "ExVR debug mode (display debug top bar)", nullptr));
        cbCatchComponentsExceptions->setText(QCoreApplication::translate("SettingsUI", "Catch exceptions  of components functions calls (more errors details, may be slower)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDebug), QCoreApplication::translate("SettingsUI", "Debug", nullptr));
        pbReset->setText(QCoreApplication::translate("SettingsUI", "Reset", nullptr));
        pbOk->setText(QCoreApplication::translate("SettingsUI", "OK", nullptr));
        pbCancel->setText(QCoreApplication::translate("SettingsUI", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsUI: public Ui_SettingsUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
