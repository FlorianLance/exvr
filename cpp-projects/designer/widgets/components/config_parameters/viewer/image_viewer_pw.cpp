
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "image_viewer_pw.hpp"


using namespace tool::ex;

void ImageViewerInitConfigParametersW::insert_widgets(){

}

void ImageViewerInitConfigParametersW::init_and_register_widgets(){

}

void ImageViewerInitConfigParametersW::create_connections(){

}

void ImageViewerInitConfigParametersW::late_update_ui(){

}


void ImageViewerConfigParametersW::insert_widgets(){

    layout()->setContentsMargins(0,0,0,0);
    add_sub_part_widget(m_eye);

    auto useImageF      = ui::F::gen(ui::L::HB(), {m_useImageSize()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto followCameraF  = ui::F::gen(ui::L::HB(), {m_followEyeCamera()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto topF = ui::F::gen(ui::L::VB(), {m_image(), useImageF, followCameraF}, LStretch{false}, LMargins{false}, QFrame::Box);
    add_widget(topF);
    add_sub_part_widget(m_cameraSettings);
    add_widget(ui::F::gen(ui::L::HB(), {m_pivot(), ui::W::txt("Distance"),  m_distance()}, LStretch{true}, LMargins{true}, QFrame::Box));
}

void ImageViewerConfigParametersW::init_and_register_widgets(){

    m_inputUiElements["image"] = m_image.init_widget(Resource::Type::Image, "Image resource: ");
    m_inputUiElements["use_eye_camera"]     = m_followEyeCamera.init_widget("Image always in front of the eyes camera", true);
    m_inputUiElements["use_original_size"]  = m_useImageSize.init_widget("Use image original size", true);

    Vector2dSettings pivotSettings= {
        {MinV<qreal>{-0.5}, V<qreal>{0.5}, MaxV<qreal>{1.5}, StepV<qreal>{0.01}, 2},
        {MinV<qreal>{-0.5}, V<qreal>{0.5}, MaxV<qreal>{1.5}, StepV<qreal>{0.01}, 2}
    };
    m_inputUiElements["pivot"]      = m_pivot.init_widget("Pivot", pivotSettings);
    DsbSettings distanceSettings= {MinV<qreal>{0}, V<qreal>{1.}, MaxV<qreal>{1000.}, StepV<qreal>{0.1}, 2};
    m_inputUiElements["distance"]   = m_distance.init_widget(distanceSettings);

    map_sub_part(m_eye.init_widget());
    map_sub_part(m_cameraSettings.init_widget());
}

void ImageViewerConfigParametersW::create_connections(){
    connect(m_useImageSize(), &QCheckBox::toggled, this, [&](bool checked){
        m_cameraSettings.width()->setEnabled(!checked);
        m_cameraSettings.height()->setEnabled(!checked);
    });

    connect(m_followEyeCamera(), &QCheckBox::toggled, this, [&](bool checked){
        m_pivot.w->setEnabled(checked);
        m_distance.w->setEnabled(checked);
        m_cameraSettings.position.x.w->setEnabled(!checked);
        m_cameraSettings.position.y.w->setEnabled(!checked);
        m_cameraSettings.position.z.w->setEnabled(!checked);
    });
}

void ImageViewerConfigParametersW::late_update_ui(){
    m_cameraSettings.width()->setEnabled(!m_useImageSize()->isChecked());
    m_cameraSettings.height()->setEnabled(!m_useImageSize()->isChecked());
    m_pivot.w->setEnabled(m_followEyeCamera()->isChecked());
    m_cameraSettings.position.x.w->setEnabled(!m_followEyeCamera()->isChecked());
    m_cameraSettings.position.y.w->setEnabled(!m_followEyeCamera()->isChecked());
    m_cameraSettings.position.z.w->setEnabled(!m_followEyeCamera()->isChecked());
}
