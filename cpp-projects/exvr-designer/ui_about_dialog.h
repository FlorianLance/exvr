/********************************************************************************
** Form generated from reading UI file 'about_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_DIALOG_H
#define UI_ABOUT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutD
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbClose;

    void setupUi(QDialog *AboutD)
    {
        if (AboutD->objectName().isEmpty())
            AboutD->setObjectName("AboutD");
        AboutD->resize(693, 978);
        gridLayout = new QGridLayout(AboutD);
        gridLayout->setObjectName("gridLayout");
        textEdit = new QTextEdit(AboutD);
        textEdit->setObjectName("textEdit");
        textEdit->setReadOnly(true);
        textEdit->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        widget = new QWidget(AboutD);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbClose = new QPushButton(widget);
        pbClose->setObjectName("pbClose");

        horizontalLayout->addWidget(pbClose);


        gridLayout->addWidget(widget, 1, 0, 1, 1);


        retranslateUi(AboutD);

        QMetaObject::connectSlotsByName(AboutD);
    } // setupUi

    void retranslateUi(QDialog *AboutD)
    {
        AboutD->setWindowTitle(QCoreApplication::translate("AboutD", "About ExVR", nullptr));
        textEdit->setHtml(QCoreApplication::translate("AboutD", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<h2 style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a name=\"user-content-exvr---open-virtual-psychology\"></a><span style=\" font-size:8pt; font-weight:600;\">E</span><span style=\" font-size:8pt; font-weight:600;\">xVR - Open Virtual Psychology</span></h2>\n"
"<h2 style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Public repository is available </span><a href=\"https://github.com/FlorianLance/exvr\"><span style=\" font-size:8pt; font-weight:600; text-decoration: underline; color:#007"
                        "af4;\">here.</span></a></h2>\n"
"<h2 style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a name=\"user-content-description\"></a><span style=\" font-size:8pt; font-weight:600;\">D</span><span style=\" font-size:8pt; font-weight:600;\">escription</span></h2>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">ExVR is a solution for creating and executing 3D/2D experiments using VR or not. Its philosophy is roughly similar to </span><a href=\"https://www.psychopy.org/\"><span style=\" font-size:8pt; text-decoration: underline; color:#007af4;\">Psychopy</span></a><span style=\" font-size:8pt;\"> and can easily be extended by users using scripting (C#, Python) or visual scripting (with nodes).</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style="
                        "\" font-size:8pt;\">It is subdivided in two software:</span></p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" font-size:8pt;\" style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">the designer GUI for creating the experiment content and its randomization</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">the experiment launcher for that will generate and execute experiments at runtime using Unity3D</li></ul>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">They both communicate between themselves and makes easy to operate changes and see immediately the results. Once the design done, the user can then share the full experiment by exporting it, allowing a"
                        "ccurate replications on others computers.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Origin</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">The project has been developped at </span><a href=\"https://www.epfl.ch/labs/lnco/\"><span style=\" font-size:8pt; text-decoration: underline; color:#007af4;\">EPFL LNCO laboratory</span></a><span style=\" font-size:8pt;\"> (Laboratory of Cognitive Neuroscience) and has been funded by the </span><a href=\"https://www.epfl.ch/research/open-science/in-practice/open-science-fund/\"><span style=\" font-size:8pt; text-decoration: underline; "
                        "color:#007af4;\">EPFL Open Science Fund</span></a><span style=\" font-size:8pt;\"> from the 2019 cohort. It has been used for dozains of experiments and demos inside LNCO or during external collaborations since its creation in 2018.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Content</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">ExVR</span><span style=\" font-size:8pt;\"> is subdivided in two software:</span></p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" font-size:8pt;\" sty"
                        "le=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">ExVR-designer</span>: a GUI for creating the experiments and controlling their execution </li>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 2;\"><li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">creation </li>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 3;\"><li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">experimental flow (routines, loops, interstimulus state)</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">components, configurations and "
                        "their parameters</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">randomization of the differents loops</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">management of resources (scripts, images, sounds, 3D objects..)</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">actions (association of conditions and components using update/visibility timelines)</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">scripting using (C#,Python)</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">visual s"
                        "cripting using nodes</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">global settings (display options and others)</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">generation of the differents randomization (using instances files)</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">saving/eport/loading functions</li></ul>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">execution </li></ul>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 3;\"><li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; marg"
                        "in-right:0px; -qt-block-indent:0; text-indent:0px;\">load current exp (or a subpart) to the launcher</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">load default or specific randomization (using instance files)</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">play/pause/stop/next/previous/goto</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">feedback (exp state, time, routine name, nodes states) from the exp-launcher</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">logs (messages, errors) from the software and the scripts</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; "
                        "margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">realtime update of components parameters</li></ul>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">ExVR-exp</span>: an exp launcher for executing experiments </li></ul>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 2;\"><li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">runtime generation for experiments from two xml files generated by the designer: </li></ul>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 3;\"><li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">experiment f"
                        "ile -&gt; for the content</li>\n"
"<li style=\" font-size:8pt;\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">instance file -&gt; for the randomization</li></ul>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Author</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Created by <span style=\" font-weight:600;\">Florian Lance</span> (EPFL LNCO VR Lab manager)<span style=\" font-size:8pt;\"><br /></span><span style=\" font-weight:600;\">Email</span>: lance.florian@protonmail.com<br /><span style=\" font-weight:600;\">Github</span>: <span style=\" font-si"
                        "ze:8pt;\">https://github.com/FlorianLance</span><br /><span style=\" font-weight:600;\">Linkedin</span>: https://www.linkedin.com/in/florian-lance-b3322741</p></body></html>", nullptr));
        pbClose->setText(QCoreApplication::translate("AboutD", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutD: public Ui_AboutD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_DIALOG_H
