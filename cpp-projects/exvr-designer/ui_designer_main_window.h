/********************************************************************************
** Form generated from reading UI file 'designer_main_window.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESIGNER_MAIN_WINDOW_H
#define UI_DESIGNER_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExVrMainUI
{
public:
    QAction *actionNew_project;
    QAction *actionOpen_project;
    QAction *actionSave_as;
    QAction *actionSave_project_as;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *wMiddle;
    QVBoxLayout *vlExpDesigner;
    QWidget *wFlow;
    QHBoxLayout *horizontalLayout_3;
    QFrame *wZoom;
    QVBoxLayout *verticalLayout;
    QPushButton *pbResize;
    QSlider *vsZoom;
    QScrollArea *saFlow;
    QWidget *sacFlow;
    QHBoxLayout *hlFlows;
    QWidget *wRoutines;
    QFrame *fState;
    QHBoxLayout *horizontalLayout;
    QLabel *laExVRExpState;
    QFrame *line1;
    QLabel *laExpState;
    QFrame *line2;
    QLabel *laElementName;
    QFrame *line3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLabel *laElementCurrentTime;
    QLabel *laExpTime;
    QProgressBar *pgbElementCurrentTIme;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ExVrMainUI)
    {
        if (ExVrMainUI->objectName().isEmpty())
            ExVrMainUI->setObjectName("ExVrMainUI");
        ExVrMainUI->resize(1665, 894);
        ExVrMainUI->setStyleSheet(QString::fromUtf8(""));
        actionNew_project = new QAction(ExVrMainUI);
        actionNew_project->setObjectName("actionNew_project");
        actionOpen_project = new QAction(ExVrMainUI);
        actionOpen_project->setObjectName("actionOpen_project");
        actionSave_as = new QAction(ExVrMainUI);
        actionSave_as->setObjectName("actionSave_as");
        actionSave_project_as = new QAction(ExVrMainUI);
        actionSave_project_as->setObjectName("actionSave_project_as");
        actionExit = new QAction(ExVrMainUI);
        actionExit->setObjectName("actionExit");
        centralWidget = new QWidget(ExVrMainUI);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(2, 2, 2, 2);
        wMiddle = new QWidget(centralWidget);
        wMiddle->setObjectName("wMiddle");
        vlExpDesigner = new QVBoxLayout(wMiddle);
        vlExpDesigner->setSpacing(2);
        vlExpDesigner->setContentsMargins(11, 11, 11, 11);
        vlExpDesigner->setObjectName("vlExpDesigner");
        vlExpDesigner->setContentsMargins(0, 0, 0, 0);
        wFlow = new QWidget(wMiddle);
        wFlow->setObjectName("wFlow");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(wFlow->sizePolicy().hasHeightForWidth());
        wFlow->setSizePolicy(sizePolicy);
        wFlow->setMinimumSize(QSize(0, 0));
        horizontalLayout_3 = new QHBoxLayout(wFlow);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        wZoom = new QFrame(wFlow);
        wZoom->setObjectName("wZoom");
        wZoom->setMinimumSize(QSize(0, 0));
        wZoom->setStyleSheet(QString::fromUtf8("QFrame{\n"
"	background-color:rgb(45,45,45);\n"
"}"));
        wZoom->setFrameShape(QFrame::Box);
        wZoom->setFrameShadow(QFrame::Sunken);
        verticalLayout = new QVBoxLayout(wZoom);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 2, 0, 2);
        pbResize = new QPushButton(wZoom);
        pbResize->setObjectName("pbResize");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pbResize->sizePolicy().hasHeightForWidth());
        pbResize->setSizePolicy(sizePolicy1);
        pbResize->setMinimumSize(QSize(0, 0));
        pbResize->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/Expand"), QSize(), QIcon::Normal, QIcon::Off);
        pbResize->setIcon(icon);
        pbResize->setIconSize(QSize(14, 14));

        verticalLayout->addWidget(pbResize, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        vsZoom = new QSlider(wZoom);
        vsZoom->setObjectName("vsZoom");
        vsZoom->setMinimum(5);
        vsZoom->setMaximum(50);
        vsZoom->setSingleStep(1);
        vsZoom->setValue(30);
        vsZoom->setOrientation(Qt::Vertical);

        verticalLayout->addWidget(vsZoom, 0, Qt::AlignHCenter);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 50);

        horizontalLayout_3->addWidget(wZoom);

        saFlow = new QScrollArea(wFlow);
        saFlow->setObjectName("saFlow");
        sizePolicy1.setHeightForWidth(saFlow->sizePolicy().hasHeightForWidth());
        saFlow->setSizePolicy(sizePolicy1);
        saFlow->setFrameShape(QFrame::Box);
        saFlow->setWidgetResizable(true);
        sacFlow = new QWidget();
        sacFlow->setObjectName("sacFlow");
        sacFlow->setGeometry(QRect(0, 0, 1622, 244));
        hlFlows = new QHBoxLayout(sacFlow);
        hlFlows->setSpacing(0);
        hlFlows->setContentsMargins(11, 11, 11, 11);
        hlFlows->setObjectName("hlFlows");
        hlFlows->setContentsMargins(0, 0, 0, 0);
        saFlow->setWidget(sacFlow);

        horizontalLayout_3->addWidget(saFlow);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 50);

        vlExpDesigner->addWidget(wFlow);

        wRoutines = new QWidget(wMiddle);
        wRoutines->setObjectName("wRoutines");

        vlExpDesigner->addWidget(wRoutines);

        vlExpDesigner->setStretch(0, 3);
        vlExpDesigner->setStretch(1, 7);

        gridLayout->addWidget(wMiddle, 1, 0, 1, 1);

        fState = new QFrame(centralWidget);
        fState->setObjectName("fState");
        fState->setMinimumSize(QSize(0, 0));
        fState->setStyleSheet(QString::fromUtf8("QFrame{\n"
"	background-color:rgb(45,45,45);\n"
"}\n"
"QLabel{\n"
"	color:rgb(255,255,255);\n"
"}"));
        fState->setFrameShape(QFrame::Box);
        fState->setFrameShadow(QFrame::Sunken);
        horizontalLayout = new QHBoxLayout(fState);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(4, 4, 4, 4);
        laExVRExpState = new QLabel(fState);
        laExVRExpState->setObjectName("laExVRExpState");

        horizontalLayout->addWidget(laExVRExpState);

        line1 = new QFrame(fState);
        line1->setObjectName("line1");
        line1->setStyleSheet(QString::fromUtf8("background-color: white;"));
        line1->setFrameShape(QFrame::VLine);
        line1->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line1);

        laExpState = new QLabel(fState);
        laExpState->setObjectName("laExpState");

        horizontalLayout->addWidget(laExpState);

        line2 = new QFrame(fState);
        line2->setObjectName("line2");
        line2->setStyleSheet(QString::fromUtf8("background-color: white;"));
        line2->setFrameShape(QFrame::VLine);
        line2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line2);

        laElementName = new QLabel(fState);
        laElementName->setObjectName("laElementName");

        horizontalLayout->addWidget(laElementName);

        line3 = new QFrame(fState);
        line3->setObjectName("line3");
        line3->setStyleSheet(QString::fromUtf8("background-color: white;"));
        line3->setFrameShape(QFrame::VLine);
        line3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(fState);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        laElementCurrentTime = new QLabel(fState);
        laElementCurrentTime->setObjectName("laElementCurrentTime");

        horizontalLayout->addWidget(laElementCurrentTime);

        laExpTime = new QLabel(fState);
        laExpTime->setObjectName("laExpTime");

        horizontalLayout->addWidget(laExpTime);

        pgbElementCurrentTIme = new QProgressBar(fState);
        pgbElementCurrentTIme->setObjectName("pgbElementCurrentTIme");
        pgbElementCurrentTIme->setMaximumSize(QSize(150, 16777215));
        pgbElementCurrentTIme->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"	color : white;\n"
"}\n"
"\n"
""));
        pgbElementCurrentTIme->setValue(0);

        horizontalLayout->addWidget(pgbElementCurrentTIme);


        gridLayout->addWidget(fState, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 30);
        gridLayout->setRowMinimumHeight(0, 1);
        gridLayout->setRowMinimumHeight(1, 30);
        ExVrMainUI->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ExVrMainUI);
        statusBar->setObjectName("statusBar");
        ExVrMainUI->setStatusBar(statusBar);

        retranslateUi(ExVrMainUI);

        QMetaObject::connectSlotsByName(ExVrMainUI);
    } // setupUi

    void retranslateUi(QMainWindow *ExVrMainUI)
    {
        ExVrMainUI->setWindowTitle(QCoreApplication::translate("ExVrMainUI", "ExpyVR3", nullptr));
        actionNew_project->setText(QCoreApplication::translate("ExVrMainUI", "New project", nullptr));
        actionOpen_project->setText(QCoreApplication::translate("ExVrMainUI", "Open project", nullptr));
        actionSave_as->setText(QCoreApplication::translate("ExVrMainUI", "Save as", nullptr));
        actionSave_project_as->setText(QCoreApplication::translate("ExVrMainUI", "Save project as..;", nullptr));
        actionExit->setText(QCoreApplication::translate("ExVrMainUI", "Exit", nullptr));
        pbResize->setText(QString());
        laExVRExpState->setText(QCoreApplication::translate("ExVrMainUI", "...", nullptr));
        laExpState->setText(QCoreApplication::translate("ExVrMainUI", "...", nullptr));
        laElementName->setText(QCoreApplication::translate("ExVrMainUI", "...", nullptr));
        label->setText(QCoreApplication::translate("ExVrMainUI", "Times (s):", nullptr));
        laElementCurrentTime->setText(QCoreApplication::translate("ExVrMainUI", "[Current] ...", nullptr));
        laExpTime->setText(QCoreApplication::translate("ExVrMainUI", "[Total] ...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExVrMainUI: public Ui_ExVrMainUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESIGNER_MAIN_WINDOW_H
