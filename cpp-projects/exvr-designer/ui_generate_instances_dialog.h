/********************************************************************************
** Form generated from reading UI file 'generate_instances_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATE_INSTANCES_DIALOG_H
#define UI_GENERATE_INSTANCES_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateInstanceW
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *laSeed;
    QSpinBox *sbSeed;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line;
    QLabel *label_5;
    QFrame *frame_6;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QRadioButton *rbBasename;
    QRadioButton *rbManual;
    QTabWidget *twNamesOptions;
    QWidget *tBaseName;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_4;
    QGridLayout *gridLayout;
    QLabel *laBaseName;
    QSpinBox *sbNbInstancesFiles;
    QLabel *laNumber;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *leBaseName;
    QLabel *label_2;
    QSpinBox *sbStartId;
    QSpacerItem *verticalSpacer_2;
    QWidget *tManual;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pbAdd;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pbMoveUp;
    QPushButton *pbDelete;
    QPushButton *pbMoveDown;
    QSpacerItem *horizontalSpacer_7;
    QTextEdit *teAdd;
    QTableWidget *twNames;
    QLabel *laInstancesNamesList;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbCancel;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbGenerateFiles;

    void setupUi(QWidget *GenerateInstanceW)
    {
        if (GenerateInstanceW->objectName().isEmpty())
            GenerateInstanceW->setObjectName("GenerateInstanceW");
        GenerateInstanceW->resize(473, 485);
        verticalLayout = new QVBoxLayout(GenerateInstanceW);
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        label = new QLabel(GenerateInstanceW);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        frame_5 = new QFrame(GenerateInstanceW);
        frame_5->setObjectName("frame_5");
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Plain);
        verticalLayout_2 = new QVBoxLayout(frame_5);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(frame_5);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(3, 3, 3, 3);
        laSeed = new QLabel(frame);
        laSeed->setObjectName("laSeed");

        horizontalLayout_2->addWidget(laSeed);

        sbSeed = new QSpinBox(frame);
        sbSeed->setObjectName("sbSeed");
        sbSeed->setMaximum(1000000);

        horizontalLayout_2->addWidget(sbSeed);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        line = new QFrame(frame);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);


        verticalLayout_2->addWidget(frame);

        frame_6 = new QFrame(frame_5);
        frame_6->setObjectName("frame_6");
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_6);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 1, 1, 1);

        rbBasename = new QRadioButton(frame_6);
        rbBasename->setObjectName("rbBasename");
        rbBasename->setChecked(true);

        gridLayout_2->addWidget(rbBasename, 0, 0, 1, 1);

        rbManual = new QRadioButton(frame_6);
        rbManual->setObjectName("rbManual");

        gridLayout_2->addWidget(rbManual, 1, 0, 1, 1);


        verticalLayout_2->addWidget(frame_6);

        twNamesOptions = new QTabWidget(frame_5);
        twNamesOptions->setObjectName("twNamesOptions");
        tBaseName = new QWidget();
        tBaseName->setObjectName("tBaseName");
        verticalLayout_3 = new QVBoxLayout(tBaseName);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_4 = new QFrame(tBaseName);
        frame_4->setObjectName("frame_4");
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_4);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(3, 3, 3, 3);
        laBaseName = new QLabel(frame_4);
        laBaseName->setObjectName("laBaseName");

        gridLayout->addWidget(laBaseName, 1, 0, 1, 1);

        sbNbInstancesFiles = new QSpinBox(frame_4);
        sbNbInstancesFiles->setObjectName("sbNbInstancesFiles");
        sbNbInstancesFiles->setMinimum(1);
        sbNbInstancesFiles->setMaximum(1000);
        sbNbInstancesFiles->setValue(5);

        gridLayout->addWidget(sbNbInstancesFiles, 2, 2, 1, 1);

        laNumber = new QLabel(frame_4);
        laNumber->setObjectName("laNumber");

        gridLayout->addWidget(laNumber, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        leBaseName = new QLineEdit(frame_4);
        leBaseName->setObjectName("leBaseName");

        gridLayout->addWidget(leBaseName, 1, 2, 1, 1);

        label_2 = new QLabel(frame_4);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        sbStartId = new QSpinBox(frame_4);
        sbStartId->setObjectName("sbStartId");
        sbStartId->setMaximum(1000);

        gridLayout->addWidget(sbStartId, 3, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 4, 2, 1, 1);


        verticalLayout_3->addWidget(frame_4);

        twNamesOptions->addTab(tBaseName, QString());
        tManual = new QWidget();
        tManual->setObjectName("tManual");
        gridLayout_3 = new QGridLayout(tManual);
        gridLayout_3->setObjectName("gridLayout_3");
        widget = new QWidget(tManual);
        widget->setObjectName("widget");
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        pbAdd = new QPushButton(widget);
        pbAdd->setObjectName("pbAdd");
        pbAdd->setEnabled(false);

        horizontalLayout_3->addWidget(pbAdd);


        gridLayout_3->addWidget(widget, 1, 0, 1, 2);

        widget_2 = new QWidget(tManual);
        widget_2->setObjectName("widget_2");
        horizontalLayout_4 = new QHBoxLayout(widget_2);
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        pbMoveUp = new QPushButton(widget_2);
        pbMoveUp->setObjectName("pbMoveUp");

        horizontalLayout_4->addWidget(pbMoveUp);

        pbDelete = new QPushButton(widget_2);
        pbDelete->setObjectName("pbDelete");

        horizontalLayout_4->addWidget(pbDelete);

        pbMoveDown = new QPushButton(widget_2);
        pbMoveDown->setObjectName("pbMoveDown");

        horizontalLayout_4->addWidget(pbMoveDown);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);


        gridLayout_3->addWidget(widget_2, 5, 0, 1, 2);

        teAdd = new QTextEdit(tManual);
        teAdd->setObjectName("teAdd");

        gridLayout_3->addWidget(teAdd, 2, 0, 1, 2);

        twNames = new QTableWidget(tManual);
        if (twNames->columnCount() < 1)
            twNames->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twNames->setHorizontalHeaderItem(0, __qtablewidgetitem);
        twNames->setObjectName("twNames");

        gridLayout_3->addWidget(twNames, 4, 0, 1, 2);

        laInstancesNamesList = new QLabel(tManual);
        laInstancesNamesList->setObjectName("laInstancesNamesList");

        gridLayout_3->addWidget(laInstancesNamesList, 3, 0, 1, 2, Qt::AlignHCenter);

        gridLayout_3->setRowStretch(0, 1);
        gridLayout_3->setRowStretch(1, 1);
        gridLayout_3->setRowStretch(2, 90);
        gridLayout_3->setRowStretch(3, 1);
        gridLayout_3->setRowStretch(4, 180);
        gridLayout_3->setRowStretch(5, 1);
        twNamesOptions->addTab(tManual, QString());

        verticalLayout_2->addWidget(twNamesOptions);


        verticalLayout->addWidget(frame_5);

        frame_2 = new QFrame(GenerateInstanceW);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pbCancel = new QPushButton(frame_2);
        pbCancel->setObjectName("pbCancel");

        horizontalLayout->addWidget(pbCancel);

        horizontalSpacer = new QSpacerItem(48, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbGenerateFiles = new QPushButton(frame_2);
        pbGenerateFiles->setObjectName("pbGenerateFiles");

        horizontalLayout->addWidget(pbGenerateFiles);


        verticalLayout->addWidget(frame_2);


        retranslateUi(GenerateInstanceW);

        twNamesOptions->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GenerateInstanceW);
    } // setupUi

    void retranslateUi(QWidget *GenerateInstanceW)
    {
        GenerateInstanceW->setWindowTitle(QCoreApplication::translate("GenerateInstanceW", "Instances generator", nullptr));
        label->setText(QCoreApplication::translate("GenerateInstanceW", "<b>Generate randomized instances files to be played by the current experiment:</b>", nullptr));
        laSeed->setText(QCoreApplication::translate("GenerateInstanceW", "Randomization seed:", nullptr));
#if QT_CONFIG(tooltip)
        sbSeed->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("GenerateInstanceW", "using a speciic seed for an experiment\n"
" will always create the same randomization", nullptr));
        rbBasename->setText(QCoreApplication::translate("GenerateInstanceW", "Use names defined by a basename and and id", nullptr));
        rbManual->setText(QCoreApplication::translate("GenerateInstanceW", "Use names defined manually", nullptr));
        laBaseName->setText(QCoreApplication::translate("GenerateInstanceW", "Base name of instances XML files:", nullptr));
        laNumber->setText(QCoreApplication::translate("GenerateInstanceW", "Nb of instances files to generate", nullptr));
        leBaseName->setText(QCoreApplication::translate("GenerateInstanceW", "instance_", nullptr));
        label_2->setText(QCoreApplication::translate("GenerateInstanceW", "Start id:", nullptr));
        twNamesOptions->setTabText(twNamesOptions->indexOf(tBaseName), QCoreApplication::translate("GenerateInstanceW", "Basename", nullptr));
        label_4->setText(QCoreApplication::translate("GenerateInstanceW", "Instances names to add:", nullptr));
        pbAdd->setText(QCoreApplication::translate("GenerateInstanceW", "Add", nullptr));
        pbMoveUp->setText(QCoreApplication::translate("GenerateInstanceW", "Move up", nullptr));
        pbDelete->setText(QCoreApplication::translate("GenerateInstanceW", "Delete", nullptr));
        pbMoveDown->setText(QCoreApplication::translate("GenerateInstanceW", "Move down", nullptr));
        teAdd->setHtml(QCoreApplication::translate("GenerateInstanceW", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">default_instance_name_0</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">default_instance_name_1</p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = twNames->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GenerateInstanceW", "Name", nullptr));
        laInstancesNamesList->setText(QCoreApplication::translate("GenerateInstanceW", "Instances names list (0)", nullptr));
        twNamesOptions->setTabText(twNamesOptions->indexOf(tManual), QCoreApplication::translate("GenerateInstanceW", "Manual", nullptr));
        pbCancel->setText(QCoreApplication::translate("GenerateInstanceW", "Close", nullptr));
        pbGenerateFiles->setText(QCoreApplication::translate("GenerateInstanceW", "Generate instances", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenerateInstanceW: public Ui_GenerateInstanceW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATE_INSTANCES_DIALOG_H
