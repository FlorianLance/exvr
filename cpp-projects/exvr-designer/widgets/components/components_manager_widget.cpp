
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "components_manager_widget.hpp"

// Qt
#include <QMimeData>
#include <QVector2D>
#include <QWidgetAction>

// base
#include "utility/benchmark.hpp"

// local
#include "experiment/global_signals.hpp"

using namespace tool::ex;

ComponentsManagerW::ComponentsManagerW(bool lncoComponents) :
      m_lncoComponents(lncoComponents){

    setAcceptDrops(true);

    setLayout(ui::L::VB());
    layout()->setContentsMargins(1,2,1,0);

    auto w1 = new QWidget();
    w1->setLayout(new QVBoxLayout());

    auto l = ui::L::HB();

    LStretchD s;
    s.spacerStretch = 0;
    s.elementsStretch = {1,20};
    w1->layout()->addWidget(ui::F::gen_frame(l, {ui::W::txt(QSL("Categories filter: ")), &m_cbComponentsToDisplay}, s));
    w1->layout()->setContentsMargins(0,0,0,0);
    auto w2 = new QWidget();
    w2->setLayout(new QVBoxLayout());
    w2->layout()->addWidget(ui::W::txt(QSL("[Right click below to add components]")));
    w2->layout()->addWidget(&m_componentsListW);
    w2->layout()->setContentsMargins(0,0,0,0);
    w1->layout()->addWidget(w2);

//    QScrollArea { background: transparent; }
//    QScrollArea > QWidget > QWidget { background: transparent; }
//    QScrollArea > QWidget > QScrollBar { background: palette(base); }
//    m_componentsListW.setStyleSheet("QScrollArea > QWidget > QWidget{ background: red; }");
    layout()->addWidget(w1);

    m_cbComponentsToDisplay.addItem(QSL("All"));
    for(const auto &category : Component::all_categories_name()){
        m_cbComponentsToDisplay.addItem(from_view(category));
    }

    // connections
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &ComponentsManagerW::customContextMenuRequested, this, &ComponentsManagerW::show_context_menu);
    connect(&m_cbComponentsToDisplay, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&](int index){
        Q_UNUSED(index)
        update_components_to_display();
    });

    initialize_menues();


}

ComponentConfigDialog *ComponentsManagerW::component_dialog(ComponentKey componentKey){

    if(m_dialogsW.count(componentKey.v) != 0){
        return m_dialogsW[componentKey.v].get();
    }

    return nullptr;
}

ComponentW *ComponentsManagerW::component_widget(ComponentKey componentKey){

    for(int ii = 0; ii < m_componentsListW.count(); ++ii){
        auto componentW = qobject_cast<ComponentW*>(m_componentsListW.widget_at(ii));
        if(componentW->key == componentKey){
            return componentW;
        }
    }

    return nullptr;
}

std::pair<int, ComponentW*> ComponentsManagerW::component_widget_with_position(ComponentKey componentKey){

    for(int ii = 0; ii < m_componentsListW.count(); ++ii){
        auto componentW = qobject_cast<ComponentW*>(m_componentsListW.widget_at(ii));
        if(componentW->key == componentKey){
            return {ii,componentW};
        }
    }

    return {0,nullptr};
}

