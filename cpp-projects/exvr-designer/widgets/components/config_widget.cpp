
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "config_widget.hpp"

// base
#include "utility/benchmark.hpp"

using namespace tool::ex;

ConfigW::ConfigW(Config *config, ConfigParametersW *parametersW) : p(parametersW), key(config->key()), name(config->name){

    Bench::start("[ConfigW init 1]"sv, false);
        setLayout(new QHBoxLayout());
        layout()->addWidget(p);
        p->setVisible(true);
    Bench::stop();

    Bench::start("[ConfigW init 2]"sv, false);
        p->update_from_resources();
    Bench::stop();

    Bench::start("[ConfigW init 3]"sv, false);
        p->update_from_components();
    Bench::stop();
}

void ConfigW::update_from_config(Config *config){

    name = config->name;

    Bench::start("[ConfigW::update_from_resources]"sv);
        p->update_from_resources();
    Bench::stop();

    Bench::start("[ConfigW::update_from_components]"sv);
        p->update_from_components();
    Bench::stop();
}


#include "moc_config_widget.cpp"
