/********************************************************************************
** Form generated from reading UI file 'base_component_config_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASE_COMPONENT_CONFIG_WIDGET_H
#define UI_BASE_COMPONENT_CONFIG_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseComponentConfigWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *fTop;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *laName;
    QLineEdit *leName;
    QPushButton *pbReset;
    QPushButton *pbPin;
    QPushButton *pbHelp;
    QFrame *line_2;
    QFrame *fChildCompo;
    QVBoxLayout *verticalLayout_3;
    QFrame *fInitConfig;
    QGridLayout *glAllConfigs;
    QTabWidget *twAllConfigs;
    QWidget *initConfigW;
    QVBoxLayout *vlInitConfig;
    QWidget *configsW;
    QVBoxLayout *verticalLayout_5;
    QWidget *wTopConfigs;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cbSelectedConfig;
    QFrame *fConfigParameters;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabConfigs;
    QFrame *fConfigManager;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pbInsertNewConfig;
    QPushButton *pbDuplicate;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbRenameConfig;
    QPushButton *pbRemoveConfig;

    void setupUi(QWidget *BaseComponentConfigWidget)
    {
        if (BaseComponentConfigWidget->objectName().isEmpty())
            BaseComponentConfigWidget->setObjectName("BaseComponentConfigWidget");
        BaseComponentConfigWidget->resize(557, 586);
        verticalLayout = new QVBoxLayout(BaseComponentConfigWidget);
        verticalLayout->setObjectName("verticalLayout");
        fTop = new QFrame(BaseComponentConfigWidget);
        fTop->setObjectName("fTop");
        fTop->setFrameShape(QFrame::StyledPanel);
        fTop->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(fTop);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame = new QFrame(fTop);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        laName = new QLabel(frame);
        laName->setObjectName("laName");

        horizontalLayout_2->addWidget(laName);

        leName = new QLineEdit(frame);
        leName->setObjectName("leName");

        horizontalLayout_2->addWidget(leName);

        pbReset = new QPushButton(frame);
        pbReset->setObjectName("pbReset");

        horizontalLayout_2->addWidget(pbReset);

        pbPin = new QPushButton(frame);
        pbPin->setObjectName("pbPin");
        pbPin->setMinimumSize(QSize(25, 25));
        pbPin->setMaximumSize(QSize(25, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/Pin"), QSize(), QIcon::Normal, QIcon::Off);
        pbPin->setIcon(icon);
        pbPin->setIconSize(QSize(25, 25));

        horizontalLayout_2->addWidget(pbPin);

        pbHelp = new QPushButton(frame);
        pbHelp->setObjectName("pbHelp");
        pbHelp->setMinimumSize(QSize(25, 25));
        pbHelp->setMaximumSize(QSize(25, 25));
        pbHelp->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/Help"), QSize(), QIcon::Normal, QIcon::Off);
        pbHelp->setIcon(icon1);
        pbHelp->setIconSize(QSize(25, 25));

        horizontalLayout_2->addWidget(pbHelp);

        horizontalLayout_2->setStretch(1, 20);

        verticalLayout_2->addWidget(frame);


        verticalLayout->addWidget(fTop);

        line_2 = new QFrame(BaseComponentConfigWidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        fChildCompo = new QFrame(BaseComponentConfigWidget);
        fChildCompo->setObjectName("fChildCompo");
        fChildCompo->setFrameShape(QFrame::StyledPanel);
        fChildCompo->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(fChildCompo);
        verticalLayout_3->setObjectName("verticalLayout_3");
        fInitConfig = new QFrame(fChildCompo);
        fInitConfig->setObjectName("fInitConfig");
        fInitConfig->setFrameShape(QFrame::StyledPanel);
        fInitConfig->setFrameShadow(QFrame::Raised);
        glAllConfigs = new QGridLayout(fInitConfig);
        glAllConfigs->setSpacing(0);
        glAllConfigs->setObjectName("glAllConfigs");
        glAllConfigs->setContentsMargins(0, 0, 0, 0);
        twAllConfigs = new QTabWidget(fInitConfig);
        twAllConfigs->setObjectName("twAllConfigs");
        initConfigW = new QWidget();
        initConfigW->setObjectName("initConfigW");
        vlInitConfig = new QVBoxLayout(initConfigW);
        vlInitConfig->setSpacing(0);
        vlInitConfig->setObjectName("vlInitConfig");
        vlInitConfig->setContentsMargins(0, 0, 0, 0);
        twAllConfigs->addTab(initConfigW, QString());
        configsW = new QWidget();
        configsW->setObjectName("configsW");
        verticalLayout_5 = new QVBoxLayout(configsW);
        verticalLayout_5->setObjectName("verticalLayout_5");
        wTopConfigs = new QWidget(configsW);
        wTopConfigs->setObjectName("wTopConfigs");
        horizontalLayout = new QHBoxLayout(wTopConfigs);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(wTopConfigs);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        cbSelectedConfig = new QComboBox(wTopConfigs);
        cbSelectedConfig->setObjectName("cbSelectedConfig");
        cbSelectedConfig->setMaxVisibleItems(50);

        horizontalLayout->addWidget(cbSelectedConfig);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 50);

        verticalLayout_5->addWidget(wTopConfigs);

        fConfigParameters = new QFrame(configsW);
        fConfigParameters->setObjectName("fConfigParameters");
        fConfigParameters->setFrameShape(QFrame::StyledPanel);
        fConfigParameters->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(fConfigParameters);
        verticalLayout_4->setSpacing(5);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        tabConfigs = new QTabWidget(fConfigParameters);
        tabConfigs->setObjectName("tabConfigs");

        verticalLayout_4->addWidget(tabConfigs);


        verticalLayout_5->addWidget(fConfigParameters);

        fConfigManager = new QFrame(configsW);
        fConfigManager->setObjectName("fConfigManager");
        horizontalLayout_3 = new QHBoxLayout(fConfigManager);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pbInsertNewConfig = new QPushButton(fConfigManager);
        pbInsertNewConfig->setObjectName("pbInsertNewConfig");
        pbInsertNewConfig->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(pbInsertNewConfig);

        pbDuplicate = new QPushButton(fConfigManager);
        pbDuplicate->setObjectName("pbDuplicate");
        pbDuplicate->setEnabled(true);
        pbDuplicate->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(pbDuplicate);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pbRenameConfig = new QPushButton(fConfigManager);
        pbRenameConfig->setObjectName("pbRenameConfig");
        pbRenameConfig->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(pbRenameConfig);

        pbRemoveConfig = new QPushButton(fConfigManager);
        pbRemoveConfig->setObjectName("pbRemoveConfig");
        pbRemoveConfig->setEnabled(false);
        pbRemoveConfig->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(pbRemoveConfig);


        verticalLayout_5->addWidget(fConfigManager);

        twAllConfigs->addTab(configsW, QString());

        glAllConfigs->addWidget(twAllConfigs, 0, 0, 1, 1);


        verticalLayout_3->addWidget(fInitConfig);


        verticalLayout->addWidget(fChildCompo);


        retranslateUi(BaseComponentConfigWidget);

        twAllConfigs->setCurrentIndex(0);
        tabConfigs->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(BaseComponentConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *BaseComponentConfigWidget)
    {
        BaseComponentConfigWidget->setWindowTitle(QCoreApplication::translate("BaseComponentConfigWidget", "Base component title", nullptr));
        laName->setText(QCoreApplication::translate("BaseComponentConfigWidget", "Name:", nullptr));
        pbReset->setText(QCoreApplication::translate("BaseComponentConfigWidget", "Reset", nullptr));
        pbPin->setText(QString());
#if QT_CONFIG(shortcut)
        pbPin->setShortcut(QCoreApplication::translate("BaseComponentConfigWidget", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbHelp->setToolTip(QCoreApplication::translate("BaseComponentConfigWidget", "DIsplay documentation page for this component", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        pbHelp->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        pbHelp->setText(QString());
        twAllConfigs->setTabText(twAllConfigs->indexOf(initConfigW), QCoreApplication::translate("BaseComponentConfigWidget", "Initialization config", nullptr));
        label->setText(QCoreApplication::translate("BaseComponentConfigWidget", "Selected config:", nullptr));
        pbInsertNewConfig->setText(QCoreApplication::translate("BaseComponentConfigWidget", "Insert new ", nullptr));
        pbDuplicate->setText(QCoreApplication::translate("BaseComponentConfigWidget", "Duplicate", nullptr));
        pbRenameConfig->setText(QCoreApplication::translate("BaseComponentConfigWidget", "Rename", nullptr));
        pbRemoveConfig->setText(QCoreApplication::translate("BaseComponentConfigWidget", "Remove  ", nullptr));
        twAllConfigs->setTabText(twAllConfigs->indexOf(configsW), QCoreApplication::translate("BaseComponentConfigWidget", "Conditions configs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BaseComponentConfigWidget: public Ui_BaseComponentConfigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASE_COMPONENT_CONFIG_WIDGET_H
