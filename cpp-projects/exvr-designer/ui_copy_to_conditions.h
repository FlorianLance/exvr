/********************************************************************************
** Form generated from reading UI file 'copy_to_conditions.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPY_TO_CONDITIONS_H
#define UI_COPY_TO_CONDITIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CopyConditionToUiD
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *gbConditionsToBeErased;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QTabWidget *twRoutines;
    QLabel *label_3;
    QLabel *label_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbCheckAllConds;
    QPushButton *pbUncheckAllConds;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QListWidget *lwRoutinesNames;
    QWidget *wBot;
    QGridLayout *gridLayout;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *laConditionsCount;
    QFrame *line_2;
    QRadioButton *rbCopyBoth;
    QRadioButton *rbCopyActions;
    QRadioButton *rbCopyConnections;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CopyConditionToUiD)
    {
        if (CopyConditionToUiD->objectName().isEmpty())
            CopyConditionToUiD->setObjectName("CopyConditionToUiD");
        CopyConditionToUiD->setWindowModality(Qt::ApplicationModal);
        CopyConditionToUiD->resize(596, 613);
        CopyConditionToUiD->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(CopyConditionToUiD);
        verticalLayout->setObjectName("verticalLayout");
        gbConditionsToBeErased = new QWidget(CopyConditionToUiD);
        gbConditionsToBeErased->setObjectName("gbConditionsToBeErased");
        verticalLayout_3 = new QVBoxLayout(gbConditionsToBeErased);
        verticalLayout_3->setSpacing(4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(4, 4, 4, 4);
        widget_2 = new QWidget(gbConditionsToBeErased);
        widget_2->setObjectName("widget_2");
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(-1, -1, -1, 9);
        twRoutines = new QTabWidget(widget_2);
        twRoutines->setObjectName("twRoutines");

        gridLayout_2->addWidget(twRoutines, 1, 2, 1, 1);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 2, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        widget = new QWidget(widget_2);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbCheckAllConds = new QPushButton(widget);
        pbCheckAllConds->setObjectName("pbCheckAllConds");

        horizontalLayout->addWidget(pbCheckAllConds);

        pbUncheckAllConds = new QPushButton(widget);
        pbUncheckAllConds->setObjectName("pbUncheckAllConds");

        horizontalLayout->addWidget(pbUncheckAllConds);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addWidget(widget, 2, 2, 1, 1);

        line = new QFrame(widget_2);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_2->addWidget(line, 0, 1, 3, 1);

        lwRoutinesNames = new QListWidget(widget_2);
        lwRoutinesNames->setObjectName("lwRoutinesNames");

        gridLayout_2->addWidget(lwRoutinesNames, 1, 0, 2, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 1);
        gridLayout_2->setColumnStretch(2, 2);

        verticalLayout_3->addWidget(widget_2);

        wBot = new QWidget(gbConditionsToBeErased);
        wBot->setObjectName("wBot");
        wBot->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(wBot);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout_3->addWidget(wBot);

        widget_4 = new QWidget(gbConditionsToBeErased);
        widget_4->setObjectName("widget_4");
        verticalLayout_4 = new QVBoxLayout(widget_4);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        laConditionsCount = new QLabel(widget_4);
        laConditionsCount->setObjectName("laConditionsCount");

        verticalLayout_4->addWidget(laConditionsCount, 0, Qt::AlignHCenter);

        line_2 = new QFrame(widget_4);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_2);

        rbCopyBoth = new QRadioButton(widget_4);
        rbCopyBoth->setObjectName("rbCopyBoth");
        rbCopyBoth->setChecked(true);

        verticalLayout_4->addWidget(rbCopyBoth);

        rbCopyActions = new QRadioButton(widget_4);
        rbCopyActions->setObjectName("rbCopyActions");

        verticalLayout_4->addWidget(rbCopyActions);

        rbCopyConnections = new QRadioButton(widget_4);
        rbCopyConnections->setObjectName("rbCopyConnections");

        verticalLayout_4->addWidget(rbCopyConnections);


        verticalLayout_3->addWidget(widget_4);


        verticalLayout->addWidget(gbConditionsToBeErased);

        buttonBox = new QDialogButtonBox(CopyConditionToUiD);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CopyConditionToUiD);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, CopyConditionToUiD, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, CopyConditionToUiD, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(CopyConditionToUiD);
    } // setupUi

    void retranslateUi(QDialog *CopyConditionToUiD)
    {
        CopyConditionToUiD->setWindowTitle(QCoreApplication::translate("CopyConditionToUiD", "Copy current condition to...", nullptr));
        label_3->setText(QCoreApplication::translate("CopyConditionToUiD", "Selected routine conditions:", nullptr));
        label_2->setText(QCoreApplication::translate("CopyConditionToUiD", "Routines names:", nullptr));
        pbCheckAllConds->setText(QCoreApplication::translate("CopyConditionToUiD", "Check all", nullptr));
        pbUncheckAllConds->setText(QCoreApplication::translate("CopyConditionToUiD", "Uncheck all", nullptr));
        laConditionsCount->setText(QCoreApplication::translate("CopyConditionToUiD", "Copy will be applied on  0 condition.", nullptr));
        rbCopyBoth->setText(QCoreApplication::translate("CopyConditionToUiD", "Copy both actions and connections", nullptr));
        rbCopyActions->setText(QCoreApplication::translate("CopyConditionToUiD", "Copy only actions", nullptr));
        rbCopyConnections->setText(QCoreApplication::translate("CopyConditionToUiD", "Copy only connections (when possible)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CopyConditionToUiD: public Ui_CopyConditionToUiD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPY_TO_CONDITIONS_H
