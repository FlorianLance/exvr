

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "multi_ab_pw.hpp"

using namespace tool::ex;

void MultiABInitConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::VB(), {abList()}, LStretch{false}, LMargins{true}, QFrame::Box));
    no_end_stretch();
}

void MultiABInitConfigParametersW::init_and_register_widgets(){
    add_input_ui(abList.init_widget(Resource::Type::AssetBundle, "Assets bundles:"));
}

void MultiABConfigParametersW::insert_widgets(){
    add_sub_part_widget(m_transfo);
    add_widget(ui::F::gen(ui::L::HB(), {m_currentAB()}, LStretch{false}, LMargins{true}, QFrame::Box));
}

void MultiABConfigParametersW::init_and_register_widgets(){
    map_sub_part(m_transfo.init_widget(QSL("Config transform</b> (applied when routine starts)<b>")));
    add_input_ui(m_currentAB.init_widget(Resource::Type::AssetBundle,QSL("Current asset bundle resource")));

}

