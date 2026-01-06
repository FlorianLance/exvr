/********************************************************************************
** Form generated from reading UI file 'resources_manager_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESOURCES_MANAGER_DIALOG_H
#define UI_RESOURCES_MANAGER_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ResourcesManagerD
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame_3;
    QGridLayout *gridLayout;
    QCheckBox *cbReloadTextes;
    QLabel *label_2;
    QCheckBox *cbReloadImages;
    QCheckBox *cbReloadMeshes;
    QCheckBox *cbReloadPythonScripts;
    QCheckBox *cbReloadCSharpScripts;
    QCheckBox *cbReloadAudio;
    QCheckBox *cbReloadVideos;
    QCheckBox *cbReloadClouds;
    QCheckBox *cbReloadAssetBundles;
    QCheckBox *cbReloadScanerVideos;
    QCheckBox *cbReloadPlots;
    QSpacerItem *horizontalSpacer;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *twCategories;

    void setupUi(QDialog *ResourcesManagerD)
    {
        if (ResourcesManagerD->objectName().isEmpty())
            ResourcesManagerD->setObjectName("ResourcesManagerD");
        ResourcesManagerD->resize(1099, 789);
        verticalLayout = new QVBoxLayout(ResourcesManagerD);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        frame = new QFrame(ResourcesManagerD);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(0, 75));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setMinimumSize(QSize(0, 85));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(0, 0));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_3);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(2, 2, 2, 2);
        cbReloadTextes = new QCheckBox(frame_3);
        cbReloadTextes->setObjectName("cbReloadTextes");
        cbReloadTextes->setChecked(true);

        gridLayout->addWidget(cbReloadTextes, 2, 1, 1, 1);

        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 5);

        cbReloadImages = new QCheckBox(frame_3);
        cbReloadImages->setObjectName("cbReloadImages");

        gridLayout->addWidget(cbReloadImages, 1, 0, 1, 1);

        cbReloadMeshes = new QCheckBox(frame_3);
        cbReloadMeshes->setObjectName("cbReloadMeshes");

        gridLayout->addWidget(cbReloadMeshes, 2, 2, 1, 1);

        cbReloadPythonScripts = new QCheckBox(frame_3);
        cbReloadPythonScripts->setObjectName("cbReloadPythonScripts");
        cbReloadPythonScripts->setChecked(true);

        gridLayout->addWidget(cbReloadPythonScripts, 2, 3, 1, 1);

        cbReloadCSharpScripts = new QCheckBox(frame_3);
        cbReloadCSharpScripts->setObjectName("cbReloadCSharpScripts");
        cbReloadCSharpScripts->setChecked(true);

        gridLayout->addWidget(cbReloadCSharpScripts, 1, 3, 1, 1);

        cbReloadAudio = new QCheckBox(frame_3);
        cbReloadAudio->setObjectName("cbReloadAudio");

        gridLayout->addWidget(cbReloadAudio, 1, 2, 1, 1);

        cbReloadVideos = new QCheckBox(frame_3);
        cbReloadVideos->setObjectName("cbReloadVideos");

        gridLayout->addWidget(cbReloadVideos, 1, 1, 1, 1);

        cbReloadClouds = new QCheckBox(frame_3);
        cbReloadClouds->setObjectName("cbReloadClouds");

        gridLayout->addWidget(cbReloadClouds, 1, 4, 1, 1);

        cbReloadAssetBundles = new QCheckBox(frame_3);
        cbReloadAssetBundles->setObjectName("cbReloadAssetBundles");

        gridLayout->addWidget(cbReloadAssetBundles, 2, 0, 1, 1);

        cbReloadScanerVideos = new QCheckBox(frame_3);
        cbReloadScanerVideos->setObjectName("cbReloadScanerVideos");

        gridLayout->addWidget(cbReloadScanerVideos, 2, 4, 1, 1);

        cbReloadPlots = new QCheckBox(frame_3);
        cbReloadPlots->setObjectName("cbReloadPlots");

        gridLayout->addWidget(cbReloadPlots, 1, 5, 1, 1);


        horizontalLayout_2->addWidget(frame_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        horizontalLayout->addWidget(frame_2);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_4);
        verticalLayout_2->setObjectName("verticalLayout_2");

        horizontalLayout->addWidget(frame_4);


        verticalLayout->addWidget(frame);

        twCategories = new QTabWidget(ResourcesManagerD);
        twCategories->setObjectName("twCategories");
        twCategories->setTabPosition(QTabWidget::West);

        verticalLayout->addWidget(twCategories);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 10);

        retranslateUi(ResourcesManagerD);

        twCategories->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(ResourcesManagerD);
    } // setupUi

    void retranslateUi(QDialog *ResourcesManagerD)
    {
        ResourcesManagerD->setWindowTitle(QCoreApplication::translate("ResourcesManagerD", "Dialog", nullptr));
        cbReloadTextes->setText(QCoreApplication::translate("ResourcesManagerD", "Textes", nullptr));
        label_2->setText(QCoreApplication::translate("ResourcesManagerD", "Resources to reload when loading experiment:", nullptr));
        cbReloadImages->setText(QCoreApplication::translate("ResourcesManagerD", "Images", nullptr));
        cbReloadMeshes->setText(QCoreApplication::translate("ResourcesManagerD", "Meshes", nullptr));
        cbReloadPythonScripts->setText(QCoreApplication::translate("ResourcesManagerD", "Python scripts", nullptr));
        cbReloadCSharpScripts->setText(QCoreApplication::translate("ResourcesManagerD", "C# scripts", nullptr));
        cbReloadAudio->setText(QCoreApplication::translate("ResourcesManagerD", "Audio", nullptr));
        cbReloadVideos->setText(QCoreApplication::translate("ResourcesManagerD", "Videos", nullptr));
        cbReloadClouds->setText(QCoreApplication::translate("ResourcesManagerD", "Clouds", nullptr));
        cbReloadAssetBundles->setText(QCoreApplication::translate("ResourcesManagerD", "Asset bundles", nullptr));
        cbReloadScanerVideos->setText(QCoreApplication::translate("ResourcesManagerD", "Scaner videos", nullptr));
        cbReloadPlots->setText(QCoreApplication::translate("ResourcesManagerD", "Plots", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResourcesManagerD: public Ui_ResourcesManagerD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESOURCES_MANAGER_DIALOG_H
