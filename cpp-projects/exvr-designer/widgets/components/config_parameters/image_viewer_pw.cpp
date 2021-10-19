
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "image_viewer_pw.hpp"


using namespace tool::ex;

struct ImageViewerConfigParametersW::Impl{
    EyeRendererSubPart eye;
    ExResourceW image{"image"};
    ExCheckBoxW doNotLoad{"do_not_load"};
    WordSpaceCanvasSubPart cameraSettings;
    ExCheckBoxW followEyeCamera{"use_eye_camera"};
    ExCheckBoxW useImageSize{"use_original_size"};
    ExVector2dW pivot{"pivot"};
    ExFloatSpinBoxW distance{"distance"};
};

ImageViewerConfigParametersW::ImageViewerConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void ImageViewerConfigParametersW::insert_widgets(){

    layout()->setContentsMargins(0,0,0,0);
    add_sub_part_widget(m_p->eye);

    auto useImageF      = ui::F::gen(ui::L::HB(), {m_p->useImageSize()}, LStretch{true}, LMargins{false}, QFrame::NoFrame);
    auto followCameraF  = ui::F::gen(ui::L::HB(), {m_p->followEyeCamera()}, LStretch{true}, LMargins{false}, QFrame::NoFrame);
    add_widget(ui::F::gen(ui::L::VB(), {m_p->image(), m_p->doNotLoad(), useImageF, followCameraF}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
    add_sub_part_widget(m_p->cameraSettings);
    add_widget(ui::F::gen(ui::L::HB(), {m_p->pivot(), ui::W::txt("Distance"),  m_p->distance()}, LStretch{true}, LMargins{true}, QFrame::Box));
}

void ImageViewerConfigParametersW::init_and_register_widgets(){

    add_input_ui(m_p->image.init_widget(Resource::Type::Image, "Image resource: "));
    add_input_ui(m_p->doNotLoad.init_widget("Do not load", false));
    add_input_ui(m_p->followEyeCamera.init_widget("Image always in front of the eyes camera", true));
    add_input_ui(m_p->useImageSize.init_widget("Use image original size", true));

    Vector2dSettings pivotSettings= {
        {MinV<qreal>{-0.5}, V<qreal>{0.5}, MaxV<qreal>{1.5}, StepV<qreal>{0.01}, 2},
        {MinV<qreal>{-0.5}, V<qreal>{0.5}, MaxV<qreal>{1.5}, StepV<qreal>{0.01}, 2}
    };
    add_input_ui(m_p->pivot.init_widget("Pivot", pivotSettings));
    DsbSettings distanceSettings= {MinV<qreal>{0}, V<qreal>{1.}, MaxV<qreal>{1000.}, StepV<qreal>{0.1}, 2};
    add_input_ui(m_p->distance.init_widget(distanceSettings));

    map_sub_part(m_p->eye.init_widget());
    map_sub_part(m_p->cameraSettings.init_widget());
}

void ImageViewerConfigParametersW::create_connections(){
    connect(m_p->useImageSize(), &QCheckBox::toggled, this, [&](bool checked){
        m_p->cameraSettings.set_wh_enable_state(!checked,!checked);
    });

    connect(m_p->followEyeCamera(), &QCheckBox::toggled, this, [&](bool checked){
        m_p->pivot.w->setEnabled(checked);
        m_p->distance.w->setEnabled(checked);
        m_p->cameraSettings.set_position_enable_state(!checked,!checked,!checked);
    });
}

void ImageViewerConfigParametersW::late_update_ui(){
    bool state1 = !m_p->useImageSize()->isChecked();
    m_p->cameraSettings.set_wh_enable_state(state1,state1);

    m_p->pivot.w->setEnabled(m_p->followEyeCamera()->isChecked());
    bool state2 = !m_p->followEyeCamera()->isChecked();
    m_p->cameraSettings.set_position_enable_state(state2,state2,state2);
}
