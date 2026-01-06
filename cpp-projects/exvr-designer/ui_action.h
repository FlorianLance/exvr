/********************************************************************************
** Form generated from reading UI file 'action.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTION_H
#define UI_ACTION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ActionW
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *wAction;
    QVBoxLayout *verticalLayout_5;
    QWidget *wTop;
    QHBoxLayout *hlTop;
    QPushButton *pbMinimizedIcon;
    QPushButton *pbUpTop;
    QPushButton *pbDownTop;
    QLabel *laId;
    QLabel *laName;
    QLabel *label;
    QComboBox *cbConfig;
    QSpacerItem *horizontalSpacer;
    QFrame *line_2;
    QLabel *laApplyTo;
    QCheckBox *cbUpdate;
    QCheckBox *cbVisibility;
    QPushButton *pbFill;
    QPushButton *pbClean;
    QPushButton *pbDelete;
    QPushButton *pbMinimizeExtend;
    QWidget *wBottom;
    QHBoxLayout *horizontalLayout;
    QWidget *wIcon;
    QVBoxLayout *verticalLayout_2;
    QToolButton *tbIcon;
    QWidget *wMove;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pbUp;
    QPushButton *pbDown;
    QSpacerItem *verticalSpacer;
    QWidget *wTimeline;
    QHBoxLayout *horizontalLayout_3;
    QScrollArea *scrollArea;
    QWidget *sacTimeline;
    QHBoxLayout *hlSpace;
    QFrame *f2;
    QVBoxLayout *vlTimeline;

    void setupUi(QWidget *ActionW)
    {
        if (ActionW->objectName().isEmpty())
            ActionW->setObjectName("ActionW");
        ActionW->resize(1057, 377);
        verticalLayout_3 = new QVBoxLayout(ActionW);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        wAction = new QWidget(ActionW);
        wAction->setObjectName("wAction");
        wAction->setMinimumSize(QSize(0, 0));
        verticalLayout_5 = new QVBoxLayout(wAction);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        wTop = new QWidget(wAction);
        wTop->setObjectName("wTop");
        hlTop = new QHBoxLayout(wTop);
        hlTop->setSpacing(5);
        hlTop->setObjectName("hlTop");
        hlTop->setContentsMargins(2, 2, 2, 2);
        pbMinimizedIcon = new QPushButton(wTop);
        pbMinimizedIcon->setObjectName("pbMinimizedIcon");

        hlTop->addWidget(pbMinimizedIcon);

        pbUpTop = new QPushButton(wTop);
        pbUpTop->setObjectName("pbUpTop");
        pbUpTop->setEnabled(true);
        pbUpTop->setMinimumSize(QSize(0, 0));
        pbUpTop->setMaximumSize(QSize(20, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/up"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbUpTop->setIcon(icon);
        pbUpTop->setIconSize(QSize(10, 10));

        hlTop->addWidget(pbUpTop);

        pbDownTop = new QPushButton(wTop);
        pbDownTop->setObjectName("pbDownTop");
        pbDownTop->setMinimumSize(QSize(0, 0));
        pbDownTop->setMaximumSize(QSize(20, 25));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/down"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbDownTop->setIcon(icon1);
        pbDownTop->setIconSize(QSize(10, 10));

        hlTop->addWidget(pbDownTop);

        laId = new QLabel(wTop);
        laId->setObjectName("laId");

        hlTop->addWidget(laId, 0, Qt::AlignRight);

        laName = new QLabel(wTop);
        laName->setObjectName("laName");

        hlTop->addWidget(laName, 0, Qt::AlignLeft);

        label = new QLabel(wTop);
        label->setObjectName("label");

        hlTop->addWidget(label);

        cbConfig = new QComboBox(wTop);
        cbConfig->setObjectName("cbConfig");
        cbConfig->setMaxVisibleItems(50);

        hlTop->addWidget(cbConfig);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hlTop->addItem(horizontalSpacer);

        line_2 = new QFrame(wTop);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        hlTop->addWidget(line_2);

        laApplyTo = new QLabel(wTop);
        laApplyTo->setObjectName("laApplyTo");

        hlTop->addWidget(laApplyTo);

        cbUpdate = new QCheckBox(wTop);
        cbUpdate->setObjectName("cbUpdate");
        cbUpdate->setChecked(true);

        hlTop->addWidget(cbUpdate);

        cbVisibility = new QCheckBox(wTop);
        cbVisibility->setObjectName("cbVisibility");
        cbVisibility->setChecked(true);

        hlTop->addWidget(cbVisibility);

        pbFill = new QPushButton(wTop);
        pbFill->setObjectName("pbFill");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbFill->sizePolicy().hasHeightForWidth());
        pbFill->setSizePolicy(sizePolicy);
        pbFill->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/Fill_action"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbFill->setIcon(icon2);
        pbFill->setIconSize(QSize(25, 25));

        hlTop->addWidget(pbFill);

        pbClean = new QPushButton(wTop);
        pbClean->setObjectName("pbClean");
        sizePolicy.setHeightForWidth(pbClean->sizePolicy().hasHeightForWidth());
        pbClean->setSizePolicy(sizePolicy);
        pbClean->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/Empty_action"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbClean->setIcon(icon3);
        pbClean->setIconSize(QSize(25, 25));

        hlTop->addWidget(pbClean);

        pbDelete = new QPushButton(wTop);
        pbDelete->setObjectName("pbDelete");
        pbDelete->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/remove_action"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pbDelete->setIcon(icon4);
        pbDelete->setIconSize(QSize(25, 25));

        hlTop->addWidget(pbDelete);

        pbMinimizeExtend = new QPushButton(wTop);
        pbMinimizeExtend->setObjectName("pbMinimizeExtend");
        pbMinimizeExtend->setMaximumSize(QSize(20, 16777215));

        hlTop->addWidget(pbMinimizeExtend);

        hlTop->setStretch(0, 1);
        hlTop->setStretch(1, 1);
        hlTop->setStretch(2, 1);
        hlTop->setStretch(3, 1);
        hlTop->setStretch(4, 1);
        hlTop->setStretch(5, 1);
        hlTop->setStretch(6, 20);
        hlTop->setStretch(7, 20);
        hlTop->setStretch(8, 1);
        hlTop->setStretch(9, 1);
        hlTop->setStretch(10, 1);
        hlTop->setStretch(11, 1);
        hlTop->setStretch(12, 1);
        hlTop->setStretch(13, 1);
        hlTop->setStretch(14, 1);
        hlTop->setStretch(15, 1);

        verticalLayout_5->addWidget(wTop);

        wBottom = new QWidget(wAction);
        wBottom->setObjectName("wBottom");
        wBottom->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout = new QHBoxLayout(wBottom);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        wIcon = new QWidget(wBottom);
        wIcon->setObjectName("wIcon");
        verticalLayout_2 = new QVBoxLayout(wIcon);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        tbIcon = new QToolButton(wIcon);
        tbIcon->setObjectName("tbIcon");
        tbIcon->setMinimumSize(QSize(0, 0));
        tbIcon->setMaximumSize(QSize(40, 40));
        tbIcon->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(tbIcon);

        wMove = new QWidget(wIcon);
        wMove->setObjectName("wMove");
        horizontalLayout_4 = new QHBoxLayout(wMove);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addWidget(wMove);


        horizontalLayout->addWidget(wIcon);

        widget = new QWidget(wBottom);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pbUp = new QPushButton(widget);
        pbUp->setObjectName("pbUp");
        pbUp->setMinimumSize(QSize(0, 0));
        pbUp->setMaximumSize(QSize(20, 25));
        pbUp->setIcon(icon);
        pbUp->setIconSize(QSize(10, 10));

        verticalLayout->addWidget(pbUp);

        pbDown = new QPushButton(widget);
        pbDown->setObjectName("pbDown");
        pbDown->setMinimumSize(QSize(0, 0));
        pbDown->setMaximumSize(QSize(20, 25));
        pbDown->setIcon(icon1);
        pbDown->setIconSize(QSize(10, 10));

        verticalLayout->addWidget(pbDown);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget);

        wTimeline = new QWidget(wBottom);
        wTimeline->setObjectName("wTimeline");
        horizontalLayout_3 = new QHBoxLayout(wTimeline);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(2, 2, 2, 2);
        scrollArea = new QScrollArea(wTimeline);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(10);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setMaximumSize(QSize(16777215, 16777215));
        scrollArea->setFrameShadow(QFrame::Raised);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        sacTimeline = new QWidget();
        sacTimeline->setObjectName("sacTimeline");
        sacTimeline->setGeometry(QRect(0, 0, 979, 316));
        sacTimeline->setStyleSheet(QString::fromUtf8("\n"
"background-color:white;"));
        hlSpace = new QHBoxLayout(sacTimeline);
        hlSpace->setSpacing(0);
        hlSpace->setObjectName("hlSpace");
        hlSpace->setContentsMargins(2, 2, 2, 0);
        f2 = new QFrame(sacTimeline);
        f2->setObjectName("f2");
        f2->setFrameShape(QFrame::NoFrame);
        f2->setFrameShadow(QFrame::Plain);
        f2->setLineWidth(0);
        vlTimeline = new QVBoxLayout(f2);
        vlTimeline->setSpacing(0);
        vlTimeline->setObjectName("vlTimeline");
        vlTimeline->setContentsMargins(0, 0, 0, 0);

        hlSpace->addWidget(f2);

        scrollArea->setWidget(sacTimeline);

        horizontalLayout_3->addWidget(scrollArea);


        horizontalLayout->addWidget(wTimeline);


        verticalLayout_5->addWidget(wBottom);

        verticalLayout_5->setStretch(1, 10);

        verticalLayout_3->addWidget(wAction);


        retranslateUi(ActionW);

        QMetaObject::connectSlotsByName(ActionW);
    } // setupUi

    void retranslateUi(QWidget *ActionW)
    {
        ActionW->setWindowTitle(QCoreApplication::translate("ActionW", "Form", nullptr));
        pbMinimizedIcon->setText(QString());
        pbUpTop->setText(QString());
        pbDownTop->setText(QString());
        laId->setText(QCoreApplication::translate("ActionW", "1#", nullptr));
        laName->setText(QCoreApplication::translate("ActionW", "Name", nullptr));
        label->setText(QCoreApplication::translate("ActionW", "Config:", nullptr));
#if QT_CONFIG(tooltip)
        cbConfig->setToolTip(QCoreApplication::translate("ActionW", "Component configuration used for the action", nullptr));
#endif // QT_CONFIG(tooltip)
        laApplyTo->setText(QCoreApplication::translate("ActionW", "Apply to:", nullptr));
#if QT_CONFIG(tooltip)
        cbUpdate->setToolTip(QCoreApplication::translate("ActionW", "If checked, apply to update timeline", nullptr));
#endif // QT_CONFIG(tooltip)
        cbUpdate->setText(QCoreApplication::translate("ActionW", "update", nullptr));
#if QT_CONFIG(tooltip)
        cbVisibility->setToolTip(QCoreApplication::translate("ActionW", "If checked, apply to visibility timeline", nullptr));
#endif // QT_CONFIG(tooltip)
        cbVisibility->setText(QCoreApplication::translate("ActionW", "visibility", nullptr));
#if QT_CONFIG(tooltip)
        pbFill->setToolTip(QCoreApplication::translate("ActionW", "Fill timeline", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbFill->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbFill->setText(QString());
#if QT_CONFIG(tooltip)
        pbClean->setToolTip(QCoreApplication::translate("ActionW", "Empty timeline", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbClean->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbClean->setText(QString());
#if QT_CONFIG(tooltip)
        pbDelete->setToolTip(QCoreApplication::translate("ActionW", "Remove the action", nullptr));
#endif // QT_CONFIG(tooltip)
        pbDelete->setText(QString());
#if QT_CONFIG(tooltip)
        pbMinimizeExtend->setToolTip(QCoreApplication::translate("ActionW", "Minimize, expand action", nullptr));
#endif // QT_CONFIG(tooltip)
        pbMinimizeExtend->setText(QCoreApplication::translate("ActionW", "-", nullptr));
        tbIcon->setText(QString());
        pbUp->setText(QString());
        pbDown->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ActionW: public Ui_ActionW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTION_H
