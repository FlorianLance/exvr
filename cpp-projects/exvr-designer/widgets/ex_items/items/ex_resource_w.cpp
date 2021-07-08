
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_resource_w.hpp"

// Qt
#include <QStringBuilder>

// base
#include "utility/benchmark.hpp"

// local
#include "resources_manager.hpp"
#include "global_signals.hpp"

using namespace tool::ex;




ExResourceW::ExResourceW() : ExItemW<QFrame>(UiType::Resource){

    w->setFrameShadow(QFrame::Raised);
    w->setFrameShape(QFrame::Shape::NoFrame);

    QHBoxLayout *l = new QHBoxLayout();
    w->setLayout(l);
    l->addWidget(m_icon = new QPushButton());
    l->addWidget(m_title = new QLabel());
    l->addWidget(m_resourcesAlias = new QComboBox());
    l->addWidget(m_resources = new QPushButton());
    l->setStretch(0,1);
    l->setStretch(1,10);
    l->setStretch(2,50);
    l->setStretch(3,1);
    l->setContentsMargins(2,2,2,2);
    l->setSpacing(5);
}

ExResourceW *ExResourceW::init_widget(Resource::Type resourceType, QString title, bool enabled){

    w->setEnabled(enabled);
    m_resourceType = resourceType;
    m_title->setText(title);

    m_icon->setText("");
    m_icon->setIcon(QIcon(from_view(Resource::get_icon_path(m_resourceType))));
    m_icon->setIconSize(QSize(30,30));
    m_icon->setMinimumWidth(35);

    m_resources->setText("");
    m_resources->setIcon(QIcon(":/icons/Resources"));
    m_resources->setIconSize(QSize(20,20));
    m_resources->setMinimumWidth(25);
    m_resources->setMinimumHeight(25);
    m_resources->setToolTip("Open resources manager");

    return this;
}

void ExResourceW::init_connection(const QString &nameParam){

    connect(m_resources, &QPushButton::clicked, this, [&]{
        emit GSignals::get()->show_resources_manager_dialog_signal(m_resourceType);
    });
    connect(m_resourcesAlias, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{

        m_currentKey = -1;
        if(m_resourcesAlias->currentIndex() > 0){

            const size_t id = to_unsigned(m_resourcesAlias->currentIndex()-1);
            ResourcesManager *resourcesM = ResourcesManager::get();

            if(auto resources = resourcesM->get_resources(m_resourceType); id < resources.size()){
                m_currentKey =  resources[id]->key();
            }
        }
        emit ui_change_signal(nameParam);
    });
}


void ExResourceW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    if(generatorName.length() > 0 && arg.generator.info.has_value()){
        if(auto type = Resource::get_type(arg.generator.info.value().toStdString()); type.has_value()){
            m_resourceType = type.value();
            m_icon->setIcon(QIcon(from_view(Resource::get_icon_path(m_resourceType))));
            m_title->setText(arg.generator.info.value());
        }
    }

    auto split = arg.split_value();
    m_currentKey = split[1].toInt();
    update_from_resources();

    w->blockSignals(false);
}

Arg ExResourceW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    QString alias=  "";
    if(auto resource = ResourcesManager::get()->get_resource(m_resourceType, m_currentKey, false); resource != nullptr){
        alias = resource->alias;
    }
    arg.init_from({alias, std::to_string(m_currentKey).c_str()}, "%%%");

    if(generatorName.length() > 0){
        arg.generator.info = std::string(Resource::get_name(m_resourceType)).c_str();
    }

    return arg;
}

void ExResourceW::update_from_resources(){

    blockSignals(true);

    Bench::start("ExResourceW::update_from_resources_1"sv);

    ResourcesManager *resourcesM = ResourcesManager::get();
    QString currentText = "";
    if(m_currentKey != -1){
        // check if component still available
        if(auto resource = resourcesM->get_resource(m_resourceType, m_currentKey, false); resource != nullptr){
            currentText = resource->display_name();
        }
    }

    Bench::stop();
    Bench::start("ExResourceW::update_from_resources_2"sv);

    auto resources = resourcesM->get_resources(m_resourceType);

    bool rebuild = false;
    if(resourcesId.size() != resources.size()){
        rebuild = true;
    }else{
        for(size_t ii = 0; ii < resources.size(); ++ii){
            if(resources[ii]->key() != resourcesId[ii]){
                rebuild = true;
                break;
            }
        }
    }


    Bench::stop();
    Bench::start("ExResourceW::update_from_resources_3"sv);

    if(rebuild){

        m_resourcesAlias->blockSignals(true);

        m_resourcesAlias->clear();

        resourcesId.clear();
        resources.reserve(resources.size());

        QStringList names;
        names.reserve(to_signed(resources.size()+1));
        names << "";
        for(const auto &resource : resources){
            names << resource->display_name();
            resourcesId.emplace_back(resource->key());
        }       
        m_resourcesAlias->addItems(names);
        m_resourcesAlias->blockSignals(false);
    }

    Bench::stop();
    Bench::start("ExResourceW::update_from_resources_4"sv);

    if(m_resourcesAlias->currentText() != currentText){
        m_resourcesAlias->setCurrentText(currentText);
    }

    Bench::stop();

    blockSignals(false);
}



#include "moc_ex_resource_w.cpp"
