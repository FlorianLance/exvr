

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_components_list_w.hpp"

// local
#include "data/components_manager.hpp"


using namespace tool::ex;

ExComponentsListW::ExComponentsListW(QString name) : ExItemW<QFrame>(UiType::ComponentsList, name){

    w->setFrameShadow(QFrame::Raised);
    w->setFrameShape(QFrame::Shape::NoFrame);

    auto f1 = ui::F::gen_frame(ui::L::HB(), {
        {m_icon     = new QPushButton(),1},
        {m_title    = new QLabel(), 1},
        {m_componentNames = new QComboBox(), 50},
        {m_add      = new QPushButton(QSL("Add")), 1},
        {m_remove   = new QPushButton(QSL("Rem")), 1}},
        0,
        LMarginsD{0,0,0,0,2}
    );

    auto l = ui::L::VB();
    l->addWidget(f1);
    l->addWidget(m_list = new ui::ListWidget());
    l->setStretch(0,1);
    l->setStretch(1,50);
    w->setLayout(l);

    m_list->set_margins(2,2,2,2,1);
    m_list->set_widget_selection(true);

    connect(m_add, &QPushButton::clicked, this, [&]{

        if(m_componentNames->count() == 0){
            return;
        }

        const auto currTxt = m_componentNames->currentText();
        if(auto component = ComponentsManager::get()->get_component(m_componentType.value(), currTxt); component != nullptr){
            m_componentsKeys.emplace_back(component->key());
            m_list->add_widget(ui::W::txt(component->name()));
            update_from_components();
            trigger_ui_change();
        }

    });
    connect(m_remove, &QPushButton::clicked, this, [&]{
        const int id = m_list->current_selected_widget_id();
        if(id != -1){
            m_list->delete_at(id);
            m_componentsKeys.erase(std::begin(m_componentsKeys) + id);
            update_from_components();
            trigger_ui_change();
        }
    });
}

ExComponentsListW *ExComponentsListW::init_widget(Component::Type componentType, QString title, bool enabled){

    w->setEnabled(enabled);
    m_componentType = {componentType};
    m_title->setText(title);

    m_icon->setText("");
    m_icon->setIcon(QIcon(from_view(Component::get_icon_path(m_componentType.value()))));
    m_icon->setIconSize(QSize(30,30));
    m_icon->setMinimumWidth(35);

    return this;
}


void ExComponentsListW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(arg.generator.has_value()){
        if(auto type = Component::get_type_from_name(arg.generator->info->toStdString()); type.has_value()){
            m_componentType = {type.value()};
            m_icon->setIcon(QIcon(from_view(Component::get_icon_path(m_componentType.value()))));
            m_title->setText(arg.generator->info.value());
        }
    }

    m_componentsKeys.clear();
    m_list->delete_all();

    if(arg.value().size() > 0){

        auto split = arg.split_value();
        for(const auto &keyStr : split){

            int key = keyStr.toInt();
            if(auto component = ComponentsManager::get()->get_component(ComponentKey{key}); component != nullptr){
                m_componentsKeys.emplace_back(keyStr.toInt());
                m_list->add_widget(ui::W::txt(component->name()));
            }
        }
    }

    update_from_components();

    w->blockSignals(false);
}

Arg ExComponentsListW::convert_to_arg() const{

    Arg arg = ExBaseW::convert_to_arg();

    QStringList keysStr;
    keysStr.reserve(static_cast<int>(m_componentsKeys.size()));
    for(const auto &key : m_componentsKeys){
        keysStr << QString::number(key);
    }

    arg.init_from(keysStr, " ");
    if(hasGenerator){
        if(m_componentType.has_value()){
            arg.generator->info = from_view(Component::get_full_name(m_componentType.value()));
        }
    }

    return arg;
}

void ExComponentsListW::update_from_components(){

    m_componentNames->blockSignals(true);

    ComponentsManager *componentsM = ComponentsManager::get();

    QString currentText = m_componentNames->currentText();
    m_componentNames->clear();

    QStringList names;    
    if(auto components = componentsM->get_components(m_componentType.value()); components.size() > 0){

        // remove component keys not existing anymore
        std_v1<int> elemsToRemove;
        for(size_t ii = 0; ii < m_componentsKeys.size(); ++ii){

            bool found = false;
            for(const auto &component : components){
                if(component->key() == m_componentsKeys[ii]){
                    found = true;
                    break;
                }
            }

            if(!found){
                elemsToRemove.push_back(ii);
            }
        }
        if(elemsToRemove.size() > 0){
            for(int ii = static_cast<int>(elemsToRemove.size()) -1; ii >= 0; --ii){
                m_list->delete_at(elemsToRemove[ii]);
                m_componentsKeys.erase(std::begin(m_componentsKeys) + elemsToRemove[ii]);
            }
        }

        // check for new components
        for(const auto &component : components){

            bool found = false;
            for(size_t ii = 0; ii < m_componentsKeys.size(); ++ii){

                if(component->key() == m_componentsKeys[ii]){
                    dynamic_cast<QLabel*>(m_list->widget_at(to_signed(ii)))->setText(component->name());
                    found = true;
                    break;
                }
            }

            if(!found){
                names << component->name();
            }
        }
    }

    m_componentNames->addItems(names);
    m_componentNames->setCurrentText(currentText);

    m_componentNames->blockSignals(false);
}

#include "moc_ex_components_list_w.cpp"

