/********************************************************************************
** Form generated from reading UI file 'resource_type.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESOURCE_TYPE_H
#define UI_RESOURCE_TYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResourceTypeW
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbAdd;
    QPushButton *pbRemove;
    QCheckBox *cbDisplayPreview;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbClear;
    QLabel *laTitle;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QListWidget *lwFiles;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QLabel *laPath;
    QLabel *label_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pbFind;
    QPushButton *pbOpenFile;
    QPushButton *pbOpenDir;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pbGenerate;
    QPushButton *pbSetAlias;
    QLabel *label_2;
    QLabel *laAlias;
    QFrame *line;

    void setupUi(QWidget *ResourceTypeW)
    {
        if (ResourceTypeW->objectName().isEmpty())
            ResourceTypeW->setObjectName("ResourceTypeW");
        ResourceTypeW->resize(799, 551);
        verticalLayout_2 = new QVBoxLayout(ResourceTypeW);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget = new QWidget(ResourceTypeW);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        pbAdd = new QPushButton(widget);
        pbAdd->setObjectName("pbAdd");
        pbAdd->setAutoDefault(false);

        horizontalLayout->addWidget(pbAdd);

        pbRemove = new QPushButton(widget);
        pbRemove->setObjectName("pbRemove");

        horizontalLayout->addWidget(pbRemove);

        cbDisplayPreview = new QCheckBox(widget);
        cbDisplayPreview->setObjectName("cbDisplayPreview");
        cbDisplayPreview->setEnabled(false);

        horizontalLayout->addWidget(cbDisplayPreview);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbClear = new QPushButton(widget);
        pbClear->setObjectName("pbClear");

        horizontalLayout->addWidget(pbClear);


        verticalLayout_2->addWidget(widget);

        laTitle = new QLabel(ResourceTypeW);
        laTitle->setObjectName("laTitle");

        verticalLayout_2->addWidget(laTitle);

        scrollArea_2 = new QScrollArea(ResourceTypeW);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 779, 331));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        lwFiles = new QListWidget(scrollAreaWidgetContents);
        lwFiles->setObjectName("lwFiles");

        verticalLayout->addWidget(lwFiles);

        scrollArea_2->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea_2);

        widget_2 = new QWidget(ResourceTypeW);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 130));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName("gridLayout");
        laPath = new QLabel(widget_2);
        laPath->setObjectName("laPath");

        gridLayout->addWidget(laPath, 1, 1, 1, 3);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        frame = new QFrame(widget_2);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pbFind = new QPushButton(frame);
        pbFind->setObjectName("pbFind");

        horizontalLayout_2->addWidget(pbFind);

        pbOpenFile = new QPushButton(frame);
        pbOpenFile->setObjectName("pbOpenFile");

        horizontalLayout_2->addWidget(pbOpenFile);

        pbOpenDir = new QPushButton(frame);
        pbOpenDir->setObjectName("pbOpenDir");

        horizontalLayout_2->addWidget(pbOpenDir);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pbGenerate = new QPushButton(frame);
        pbGenerate->setObjectName("pbGenerate");

        horizontalLayout_2->addWidget(pbGenerate);


        gridLayout->addWidget(frame, 3, 0, 1, 5);

        pbSetAlias = new QPushButton(widget_2);
        pbSetAlias->setObjectName("pbSetAlias");

        gridLayout->addWidget(pbSetAlias, 0, 4, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        laAlias = new QLabel(widget_2);
        laAlias->setObjectName("laAlias");

        gridLayout->addWidget(laAlias, 0, 1, 1, 3);

        line = new QFrame(widget_2);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout->addWidget(line, 2, 0, 1, 5);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 10);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);
        gridLayout->setColumnStretch(4, 1);

        verticalLayout_2->addWidget(widget_2);

        QWidget::setTabOrder(pbAdd, pbRemove);
        QWidget::setTabOrder(pbRemove, cbDisplayPreview);
        QWidget::setTabOrder(cbDisplayPreview, pbClear);
        QWidget::setTabOrder(pbClear, scrollArea_2);
        QWidget::setTabOrder(scrollArea_2, lwFiles);

        retranslateUi(ResourceTypeW);

        QMetaObject::connectSlotsByName(ResourceTypeW);
    } // setupUi

    void retranslateUi(QWidget *ResourceTypeW)
    {
        ResourceTypeW->setWindowTitle(QCoreApplication::translate("ResourceTypeW", "Form", nullptr));
        pbAdd->setText(QCoreApplication::translate("ResourceTypeW", "Add", nullptr));
        pbRemove->setText(QCoreApplication::translate("ResourceTypeW", "Remove", nullptr));
        cbDisplayPreview->setText(QCoreApplication::translate("ResourceTypeW", "Display preview", nullptr));
        pbClear->setText(QCoreApplication::translate("ResourceTypeW", "Clear", nullptr));
        laTitle->setText(QCoreApplication::translate("ResourceTypeW", "All files:", nullptr));
        laPath->setText(QCoreApplication::translate("ResourceTypeW", "...", nullptr));
        label_3->setText(QCoreApplication::translate("ResourceTypeW", "Path:", nullptr));
        pbFind->setText(QCoreApplication::translate("ResourceTypeW", "Find", nullptr));
        pbOpenFile->setText(QCoreApplication::translate("ResourceTypeW", "Open file", nullptr));
        pbOpenDir->setText(QCoreApplication::translate("ResourceTypeW", "Open dir", nullptr));
        pbGenerate->setText(QCoreApplication::translate("ResourceTypeW", "Generate", nullptr));
        pbSetAlias->setText(QCoreApplication::translate("ResourceTypeW", "Set alias", nullptr));
        label_2->setText(QCoreApplication::translate("ResourceTypeW", "Alias:", nullptr));
        laAlias->setText(QCoreApplication::translate("ResourceTypeW", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResourceTypeW: public Ui_ResourceTypeW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESOURCE_TYPE_H
