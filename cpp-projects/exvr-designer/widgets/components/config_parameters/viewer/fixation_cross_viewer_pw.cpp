
#include "fixation_cross_viewer_pw.hpp"

using namespace tool::ex;

void FixationCrossViewerInitConfigParametersW::insert_widgets(){}

void FixationCrossViewerInitConfigParametersW::init_and_register_widgets(){}

void FixationCrossViewerInitConfigParametersW::create_connections(){}

void FixationCrossViewerInitConfigParametersW::late_update_ui(){}

void FixationCrossViewerConfigParametersW::insert_widgets(){

    layout()->setContentsMargins(0,0,0,0);
    add_sub_part_widget(m_eye);

    auto useImageF      = ui::F::gen(ui::L::HB(), {m_useImageSize()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto followCameraF  = ui::F::gen(ui::L::HB(), {m_followEyeCamera()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto topF = ui::F::gen(ui::L::VB(), {useImageF, followCameraF}, LStretch{false}, LMargins{false}, QFrame::Box);
    add_widget(topF);
    add_sub_part_widget(m_cameraSettings);
    add_widget(ui::F::gen(ui::L::HB(), {m_pivot(), ui::W::txt("Distance"),  m_distance()}, LStretch{true}, LMargins{true}, QFrame::Box));
}

void FixationCrossViewerConfigParametersW::init_and_register_widgets(){

    add_input_ui(m_followEyeCamera.init_widget("Cross always in front of the eyes camera", true));
    add_input_ui(m_useImageSize.init_widget("Use cross original size", true));

    Vector2dSettings pivotSettings= {
        {MinV<qreal>{-0.5}, V<qreal>{0.5}, MaxV<qreal>{1.5}, StepV<qreal>{0.01}, 2},
        {MinV<qreal>{-0.5}, V<qreal>{0.5}, MaxV<qreal>{1.5}, StepV<qreal>{0.01}, 2}
    };
    add_input_ui(m_pivot.init_widget("Pivot", pivotSettings));
    DsbSettings distanceSettings= {MinV<qreal>{0}, V<qreal>{1.}, MaxV<qreal>{1000.}, StepV<qreal>{0.1}, 2};
    add_input_ui(m_distance.init_widget(distanceSettings));

    map_sub_part(m_eye.init_widget());
    map_sub_part(m_cameraSettings.init_widget());
}

void FixationCrossViewerConfigParametersW::create_connections(){
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

void FixationCrossViewerConfigParametersW::late_update_ui(){

    m_cameraSettings.width()->setEnabled(!m_useImageSize()->isChecked());
    m_cameraSettings.height()->setEnabled(!m_useImageSize()->isChecked());
    m_pivot.w->setEnabled(m_followEyeCamera()->isChecked());
    m_distance.w->setEnabled(m_followEyeCamera()->isChecked());
    m_cameraSettings.position.x.w->setEnabled(!m_followEyeCamera()->isChecked());
    m_cameraSettings.position.y.w->setEnabled(!m_followEyeCamera()->isChecked());
    m_cameraSettings.position.z.w->setEnabled(!m_followEyeCamera()->isChecked());

}