void ComponentsManagerW::update_from_components_manager(ComponentsManager *compM){

    Bench::start("[Update components 0]"sv, false);

        // # remove inused components
        std::map<int,bool> mask;
        for(int ii = m_componentsListW.count()-1; ii >= 0; --ii){

            bool found = false;
            auto componentW = qobject_cast<ComponentW*>(m_componentsListW.widget_at(ii));
            for(const auto &component : compM->components){
                if(component->key() == componentW->key.v){
                    found = true;
                    break;
                }
            }
            mask[componentW->key.v] = found;
            if(!found){
                m_dialogsW.erase(componentW->key.v);
                delete m_componentsListW.remove_at(ii);
            }
        }

    Bench::stop();
    Bench::start("[CM: Generates new components]"sv, false);

        // add new widget/dialog
        for(const auto &component : compM->components){

             if(!mask[component->key()]){

                 Bench::start("[CM: Generate component config dialog]"sv, false);

                     ComponentKey componentKey  = ComponentKey{component->key()};

                     // dialog
                     auto configDialog = std::make_unique<ComponentConfigDialog>(this, component.get());                     
                     connect(configDialog.get(), &ComponentConfigDialog::finished, this, [=](){
                         component_widget(componentKey)->showWindow = false;
                         update_style();
                     });

                 Bench::stop();
                    m_dialogsW[componentKey.v] = std::move(configDialog);

                 Bench::start("[CM: Generate Component widget]"sv, false);
                     auto componentW = new ComponentW(component.get());
                     connect(componentW, &ComponentW::show_component_custom_menu_signal,     this, &ComponentsManagerW::show_howering_component_custom_menu);
                     connect(componentW, &ComponentW::toggle_component_parameters_signal,    this, &ComponentsManagerW::toggle_component_parameters_dialog);
                     connect(componentW, &ComponentW::remove_component_signal,               this, &ComponentsManagerW::remove_component_signal);
                     connect(componentW, &ComponentW::toggle_selection_component_signal,     this, &ComponentsManagerW::toggle_component_selection);
                     connect(componentW, &ComponentW::enter_component_signal,                this, &ComponentsManagerW::update_style);
                     connect(componentW, &ComponentW::leave_component_signal,                this, &ComponentsManagerW::update_style);
                 Bench::stop();
                 Bench::start("[CM: Add component widget]"sv, false);
                    m_componentsListW.add_widget(componentW);
                 Bench::stop();
             }
        }

    Bench::stop();
    Bench::start("[CM: Move components]"sv, false);

        // reorder
        for(int ii = 0; ii < to_signed(compM->components.size()); ++ii){
            for(int jj = 0; jj < to_signed(m_componentsListW.count()); ++jj){
                if(qobject_cast<ComponentW*>(m_componentsListW.widget_at(jj))->key.v == compM->components[to_unsigned(ii)]->key()){
                    if(ii != jj){
                        m_componentsListW.move_from_to(jj,ii);
                    }
                    break;
                }
            }
        }

    Bench::stop();
    Bench::start("[CM: Update components]"sv, false);

    // update components
    for(int ii = 0; ii< m_componentsListW.count(); ++ii){
        auto component  = compM->components[to_unsigned(ii)].get();
        auto componentW = qobject_cast<ComponentW*>(m_componentsListW.widget_at(ii));
        Bench::start("[CM: Update component]"sv, false);
            componentW->update_from_component(component);
        Bench::stop();
        Bench::start("[CM: Update dialog]"sv, false);
            m_dialogsW[component->key()]->update_from_component(component);
        Bench::stop();
    }

    Bench::start("[CM: Update style]"sv, false);
        update_style();
    Bench::stop();

    Bench::start("[CM: Update display]"sv, false);
        update_components_to_display();
    Bench::stop();

    Bench::stop();
}

void ComponentsManagerW::reset(){
    m_dialogsW.clear();
    m_componentsListW.delete_all();
}

void ComponentsManagerW::toggle_component_selection(ComponentKey componentKey){

    auto componentW = component_widget(componentKey);
    if(componentW){
        auto paramsD = component_dialog(componentKey);
        if(paramsD->isVisible()){
            paramsD->show();
            paramsD->activateWindow();
            paramsD->raise();
        }
    }

    update_style();
}

