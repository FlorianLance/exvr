
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "config_pw.hpp"

#include "resources_manager.hpp"
#include "ex_resource_w.hpp"
#include "ex_component_w.hpp"

using namespace tool::ex;

ConfigParametersW::ConfigParametersW() {

    // main widget
//    setContentsMargins(0,0,0,0);
//    setLayout(m_layout = new QVBoxLayout());

    setContentsMargins(0,0,0,0);
    setLayout(m_layout = new QVBoxLayout());
    QScrollArea *area = new QScrollArea();
    area->setWidgetResizable(true);
    QWidget *w = new QWidget();
    w->setObjectName("ConfigW");
    w->setStyleSheet("QWidget#ConfigW { background-color: white }");

    auto scrollL = ui::L::VB();
    w->setLayout(scrollL);
    area->setWidget(w);
    layout()->addWidget(area);
    m_layout = scrollL;
}

void ConfigParametersW::end_stretch(){
    if(endStretch){
        qobject_cast<QVBoxLayout*>(m_layout)->addStretch();
    }
}

void ConfigParametersW::set_stretch(int id, int value){
    m_layout->setStretch(id, value);
}

void ConfigParametersW::add_widget(QWidget *w){
    m_layout->addWidget(w);
}

void ConfigParametersW::add_horizontal_widgets(std::vector<QWidget *> widgets, LMargins margins, QFrame::Shape shape, QFrame::Shadow shadow){
    add_widget(ui::F::gen(ui::L::HB(),widgets, LStretch{false}, margins, shape, shadow));
}

void ConfigParametersW::add_stretched_horizontal_widgets(std::vector<QWidget*> widgets, LMargins margins, QFrame::Shape shape, QFrame::Shadow shadow){
    add_widget(ui::F::gen(ui::L::HB(),widgets, LStretch{true}, margins, shape, shadow));
}

void ConfigParametersW::add_vertical_widgets(std::vector<QWidget *> widgets, LMargins margins, QFrame::Shape shape, QFrame::Shadow shadow){
    add_widget(ui::F::gen(ui::L::VB(),widgets, LStretch{false}, margins, shape, shadow));
}

void ConfigParametersW::add_stretched_vertical_widgets(std::vector<QWidget *> widgets, LMargins margins, QFrame::Shape shape, QFrame::Shadow shadow){
    add_widget(ui::F::gen(ui::L::VB(),widgets, LStretch{true}, margins, shape, shadow));
}

void ConfigParametersW::add_sub_part_widget(ConfigParametersSubPart &subPart){
    add_widget(subPart.frame);
}

void ConfigParametersW::map_sub_part(ConfigParametersSubPart *subPart){
    for(auto &w : subPart->inputUiElements){
        m_inputUiElements[w.first] = w.second;
    }
}

void ConfigParametersW::update_from_args(std::map<QString,Arg> &args){

    // read and write ui    
    for(const auto &inputUiElem : m_inputUiElements){

        const QString &nameParam = inputUiElem.first;
        ExBaseW *exW = inputUiElem.second;

        // event filter
        exW->installEventFilter(this);

        if(args.count(nameParam) != 0){
            // if argument exist, update ui from it
            args.at(nameParam).uiElementKey = UiElementKey{exW->key()}; // update argument key with ui element key
            exW->update_from_arg(args.at(nameParam));
        }else{
            // else update argument from ui
            emit new_arg_signal(nameParam, exW->convert_to_arg());
        }

        // init connections
        exW->init_connection(nameParam);
        connect(exW, &ExBaseW::ui_change_signal, this, [=](QString nameParam){
            emit arg_updated_signal(nameParam, exW->convert_to_arg());
        });

        // set tooltip
        exW->init_default_tooltip(nameParam);
    }

    // actions only
    for(const auto &actionUiElem : m_actionUiElements){

        const QString &action = actionUiElem.first;
        ExBaseW *exW = actionUiElem.second;

        // event filter
        exW->installEventFilter(this);

        // init connections
        exW->init_connection(action);
        connect(exW, &ExBaseW::action_signal, this, &ConfigParametersW::action_signal);

        // set tooltip
//        exW->init_default_tooltip(nameParam);
    }

    // arg only
    for(const auto &inputNonUiArg : m_inputNonUiArguments){
        if(args.count(inputNonUiArg.first) == 0){
            emit new_arg_signal(inputNonUiArg.first, inputNonUiArg.second);
        }
    }

    // update generators
    for(const auto &generatorUiElem : m_generatorsUiElements){

        const QString &nameParam = generatorUiElem.first;
        ExParametersGeneratorWidgetW* generator = generatorUiElem.second;

        generator->init_connection(nameParam);
        connect(generator, &ExParametersGeneratorWidgetW::add_ui_signal, this, [this](QString nameParam){
            emit new_arg_signal(nameParam, m_inputUiElements[nameParam]->convert_to_arg());
        });

        connect(generator, &ExParametersGeneratorWidgetW::move_up_ui_signal, this, [this](QString prevNameParam, QString nameParam){
            emit move_arg_up_signal(prevNameParam, nameParam);
        });
        connect(generator, &ExParametersGeneratorWidgetW::move_down_ui_signal, this, [this](QString nextNameParam, QString nameParam){
            emit move_arg_down_signal(nextNameParam, nameParam);
        });
        connect(generator, &ExParametersGeneratorWidgetW::remove_ui_signal, this, [this](QString nameParam){
            emit arg_removed_signal(nameParam);
        });
        connect(generator, &ExParametersGeneratorWidgetW::ui_change_signal, this, [this](QString nameParam){
            emit arg_updated_signal(nameParam, m_inputUiElements[nameParam]->convert_to_arg());
        });

        for(const auto &arg : args){
            if(arg.second.generator.name == generator->generatorName){
                generator->update_from_arg(arg.second);
            }
        }
    }
}

void ConfigParametersW::update_from_resources(){
    for(auto &ui : m_inputUiElements){
        ui.second->update_from_resources();
    }
}

void ConfigParametersW::update_from_components(){
    for(auto &ui : m_inputUiElements){
        ui.second->update_from_components();
    }
}

void ConfigParametersW::reset_args(){

    init_and_register_widgets();
    for(auto &ui : m_inputUiElements){
        emit arg_updated_signal(ui.first, ui.second->convert_to_arg());
    }
}

