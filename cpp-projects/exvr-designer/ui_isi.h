/********************************************************************************
** Form generated from reading UI file 'isi.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ISI_H
#define UI_ISI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
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

class Ui_IsiW
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *laNameT;
    QLabel *laName;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbSetName;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *cbRandomize;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line_2;
    QLabel *laIsi;
    QHBoxLayout *horizontalLayout_3;
    QLabel *laIntervals;
    QDoubleSpinBox *dsbNewIsi;
    QPushButton *pbAdd;
    QSpacerItem *horizontalSpacer_3;
    QListWidget *lwIsi;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pbUp;
    QPushButton *pbRemove;
    QPushButton *pbDown;
    QSpacerItem *horizontalSpacer_5;
    QFrame *line_3;
    QLabel *label;
    QTextEdit *teInformations;

    void setupUi(QWidget *IsiW)
    {
        if (IsiW->objectName().isEmpty())
            IsiW->setObjectName("IsiW");
        IsiW->resize(307, 448);
        verticalLayout = new QVBoxLayout(IsiW);
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(4, 4, 4, 4);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        laNameT = new QLabel(IsiW);
        laNameT->setObjectName("laNameT");

        horizontalLayout->addWidget(laNameT);

        laName = new QLabel(IsiW);
        laName->setObjectName("laName");

        horizontalLayout->addWidget(laName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbSetName = new QPushButton(IsiW);
        pbSetName->setObjectName("pbSetName");
        pbSetName->setMinimumSize(QSize(50, 0));

        horizontalLayout->addWidget(pbSetName);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 10);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(IsiW);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        cbRandomize = new QCheckBox(IsiW);
        cbRandomize->setObjectName("cbRandomize");

        horizontalLayout_2->addWidget(cbRandomize);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        line_2 = new QFrame(IsiW);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        laIsi = new QLabel(IsiW);
        laIsi->setObjectName("laIsi");

        verticalLayout->addWidget(laIsi, 0, Qt::AlignHCenter);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        laIntervals = new QLabel(IsiW);
        laIntervals->setObjectName("laIntervals");

        horizontalLayout_3->addWidget(laIntervals);

        dsbNewIsi = new QDoubleSpinBox(IsiW);
        dsbNewIsi->setObjectName("dsbNewIsi");
        dsbNewIsi->setDecimals(3);
        dsbNewIsi->setMinimum(0.001000000000000);
        dsbNewIsi->setMaximum(10000.000000000000000);
        dsbNewIsi->setSingleStep(0.100000000000000);
        dsbNewIsi->setValue(1.000000000000000);

        horizontalLayout_3->addWidget(dsbNewIsi);

        pbAdd = new QPushButton(IsiW);
        pbAdd->setObjectName("pbAdd");
        pbAdd->setEnabled(true);
        pbAdd->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(pbAdd);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        lwIsi = new QListWidget(IsiW);
        lwIsi->setObjectName("lwIsi");

        verticalLayout->addWidget(lwIsi);

        frame = new QFrame(IsiW);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        pbUp = new QPushButton(frame);
        pbUp->setObjectName("pbUp");
        pbUp->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(pbUp);

        pbRemove = new QPushButton(frame);
        pbRemove->setObjectName("pbRemove");
        pbRemove->setEnabled(false);
        pbRemove->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(pbRemove);

        pbDown = new QPushButton(frame);
        pbDown->setObjectName("pbDown");
        pbDown->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(pbDown);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout->addWidget(frame);

        line_3 = new QFrame(IsiW);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        label = new QLabel(IsiW);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        teInformations = new QTextEdit(IsiW);
        teInformations->setObjectName("teInformations");
        teInformations->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(teInformations);


        retranslateUi(IsiW);

        QMetaObject::connectSlotsByName(IsiW);
    } // setupUi

    void retranslateUi(QWidget *IsiW)
    {
        IsiW->setWindowTitle(QCoreApplication::translate("IsiW", "Form", nullptr));
        laNameT->setText(QCoreApplication::translate("IsiW", "Name", nullptr));
        laName->setText(QString());
        pbSetName->setText(QCoreApplication::translate("IsiW", "Set", nullptr));
        cbRandomize->setText(QCoreApplication::translate("IsiW", "Randomize", nullptr));
        laIsi->setText(QCoreApplication::translate("IsiW", "Interstimulus state interval list", nullptr));
        laIntervals->setText(QCoreApplication::translate("IsiW", "Interval (s)", nullptr));
        pbAdd->setText(QCoreApplication::translate("IsiW", "Add", nullptr));
        pbUp->setText(QCoreApplication::translate("IsiW", "Up", nullptr));
        pbRemove->setText(QCoreApplication::translate("IsiW", "Del", nullptr));
        pbDown->setText(QCoreApplication::translate("IsiW", "Down", nullptr));
        label->setText(QCoreApplication::translate("IsiW", "Informations:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IsiW: public Ui_IsiW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ISI_H
