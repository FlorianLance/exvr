
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "component_config_dialog.hpp"

// Qt
#include <QIcon>
#include <QImage>
#include <QToolButton>
#include <QLineEdit>
#include <QMessageBox>

// base
#include "utility/types_utility.hpp"
#include "utility/benchmark.hpp"

// local
#include "experiment/global_signals.hpp"



// debug
#include <QDebug>


using namespace tool::ex;

ComponentConfigDialog::ComponentConfigDialog(QWidget *parent, Component *component) :
      componentKey({component->key()}), componentType(component->type){

    m_parent = parent;

    // set base ui of the dialog
    m_ui.setupUi(this);
    m_ui.leName->setText(component->name());
    m_ui.tabConfigs->setMovable(true);
    m_ui.pbReset->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_ui.pbPin->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_ui.pbHelp->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    setModal(false);
    defaultFlags = windowFlags() & ~Qt::WindowContextHelpButtonHint;
    setWindowFlags(defaultFlags); 
    setWindowTitle(QSL("[") % from_view(Component::get_full_name(component->type)) % QSL("] component settings"));
    setWindowIcon(QIcon(from_view(Component::get_icon_path(component->type))));

    set_connections();

    Bench::start("[ComponentsConfigDialog generate init config w]"sv, false);
        // add init config widget
        m_initConfigW = new ConfigW(component->initConfig.get(), component, true, component->initConfig->args);
        m_ui.vlInitConfig->addWidget(m_initConfigW);
    Bench::stop();


    Bench::start("[ComponentsConfigDialog init 5]"sv, false);

    // enable configurations
    auto configOpt = Component::get_config_opt(component->type);
    m_ui.twAllConfigs->setEnabled(configOpt !=  Component::ConfigO::None);
    m_ui.twAllConfigs->setTabEnabled(0,configOpt == Component::ConfigO::Initalization || configOpt ==  Component::ConfigO::Both);
    m_ui.twAllConfigs->setTabEnabled(1,configOpt == Component::ConfigO::Condition      || configOpt ==  Component::ConfigO::Both);

    if(m_ui.twAllConfigs->isTabEnabled(0)){
        m_ui.twAllConfigs->setCurrentIndex(0);
    }

    Bench::stop();
    Bench::start("[ComponentsConfigDialog init 6]"sv, false);

    update_from_component(component);

    Bench::stop();
}

