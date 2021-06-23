
#include "webcam_viewer_pw.hpp"

using namespace tool::ex;

void WebcamViewerInitConfigParametersW::insert_widgets(){

    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Device id: "), m_sbDeviceId()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Requested FPS: "), m_sbFPS()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
}

void WebcamViewerInitConfigParametersW::init_and_register_widgets(){

    m_inputUiElements["device_id"]          = m_sbDeviceId.init_widget(MinV<int>{0}, V<int>{0}, MaxV<int>{32}, StepV<int>{1},  true);
    m_inputUiElements["requested_fps"]      = m_sbFPS.init_widget(MinV<int>{1}, V<int>{30}, MaxV<int>{120}, StepV<int>{1},  true);
}



void WebcamViewerConfigParametersW::insert_widgets(){

    layout()->setContentsMargins(0,0,0,0);
    add_sub_part_widget(m_eye);

    auto useImageF      = ui::F::gen(ui::L::HB(), {m_cbUseVideoSize()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto followCameraF  = ui::F::gen(ui::L::HB(), {m_followEyeCamera()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto topF = ui::F::gen(ui::L::VB(), {useImageF, followCameraF}, LStretch{false}, LMargins{false}, QFrame::Box);
    add_widget(topF);
    add_sub_part_widget(m_cameraSettings);
    add_widget(ui::F::gen(ui::L::HB(), {m_pivot(), ui::W::txt("Distance"),  m_distance()}, LStretch{true}, LMargins{true}, QFrame::Box));
}

void WebcamViewerConfigParametersW::init_and_register_widgets(){

    map_sub_part(m_eye.init_widget());
    m_inputUiElements["use_eye_camera"]     = m_followEyeCamera.init_widget("Video always in front of the eyes camera", false);
    m_inputUiElements["use_original_size"]  = m_cbUseVideoSize.init_widget("Use video original size", true);

    Vector2dSettings pivotSettings= {
        {MinV<qreal>{-0.5}, V<qreal>{0.5}, MaxV<qreal>{1.5}, StepV<qreal>{0.01}, 2},
        {MinV<qreal>{-0.5}, V<qreal>{0.5}, MaxV<qreal>{1.5}, StepV<qreal>{0.01}, 2}
    };
    m_inputUiElements["pivot"]      = m_pivot.init_widget("Pivot", pivotSettings);
    DsbSettings distanceSettings= {MinV<qreal>{0}, V<qreal>{10.}, MaxV<qreal>{1000.}, StepV<qreal>{0.1}, 2};
    m_inputUiElements["distance"]   = m_distance.init_widget(distanceSettings);

    map_sub_part(m_cameraSettings.init_widget());
}

void WebcamViewerConfigParametersW::create_connections(){
    connect(m_cbUseVideoSize(), &QCheckBox::toggled, this, [&](bool checked){
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

void WebcamViewerConfigParametersW::late_update_ui(){
    m_cameraSettings.width()->setEnabled(!m_cbUseVideoSize()->isChecked());
    m_cameraSettings.height()->setEnabled(!m_cbUseVideoSize()->isChecked());
    m_pivot.w->setEnabled(m_followEyeCamera()->isChecked());
    m_cameraSettings.position.x.w->setEnabled(!m_followEyeCamera()->isChecked());
    m_cameraSettings.position.y.w->setEnabled(!m_followEyeCamera()->isChecked());
    m_cameraSettings.position.z.w->setEnabled(!m_followEyeCamera()->isChecked());
}