void ComponentsManagerW::initialize_menues(){

    // sort sub menu
    m_sortComponentsSubMenu.setTitle(QSL("Sort components by..."));
    {
        QAction *sortA = new QAction(QSL("category"));
        connect(sortA, &QAction::triggered, this, [=](){
            emit sort_components_by_category_signal();
        });
        m_sortComponentsSubMenu.addAction(sortA);

        sortA = new QAction(QSL("type"));
        connect(sortA, &QAction::triggered, this, [=](){
            emit sort_components_by_type_signal();
        });
        m_sortComponentsSubMenu.addAction(sortA);

        sortA = new QAction(QSL("name"));
        connect(sortA, &QAction::triggered, this, [=](){
            emit sort_components_by_name_signal();
        });
        m_sortComponentsSubMenu.addAction(sortA);
    }

    // fill types categories mapping
    using umComps = std::unordered_map<Component::Category, std_v1<Component::Type>>;
    umComps stableComponentsT;
    umComps experimentalComponentsT;
    umComps legacyComponentsT;
    for(const auto &type : Component::all_components_types()){        

        if(Component::get_restricted(type) == Component::Restricted::LNCO && !m_lncoComponents){
            continue;
        }

        const auto category = Component::get_category(type);

        if(Component::get_state(type) == Component::State::Sta){ // stable
            if(stableComponentsT.count(category) == 0){
                stableComponentsT[category] = {};
            }
            stableComponentsT[category].emplace_back(type);
        }else if(Component::get_state(type) == Component::State::Exp){ // experimental
            if(experimentalComponentsT.count(category) == 0){
                experimentalComponentsT[category] = {};
            }
            experimentalComponentsT[category].emplace_back(type);
        }else if(Component::get_state(type) == Component::State::Leg){ // legacy
            if(legacyComponentsT.count(category) == 0){
                legacyComponentsT[category] = {};
            }
            legacyComponentsT[category].emplace_back(type);
        }
    }

    auto createMenu = [&](const QString &title, umComps &componentsT, QMenu &menu){
        // new sub menu
        menu.clear();
        menu.setTitle(title);
        for(const auto &category : Component::all_categories()){

            if(category == Component::C::SizeEnum){
                continue;
            }

            if(Component::components_nb_per_category(category) == 0){
                continue;
            }

            if(componentsT.count(category) == 0){
                continue;
            }

            QMenu *typesMenu = new QMenu();
            typesMenu->setTitle(from_view(Component::to_string(category)));

            for(const auto &componentT : componentsT[category]){

                QAction *action = new QAction();
                action->setIcon(QIcon(from_view(Component::get_icon_path(componentT))));
                action->setText(from_view(Component::get_full_name(componentT)));
                typesMenu->addAction(action);

                connect(action, &QWidgetAction::triggered, this, [=](){
                    add_new_component(componentT, m_componentsListW.count());
                });
            }
            menu.addMenu(typesMenu);
        }
    };

    // new sub menues
    createMenu(QSL("Create component"), stableComponentsT, m_createNewComponentsSubMenu);
    createMenu(QSL("Create component (experimental)"), experimentalComponentsT, m_createNewExperimentalComponentsSubMenu);
    createMenu(QSL("Create component (legacy)"), legacyComponentsT, m_createNewLegacyComponentsSubMenu);
}

void ComponentsManagerW::toggle_component_parameters_dialog(ComponentKey componentKey){


    auto paramsD = component_dialog(componentKey);
    if(paramsD){
        if(!paramsD->isVisible()){
            paramsD->show();
            component_widget(componentKey)->showWindow = true;
        }else{
            paramsD->hide();
            component_widget(componentKey)->showWindow = false;
        }
    }

    update_style();
}

void ComponentsManagerW::update_style(){

    for(int ii = 0; ii < m_componentsListW.count(); ++ii){
        auto componentW = qobject_cast<ComponentW*>(m_componentsListW.widget_at(ii));
        componentW->update_style();
    }
}

void ComponentsManagerW::update_components_to_display(){

    auto currTxt = m_cbComponentsToDisplay.currentText();
    if(currTxt == "All"){                
        for(int ii = 0; ii < m_componentsListW.count(); ++ii){
            qobject_cast<ComponentW*>(m_componentsListW.widget_at(ii))->show();
        }
    }else{

        if(auto category = Component::get_category(currTxt.toStdString()); category.has_value()){

            for(int ii = 0; ii < m_componentsListW.count(); ++ii){
                auto componentW = qobject_cast<ComponentW*>(m_componentsListW.widget_at(ii));
                if(category.value() == componentW->category){
                    componentW->show();
                }else{
                    componentW->hide();
                }

            }
        }
    }
}

