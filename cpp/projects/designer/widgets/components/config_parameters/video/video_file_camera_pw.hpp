
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"

namespace tool::ex {


class VideoFileCameraInitConfigParametersW : public ConfigParametersW{

public :

    EyeRendererSubPart m_eye;
    ExResourceW m_video;

    void insert_widgets() override{
        add_sub_part_widget(m_eye);
        add_widget(ui::F::gen(ui::L::HB(), {m_video()}, LStretch{false}, LMargins{true}, QFrame::Box));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_eye.init_widget());
        m_inputUiElements["video"] = m_video.init_widget(Resource::Type::Video, "Video resource: ");
    }

    void create_connections() override{}    
    void late_update_ui() override{}
};


class VideoFileCameraConfigParametersW : public ConfigParametersW{

public :

    WordSpaceCameraCanvasSubPart m_cameraSettings;
    ExCheckBoxW m_cbUseVideoSize;

    void insert_widgets() override{
        layout()->setContentsMargins(0,0,0,0);
        add_sub_part_widget(m_cameraSettings);
        add_widget(ui::F::gen(ui::L::HB(), {m_cbUseVideoSize()}, LStretch{true}, LMargins{true}, QFrame::Box));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_cameraSettings.init_widget());
        m_inputUiElements["use_original_size"]  = m_cbUseVideoSize.init_widget("Use video original size", true, true);
    }

    void create_connections() override{
        connect(m_cbUseVideoSize(), &QCheckBox::toggled, this, [&](bool checked){
            m_cameraSettings.width()->setEnabled(!checked);
            m_cameraSettings.height()->setEnabled(!checked);
        });

    }

    void late_update_ui() override{
        m_cameraSettings.width()->setEnabled(!m_cbUseVideoSize()->isChecked());
        m_cameraSettings.height()->setEnabled(!m_cbUseVideoSize()->isChecked());
    }
};

}
