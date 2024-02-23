/********************************************************************************
** Form generated from reading UI file 'conditions_selecter.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONDITIONS_SELECTER_H
#define UI_CONDITIONS_SELECTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConditionsSelecter
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *gbTop;
    QVBoxLayout *verticalLayout_3;
    QWidget *wTop;
    QWidget *wMid;
    QGridLayout *gridLayout_2;
    QTabWidget *twRoutines;
    QLabel *routinesNames;
    QLabel *selectedRoutinesConditions;
    QWidget *checkW;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *pbCheckRoutineConds;
    QPushButton *pbUncheckRoutineConds;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbApplyToSelection;
    QFrame *line;
    QListWidget *lwRoutinesNames;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QPushButton *pbCheckAllConds;
    QPushButton *pbUncheckAllConds;
    QSpacerItem *horizontalSpacer_3;
    QWidget *wBot;
    QDialogButtonBox *validateButtonBox;

    void setupUi(QWidget *ConditionsSelecter)
    {
        if (ConditionsSelecter->objectName().isEmpty())
            ConditionsSelecter->setObjectName("ConditionsSelecter");
        ConditionsSelecter->resize(1174, 669);
        verticalLayout = new QVBoxLayout(ConditionsSelecter);
        verticalLayout->setObjectName("verticalLayout");
        gbTop = new QWidget(ConditionsSelecter);
        gbTop->setObjectName("gbTop");
        verticalLayout_3 = new QVBoxLayout(gbTop);
        verticalLayout_3->setSpacing(4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(4, 4, 4, 4);
        wTop = new QWidget(gbTop);
        wTop->setObjectName("wTop");

        verticalLayout_3->addWidget(wTop);

        wMid = new QWidget(gbTop);
        wMid->setObjectName("wMid");
        gridLayout_2 = new QGridLayout(wMid);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setHorizontalSpacing(5);
        gridLayout_2->setVerticalSpacing(2);
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        twRoutines = new QTabWidget(wMid);
        twRoutines->setObjectName("twRoutines");

        gridLayout_2->addWidget(twRoutines, 1, 2, 1, 1);

        routinesNames = new QLabel(wMid);
        routinesNames->setObjectName("routinesNames");

        gridLayout_2->addWidget(routinesNames, 0, 0, 1, 1);

        selectedRoutinesConditions = new QLabel(wMid);
        selectedRoutinesConditions->setObjectName("selectedRoutinesConditions");

        gridLayout_2->addWidget(selectedRoutinesConditions, 0, 2, 1, 1);

        checkW = new QWidget(wMid);
        checkW->setObjectName("checkW");
        horizontalLayout = new QHBoxLayout(checkW);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(checkW);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        pbCheckRoutineConds = new QPushButton(checkW);
        pbCheckRoutineConds->setObjectName("pbCheckRoutineConds");

        horizontalLayout->addWidget(pbCheckRoutineConds);

        pbUncheckRoutineConds = new QPushButton(checkW);
        pbUncheckRoutineConds->setObjectName("pbUncheckRoutineConds");

        horizontalLayout->addWidget(pbUncheckRoutineConds);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pbApplyToSelection = new QPushButton(checkW);
        pbApplyToSelection->setObjectName("pbApplyToSelection");

        horizontalLayout->addWidget(pbApplyToSelection);


        gridLayout_2->addWidget(checkW, 2, 2, 1, 1);

        line = new QFrame(wMid);
        line->setObjectName("line");
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 0, 1, 3, 1);

        lwRoutinesNames = new QListWidget(wMid);
        lwRoutinesNames->setObjectName("lwRoutinesNames");

        gridLayout_2->addWidget(lwRoutinesNames, 1, 0, 1, 1);

        widget = new QWidget(wMid);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 0));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        pbCheckAllConds = new QPushButton(widget);
        pbCheckAllConds->setObjectName("pbCheckAllConds");

        horizontalLayout_2->addWidget(pbCheckAllConds);

        pbUncheckAllConds = new QPushButton(widget);
        pbUncheckAllConds->setObjectName("pbUncheckAllConds");

        horizontalLayout_2->addWidget(pbUncheckAllConds);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        gridLayout_2->addWidget(widget, 2, 0, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 1);
        gridLayout_2->setColumnStretch(2, 2);

        verticalLayout_3->addWidget(wMid);

        wBot = new QWidget(gbTop);
        wBot->setObjectName("wBot");
        wBot->setMinimumSize(QSize(0, 0));

        verticalLayout_3->addWidget(wBot);


        verticalLayout->addWidget(gbTop);

        validateButtonBox = new QDialogButtonBox(ConditionsSelecter);
        validateButtonBox->setObjectName("validateButtonBox");
        validateButtonBox->setOrientation(Qt::Horizontal);
        validateButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(validateButtonBox);


        retranslateUi(ConditionsSelecter);

        QMetaObject::connectSlotsByName(ConditionsSelecter);
    } // setupUi

    void retranslateUi(QWidget *ConditionsSelecter)
    {
        ConditionsSelecter->setWindowTitle(QCoreApplication::translate("ConditionsSelecter", "Form", nullptr));
        routinesNames->setText(QCoreApplication::translate("ConditionsSelecter", "Routines names:", nullptr));
        selectedRoutinesConditions->setText(QCoreApplication::translate("ConditionsSelecter", "Selected routine conditions:", nullptr));
        label->setText(QCoreApplication::translate("ConditionsSelecter", "Routine conditions:", nullptr));
        pbCheckRoutineConds->setText(QCoreApplication::translate("ConditionsSelecter", "Check", nullptr));
        pbUncheckRoutineConds->setText(QCoreApplication::translate("ConditionsSelecter", "Uncheck", nullptr));
        pbApplyToSelection->setText(QCoreApplication::translate("ConditionsSelecter", "Apply to selection", nullptr));
        label_2->setText(QCoreApplication::translate("ConditionsSelecter", "All conditions:", nullptr));
        pbCheckAllConds->setText(QCoreApplication::translate("ConditionsSelecter", "Check", nullptr));
        pbUncheckAllConds->setText(QCoreApplication::translate("ConditionsSelecter", "Uncheck", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConditionsSelecter: public Ui_ConditionsSelecter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONDITIONS_SELECTER_H