void ComponentsManagerW::show_howering_component_custom_menu(QPoint pos, ComponentKey componentKey){

    QMenu contextMenu(tr("Context menu"), this);
    contextMenu.addMenu(&m_createNewComponentsSubMenu);
    contextMenu.addMenu(&m_createNewExperimentalComponentsSubMenu);
    contextMenu.addMenu(&m_createNewLegacyComponentsSubMenu);
    contextMenu.addSeparator();

    QMenu addComponentSubMenu(tr("Add to..."));
    {
        QAction *addA = new QAction("current condition");
        connect(addA, &QAction::triggered, this, [=](){
            emit GSignals::get()->insert_action_signal(componentKey);
        });
        addComponentSubMenu.addAction(addA);

        addA = new QAction("all conditions of the selected routine");
        connect(addA, &QAction::triggered, this, [=](){
            emit GSignals::get()->insert_action_to_all_selected_routine_conditions_signal(componentKey);
        });
        addComponentSubMenu.addAction(addA);

        addA = new QAction("all conditions of every routine");
        connect(addA, &QAction::triggered, this, [=](){
            emit GSignals::get()->insert_action_to_all_routines_conditions_signal(componentKey);
        });
        addComponentSubMenu.addAction(addA);
    }
    contextMenu.addMenu(&addComponentSubMenu);

    QMenu removeComponentSubMenu(tr("Remove from..."));
    {
        QAction *removeA = new QAction("all conditions of the selected routine ");
        connect(removeA, &QAction::triggered, this, [=](){
            emit GSignals::get()->remove_action_from_all_selected_routine_conditions_signal(componentKey);
        });
        removeComponentSubMenu.addAction(removeA);

        removeA = new QAction("all conditions of every routine");
        connect(removeA, &QAction::triggered, this, [=](){
            emit GSignals::get()->remove_action_from_all_routines_conditions_signal(componentKey);
        });
        removeComponentSubMenu.addAction(removeA);
    }
    contextMenu.addMenu(&removeComponentSubMenu);

    contextMenu.addSeparator();

    QAction *editA = new QAction("Edit parameters");
    connect(editA, &QAction::triggered, this, [=](){
        auto paramsD = component_dialog(componentKey);
        if(paramsD){
            paramsD->show();
            paramsD->raise();
            component_widget(componentKey)->showWindow = true;
            update_style();
        }
    });
    contextMenu.addAction(editA);

    QAction *duplicateA = new QAction(QSL("Duplicate"));
    connect(duplicateA, &QAction::triggered, this, [=](){
        emit duplicate_component_signal(componentKey);
    });
    contextMenu.addAction(duplicateA);

    QAction *removeA = new QAction(QSL("Delete"));
    connect(removeA, &QAction::triggered, this, [=](){
        emit remove_component_signal(componentKey);
    });
    contextMenu.addAction(removeA);
    contextMenu.addSeparator();


    contextMenu.addMenu(&m_sortComponentsSubMenu);

    QAction *identifyA = new QAction(QSL("Show informations"));
    connect(identifyA, &QAction::triggered, this, [=](){
        emit show_component_informations_signal(componentKey);
    });
    contextMenu.addAction(identifyA);


    contextMenu.addSeparator();
    QAction *closeAllA = new QAction(QSL("Close all parameters windows"));
    connect(closeAllA, &QAction::triggered, this, [=](){
        for(auto &dialogW : m_dialogsW){
            dialogW.second->close();
            component_widget(ComponentKey{dialogW.first})->showWindow = false;
        }
    });
    contextMenu.addAction(closeAllA);
    contextMenu.exec(pos);
}

