

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "documentation_dialog.hpp"

// Qt
#include <QFile>
#include <QStringBuilder>

// qt-utility
#include "qt_logger.hpp"

// local
#include "path_utility.hpp"
//#include "qmarkdowntextedit.h"
//#include "markdownhighlighter.h"


using namespace tool::ex;


DocumentationDialog::DocumentationDialog(bool onlyPublicComponents, bool onlyStableComponents) :
      m_onlyPublicComponents(onlyPublicComponents), m_onlyStableComponents(onlyStableComponents){

    setWindowFlag(Qt::Window);
    setModal(false);
    resize(1100,600);
    setWindowTitle(QSL("DOC"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // init main
    setLayout(mainLayout = new QHBoxLayout());
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(documentationsCategoriesW = new SectionW(QSL("<b>Sections:</b>")));

    documentationsCategoriesW->lwContent->addItems({
      /* 0 **/  QSL("General"),      // program general description
      /* 1 **/  QSL("Experiment"),   // describes the life of an experiment
      /* 2 **/  QSL("Elements"),     // routine, isi, loops
      /* 3 **/  QSL("Randomization"),// Loops, conditions, config
      /* 4 **/  QSL("Components"),   // components details
      /* 5 **/  QSL("Connectors"),   // connectors details
      /* 6 **/  QSL("Interface"),    // differents interface descriptions: panels, toolbar
      /* 7 **/  QSL("Exp launcher"),     // how the exvr-exp is managed
      /* 8 **/  QSL("Logs"),         // log behaviour
      /* 9 **/  QSL("Settings"),     //
    });
    connect(documentationsCategoriesW->lwContent, &QListWidget::currentRowChanged, this, [&](int index){
        show_section(currentSection = static_cast<DocSection>(index), false);
    });

    mainLayout->addWidget(generalDocW = generate_text_browser());
    mainLayout->addWidget(experimentDocW = generate_text_browser());
    mainLayout->addWidget(elementsDocW = generate_text_browser());
    mainLayout->addWidget(randomizationDocW = generate_text_browser());
    init_components_doc();
    init_connectors_doc();
    mainLayout->addWidget(interfaceDocW = generate_text_browser());
    mainLayout->addWidget(expLauncherDocW = generate_text_browser());
    mainLayout->addWidget(logsDocW = generate_text_browser());
    mainLayout->addWidget(settingsDocW = generate_text_browser());
}

QTextBrowser *DocumentationDialog::generate_text_browser(){
    auto docW = new QTextBrowser();
    docW->setOpenExternalLinks(true);
    docW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
    docW->zoomIn(2);
    docW->setReadOnly(true);

    auto layout = new QHBoxLayout();
    docW->setLayout(layout);
    layout->setContentsMargins(0,0,0,0);

    return docW;
}

void DocumentationDialog::init_components_doc(){

    // init components
    mainLayout->addWidget(componentsDocW = new QWidget());

    auto componentsDocL = new QHBoxLayout();
    componentsDocW->setLayout(componentsDocL);
    componentsDocL->setContentsMargins(0,0,0,0);
    componentsDocL->addWidget(componentsCategoriesSectionW = new SectionW("Categories"));
    componentsDocL->addWidget(componentsSectionW = new SectionW("Components"));
    componentsDocL->addWidget(tabComponentsDocW = new QTabWidget());
    componentsDocL->setStretch(0,1);
    componentsDocL->setStretch(1,2);
    componentsDocL->setStretch(2,10);

    // fill categories
    using C = Component;
    for(const auto &category : C::all_categories()){

        auto categoryComponents = C::components.tuples_matching_columns_values<C::ColCategory>(category);
//        auto categoryComponents = C::components.tuples_matching_columns_values<C::ColCategory, C::ColRestricted, C::ColState>(
//            category,
//            m_onlyPublicComponents ? C::Restricted::Publ : C::Restricted::LNCO,
//            m_onlyStableComponents ? C::State::Sta       : C::State::Exp
//        );

        if(categoryComponents.size() > 0){
            componentsCategoriesStr << from_view(C::to_string(category));
        }
    }
    componentsCategoriesSectionW->lwContent->addItems(componentsCategoriesStr);

    // connections
    connect(componentsCategoriesSectionW->lwContent, &QListWidget::currentRowChanged, this, [&](int index){

        componentsSectionW->lwContent->blockSignals(true);
        componentsSectionW->lwContent->clear();
        componentsFullStr.clear();

        currentComponentCategory = Component::get_category(componentsCategoriesStr[index].toStdString()).value();

        for(const auto &type : Component::all_components_types()){

            if(Component::get_category(type) != currentComponentCategory){
                continue;
            }

//            if(m_onlyPublicComponents){
//                if(Component::get_restricted(type) == Component::Restricted::LNCO){
//                    continue;
//                }
//            }
//            if(m_onlyStableComponents){
//                if(Component::get_state(type) == Component::State::Exp){
//                    continue;
//                }
//            }
            componentsFullStr <<  from_view(Component::get_full_name(type));
        }

        componentsSectionW->lwContent->addItems(componentsFullStr);
        componentsSectionW->lwContent->blockSignals(false);

        if(componentsFullStr.size() > 0){
            update_current_component_doc(Component::get_type_from_name(componentsFullStr[0].toStdString()).value());
        }
    });

    connect(componentsSectionW->lwContent, &QListWidget::currentRowChanged, this, [&](int index){
        update_current_component_doc(Component::get_type_from_name(componentsFullStr[index].toStdString()).value());
    });


    // fill tabs
    tabComponentsDocW->addTab(componentsInfoW            = new QTextBrowser(), QSL("Infos"));
    tabComponentsDocW->addTab(componentsConnectionsW     = new QTextBrowser(), QSL("Connections"));
    tabComponentsDocW->addTab(componentsCsharpScriptingW = new QTextBrowser(), QSL("CSharp scripting"));
    tabComponentsDocW->addTab(componentsPythonScriptingW = new QTextBrowser(), QSL("Python scripting"));

    componentsInfoW->setOpenExternalLinks(true);
    componentsInfoW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
    componentsInfoW->zoomIn(2);
    componentsInfoW->setSearchPaths({Paths::componentsDocDir});
    componentsInfoW->setReadOnly(true);

    componentsConnectionsW->setOpenExternalLinks(true);
    componentsConnectionsW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
    componentsConnectionsW->zoomIn(2);
    componentsConnectionsW->setSearchPaths({Paths::componentsDocDir});
    componentsConnectionsW->setReadOnly(true);

    componentsCsharpScriptingW->setOpenExternalLinks(true);
    componentsCsharpScriptingW->setStyleSheet("background-color: rgb(30,30,30);");
    componentsCsharpScriptingW->zoomIn(3);
    componentsCsharpScriptingW->setSearchPaths({Paths::componentsDocDir});
    componentsCsharpScriptingW->setReadOnly(true);

    componentsPythonScriptingW->setOpenExternalLinks(true);
    componentsPythonScriptingW->setSearchPaths({Paths::componentsDocDir});
    componentsPythonScriptingW->setReadOnly(true);

    csharpHighlighter = new CSharpHighlighter(componentsCsharpScriptingW->document());
}

void DocumentationDialog::init_connectors_doc(){

    // init connectors
    mainLayout->addWidget(connectorsDocW = new QWidget());

    auto connectorsDocL  = new QHBoxLayout();
    connectorsDocW->setLayout(connectorsDocL);
    connectorsDocL->setContentsMargins(0,0,0,0);
    connectorsDocL->addWidget(connectorsCategoriesSectionW = new SectionW("Categories"));
    connectorsDocL->addWidget(connectorsSectionW = new SectionW("Connectors"));
    connectorsDocL->addWidget(tabConnectorsDocW = new QTabWidget());
    connectorsDocL->setStretch(0,1);
    connectorsDocL->setStretch(1,2);
    connectorsDocL->setStretch(2,10);

    // fill categories
    for(const auto &categoryName : Connector::all_categories_name()){
        connectorsCategoriesStr << from_view(categoryName);
    }
    connectorsCategoriesSectionW->lwContent->addItems(connectorsCategoriesStr);

    // connections
    connect(connectorsCategoriesSectionW->lwContent, &QListWidget::currentRowChanged, this, [&](int index){

        connectorsSectionW->lwContent->blockSignals(true);
        connectorsSectionW->lwContent->clear();
        connectorsFullStr.clear();

        currentConnectorCategory = Connector::get_category_from_name(connectorsCategoriesStr[index].toStdString()).value();

        for(const auto &type : Connector::all_types()){
            if(Connector::get_category(type) != currentConnectorCategory){
                continue;
            }
            connectorsFullStr <<  from_view(Connector::get_caption(type));
        }

        connectorsSectionW->lwContent->addItems(connectorsFullStr);
        connectorsSectionW->lwContent->blockSignals(false);

        if(connectorsFullStr.size() > 0){
            update_current_connector_doc(Connector::get_type_from_caption(connectorsFullStr[0].toStdString()).value());
        }
    });


    connect(connectorsSectionW->lwContent, &QListWidget::currentRowChanged, this, [&](int index){
         update_current_connector_doc(Connector::get_type_from_caption(connectorsFullStr[index].toStdString()).value());
    });

    // fill tabs
    tabConnectorsDocW->addTab(connectorsInfoW            = new QTextBrowser(), QSL("Infos"));
    tabConnectorsDocW->addTab(connectorsConnectionsW     = new QTextBrowser(), QSL("Connections"));

    connectorsInfoW->setOpenExternalLinks(true);
    connectorsInfoW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
    connectorsInfoW->zoomIn(2);
    connectorsInfoW->setSearchPaths({Paths::connectorsDocDir});
    connectorsInfoW->setReadOnly(true);

    connectorsConnectionsW->setOpenExternalLinks(true);
    connectorsConnectionsW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
    connectorsConnectionsW->zoomIn(2);
    connectorsConnectionsW->setSearchPaths({Paths::connectorsDocDir});
    connectorsConnectionsW->setReadOnly(true);
}


void DocumentationDialog::show_window(){
    show_section(currentSection, true);
}

void DocumentationDialog::show_section(DocSection section, bool resetWindow){

    if(resetWindow){
        if(isVisible()){
            hide();
        }
    }

    bool generalS = false;
    bool experimentS = false;
    bool elementsS = false;
    bool randomizationS = false;
    bool componentsS = false;
    bool connectorsS = false;
    bool interfaceS = false;
    bool expLauncherS = false;
    bool logsS = false;
    bool settingsS = false;

    switch (section) {
        case DocSection::General:
            display_section("General", DocSection::General, generalDocW, Paths::generalDocFile, QSL("DOC: GENERAL"));
            generalS = true;
            break;
        case DocSection::Experiment:
            display_section("Experiment", DocSection::Experiment, experimentDocW, Paths::experimentDocFile, QSL("DOC: EXPERIMENT"));
            experimentS = true;
            break;
        case DocSection::Elements:
            display_section("Elements", DocSection::Elements, elementsDocW, Paths::elementsDocFile, QSL("DOC: ELEMENTS"));
            elementsS = true;
            break;
        case DocSection::Randomization:
            display_section("Randomization", DocSection::Randomization, randomizationDocW, Paths::randomizationDocFile, QSL("DOC: RANDOMIZATION"));
            randomizationS = true;
            break;
        case DocSection::Components:
            display_components_section(currentComponent);
            componentsS = true;
            break;
        case DocSection::Connectors:
            display_connectors_section(currentConnector);
            connectorsS = true;
            break;
        case DocSection::Interface:
            display_section("Interface", DocSection::Interface, interfaceDocW, Paths::interfaceDocFile, QSL("DOC: INTERFACE"));
            interfaceS = true;
            break;
        case DocSection::ExpLauncher:
            display_section("Exp launcher,", DocSection::ExpLauncher, expLauncherDocW, Paths::expLauncherDocFile, QSL("DOC: EXP-LAUNCHER"));
            expLauncherS = true;
            break;
        case DocSection::Logs:
            display_section("Logs", DocSection::Logs, logsDocW, Paths::logsDocFile, QSL("DOC: LOGS"));
            logsS = true;
            break;
        case DocSection::Settings:
            display_section("Settings", DocSection::Settings, settingsDocW, Paths::settingsDocFile, QSL("DOC: SETTINGS"));
            settingsS = true;
            break;
        default:
            break;
    }

    // show widgets
    generalDocW->setVisible(generalS);
    experimentDocW->setVisible(experimentS);
    elementsDocW->setVisible(elementsS);
    randomizationDocW->setVisible(randomizationS);
    componentsDocW->setVisible(componentsS);
    connectorsDocW->setVisible(connectorsS);
    interfaceDocW->setVisible(interfaceS);
    expLauncherDocW->setVisible(expLauncherS);
    logsDocW->setVisible(logsS);
    settingsDocW->setVisible(settingsS);

    // set strech
    mainLayout->setStretch(0,1);  // section
    mainLayout->setStretch(1,generalS ? 10 : 0);
    mainLayout->setStretch(2,experimentS ? 10 : 0);
    mainLayout->setStretch(3,elementsS ? 10 : 0);
    mainLayout->setStretch(4,randomizationS ? 10 : 0);
    mainLayout->setStretch(5,componentsS ? 10 : 0);
    mainLayout->setStretch(6,connectorsS ? 10 : 0);
    mainLayout->setStretch(7,interfaceS ? 10 : 0);
    mainLayout->setStretch(8,expLauncherS ? 10 : 0);
    mainLayout->setStretch(9,logsS ? 10 : 0);
    mainLayout->setStretch(10,settingsS ? 10 : 0);

    // show dialog
    show();
}

void DocumentationDialog::show_components_section(Component::Type type, bool resetWindow){
    currentComponent = type;
    currentComponentCategory = Component::get_category(currentComponent);
    show_section(DocSection::Components, resetWindow);
}

void DocumentationDialog::show_connectors_section(Connector::Type type, bool resetWindow){
    currentConnector = type;
    currentConnectorCategory = Connector::get_category(currentConnector);
    show_section(DocSection::Connectors, resetWindow);
}

void DocumentationDialog::display_section(const QString &docCategory, DocSection section, QTextBrowser *browser, const QString &pathDocFile, const QString &windowsTitle){

    // update section
    currentSection   = section;
    documentationsCategoriesW->set_current_row(docCategory);

    QFile docFile(pathDocFile);
    if(!docFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        browser->setText(QSL("No documentation file found: ") % pathDocFile);
    }else {
        QTextStream in(&docFile);
        browser->setMarkdown(in.readAll());
    }

    setWindowTitle(windowsTitle);
}

void DocumentationDialog::display_components_section(Component::Type type){

    // update section
    currentSection   = DocSection::Components;
    documentationsCategoriesW->set_current_row(QSL("Components"));

    // update category row
    componentsCategoriesSectionW->set_current_row(from_view(Component::to_string(Component::get_category(type))));

    // update component row
    if(componentsSectionW->lwContent->count() == 0 || currentComponentCategory != Component::get_category(type)){

        componentsSectionW->lwContent->blockSignals(true);
        componentsSectionW->lwContent->clear();
        componentsFullStr.clear();
        currentComponentCategory = Component::get_category(type);
        for(const auto &component : Component::components.data){
            if(std::get<1>(component) == currentComponentCategory){
                componentsFullStr << from_view(Component::get_full_name(std::get<0>(component)));
            }
        }
        componentsSectionW->lwContent->addItems(componentsFullStr);
        componentsSectionW->lwContent->blockSignals(false);

//        if(componentsFullStr.size() > 0){
//            update_current_component_doc(Component::get_type_from_name(componentsFullStr[0].toStdString()).value());
//        }
    }
    componentsSectionW->set_current_row(from_view(Component::get_full_name(type)));

    // update markdown from type
    update_current_component_doc(type);
}

void DocumentationDialog::display_connectors_section(Connector::Type type){

    // update section
    currentSection   = DocSection::Connectors;
    documentationsCategoriesW->set_current_row(QSL("Connectors"));

    // update category row
    connectorsCategoriesSectionW->set_current_row(from_view(Connector::get_name((Connector::get_category(type)))));


    // update connector row
    if(connectorsSectionW->lwContent->count() == 0 || currentConnectorCategory != Connector::get_category(type)){

        connectorsSectionW->lwContent->blockSignals(true);
        connectorsSectionW->lwContent->clear();
        connectorsFullStr.clear();
        currentConnectorCategory = Connector::get_category(type);

        for(const auto &connector : Connector::connectors.data){
            if(std::get<1>(connector) == currentConnectorCategory){
                connectorsFullStr << from_view(Connector::get_caption(std::get<0>(connector)));
            }
        }
        connectorsSectionW->lwContent->addItems(connectorsFullStr);
        connectorsSectionW->lwContent->blockSignals(false);

//        if(connectorsFullStr.size() > 0){
//            update_current_connector_doc(Connector::get_type_from_name(connectorsFullStr[0].toStdString()).value());
//        }
    }
    connectorsSectionW->set_current_row(from_view(Connector::get_caption(type)));

    // update markdown from type
    update_current_connector_doc(type);
}

void DocumentationDialog::update_current_component_doc(Component::Type type){

    currentComponent = type;

    // update window with component type
    const QString componentTypeName = from_view(Component::get_type_name(currentComponent));
    setWindowTitle(QSL("DOC: COMPONENT: ") % from_view(Component::get_full_name(currentComponent)));
    const QString infoPath        = Paths::componentsDocDir % QSL("/") % componentTypeName % QSL("_info.md");
    const QString connectionsPath = Paths::componentsDocDir % QSL("/") % componentTypeName % QSL("_connections.md");
    const QString csPath          = Paths::componentsDocDir % QSL("/") % componentTypeName % QSL("_csharp.md");
    const QString pyPath          = Paths::componentsDocDir % QSL("/") % componentTypeName % QSL("_python.md");

    QFile infoFile(infoPath);
    if(!infoFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        componentsInfoW->setText(QSL("No documentation file found: ") % infoPath);
    }else {
        QTextStream in(&infoFile);
        componentsInfoW->setMarkdown(in.readAll());
    }

    QFile connectionsFile(connectionsPath);
    if(!connectionsFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        componentsConnectionsW->setText(QSL("No documentation file found: ") % connectionsPath);
    }else {
        QTextStream in(&connectionsFile);
        componentsConnectionsW->setMarkdown(in.readAll());
    }

    QFile csFile(csPath);
    if(!csFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        componentsCsharpScriptingW->setMarkdown(QSL("No documentation file found: ") % csPath);
    }else {
        QTextStream in(&csFile);
        componentsCsharpScriptingW->setMarkdown(in.readAll());

    }

    QFile pyFile(pyPath);
    if(!pyFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        // componentsPythonScriptingW->setMarkdown(QSL("No documentation file found: ") % pyPath);
        componentsPythonScriptingW->setMarkdown(QSL("No implemented yet.")); // [TODO_DOC]
    }else {
        QTextStream in(&pyFile);
        componentsPythonScriptingW->setMarkdown(in.readAll());
    }
}

void DocumentationDialog::update_current_connector_doc(Connector::Type type){

    currentConnector = type;

    // update window with component type
    const QString connectorTypeName = from_view(Connector::get_name(currentConnector));
    setWindowTitle(QSL("DOC: CONNECTOR: ") % from_view(Connector::get_caption(currentConnector)));
    const QString infoPath        = Paths::connectorsDocDir % QSL("/") % connectorTypeName % QSL("_info.md");
    const QString connectionsPath = Paths::connectorsDocDir % QSL("/") % connectorTypeName % QSL("_connections.md");

    QFile infoFile(infoPath);
    if(!infoFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        connectorsInfoW->setText(QSL("No documentation file found: ") % infoPath);
    }else {
        QTextStream in(&infoFile);
        connectorsInfoW->setMarkdown(in.readAll());
    }

    QFile connectionsFile(connectionsPath);
    if(!connectionsFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        connectorsConnectionsW->setText(QSL("No documentation file found: ") % connectionsPath);
    }else {
        QTextStream in(&connectionsFile);
        connectorsConnectionsW->setMarkdown(in.readAll());
    }
}



CSharpHighlighter::CSharpHighlighter(QTextDocument *parent): QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    // set formats
    keywordFormat.setForeground(QColor(82,156,214));
    keywordFormat.setFontWeight(QFont::Bold);

    digitFormat.setForeground(QColor(167,206,168));

    typeFormat.setForeground(QColor(82,156,214));
    typeFormat.setFontWeight(QFont::Bold);

    structInstancesFormat.setForeground(QColor(134,176,95));
    structInstancesFormat.setFontWeight(QFont::Bold);

    classesInstancesFormat.setForeground(QColor(63, 201, 176));
    classesInstancesFormat.setFontWeight(QFont::Bold);


    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(QColor(63, 201, 176));

    quotationFormat.setForeground(QColor(214, 157, 133));

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(QColor(220,220,200));

    singleLineCommentFormat.setForeground(QColor(87, 166, 70));
    multiLineCommentFormat.setForeground(QColor(87, 166, 70));

    defaultFormat.setForeground(QColor(220,220,200));

    // class
    rule.pattern = QRegularExpression(QSL("\\b[A-Za-z]+\\b"));
    rule.format = classFormat;
//    highlightingRules.append(rule);


    // digits
    rule.pattern = QRegularExpression(QSL("\\b[0-9]*[,.]?[0-9]*[f]?\\b"));
    rule.format = digitFormat;
    highlightingRules.append(rule);

    // function
    rule.pattern = QRegularExpression(QSL("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);

    // keywords
    const QString keywordPatterns[] = {
        QSL("\\bdo\\b"), QSL("\\bsizeof\\b"), QSL("\\bthis\\b"),
        QSL("\\bref\\b"), QSL("\\binternal\\b"), QSL("\\bout\\b"),
        QSL("\\bvolatile\\b"), QSL("\\breturn\\b"),QSL("\\babstract\\b"),
        QSL("\\bas\\b"), QSL("\\bbase\\b"),QSL("\\btry\\b"),
        QSL("\\btry\\b"), QSL("\\bcatch\\b"), QSL("\\bdelegate\\b"),
        QSL("\\bchecked\\b"),QSL("\\bexplicit\\b"),
        QSL("\\bforeach\\b"), QSL("\\bgoto\\b"),
        QSL("\\bis\\b"),QSL("\\block\\b"), QSL("\\bevent\\b"),
        QSL("\\bdefault\\b"), QSL("\\bextern\\b"),
        QSL("\\bstackalloc\\b"), QSL("\\bin\\b"), QSL("\\bimplicit\\b"),
        QSL("\\bfinally\\b"),QSL("\\bfixed\\b"),
        QSL("\\bnull\\b"), QSL("\\boperator\\b"),
        QSL("\\bparams\\b"),QSL("\\breadonly\\b"),
        QSL("\\bnew\\b"), QSL("\\bcontinue\\b"),
        QSL("\\bsealed\\b"),QSL("\\bthrow\\b"), QSL("\\bunsafe\\b"),
        QSL("\\bunchecked\\b"),QSL("\\btypeof\\b"),
        QSL("\\bswitch\\b"), QSL("\\bcase\\b"),QSL("\\bbreak\\b"),
        QSL("\\bwhile\\b"), QSL("\\bfor\\b"),
        QSL("\\bif\\b"), QSL("\\belse\\b"),
        QSL("\\btrue\\b"), QSL("\\bfalse\\b"),
        QSL("\\bclass\\b"), QSL("\\bconst\\b"),
        QSL("\\bEnum\\b"), QSL("\\busing\\b"),
        QSL("\\bprivate\\b"), QSL("\\bprotected\\b"), QSL("\\bpublic\\b"),
        QSL("\\bstatic\\b"), QSL("\\bstruct\\b"),
        QSL("\\bvirtual\\b"), QSL("\\boverride\\b"), QSL("\\bnamespace\\b")
    };

    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // types
    const QString typesPatterns[] = {
        QSL("\\bvoid\\b"), QSL("\\bvar\\b"),
        // built-in values types
        QSL("\\bbool\\b"),
        QSL("\\bbyte\\b"), QSL("\\bsbyte\\b"),
        QSL("\\bchar\\b"),
        QSL("\\bdecimal\\b"),
        QSL("\\bdouble\\b"), QSL("\\bfloat\\b"),
        QSL("\\buint\\b"), QSL("\\bint\\b"),
        QSL("\\bulong\\b"), QSL("\\blong\\b"),
        QSL("\\bushort\\b"), QSL("\\bshort\\b"),
        // built-in references types
        QSL("\\bstring\\b"), QSL("\\bobject\\b"), QSL("\\bdynamic\\b"),
    };

    for (const QString &pattern : typesPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = typeFormat;
        highlightingRules.append(rule);
    }

    // structs instances
    const QString structsInstancesPatterns[] = {
        QSL("\\Color\\b"),
        QSL("\\bVector2\\b"), QSL("\\bVector3\\b"), QSL("\\bQuaternion\\b"),
    };
    for (const QString &pattern : structsInstancesPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = structInstancesFormat;
        highlightingRules.append(rule);
    }

    // classes instances
    const QString classesInstancesPatterns[] = {
        QSL("\\bType\\b"),
        QSL("\\bArrayList\\b"), QSL("\\bHashtable\\b"),
        QSL("\\bList\\b"), QSL("\\bSortedList\\b"),
        QSL("\\bQueue\\b"), QSL("\\bStack\\b"),
        QSL("\\bDictionary\\b"), QSL("\\bTuple\\b"),
        QSL("\\bGameObject\\b"),QSL("\\bTransform\\b"),
        QSL("\\bMesh\\b"),QSL("\\bAudioClip\\b"),
        QSL("\\bAudioSource\\b"),QSL("\\bTexture2D\\b"),
        // exvr
//        QSL("\\ExComponent\\b"),QSL("\\bExConnector\\b"),
    };
    for (const QString &pattern : classesInstancesPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = classesInstancesFormat;
        highlightingRules.append(rule);
    }

    // add components class names
    for(const auto &unityStr : Component::components.tuple_column<Component::ColUnityStr>()){
        QString componentClassName = from_view(unityStr) % QSL("Component");
        rule.pattern = QRegularExpression(componentClassName);
        rule.format = classesInstancesFormat;
        highlightingRules.append(rule);
    }

    // quotation
    rule.pattern = QRegularExpression(QSL("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    // single line comment
    rule.pattern = QRegularExpression(QSL("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    // comments
    commentStartExpression = QRegularExpression(QSL("/\\*"));
    commentEndExpression = QRegularExpression(QSL("\\*/"));
}


void CSharpHighlighter::highlightBlock(const QString &text){

    setFormat(0, text.length(), defaultFormat);

    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);

        if(!matchIterator.hasNext()){

            continue;
        }

        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1){
        startIndex = text.indexOf(commentStartExpression);
    }

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}

SectionW::SectionW(QString title){

    auto layout = new QVBoxLayout();
    layout->setContentsMargins(2,2,2,2);
    setLayout(layout);
    layout->addWidget(laTitle = new QLabel(title));
    layout->addWidget(lwContent = new QListWidget());
}

void SectionW::set_current_row(const QString &txt){

    lwContent->blockSignals(true);
    for(int ii = 0; ii < lwContent->count(); ++ii){
        if(lwContent->item(ii)->text() == txt){
            lwContent->setCurrentRow(ii);
            break;
        }
    }
    lwContent->blockSignals(false);
}