void ComponentConfigDialog::set_connections(){

    // change component name
    connect(m_ui.leName, &QLineEdit::textChanged, this, [=](QString text){
        emit GSignals::get()->component_name_changed_signal(componentKey, text);
    });

    // remove selected config
    connect(m_ui.pbRemoveConfig, &QPushButton::clicked, this, [=]{
        auto id = m_ui.tabConfigs->currentIndex();
        if(id >= 0 && id < m_ui.tabConfigs->count()){
            m_ui.tabConfigs->removeTab(id);
            emit GSignals::get()->remove_config_signal(componentKey, RowId{id});
        }
    });

    // add a new config
    connect(m_ui.pbInsertNewConfig, &QPushButton::clicked, this, [&]{

        // create a dialog for choosing the configuration name
        QDialog configNameDialog;
        configNameDialog.setWindowTitle(QSL("Add new config"));
        configNameDialog.setModal(true);
        configNameDialog.setLayout(new QHBoxLayout());
        configNameDialog.layout()->addWidget(new QLabel(QSL("Name: ")));

        QLineEdit *le = new QLineEdit(QSL("Config ") % QString::number(m_ui.tabConfigs->count()));
        configNameDialog.layout()->addWidget(le);
        QPushButton *pbV = new QPushButton(QSL("Ok"));
        QPushButton *pbC = new QPushButton(QSL("Cancel"));
        connect(pbV, &QPushButton::clicked, this, [&]{
            configNameDialog.done(1);
        });
        connect(pbC, &QPushButton::clicked, this, [&]{
            configNameDialog.done(0);
        });
        configNameDialog.layout()->addWidget(pbV);
        configNameDialog.layout()->addWidget(pbC);
        le->setFocus();

        int res = configNameDialog.exec();
        if(res == 1){ // if config validated
            int id = m_ui.tabConfigs->currentIndex();
            if(id == -1){
                id = 0;
            }
            emit GSignals::get()->insert_config_signal(componentKey, RowId{id}, le->text());
        }
    });

    connect(m_ui.pbDuplicate, &QPushButton::clicked, this, [&]{

        // create a dialog for choosing the configuration name
        QDialog configNameDialog;
        configNameDialog.setWindowTitle(QSL("Duplicate selected config"));
        configNameDialog.setModal(true);
        configNameDialog.setLayout(new QHBoxLayout());
        configNameDialog.layout()->addWidget(new QLabel(QSL("Name: ")));

        QLineEdit *le = new QLineEdit(m_ui.tabConfigs->tabText(m_ui.tabConfigs->currentIndex()) % QSL("(copy)"));
        configNameDialog.layout()->addWidget(le);
        QPushButton *pbV = new QPushButton(QSL("Ok"));
        QPushButton *pbC = new QPushButton(QSL("Cancel"));
        connect(pbV, &QPushButton::clicked, this, [&]{
            configNameDialog.done(1);
        });
        connect(pbC, &QPushButton::clicked, this, [&]{
            configNameDialog.done(0);
        });
        configNameDialog.layout()->addWidget(pbV);
        configNameDialog.layout()->addWidget(pbC);
        le->setFocus();

        int res = configNameDialog.exec();
        if(res == 1){ // if config validated
            int id = m_ui.tabConfigs->currentIndex();
            if(id == -1){
                id = 0;
            }
            emit GSignals::get()->copy_config_signal(componentKey, RowId{id}, le->text());
        }
    });

    connect(m_ui.pbRenameConfig, &QPushButton::clicked, this, [&]{

        // create a dialog for choosing the configuration name
        QDialog configNameDialog;
        configNameDialog.setWindowTitle(QSL("Rename config"));
        configNameDialog.setModal(true);
        configNameDialog.setLayout(new QHBoxLayout());
        configNameDialog.layout()->addWidget(new QLabel(QSL("Name: ")));
        QLineEdit *le = new QLineEdit(m_ui.tabConfigs->tabText(m_ui.tabConfigs->currentIndex()));
        configNameDialog.layout()->addWidget(le);
        QPushButton *pbV = new QPushButton(QSL("Ok"));
        QPushButton *pbC = new QPushButton(QSL("Cancel"));
        connect(pbV, &QPushButton::clicked, this, [&]{
            configNameDialog.done(1);
        });
        connect(pbC, &QPushButton::clicked, this, [&]{
            configNameDialog.done(0);
        });
        configNameDialog.layout()->addWidget(pbV);
        configNameDialog.layout()->addWidget(pbC);
        le->setFocus();

        int res = configNameDialog.exec();
        if(res == 1){ // if config validated
            int id = m_ui.tabConfigs->currentIndex();
            if(id == -1){
                id = 0;
            }
            emit GSignals::get()->rename_config_signal(componentKey, RowId{id}, le->text());
        }
    });

    connect(m_ui.pbHelp, &QPushButton::clicked, this, [=]{
        emit GSignals::get()->display_component_help_window_signal(componentType);
    });

    connect(m_ui.pbPin, &QPushButton::clicked, this, [=] {
        if(!pinned){
            setParent(m_parent);
            setWindowFlags(Qt::Dialog);
            setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
            m_ui.pbPin->setIcon(QIcon(":/icons/Unpin"));
        }else{
            setParent(nullptr);
            setWindowFlags(defaultFlags);
            m_ui.pbPin->setIcon(QIcon(":/icons/Pin"));
        }
        pinned = !pinned;
        show();
    });

    connect(m_ui.pbReset, &QPushButton::clicked, this, [&]{

        const bool resetInitConfig  = m_ui.twAllConfigs->currentIndex() == 0;
        const int idCurrentConfig   = m_ui.tabConfigs->currentIndex();
        ConfigW *configW = nullptr;
        if(resetInitConfig){
            configW = get_init_config_widget();
        }else{
            configW = get_config_widget(idCurrentConfig);
        }

        QDialog resetConfigDialog;
        resetConfigDialog.setWindowTitle(QSL("Reset config"));
        resetConfigDialog.setModal(true);
        resetConfigDialog.setLayout(new QHBoxLayout());
        resetConfigDialog.layout()->addWidget(new QLabel(QSL("You are going to reset ") %
                                                         QString(resetInitConfig ? QSL("init") : QSL("current selected")) % QSL(" config values.")));

        QPushButton *pbV = new QPushButton(QSL("Ok"));
        QPushButton *pbC = new QPushButton(QSL("Cancel"));
        connect(pbV, &QPushButton::clicked, this, [&]{
            resetConfigDialog.done(1);
        });
        connect(pbC, &QPushButton::clicked, this, [&]{
            resetConfigDialog.done(0);
        });
        resetConfigDialog.layout()->addWidget(pbV);
        resetConfigDialog.layout()->addWidget(pbC);

        if(resetConfigDialog.exec() == 1){ // if validated
            configW->reset_args();
        }
    });

    // move config
    connect(m_ui.tabConfigs->tabBar(), &QTabBar::tabMoved, this, [&](int from, int to){
        emit GSignals::get()->move_config_signal(componentKey, RowId{from}, RowId{to});
    });
}