void ComponentsManagerW::show_context_menu(const QPoint &pos) {

    // update mouse position
    m_lastPos = pos;

    QMenu contextMenu(tr("Context menu"), this);
    contextMenu.addMenu(&m_createNewComponentsSubMenu);
    contextMenu.addMenu(&m_createNewExperimentalComponentsSubMenu);
    contextMenu.addMenu(&m_createNewLegacyComponentsSubMenu);
    contextMenu.addSeparator();

    contextMenu.addMenu(&m_sortComponentsSubMenu);
    contextMenu.addSeparator();

    QAction *closeAllA = new QAction(QSL("Close all parameters windows"));
    connect(closeAllA, &QAction::triggered, this, [=](){
        for(auto &dialogW : m_dialogsW){
            dialogW.second->close();
            component_widget(ComponentKey{dialogW.first})->showWindow = false;
        }
    });
    contextMenu.addAction(closeAllA);

    contextMenu.exec(mapToGlobal(pos));
}

void ComponentsManagerW::add_new_component(tool::ex::Component::Type type, int id){
    // compute position
    // TODO: ...
    // ...

    if(const bool unicity = tool::ex::Component::get_unicity(type); unicity == true){
        if(tool::ex::Component::count(type) != 0){
            QtLogger::warning(QSL("Only one component for this type."));
            return;
        }
    }

    emit add_component_signal(type, RowId{id});
}

void ComponentsManagerW::close_all_configs_dialogs(){
    for(auto &dialogW : m_dialogsW){
        dialogW.second->close();
    }
}

void ComponentsManagerW::dragEnterEvent(QDragEnterEvent *event){
    if(m_cbComponentsToDisplay.currentText() == QSL("All")){
        event->acceptProposedAction();
    }
}

void ComponentsManagerW::dropEvent(QDropEvent *event){

    const QMimeData *data = event->mimeData();
    if(data->text().length() == 0 || m_componentsListW.count() == 1){
        return;
    }
    if(data->text()[0] != 'e'){
        return;
    }

    ComponentKey dropComponentKey = ComponentKey{data->text().split("_")[1].toInt()};
    auto [dropComponentPosition, dropComponentW] = component_widget_with_position(dropComponentKey);

    bool dropPositionOnComponent = false;
    const auto cursorPos = QCursor::pos();
    for(int ii = 0; ii < m_componentsListW.count(); ++ii){

        const auto &c = m_componentsListW.widget_at(ii);
        const auto cursorLocalPos = c->mapFromGlobal(cursorPos);
        if(c->rect().contains(cursorLocalPos)){

            if(ii == dropComponentPosition){
                return;
            }

            dropPositionOnComponent = true;
            bool belowId = dropComponentPosition < to_signed(ii);
            if(cursorLocalPos.y() < c->rect().center().y()){
                if(belowId){
                    emit update_component_position_signal(dropComponentKey, RowId{ii-1});
                    return;
                }else{
                    emit update_component_position_signal(dropComponentKey, RowId{ii});
                    return;
                }
            }else{
                if(belowId){
                    emit update_component_position_signal(dropComponentKey, RowId{ii});
                    return;
                }else{
                    emit update_component_position_signal(dropComponentKey, RowId{ii+1});
                    return;
                }
            }
        }
    }

    auto firstW = m_componentsListW.widget_at(0);
    const auto firstPos = firstW->mapToGlobal(firstW->rect().topLeft());
    if(cursorPos.y() < firstPos.y()){
        emit update_component_position_signal(dropComponentKey, RowId{0});
    }else{
        emit update_component_position_signal(dropComponentKey, RowId{m_componentsListW.count()-1});
    }
}

void ComponentsManagerW::update_component_dialog_with_info(ComponentKey componentKey, ConfigKey configKey, QStringView id, QStringView value){

    for(auto &dialogW : m_dialogsW){        
        if(dialogW.first == componentKey.v){
            dialogW.second->update_with_info(configKey, id, value);
            break;
        }
    }
}

#include "moc_components_manager_widget.cpp"
