


/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "image_resource_pw.hpp"


using namespace tool::ex;

void ImageResourceInitConfigParametersW::insert_widgets(){}

void ImageResourceInitConfigParametersW::init_and_register_widgets(){}

void ImageResourceInitConfigParametersW::create_connections(){}

void ImageResourceInitConfigParametersW::late_update_ui(){}

void ImageResourceConfigParametersW::insert_widgets(){
    layout()->setContentsMargins(0,0,0,0);
    add_widget(ui::F::gen(ui::L::HB(), {m_image()}, LStretch{false}, LMargins{true}, QFrame::Box));
}

void ImageResourceConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_image.init_widget(Resource::Type::Image, "Image resource: "));
}

void ImageResourceConfigParametersW::create_connections(){
}

void ImageResourceConfigParametersW::late_update_ui(){
}
