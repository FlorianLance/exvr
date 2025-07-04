
/***********************************************************************************
** exvr-designer                                                                  **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

#include "documentation_dialog.hpp"

// Qt
#include <QFile>
#include <QStringBuilder>

// qt-utility
#include "qt_logger.hpp"
#include "gui/widgets/qt_text_widget_highlighter.hpp"

// local
#include "utility/path_utility.hpp"


using namespace tool::ex;


DocumentationDialog::DocumentationDialog(){

    setWindowFlag(Qt::Window);
    setModal(false);
    resize(1100,600);
    setWindowTitle(QSL("ExVR Doc:"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // init main
    setLayout(mainLayout = new QHBoxLayout());
    mainLayout->setContentsMargins(0,0,0,0);

    genPb = new QPushButton("Generate");
    openPb = new QPushButton("Open");
    reloadPb = new QPushButton("Reload");
    connect(genPb, &QPushButton::clicked, this, [&]{
        QFile file(currentDocPath);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << "...";
            genPb->setEnabled(false);
            openPb->setEnabled(true);
        }else{
            QtLog::error(QSL("Cannot create log file with path ") % currentDocPath);
        }
    });
    connect(openPb, &QPushButton::clicked, this, [&]{
        QDesktopServices::openUrl(QUrl::fromLocalFile(currentDocPath));
    });
    connect(reloadPb, &QPushButton::clicked, this, [&]{

        auto fileName = currentDocPath.split("/").last();

        if(auto sec = get_doc_section(fileName.toStdString().c_str()); sec.has_value()){
            reload_sub_section_markdown_file(sec.value(), true);
        }else{

            if(currentSection == DocSection::ContentComponentsDescription){
                const QString componentTypeName = from_view(Component::get_type_name(currentComponent));
                const QString basePath        = Paths::documentationDir % QSL("/") % from_view(markdown_file(currentSection));

                if(fileName.contains("_csharp.md")){
                    const QString csPath          = basePath % QSL("/") % componentTypeName % QSL("_csharp.md");
                    reload_csharp_markdown_file(csPath);
                }else if(fileName.contains("_connections.md")){
                    const QString connectionsPath = basePath % QSL("/") % componentTypeName % QSL("_connections.md");
                    reload_connections_file(connectionsPath);
                }else if(fileName.contains("_info.md")){
                    const QString infoPath        = basePath % QSL("/") % componentTypeName % QSL("_info.md");
                    reload_info_file(infoPath);
                }
            }else if(currentSection == DocSection::ContentConnectorsDescription){
                // ...
            }
        }
    });
    
    auto buttons = ui::F::old_gen(ui::L::HB(),{genPb, openPb, reloadPb}, LStretch{true},LMargins{false});
    mainLayout->addWidget(ui::F::old_gen(ui::L::VB(),{buttons, documentationsCategoriesW = new SectionW(QSL("<b>Sections:</b>"))}, LStretch{false}, LMargins{true}));

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
    connect(documentationsCategoriesW->lwContent, &QListWidget::clicked, this, [&](QModelIndex index){
        if(auto section = get_doc_section(index.row()); section.has_value()){
            show_section(section.value(), false);
        }
    });

    // by id order
    for(const auto &section : all_sections()){
        auto sectionW = ui_doc_type(section) == UiDocType::TextBrowser ?  generate_text_browser() : new QWidget();
        sectionsWidgets[section] = sectionW;
        mainLayout->addWidget(sectionW);

        if(section != DocSection::ContentComponentsDescription && section != DocSection::ContentConnectorsDescription){
            QTextBrowser *browser = dynamic_cast<QTextBrowser*>(sectionsWidgets[section]);
            browser->setOpenLinks(false);
//
            connect(browser, &QTextBrowser::anchorClicked, this, [&](const QUrl &link){
                if(link.toString().contains("https://www")){
                    QDesktopServices::openUrl(link);
                }else{

                    if(auto sec = get_doc_section(link.fileName().toStdString().c_str()); sec.has_value()){
                        show_section(sec.value(), true);
                    }else if(link.toString().contains("components/")){
                        auto name = link.toString().remove("components/").split("_").first();
                        auto componentType = Component::get_type_from_unity_name(Component::UnityStr{name.toStdString().c_str()});
                        if(componentType.has_value()){
                            currentComponent = componentType.value();
                            show_components_section(componentType.value(), false);
                        }                        
                    }else if(link.toString().contains("connectors/")){
                        auto name = link.toString().remove("connectors/").split("_").first();
                        auto connectorType = Connector::get_type_from_name(Connector::Name{name.toStdString().c_str()});
                        if(connectorType.has_value()){
                            currentConnector = connectorType.value();
                            show_connectors_section(connectorType.value(), false);
                        }
                    }
                }
            });

            const QString pathDocFile = Paths::documentationDir % QSL("/") % from_view(markdown_file(section));
            QFile docFile(pathDocFile);
            if(!docFile.open(QIODevice::ReadOnly | QIODevice::Text)){
                QString defaultText = QSL("No documentation file found: ") % pathDocFile;
                browser->setText(defaultText);
                sectionsDocContent[section] = defaultText;
            }else {
                QTextStream in(&docFile);
                sectionsDocContent[section] = in.readAll();
                browser->setMarkdown(sectionsDocContent[section]);
            }
        }
    }
    init_components_doc();
    init_connectors_doc();
}

QTextBrowser *DocumentationDialog::generate_text_browser(){
    auto docW = new QTextBrowser();
    docW->setOpenExternalLinks(false);
    docW->setOpenLinks(false);
//    docW->setStyleSheet("background-color: rgb(30,30,30); color: rgb(220,220,200);");
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

    connect(tabComponentsDocW, &QTabWidget::currentChanged, this, [&]{

        const QString componentTypeName = from_view(Component::get_type_name(currentComponent));
        const QString basePath        = Paths::documentationDir % QSL("/") % from_view(markdown_file(currentSection));
        const QString infoPath        = basePath % QSL("/") % componentTypeName % QSL("_info.md");
        const QString connectionsPath = basePath % QSL("/") % componentTypeName % QSL("_connections.md");
        const QString csPath          = basePath % QSL("/") % componentTypeName % QSL("_csharp.md");
        const QString pyPath          = basePath % QSL("/") % componentTypeName % QSL("_python.md");

        int id = tabComponentsDocW->currentIndex();
        if(id == 0){
            currentDocPath = infoPath;
        }else if(id == 1){
            currentDocPath = connectionsPath;
        }else if(id == 2){
            currentDocPath = csPath;
        }else if(id == 3){
            currentDocPath = pyPath;
        }

        genPb->setEnabled(!QFile::exists(currentDocPath));
        openPb->setEnabled(QFile::exists(currentDocPath));
    });

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
            componentsCategoriesStr << from_view(C::get_display_name(category));
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
    tabComponentsDocW->addTab(componentsCsharpScriptingW(), QSL("CSharp scripting"));
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

    componentsCsharpScriptingW.init_widget_as_csharp_editor(QColor(30,30,30), "");
    componentsCsharpScriptingW.w->setReadOnly(true);
    componentsCsharpScriptingW.w->setLineWrapMode(QPlainTextEdit::LineWrapMode::NoWrap);

//    componentsCsharpScriptingW->setOpenExternalLinks(true);
//    componentsCsharpScriptingW->setStyleSheet("background-color: rgb(30,30,30);");
//    componentsCsharpScriptingW->zoomIn(3);
//    componentsCsharpScriptingW->setSearchPaths({path, ".", "./csharp_images"});
//    componentsCsharpScriptingW->setReadOnly(true);
//    componentsPythonScriptingW->setOpenExternalLinks(true);
//    componentsPythonScriptingW->setSearchPaths({Paths::componentsDocDir});
//    componentsPythonScriptingW->setReadOnly(true);
//    componentsCsharpScriptingW.w->setOpenExternalLinks(true);
//    componentsCsharpScriptingW.w->setSearchPaths({path, ".", "./csharp_images"});
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

    connect(tabConnectorsDocW, &QTabWidget::currentChanged, this, [&]{

        const QString connectorTypeName = from_view(Connector::get_name(currentConnector));
        const QString basePath       = Paths::documentationDir % QSL("/") % from_view(markdown_file(currentSection));
        const QString infoPath        = basePath % QSL("/") % connectorTypeName % QSL("_info.md");
        const QString connectionsPath = basePath % QSL("/") % connectorTypeName % QSL("_connections.md");

        int id = tabConnectorsDocW->currentIndex();
        if(id == 0){
            currentDocPath = infoPath;
        }else if(id == 1){
            currentDocPath = connectionsPath;
        }
        genPb->setEnabled(!QFile::exists(currentDocPath));
        openPb->setEnabled(QFile::exists(currentDocPath));
    });


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

    currentDocPath = Paths::documentationDir % QSL("/") % from_view(markdown_file(currentSection));
    genPb->setEnabled(!QFile::exists(currentDocPath));
    openPb->setEnabled(QFile::exists(currentDocPath));

    setWindowTitle(QSL("ExVR Doc: ") % from_view(section_name(currentSection)));
}

void DocumentationDialog::display_components_section(Component::Type type){

    // update section
    documentationsCategoriesW->set_current_row(from_view(section_name(currentSection)));

    // update category row
    componentsCategoriesSectionW->set_current_row(from_view(Component::get_display_name(Component::get_category(type))));

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

    reload_info_file(infoPath);
    reload_connections_file(connectionsPath);
    reload_csharp_markdown_file(csPath);

    //    QFile pyFile(pyPath);
    //    if(!pyFile.open(QIODevice::ReadOnly | QIODevice::Text)){
    //        // componentsPythonScriptingW->setMarkdown(QSL("No documentation file found: ") % pyPath);
    //        componentsPythonScriptingW->setMarkdown(QSL("No implemented yet.")); // [TODO_DOC]
    //    }else {
    //        QTextStream in(&pyFile);
    //        componentsPythonScriptingW->setMarkdown(in.readAll());
    //    }

    int id = tabComponentsDocW->currentIndex();
    if(id == 0){
        currentDocPath = infoPath;
    }else if(id == 1){
        currentDocPath = connectionsPath;
    }else if(id == 2){
        currentDocPath = csPath;
    }else if(id == 3){
        currentDocPath = pyPath;
    }

    genPb->setEnabled(!QFile::exists(currentDocPath));
    openPb->setEnabled(QFile::exists(currentDocPath));
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

    int id = tabConnectorsDocW->currentIndex();
    if(id == 0){
        currentDocPath = infoPath;
    }else if(id == 1){
        currentDocPath = connectionsPath;
    }
    genPb->setEnabled(!QFile::exists(currentDocPath));
    openPb->setEnabled(QFile::exists(currentDocPath));
}

void DocumentationDialog::update_current_category_components_list(){

    componentsSectionW->lwContent->blockSignals(true);
    componentsSectionW->lwContent->clear();
    componentsFullStr.clear();
    for(const auto &type : Component::all_components_types()){

        if(Component::get_category(type) != currentComponentCategory){
            continue;
        }

        componentsFullStr <<  from_view(Component::get_full_name(type));
    }
    componentsSectionW->lwContent->addItems(componentsFullStr);
    componentsSectionW->lwContent->blockSignals(false);
}

void DocumentationDialog::reload_sub_section_markdown_file(DocSection section, bool forceReload){

    if(section != DocSection::ContentComponentsDescription && section != DocSection::ContentConnectorsDescription){
        QTextBrowser *browser = dynamic_cast<QTextBrowser*>(sectionsWidgets[section]);
        if(forceReload){
            const QString pathDocFile = Paths::documentationDir % QSL("/") % from_view(markdown_file(section));
            QFile docFile(pathDocFile);
            if(!docFile.open(QIODevice::ReadOnly | QIODevice::Text)){
                browser->setText(QSL("No documentation file found: ") % pathDocFile);
            }else {
                QTextStream in(&docFile);
                browser->setMarkdown(in.readAll());
            }
        }else{
            browser->setMarkdown(sectionsDocContent[section]);
        }
    }
}

void DocumentationDialog::reload_info_file(const QString &infoFilePath){
    QFile infoFile(infoFilePath);
    if(!infoFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        componentsInfoW->setText(QSL("No documentation file found: ") % infoFilePath);
    }else {
        QTextStream in(&infoFile);
        componentsInfoW->setMarkdown(in.readAll());
    }
}

void DocumentationDialog::reload_connections_file(const QString &connectionsFilePath){
    QFile connectionsFile(connectionsFilePath);
    if(!connectionsFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        componentsConnectionsW->setText(QSL("No documentation file found: ") % connectionsFilePath);
    }else {
        QTextStream in(&connectionsFile);
        componentsConnectionsW->setMarkdown(in.readAll());
    }
}

void DocumentationDialog::reload_csharp_markdown_file(const QString &csFilePath){
    QFile csFile(csFilePath);
    if(!csFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        componentsCsharpScriptingW.w->setPlainText(QSL("No documentation file found: ") % csFilePath);
    }else {
        QTextStream in(&csFile);
        componentsCsharpScriptingW.w->setPlainText(in.readAll().remove("&nbsp;").remove("```csharp").remove("```"));
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
