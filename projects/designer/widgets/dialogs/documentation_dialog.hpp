
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// Qt
#include <QDialog>
#include <QListWidget>
#include <QTextBrowser>
#include <QTabWidget>
#include <QSyntaxHighlighter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QLabel>

// local
#include "component.hpp"
#include "connector.hpp"


namespace tool::ex {

enum class DocSection {
    General=0,    // program general description
    Experiment,   // describes the life of an experiment
    Elements,     // routine, isi, loops
    Randomization,// Loops, conditions, config
    Components,   // components details
    Connectors,   // connectors details
    Interface,    // differents interface descriptions: panels, toolbar
    ExpLauncher,  // how the exp launcher is managed
    Logs,         // log behaviour
    Settings,     //
};


// test
class CSharpHighlighter : public QSyntaxHighlighter{
    Q_OBJECT

public:
    CSharpHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat digitFormat;
    QTextCharFormat keywordFormat;
    QTextCharFormat typeFormat;

    QTextCharFormat structInstancesFormat;
    QTextCharFormat classesInstancesFormat;

    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;

    QTextCharFormat defaultFormat;
};

class SectionW : public QWidget{

public:

    SectionW(QString title);

    void set_current_row(const QString &txt);

    QLabel *laTitle  = nullptr;
    QListWidget *lwContent = nullptr;
};

class DocumentationDialog : public QDialog{

    Q_OBJECT

public :

    DocumentationDialog(bool onlyPublicComponents, bool onlyStableComponents);

    static QTextBrowser *generate_text_browser();
    void init_components_doc();
    void init_connectors_doc();

public slots:

    void show_window();
    void show_section(DocSection section, bool resetWindow);
    void show_components_section(Component::Type type, bool resetWindow);
    void show_connectors_section(Connector::Type type, bool resetWindow);

private slots:

    void display_section(const QString &docCategory, DocSection section, QTextBrowser *browser, const QString &pathDocFile, const QString &windowsTitle);
    void display_components_section(Component::Type type);
    void display_connectors_section(Connector::Type type);

    void update_current_component_doc(Component::Type type);
    void update_current_connector_doc(Connector::Type type);

private:

    bool m_onlyPublicComponents = true;
    bool m_onlyStableComponents = true;

    DocSection currentSection = DocSection::General;

    QHBoxLayout *mainLayout = nullptr;

    SectionW *documentationsCategoriesW = nullptr;

    QTextBrowser *generalDocW = nullptr;
    QTextBrowser *experimentDocW = nullptr;
    QTextBrowser *elementsDocW = nullptr;
    QTextBrowser *randomizationDocW = nullptr;
    QTextBrowser *interfaceDocW = nullptr;
    QTextBrowser *expLauncherDocW = nullptr;
    QTextBrowser *logsDocW = nullptr;
    QTextBrowser *settingsDocW = nullptr;

    // components
    QWidget *componentsDocW = nullptr;
    SectionW *componentsCategoriesSectionW = nullptr;
    SectionW *componentsSectionW = nullptr;
    QTabWidget *tabComponentsDocW = nullptr;
    QTextBrowser *componentsInfoW = nullptr;
    QTextBrowser *componentsConnectionsW = nullptr;
    QTextBrowser *componentsCsharpScriptingW = nullptr;
    QTextBrowser *componentsPythonScriptingW = nullptr;
    Component::Category currentComponentCategory = Component::Category::Output;
    Component::Type currentComponent = Component::T::Logger;
    QStringList componentsCategoriesStr;
    QStringList componentsFullStr;

    // connectors
    QWidget *connectorsDocW = nullptr;
    SectionW *connectorsCategoriesSectionW = nullptr;
    SectionW *connectorsSectionW = nullptr;
    QTabWidget *tabConnectorsDocW = nullptr;
    QTextBrowser *connectorsInfoW = nullptr;
    QTextBrowser *connectorsConnectionsW = nullptr;
    Connector::Category currentConnectorCategory = Connector::Category::Generator;
    Connector::Type currentConnector = Connector::Type::Integer;
    QStringList connectorsCategoriesStr;
    QStringList connectorsFullStr;



    CSharpHighlighter *csharpHighlighter = nullptr;
    // PythonHighlighter *pythonHighlighter = nullptr;
};
}
