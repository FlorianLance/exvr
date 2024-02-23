/********************************************************************************
** Form generated from reading UI file 'routine.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROUTINE_H
#define UI_ROUTINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoutineW
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *laNameT;
    QLabel *laName;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbSetName;
    QFrame *line1;
    QCheckBox *cbIsARandomizer;
    QLabel *laConditions;
    QListWidget *lwConditions;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pbUp;
    QPushButton *pbDown;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line2;
    QLabel *label;
    QTextEdit *teInformations;

    void setupUi(QWidget *RoutineW)
    {
        if (RoutineW->objectName().isEmpty())
            RoutineW->setObjectName("RoutineW");
        RoutineW->resize(298, 397);
        verticalLayout = new QVBoxLayout(RoutineW);
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(4, 4, 4, 4);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 1, 2, 1);
        laNameT = new QLabel(RoutineW);
        laNameT->setObjectName("laNameT");

        horizontalLayout->addWidget(laNameT);

        laName = new QLabel(RoutineW);
        laName->setObjectName("laName");

        horizontalLayout->addWidget(laName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbSetName = new QPushButton(RoutineW);
        pbSetName->setObjectName("pbSetName");
        pbSetName->setMinimumSize(QSize(50, 0));

        horizontalLayout->addWidget(pbSetName);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 10);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout);

        line1 = new QFrame(RoutineW);
        line1->setObjectName("line1");
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line1);

        cbIsARandomizer = new QCheckBox(RoutineW);
        cbIsARandomizer->setObjectName("cbIsARandomizer");

        verticalLayout->addWidget(cbIsARandomizer);

        laConditions = new QLabel(RoutineW);
        laConditions->setObjectName("laConditions");

        verticalLayout->addWidget(laConditions);

        lwConditions = new QListWidget(RoutineW);
        lwConditions->setObjectName("lwConditions");
        lwConditions->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(lwConditions);

        frame = new QFrame(RoutineW);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        pbUp = new QPushButton(frame);
        pbUp->setObjectName("pbUp");
        pbUp->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(pbUp);

        pbDown = new QPushButton(frame);
        pbDown->setObjectName("pbDown");
        pbDown->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(pbDown);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(frame);

        line2 = new QFrame(RoutineW);
        line2->setObjectName("line2");
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line2);

        label = new QLabel(RoutineW);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        teInformations = new QTextEdit(RoutineW);
        teInformations->setObjectName("teInformations");

        verticalLayout->addWidget(teInformations);


        retranslateUi(RoutineW);

        QMetaObject::connectSlotsByName(RoutineW);
    } // setupUi

    void retranslateUi(QWidget *RoutineW)
    {
        RoutineW->setWindowTitle(QCoreApplication::translate("RoutineW", "Form", nullptr));
        laNameT->setText(QCoreApplication::translate("RoutineW", "Name:", nullptr));
        laName->setText(QString());
        pbSetName->setText(QCoreApplication::translate("RoutineW", "Set name", nullptr));
        cbIsARandomizer->setText(QCoreApplication::translate("RoutineW", "Set as a randomizer", nullptr));
        laConditions->setText(QCoreApplication::translate("RoutineW", "Conditions", nullptr));
        pbUp->setText(QCoreApplication::translate("RoutineW", "Up", nullptr));
        pbDown->setText(QCoreApplication::translate("RoutineW", "Down", nullptr));
        label->setText(QCoreApplication::translate("RoutineW", "Informations displayed from tooltip:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoutineW: public Ui_RoutineW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROUTINE_H
