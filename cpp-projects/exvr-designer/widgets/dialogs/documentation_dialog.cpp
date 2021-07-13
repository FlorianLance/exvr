

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


DocumentationDialog::DocumentationDialog(bool lncoComponents) :
      m_lncoComponents(lncoComponents){

    setWindowFlag(Qt::Window);
    setModal(false);
    resize(1100,600);
    setWindowTitle(QSL("ExVR Doc:"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // init main
    setLayout(mainLayout = new QHBoxLayout());
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(documentationsCategoriesW = new SectionW(QSL("<b>Sections:</b>")));

    QStringList items;
    // by id order
    for(const auto &sectionName : all_sections_names()){
        items << from_view(sectionName);
    }
    documentationsCategoriesW->lwContent->addItems(items);

    connect(documentationsCategoriesW->lwContent, &QListWidget::currentRowChanged, this, [&](int index){
        if(auto section = get_doc_section(index); section.has_value()){
            show_section(section.value(), false);
        }
    });

    // by id order
    for(const auto &section : all_sections()){
        mainLayout->addWidget((sectionsWidgets[section] = (ui_doc_type(section) == UiDocType::TextBrowser ?  generate_text_browser() : new QWidget())));
    }

    init_components_doc();
    init_connectors_doc();

}

QTextBrowser *DocumentationDialog::generate_text_browser(){
    auto docW = new QTextBrowser();
    docW->setOpenExternalLinks(true);
    docW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
    docW->zoomIn(2);
    docW->setReadOnly(true);

    const QString path = Paths::documentationDir;
    docW->setSearchPaths({path, ".", "./images"});

    auto layout = new QHBoxLayout();
    docW->setLayout(layout);
    layout->setContentsMargins(0,0,0,0);

    return docW;
}

void DocumentationDialog::init_components_doc(){

    auto componentsDocL = new QHBoxLayout();    
    sectionsWidgets[DocSection::ContentComponentsDescription]->setLayout(componentsDocL);
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
        auto selectedCategory = Component::get_category(componentsCategoriesStr[index].toStdString()).value();
        for(const auto &type : Component::all_components_types()){
            if(Component::get_category(type) == selectedCategory){
                show_components_section(type, false);
                break;
            }
        }
    });

    connect(componentsSectionW->lwContent, &QListWidget::currentRowChanged, this, [&](int index){
        update_current_component_doc(Component::get_type_from_name(componentsFullStr[index].toStdString()).value());
    });


    // fill tabs
    tabComponentsDocW->addTab(componentsInfoW            = new QTextBrowser(), QSL("Infos"));
    tabComponentsDocW->addTab(componentsConnectionsW     = new QTextBrowser(), QSL("Connections"));
    tabComponentsDocW->addTab(componentsCsharpScriptingW = new QTextBrowser(), QSL("CSharp scripting"));
//    tabComponentsDocW->addTab(componentsPythonScriptingW = new QTextBrowser(), QSL("Python scripting"));

    const QString path = Paths::documentationDir % QSL("/") % from_view(markdown_file(DocSection::ContentComponentsDescription));
    componentsInfoW->setOpenExternalLinks(true);
    componentsInfoW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
    componentsInfoW->zoomIn(2);
    componentsInfoW->setSearchPaths({path, ".", "./info_images"});
    componentsInfoW->setReadOnly(true);

    componentsConnectionsW->setOpenExternalLinks(true);
    componentsConnectionsW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
    componentsConnectionsW->zoomIn(2);                   
    componentsConnectionsW->setSearchPaths({path, ".", "./connections_images"});
    componentsConnectionsW->setReadOnly(true);

    componentsCsharpScriptingW->setOpenExternalLinks(true);
    componentsCsharpScriptingW->setStyleSheet("background-color: rgb(30,30,30);");
    componentsCsharpScriptingW->zoomIn(3);
    componentsCsharpScriptingW->setSearchPaths({path, ".", "./csharp_images"});
    componentsCsharpScriptingW->setReadOnly(true);

//    componentsPythonScriptingW->setOpenExternalLinks(true);
//    componentsPythonScriptingW->setSearchPaths({Paths::componentsDocDir});
//    componentsPythonScriptingW->setReadOnly(true);

    csharpHighlighter = new CSharpHighlighter(componentsCsharpScriptingW->document());
}

void DocumentationDialog::init_connectors_doc(){

    auto connectorsDocL  = new QHBoxLayout();
    sectionsWidgets[DocSection::ContentConnectorsDescription]->setLayout(connectorsDocL);
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

    const QString path = Paths::documentationDir % QSL("/") % from_view(markdown_file(DocSection::ContentConnectorsDescription));
    connectorsInfoW->setOpenExternalLinks(true);
    connectorsInfoW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
    connectorsInfoW->zoomIn(2);
    connectorsInfoW->setSearchPaths({path});
    connectorsInfoW->setReadOnly(true);

    connectorsConnectionsW->setOpenExternalLinks(true);
    connectorsConnectionsW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
    connectorsConnectionsW->zoomIn(2);
    connectorsConnectionsW->setSearchPaths({path});
    connectorsConnectionsW->setReadOnly(true);
}


void DocumentationDialog::show_window(){
    show_section(currentSection, true);
}

