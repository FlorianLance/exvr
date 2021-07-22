

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "asset_bundle_pw.hpp"

using namespace tool::ex;

void AssetBundleInitConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::HB(), {m_assetBundle()}, LStretch{false}, LMargins{true}, QFrame::Box));
    add_widget(ui::F::gen(ui::L::VB(),{
        ui::W::txt("Sub object to load in bundle (if empty, first object of the hierarchy will be load): "),
        m_leSubObjectName(), m_displayHierarchy(), m_hierarchy = new QTextEdit()}, LStretch{false}, LMargins{true},QFrame::Box)
    );
    m_hierarchy->setReadOnly(true);
    no_end_stretch();
}

void AssetBundleInitConfigParametersW::init_and_register_widgets(){
    m_inputUiElements["asset_bundle"]       = m_assetBundle.init_widget(Resource::Type::AssetBundle, "Asset bundle resource: ");
    m_inputUiElements["name_sub_object"]    = m_leSubObjectName.init_widget("");
    m_inputUiElements["display_hierarchy"]  = m_displayHierarchy.init_widget("Display hierarchy", false);

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
    map_sub_part(m_transfo.init_widget());
}

void AssetBundleConfigParametersW::create_connections(){}

void AssetBundleConfigParametersW::late_update_ui(){}
