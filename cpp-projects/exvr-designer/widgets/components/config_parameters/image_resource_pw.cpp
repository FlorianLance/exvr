


/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "image_resource_pw.hpp"

// local
#include "ex_widgets/ex_resources_list_w.hpp"
#include "ex_widgets/ex_line_edit_w.hpp"

using namespace tool::ex;

struct ImageResourceInitConfigParametersW::Impl{
    ExResourcesListW imagesList{"images_list"};
};

ImageResourceInitConfigParametersW::ImageResourceInitConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void ImageResourceInitConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::VB(), {m_p->imagesList()}, LStretch{false}, LMargins{true}, QFrame::Box));
    no_end_stretch();
}

void ImageResourceInitConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_p->imagesList.init_widget(Resource::Type::Image, "Images:"));
}

void ImageResourceInitConfigParametersW::create_connections(){
    connect(&m_p->imagesList, &ExResourcesListW::ui_change_signal, this, [&]{

    });
}

void ImageResourceInitConfigParametersW::late_update_ui(){}

struct ImageResourceConfigParametersW::Impl{
    ExLineEditW alias{"alias"};
};

ImageResourceConfigParametersW::ImageResourceConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void ImageResourceConfigParametersW::insert_widgets(){
    layout()->setContentsMargins(0,0,0,0);
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Current alias"), m_p->alias()}, LStretch{false}, LMargins{true}, QFrame::Box));
}

void ImageResourceConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_p->alias.init_widget(""));
}

void ImageResourceConfigParametersW::create_connections(){
}

void ImageResourceConfigParametersW::late_update_ui(){
}