void DocumentationDialog::show_components_section(Component::Type type, bool resetWindow){
    currentComponent         = type;
    currentComponentCategory = Component::get_category(currentComponent);
    show_section(DocSection::ContentComponentsDescription, resetWindow);
}

void DocumentationDialog::show_connectors_section(Connector::Type type, bool resetWindow){
    currentConnector = type;
    currentConnectorCategory = Connector::get_category(currentConnector);
    show_section(DocSection::ContentConnectorsDescription, resetWindow);
}

void DocumentationDialog::show_section(DocSection section, bool resetWindow){

    if(resetWindow){
        if(isVisible()){
            hide();
        }
    }

    currentSection   = section;
    if(currentSection == DocSection::ContentComponentsDescription){
        display_components_section(currentComponent);
    }else if(currentSection == DocSection::ContentConnectorsDescription){
        display_connectors_section(currentConnector);
    }else{
        display_other_section();
    }

    // set stretch and visibility
    mainLayout->setStretch(0,5);
    for(int ii = 1; ii < 16; ++ii){
        mainLayout->setStretch(ii,0);
    }

    for(auto &sectionW : sectionsWidgets){
        if(section == sectionW.first){
            sectionW.second->setVisible(true);
            mainLayout->setStretch(section_id(section)+1 ,20);
        }else{
            sectionW.second->setVisible(false);
        }
    }


    // show dialog
    show();
}


void DocumentationDialog::display_other_section(){

    // update section
    documentationsCategoriesW->set_current_row(from_view(section_name(currentSection)));

    QTextBrowser *browser = dynamic_cast<QTextBrowser*>(sectionsWidgets[currentSection]);
    const QString pathDocFile = Paths::documentationDir % QSL("/") % from_view(markdown_file(currentSection));
    QFile docFile(pathDocFile);
    if(!docFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        browser->setText(QSL("No documentation file found: ") % pathDocFile);
    }else {
        QTextStream in(&docFile);
        browser->setMarkdown(in.readAll());
    }

    setWindowTitle(QSL("ExVR Doc: ") % from_view(section_name(currentSection)));
}

void DocumentationDialog::display_components_section(Component::Type type){

    // update section
    documentationsCategoriesW->set_current_row(from_view(section_name(currentSection)));

    // update category row
    componentsCategoriesSectionW->set_current_row(from_view(Component::to_string(Component::get_category(type))));

    // update component row
    update_current_category_components_list();
    componentsSectionW->set_current_row(from_view(Component::get_full_name(type)));

    // update markdown from type
    update_current_component_doc(type);
}

void DocumentationDialog::display_connectors_section(Connector::Type type){

    // update section
    documentationsCategoriesW->set_current_row(from_view(section_name(currentSection)));

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

    setWindowTitle(QSL("ExVR Doc: ") % from_view(section_name(currentSection)) % QSL(" ") %from_view(Component::get_full_name(currentComponent)));
    const QString basePath        = Paths::documentationDir % QSL("/") % from_view(markdown_file(currentSection));
    const QString infoPath        = basePath % QSL("/") % componentTypeName % QSL("_info.md");
    const QString connectionsPath = basePath % QSL("/") % componentTypeName % QSL("_connections.md");
    const QString csPath          = basePath % QSL("/") % componentTypeName % QSL("_csharp.md");
    const QString pyPath          = basePath % QSL("/") % componentTypeName % QSL("_python.md");

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

//    QFile pyFile(pyPath);
//    if(!pyFile.open(QIODevice::ReadOnly | QIODevice::Text)){
//        // componentsPythonScriptingW->setMarkdown(QSL("No documentation file found: ") % pyPath);
//        componentsPythonScriptingW->setMarkdown(QSL("No implemented yet.")); // [TODO_DOC]
//    }else {
//        QTextStream in(&pyFile);
//        componentsPythonScriptingW->setMarkdown(in.readAll());
//    }
}

void DocumentationDialog::update_current_connector_doc(Connector::Type type){

    currentConnector = type;

    // update window with component type
    const QString connectorTypeName = from_view(Connector::get_name(currentConnector));

    setWindowTitle(QSL("ExVR Doc: ") % from_view(section_name(currentSection)) % QSL(" ") % from_view(Connector::get_caption(currentConnector)));
    const QString basePath       = Paths::documentationDir % QSL("/") % from_view(markdown_file(currentSection));
    const QString infoPath        = basePath % QSL("/") % connectorTypeName % QSL("_info.md");
    const QString connectionsPath = basePath % QSL("/") % connectorTypeName % QSL("_connections.md");

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

void DocumentationDialog::update_current_category_components_list(){

    componentsSectionW->lwContent->blockSignals(true);
    componentsSectionW->lwContent->clear();
    componentsFullStr.clear();
    for(const auto &type : Component::all_components_types()){

        if(Component::get_category(type) != currentComponentCategory){
            continue;
        }

        if(!m_lncoComponents && Component::get_restricted(type) == Component::Restricted::LNCO){
            continue;
        }
        componentsFullStr <<  from_view(Component::get_full_name(type));
    }
    componentsSectionW->lwContent->addItems(componentsFullStr);
    componentsSectionW->lwContent->blockSignals(false);
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
