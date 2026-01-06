/********************************************************************************
** Form generated from reading UI file 'condition.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONDITION_H
#define UI_CONDITION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConditionUiW
{
public:
    QVBoxLayout *vlMain;
    QFrame *fTop;
    QVBoxLayout *verticalLayout;
    QWidget *wOptions;
    QHBoxLayout *hlOptions;
    QWidget *wLeftOptions;
    QHBoxLayout *hlLeftOptions;
    QLabel *laMax;
    QDoubleSpinBox *dsbDuration;
    QLabel *laScale;
    QDoubleSpinBox *dsbScale;
    QLabel *laSize;
    QDoubleSpinBox *dsbUiFactorSize;
    QSpacerItem *spacer;
    QWidget *wRightOptions;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbFillActions;
    QPushButton *pbCleanActions;
    QPushButton *pbRemoveActions;
    QPushButton *pbRemoveConnections;
    QFrame *line_2;
    QPushButton *pbCopyCondTo;
    QFrame *line;
    QPushButton *pbMinimizeExtendAll;
    QTabWidget *tabCondition;
    QWidget *tActions;
    QWidget *tConnections;
    QWidget *tBoth;

    void setupUi(QWidget *ConditionUiW)
    {
        if (ConditionUiW->objectName().isEmpty())
            ConditionUiW->setObjectName("ConditionUiW");
        ConditionUiW->resize(674, 356);
        ConditionUiW->setMinimumSize(QSize(0, 0));
        vlMain = new QVBoxLayout(ConditionUiW);
        vlMain->setSpacing(0);
        vlMain->setObjectName("vlMain");
        vlMain->setContentsMargins(0, 0, 0, 0);
        fTop = new QFrame(ConditionUiW);
        fTop->setObjectName("fTop");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fTop->sizePolicy().hasHeightForWidth());
        fTop->setSizePolicy(sizePolicy);
        fTop->setMinimumSize(QSize(0, 0));
        fTop->setMaximumSize(QSize(16777215, 16777215));
        fTop->setFrameShape(QFrame::StyledPanel);
        fTop->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(fTop);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        wOptions = new QWidget(fTop);
        wOptions->setObjectName("wOptions");
        wOptions->setMinimumSize(QSize(0, 0));
        wOptions->setMaximumSize(QSize(16777215, 16777215));
        hlOptions = new QHBoxLayout(wOptions);
        hlOptions->setObjectName("hlOptions");
        hlOptions->setContentsMargins(2, 2, 2, 2);
        wLeftOptions = new QWidget(wOptions);
        wLeftOptions->setObjectName("wLeftOptions");
        sizePolicy.setHeightForWidth(wLeftOptions->sizePolicy().hasHeightForWidth());
        wLeftOptions->setSizePolicy(sizePolicy);
        wLeftOptions->setMinimumSize(QSize(0, 0));
        hlLeftOptions = new QHBoxLayout(wLeftOptions);
        hlLeftOptions->setSpacing(2);
        hlLeftOptions->setObjectName("hlLeftOptions");
        hlLeftOptions->setContentsMargins(0, 0, 0, 0);
        laMax = new QLabel(wLeftOptions);
        laMax->setObjectName("laMax");

        hlLeftOptions->addWidget(laMax);

        dsbDuration = new QDoubleSpinBox(wLeftOptions);
        dsbDuration->setObjectName("dsbDuration");
        sizePolicy.setHeightForWidth(dsbDuration->sizePolicy().hasHeightForWidth());
        dsbDuration->setSizePolicy(sizePolicy);
        dsbDuration->setMinimumSize(QSize(75, 18));
        dsbDuration->setMinimum(0.000000000000000);
        dsbDuration->setMaximum(1000000.000000000000000);
        dsbDuration->setValue(100.000000000000000);

        hlLeftOptions->addWidget(dsbDuration);

        laScale = new QLabel(wLeftOptions);
        laScale->setObjectName("laScale");

        hlLeftOptions->addWidget(laScale);

        dsbScale = new QDoubleSpinBox(wLeftOptions);
        dsbScale->setObjectName("dsbScale");
        sizePolicy.setHeightForWidth(dsbScale->sizePolicy().hasHeightForWidth());
        dsbScale->setSizePolicy(sizePolicy);
        dsbScale->setMinimumSize(QSize(75, 18));
        dsbScale->setDecimals(3);
        dsbScale->setMinimum(0.010000000000000);
        dsbScale->setMaximum(1000.000000000000000);
        dsbScale->setValue(1.000000000000000);

        hlLeftOptions->addWidget(dsbScale);

        laSize = new QLabel(wLeftOptions);
        laSize->setObjectName("laSize");

        hlLeftOptions->addWidget(laSize);

        dsbUiFactorSize = new QDoubleSpinBox(wLeftOptions);
        dsbUiFactorSize->setObjectName("dsbUiFactorSize");
        sizePolicy.setHeightForWidth(dsbUiFactorSize->sizePolicy().hasHeightForWidth());
        dsbUiFactorSize->setSizePolicy(sizePolicy);
        dsbUiFactorSize->setMinimumSize(QSize(50, 18));
        dsbUiFactorSize->setMinimum(0.500000000000000);
        dsbUiFactorSize->setMaximum(10.000000000000000);
        dsbUiFactorSize->setSingleStep(0.050000000000000);
        dsbUiFactorSize->setValue(1.000000000000000);

        hlLeftOptions->addWidget(dsbUiFactorSize);

        hlLeftOptions->setStretch(0, 1);
        hlLeftOptions->setStretch(1, 2);
        hlLeftOptions->setStretch(2, 1);
        hlLeftOptions->setStretch(3, 2);
        hlLeftOptions->setStretch(4, 1);
        hlLeftOptions->setStretch(5, 1);

        hlOptions->addWidget(wLeftOptions);

        spacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hlOptions->addItem(spacer);

        wRightOptions = new QWidget(wOptions);
        wRightOptions->setObjectName("wRightOptions");
        wRightOptions->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(wRightOptions);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pbFillActions = new QPushButton(wRightOptions);
        pbFillActions->setObjectName("pbFillActions");
        sizePolicy.setHeightForWidth(pbFillActions->sizePolicy().hasHeightForWidth());
        pbFillActions->setSizePolicy(sizePolicy);
        pbFillActions->setMinimumSize(QSize(0, 0));
        pbFillActions->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/fill_all"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbFillActions->setIcon(icon);
        pbFillActions->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(pbFillActions);

        pbCleanActions = new QPushButton(wRightOptions);
        pbCleanActions->setObjectName("pbCleanActions");
        sizePolicy.setHeightForWidth(pbCleanActions->sizePolicy().hasHeightForWidth());
        pbCleanActions->setSizePolicy(sizePolicy);
        pbCleanActions->setMinimumSize(QSize(0, 0));
        pbCleanActions->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/empty_all"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbCleanActions->setIcon(icon1);
        pbCleanActions->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(pbCleanActions);

        pbRemoveActions = new QPushButton(wRightOptions);
        pbRemoveActions->setObjectName("pbRemoveActions");
        sizePolicy.setHeightForWidth(pbRemoveActions->sizePolicy().hasHeightForWidth());
        pbRemoveActions->setSizePolicy(sizePolicy);
        pbRemoveActions->setMinimumSize(QSize(0, 0));
        pbRemoveActions->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/remove_all"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbRemoveActions->setIcon(icon2);
        pbRemoveActions->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(pbRemoveActions);

        pbRemoveConnections = new QPushButton(wRightOptions);
        pbRemoveConnections->setObjectName("pbRemoveConnections");
        sizePolicy.setHeightForWidth(pbRemoveConnections->sizePolicy().hasHeightForWidth());
        pbRemoveConnections->setSizePolicy(sizePolicy);
        pbRemoveConnections->setMinimumSize(QSize(0, 0));
        pbRemoveConnections->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(pbRemoveConnections);

        line_2 = new QFrame(wRightOptions);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line_2);

        pbCopyCondTo = new QPushButton(wRightOptions);
        pbCopyCondTo->setObjectName("pbCopyCondTo");
        sizePolicy.setHeightForWidth(pbCopyCondTo->sizePolicy().hasHeightForWidth());
        pbCopyCondTo->setSizePolicy(sizePolicy);
        pbCopyCondTo->setMinimumSize(QSize(0, 0));
        pbCopyCondTo->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(pbCopyCondTo);

        line = new QFrame(wRightOptions);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line);

        pbMinimizeExtendAll = new QPushButton(wRightOptions);
        pbMinimizeExtendAll->setObjectName("pbMinimizeExtendAll");
        sizePolicy.setHeightForWidth(pbMinimizeExtendAll->sizePolicy().hasHeightForWidth());
        pbMinimizeExtendAll->setSizePolicy(sizePolicy);
        pbMinimizeExtendAll->setMinimumSize(QSize(25, 0));
        pbMinimizeExtendAll->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(pbMinimizeExtendAll);


        hlOptions->addWidget(wRightOptions);

        hlOptions->setStretch(0, 1);
        hlOptions->setStretch(1, 10);
        hlOptions->setStretch(2, 1);

        verticalLayout->addWidget(wOptions);

        tabCondition = new QTabWidget(fTop);
        tabCondition->setObjectName("tabCondition");
        tActions = new QWidget();
        tActions->setObjectName("tActions");
        tabCondition->addTab(tActions, QString());
        tConnections = new QWidget();
        tConnections->setObjectName("tConnections");
        tabCondition->addTab(tConnections, QString());
        tBoth = new QWidget();
        tBoth->setObjectName("tBoth");
        tabCondition->addTab(tBoth, QString());

        verticalLayout->addWidget(tabCondition);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 50);

        vlMain->addWidget(fTop);


        retranslateUi(ConditionUiW);

        tabCondition->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ConditionUiW);
    } // setupUi

    void retranslateUi(QWidget *ConditionUiW)
    {
        ConditionUiW->setWindowTitle(QCoreApplication::translate("ConditionUiW", "Form", nullptr));
        laMax->setText(QCoreApplication::translate("ConditionUiW", "Duration (s)", nullptr));
        laScale->setText(QCoreApplication::translate("ConditionUiW", "Scale (s)", nullptr));
        laSize->setText(QCoreApplication::translate("ConditionUiW", "UI size", nullptr));
#if QT_CONFIG(tooltip)
        pbFillActions->setToolTip(QCoreApplication::translate("ConditionUiW", "Fill all actions intervals", nullptr));
#endif // QT_CONFIG(tooltip)
        pbFillActions->setText(QString());
#if QT_CONFIG(tooltip)
        pbCleanActions->setToolTip(QCoreApplication::translate("ConditionUiW", "Empty all actions intervals", nullptr));
#endif // QT_CONFIG(tooltip)
        pbCleanActions->setText(QString());
#if QT_CONFIG(tooltip)
        pbRemoveActions->setToolTip(QCoreApplication::translate("ConditionUiW", "Remove all actions", nullptr));
#endif // QT_CONFIG(tooltip)
        pbRemoveActions->setText(QString());
        pbRemoveConnections->setText(QCoreApplication::translate("ConditionUiW", "Remove all", nullptr));
        pbCopyCondTo->setText(QCoreApplication::translate("ConditionUiW", "Copy to...", nullptr));
        pbMinimizeExtendAll->setText(QCoreApplication::translate("ConditionUiW", "-/+", nullptr));
        tabCondition->setTabText(tabCondition->indexOf(tActions), QCoreApplication::translate("ConditionUiW", "Actions", nullptr));
        tabCondition->setTabText(tabCondition->indexOf(tConnections), QCoreApplication::translate("ConditionUiW", "Connections", nullptr));
        tabCondition->setTabText(tabCondition->indexOf(tBoth), QCoreApplication::translate("ConditionUiW", "Actions/Connections", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConditionUiW: public Ui_ConditionUiW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONDITION_H
