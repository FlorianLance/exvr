
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "ex_widgets/ex_resource_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {


class VideoFileInitConfigParametersW : public ConfigParametersW{

public :

    ExResourceW m_video{"video"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {m_video()}, LStretch{false}, LMargins{true}, QFrame::Box));
    }

    void init_and_register_widgets() override{        
        add_input_ui(m_video.init_widget(Resource::Type::Video, "Video resource: "));
    }
    void create_connections() override{


    }
    void late_update_ui() override{}
};


class VideoFileConfigParametersW : public ConfigParametersW{

public :



    void insert_widgets() override{

    }

    void init_and_register_widgets() override{

    }

    void create_connections() override{
    }

    void late_update_ui() override{
    }
};

}
