

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "asset_bundle_pw.hpp"

// local
#include "utility/path_utility.hpp"

using namespace tool::ex;

void AssetBundleInitConfigParametersW::insert_widgets(){

    add_widget(ui::F::gen(ui::L::HB(), {m_assetBundle()}, LStretch{false}, LMargins{true}, QFrame::Box));
    add_widget(ui::F::gen(ui::L::VB(),{
        ui::W::txt(QSL("Sub object to load in bundle (if empty, first object of the hierarchy will be load): ")),
        m_leSubObjectName(), m_displayHierarchy(), m_hierarchy = new QTextEdit()}, LStretch{false}, LMargins{true},QFrame::Box)
    );
    add_sub_part_widget(m_transfo);
    m_hierarchy->setReadOnly(true);
    no_end_stretch();
}

void AssetBundleInitConfigParametersW::init_and_register_widgets(){
    map_sub_part(m_transfo.init_widget(QSL("Init transform</b> (applied when experiment starts)<b>")));
    add_input_ui(m_assetBundle.init_widget(Resource::Type::AssetBundle, QSL("Asset bundle resource: ")));
    add_input_ui(m_leSubObjectName.init_widget(""));
    add_input_ui(m_displayHierarchy.init_widget(QSL("Display asset bundle content hierarchy"), false));
}

void AssetBundleInitConfigParametersW::create_connections(){
}

void AssetBundleInitConfigParametersW::late_update_ui(){}

void AssetBundleInitConfigParametersW::update_with_info(QStringView id, QStringView value){
    if(id == QSL("hierarchy")){
        m_hierarchy->setText(value.toString());
    }
}

void AssetBundleConfigParametersW::insert_widgets(){
    add_sub_part_widget(m_transfo);
}

void AssetBundleConfigParametersW::init_and_register_widgets(){
    map_sub_part(m_transfo.init_widget(QSL("Config transform</b> (applied when routine starts)<b>")));
}

void AssetBundleConfigParametersW::create_connections(){}

void AssetBundleConfigParametersW::late_update_ui(){}
