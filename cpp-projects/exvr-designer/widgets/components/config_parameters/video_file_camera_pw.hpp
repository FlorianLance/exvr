
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_checkbox_w.hpp"

// local
#include "ex_widgets/ex_resource_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {


class VideoFileCameraInitConfigParametersW : public ConfigParametersW{

public :

    EyeRendererSubPart m_eye;
    ExResourceW m_video{"video"};

    void insert_widgets() override{
        add_sub_part_widget(m_eye);
        add_widget(ui::F::gen(ui::L::HB(), {m_video()}, LStretch{false}, LMargins{true}, QFrame::Box));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_eye.init_widget());
        add_input_ui(m_video.init_widget(Resource::Type::Video, "Video resource: "));
    }

    void create_connections() override{}    
    void late_update_ui() override{}
};


class VideoFileCameraConfigParametersW : public ConfigParametersW{

public :

    WordSpaceCameraCanvasSubPart m_cameraSettings;
    ExCheckBoxW m_cbUseVideoSize{"use_original_size"};

    void insert_widgets() override{
        layout()->setContentsMargins(0,0,0,0);
        add_sub_part_widget(m_cameraSettings);
        add_widget(ui::F::gen(ui::L::HB(), {m_cbUseVideoSize()}, LStretch{true}, LMargins{true}, QFrame::Box));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_cameraSettings.init_widget());
        add_input_ui(m_cbUseVideoSize.init_widget("Use video original size", true, true));
    }

    void create_connections() override{
        connect(m_cbUseVideoSize(), &QCheckBox::toggled, this, [&](bool checked){
            m_cameraSettings.set_wh_enable_state(!checked,!checked);
        });

    }

    void late_update_ui() override{
        bool state = !m_cbUseVideoSize()->isChecked();
        m_cameraSettings.set_wh_enable_state(state,state);
    }
};

}
