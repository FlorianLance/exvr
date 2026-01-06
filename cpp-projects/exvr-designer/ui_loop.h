/********************************************************************************
** Form generated from reading UI file 'loop.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOOP_H
#define UI_LOOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoopW
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hl1;
    QLabel *laNameT;
    QLabel *laName;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pbSetName;
    QFrame *line2;
    QHBoxLayout *hl2;
    QLabel *laLoopStyle;
    QComboBox *cbLoopStyle;
    QSpacerItem *horizontalSpacer_3;
    QWidget *hl3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *cbNoFollowingValues;
    QSpacerItem *horizontalSpacer_8;
    QFrame *line1;
    QHBoxLayout *hl4;
    QLabel *laNbReps;
    QSpinBox *sbNbReps;
    QLabel *label;
    QSpinBox *sbN;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line3;
    QWidget *wSetList;
    QVBoxLayout *verticalLayout_2;
    QWidget *wAddSet;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbAdd;
    QTextEdit *teAdd;
    QSpinBox *sbRowId;
    QLabel *laNewSet;
    QLabel *label_3;
    QLabel *laSetList;
    QTableWidget *twSets;
    QWidget *wChooseFile;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pbInitFromFile;
    QFrame *line4;
    QLabel *label_2;
    QTextEdit *teInformations;

    void setupUi(QWidget *LoopW)
    {
        if (LoopW->objectName().isEmpty())
            LoopW->setObjectName("LoopW");
        LoopW->resize(597, 898);
        LoopW->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(LoopW);
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(4, 4, 4, 4);
        hl1 = new QHBoxLayout();
        hl1->setObjectName("hl1");
        laNameT = new QLabel(LoopW);
        laNameT->setObjectName("laNameT");

        hl1->addWidget(laNameT);

        laName = new QLabel(LoopW);
        laName->setObjectName("laName");

        hl1->addWidget(laName);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hl1->addItem(horizontalSpacer_4);

        pbSetName = new QPushButton(LoopW);
        pbSetName->setObjectName("pbSetName");
        pbSetName->setMinimumSize(QSize(0, 0));

        hl1->addWidget(pbSetName);

        hl1->setStretch(0, 1);
        hl1->setStretch(1, 10);
        hl1->setStretch(2, 1);
        hl1->setStretch(3, 1);

        verticalLayout->addLayout(hl1);

        line2 = new QFrame(LoopW);
        line2->setObjectName("line2");
        line2->setFrameShape(QFrame::Shape::HLine);
        line2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line2);

        hl2 = new QHBoxLayout();
        hl2->setObjectName("hl2");
        laLoopStyle = new QLabel(LoopW);
        laLoopStyle->setObjectName("laLoopStyle");

        hl2->addWidget(laLoopStyle);

        cbLoopStyle = new QComboBox(LoopW);
        cbLoopStyle->addItem(QString());
        cbLoopStyle->addItem(QString());
        cbLoopStyle->addItem(QString());
        cbLoopStyle->addItem(QString());
        cbLoopStyle->addItem(QString());
        cbLoopStyle->addItem(QString());
        cbLoopStyle->addItem(QString());
        cbLoopStyle->addItem(QString());
        cbLoopStyle->addItem(QString());
        cbLoopStyle->setObjectName("cbLoopStyle");

        hl2->addWidget(cbLoopStyle);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hl2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(hl2);

        hl3 = new QWidget(LoopW);
        hl3->setObjectName("hl3");
        hl3->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(hl3);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cbNoFollowingValues = new QCheckBox(hl3);
        cbNoFollowingValues->setObjectName("cbNoFollowingValues");
        cbNoFollowingValues->setEnabled(true);

        horizontalLayout->addWidget(cbNoFollowingValues);

        horizontalSpacer_8 = new QSpacerItem(132, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);


        verticalLayout->addWidget(hl3);

        line1 = new QFrame(LoopW);
        line1->setObjectName("line1");
        line1->setFrameShape(QFrame::Shape::HLine);
        line1->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line1);

        hl4 = new QHBoxLayout();
        hl4->setObjectName("hl4");
        laNbReps = new QLabel(LoopW);
        laNbReps->setObjectName("laNbReps");

        hl4->addWidget(laNbReps);

        sbNbReps = new QSpinBox(LoopW);
        sbNbReps->setObjectName("sbNbReps");
        sbNbReps->setMinimum(1);
        sbNbReps->setMaximum(1000);

        hl4->addWidget(sbNbReps);

        label = new QLabel(LoopW);
        label->setObjectName("label");

        hl4->addWidget(label);

        sbN = new QSpinBox(LoopW);
        sbN->setObjectName("sbN");
        sbN->setEnabled(false);
        sbN->setMinimum(1);
        sbN->setMaximum(100);

        hl4->addWidget(sbN);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hl4->addItem(horizontalSpacer_2);

        hl4->setStretch(0, 1);
        hl4->setStretch(1, 1);

        verticalLayout->addLayout(hl4);

        line3 = new QFrame(LoopW);
        line3->setObjectName("line3");
        line3->setFrameShape(QFrame::Shape::HLine);
        line3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line3);

        wSetList = new QWidget(LoopW);
        wSetList->setObjectName("wSetList");
        wSetList->setMinimumSize(QSize(0, 300));
        verticalLayout_2 = new QVBoxLayout(wSetList);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 6, 0, 0);
        wAddSet = new QWidget(wSetList);
        wAddSet->setObjectName("wAddSet");
        gridLayout_2 = new QGridLayout(wAddSet);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        pbAdd = new QPushButton(wAddSet);
        pbAdd->setObjectName("pbAdd");
        pbAdd->setEnabled(false);
        pbAdd->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(pbAdd, 0, 5, 1, 1);

        teAdd = new QTextEdit(wAddSet);
        teAdd->setObjectName("teAdd");

        gridLayout_2->addWidget(teAdd, 1, 0, 1, 6);

        sbRowId = new QSpinBox(wAddSet);
        sbRowId->setObjectName("sbRowId");

        gridLayout_2->addWidget(sbRowId, 0, 4, 1, 1);

        laNewSet = new QLabel(wAddSet);
        laNewSet->setObjectName("laNewSet");

        gridLayout_2->addWidget(laNewSet, 0, 0, 1, 1);

        label_3 = new QLabel(wAddSet);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 3, 1, 1);


        verticalLayout_2->addWidget(wAddSet);

        laSetList = new QLabel(wSetList);
        laSetList->setObjectName("laSetList");

        verticalLayout_2->addWidget(laSetList, 0, Qt::AlignHCenter);

        twSets = new QTableWidget(wSetList);
        if (twSets->columnCount() < 5)
            twSets->setColumnCount(5);
        if (twSets->rowCount() < 1)
            twSets->setRowCount(1);
        twSets->setObjectName("twSets");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(twSets->sizePolicy().hasHeightForWidth());
        twSets->setSizePolicy(sizePolicy);
        twSets->setShowGrid(true);
        twSets->setRowCount(1);
        twSets->setColumnCount(5);
        twSets->horizontalHeader()->setVisible(true);
        twSets->horizontalHeader()->setCascadingSectionResizes(false);
        twSets->horizontalHeader()->setMinimumSectionSize(10);
        twSets->horizontalHeader()->setHighlightSections(false);
        twSets->horizontalHeader()->setStretchLastSection(false);
        twSets->verticalHeader()->setVisible(false);
        twSets->verticalHeader()->setHighlightSections(false);

        verticalLayout_2->addWidget(twSets);

        wChooseFile = new QWidget(wSetList);
        wChooseFile->setObjectName("wChooseFile");
        gridLayout = new QGridLayout(wChooseFile);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(366, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 3, 4, 1);

        pbInitFromFile = new QPushButton(wChooseFile);
        pbInitFromFile->setObjectName("pbInitFromFile");

        gridLayout->addWidget(pbInitFromFile, 0, 4, 1, 1);


        verticalLayout_2->addWidget(wChooseFile);

        verticalLayout_2->setStretch(0, 20);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 30);
        verticalLayout_2->setStretch(3, 1);

        verticalLayout->addWidget(wSetList);

        line4 = new QFrame(LoopW);
        line4->setObjectName("line4");
        line4->setFrameShape(QFrame::Shape::HLine);
        line4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line4);

        label_2 = new QLabel(LoopW);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        teInformations = new QTextEdit(LoopW);
        teInformations->setObjectName("teInformations");

        verticalLayout->addWidget(teInformations);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 1);
        verticalLayout->setStretch(5, 1);
        verticalLayout->setStretch(6, 40);
        verticalLayout->setStretch(7, 40);
        verticalLayout->setStretch(8, 1);
        verticalLayout->setStretch(9, 1);
        verticalLayout->setStretch(10, 4);

        retranslateUi(LoopW);

        QMetaObject::connectSlotsByName(LoopW);
    } // setupUi

    void retranslateUi(QWidget *LoopW)
    {
        LoopW->setWindowTitle(QCoreApplication::translate("LoopW", "Form", nullptr));
        laNameT->setText(QCoreApplication::translate("LoopW", "Name:", nullptr));
        laName->setText(QString());
        pbSetName->setText(QCoreApplication::translate("LoopW", "Set name", nullptr));
        laLoopStyle->setText(QCoreApplication::translate("LoopW", "Loop style", nullptr));
        cbLoopStyle->setItemText(0, QCoreApplication::translate("LoopW", "Fixed", nullptr));
        cbLoopStyle->setItemText(1, QCoreApplication::translate("LoopW", "Random [every instance]", nullptr));
        cbLoopStyle->setItemText(2, QCoreApplication::translate("LoopW", "Shuffle [every instance]", nullptr));
        cbLoopStyle->setItemText(3, QCoreApplication::translate("LoopW", "Fixed [random start]", nullptr));
        cbLoopStyle->setItemText(4, QCoreApplication::translate("LoopW", "Fixed [shift start at each instance]", nullptr));
        cbLoopStyle->setItemText(5, QCoreApplication::translate("LoopW", "Random [one for all instances]", nullptr));
        cbLoopStyle->setItemText(6, QCoreApplication::translate("LoopW", "Shuffle [one for all instances]", nullptr));
        cbLoopStyle->setItemText(7, QCoreApplication::translate("LoopW", "Random [every N instances]", nullptr));
        cbLoopStyle->setItemText(8, QCoreApplication::translate("LoopW", "Shuffle [every N instances]", nullptr));

        cbNoFollowingValues->setText(QCoreApplication::translate("LoopW", "No following values (random and shuffle)", nullptr));
        laNbReps->setText(QCoreApplication::translate("LoopW", "Number of repetitions", nullptr));
        label->setText(QCoreApplication::translate("LoopW", "N", nullptr));
        pbAdd->setText(QCoreApplication::translate("LoopW", "Add", nullptr));
        laNewSet->setText(QCoreApplication::translate("LoopW", "Sets to add (one per line)", nullptr));
        label_3->setText(QCoreApplication::translate("LoopW", "Row:", nullptr));
        laSetList->setText(QCoreApplication::translate("LoopW", "Set list", nullptr));
        pbInitFromFile->setText(QCoreApplication::translate("LoopW", "Init from file", nullptr));
        label_2->setText(QCoreApplication::translate("LoopW", "Informations displayed from tooltip:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoopW: public Ui_LoopW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOOP_H
