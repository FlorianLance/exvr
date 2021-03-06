

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_component_w.hpp"

// local
#include "data/components_manager.hpp"

using namespace tool::ex;

ExComponentW::ExComponentW(QString name) : ExItemW<QFrame>(UiType::Component, name){

    w->setFrameShadow(QFrame::Raised);
    w->setFrameShape(QFrame::Shape::NoFrame);

    QHBoxLayout *l = new QHBoxLayout();
    w->setLayout(l);
    l->addWidget(m_icon = new QPushButton());
    l->addWidget(m_title = new QLabel());
    l->addWidget(m_componentNames = new QComboBox());
    l->setStretch(0,1);
    l->setStretch(1,1);
    l->setStretch(2,50);

    connect(m_componentNames, QOverload<int>::of(&QComboBox::currentIndexChanged), this,[&](int index){

        m_currentKey = -1;
        if(index > 0){
            const size_t id = to_unsigned(index-1);
            ComponentsManager *componentsM = ComponentsManager::get();
            if(auto components = componentsM->get_components(m_componentType.value()); id < components.size()){
                m_currentKey =  components[id]->key();
            }
        }
        trigger_ui_change();
    });
}

ExComponentW *ExComponentW::init_widget(tool::ex::Component::Type componentType, QString title, bool enabled){

    w->setEnabled(enabled);
    m_componentType = std::make_optional(componentType);
    m_title->setText(title);

    m_icon->setText("");
    m_icon->setIcon(QIcon(from_view(Component::get_icon_path(m_componentType.value()))));
    m_icon->setIconSize(QSize(30,30));
    m_icon->setMinimumWidth(35);

    return this;
}


void ExComponentW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(arg.generator.has_value()){
        if(auto type = Component::get_type_from_name(arg.generator->info.value().toStdString()); type.has_value()){
            m_componentType = type;
            m_icon->setIcon(QIcon(from_view(Component::get_icon_path(m_componentType.value()))));
            m_title->setText(arg.generator->info.value());
        }
    }

    if(auto split = arg.split_value(); split.size() > 1){
        m_currentKey = split[1].toInt();
    }
    update_from_components();

    w->blockSignals(false);
}

Arg ExComponentW::convert_to_arg() const{

    Arg arg = ExBaseW::convert_to_arg();
    arg.init_from({m_componentNames->currentText(),QString::number(m_currentKey)}, "%%%");

    if(hasGenerator){
        if(m_componentType.has_value()){
            arg.generator->info = from_view(Component::get_full_name(m_componentType.value()));
        }
    }

    return arg;
}

void ExComponentW::update_from_components(){

    m_componentNames->blockSignals(true);

    // retrieve components names list
    ComponentsManager *componentsM = ComponentsManager::get();
    auto components = componentsM->get_components(m_componentType.value());

    bool rebuildList = false;
    if(m_componentNames->count() != static_cast<int>((components.size()+1))){
        rebuildList = true;
    }

    if(!rebuildList){
        for(size_t ii = 0; ii < components.size(); ++ii){
            if(m_componentNames->itemText(static_cast<int>(ii)+1) != components[ii]->name()){
                rebuildList = true;
                break;
            }
        }
    }

    if(rebuildList){

        // clear combobox
        m_componentNames->clear();
        m_componentNames->addItem("");

        QStringList componentsNamesList;
        for(const auto component : components){
            componentsNamesList << component->name();
        }

        if(componentsNamesList.size() > 0){
            m_componentNames->addItems(componentsNamesList);
        }
    }

    // check current index
    int id = 1;
    int newId = -1;
    for(const auto &component : components){
        if(component->key() == m_currentKey){
            newId = id;
        }
        ++id;
    }

    if(newId != -1){
        m_componentNames->setCurrentIndex(newId);
    }else{
        m_currentKey = -1;
        if(m_componentNames->count() > 0){
            m_componentNames->setCurrentIndex(0);
        }
    }

    m_componentNames->blockSignals(false);
}

QString ExComponentW::current_component_name_displayed() const{
    return m_componentNames->currentText();
}