void ComponentConfigDialog::update_from_component(Component *component){

    Bench::start("[ComponentsConfigDialog 0]"sv);

    get_init_config_widget()->update_from_config(component->initConfig.get());

    Bench::stop();
    Bench::start("[ComponentsConfigDialog 1]"sv);

    // remove inused configs
    for(int ii = m_ui.tabConfigs->count()-1; ii >= 0; --ii){

        auto configW = get_config_widget(ii);
        bool found = false;
        for(const auto &config : component->configs){
            if(config->key() == configW->configKey.v){
                found = true;
                configW->update_from_config(config.get());
                break;
            }
        }
        if(!found){
            m_ui.tabConfigs->removeTab(ii);
        }
    }

    Bench::stop();
    Bench::start("[ComponentsConfigDialog 2]"sv);

    // reorder
    for(int ii = 0; ii < to_signed(component->configs.size()); ++ii){
        for(int jj = 0; jj < m_ui.tabConfigs->count(); ++jj){

            auto cw = get_config_widget(jj);
            if(cw->configKey.v == component->configs[to_unsigned(ii)]->key()){
                if(ii != jj){
                    m_ui.tabConfigs->tabBar()->moveTab(jj,ii);
                }
                break;
            }
        }
    }

    Bench::stop();


    // add new configs
    for(size_t ii = 0; ii < component->configs.size(); ++ii){
        bool found = false;
        for(int jj = 0; jj < m_ui.tabConfigs->count(); ++jj){
            if(component->configs[ii]->key() == get_config_widget(jj)->configKey.v){
                found = true;
                break;
            }
        }

        if(!found){ // insert tab for the new config
            Config *config = component->configs[ii].get();
            m_ui.tabConfigs->insertTab(to_signed(ii), new ConfigW(config, component, false, config->args), config->name);
        }
    }

    // update tab textes with configs name
    for(size_t ii = 0; ii < component->configs.size(); ++ii){
        m_ui.tabConfigs->setTabText(to_signed(ii), component->configs[ii]->name);
    }
    m_ui.pbRemoveConfig->setEnabled(m_ui.tabConfigs->count() > 1);

}

void ComponentConfigDialog::update_with_info(ConfigKey configKey, QStringView id, QStringView value){

    auto initConfigW = get_init_config_widget();
    if(initConfigW->configKey.v == configKey.v){
        initConfigW->update_with_info(id, value);
    }else{        
        for(int ii = 0; ii < m_ui.tabConfigs->count(); ++ii){
            auto configW = get_config_widget(ii);
            if(configW->configKey.v == configKey.v){
                configW->update_with_info(id, value);
                break;
            }
        }
    }    
}



#include "moc_component_config_dialog.cpp"
