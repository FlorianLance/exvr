

#include "buttons_ui_pw.hpp"

// qt-utility
#include "ex_widgets/ex_select_color_w.hpp"
#include "ex_widgets/ex_text_edit_w.hpp"
#include "ex_widgets/ex_checkbox_w.hpp"
#include "ex_widgets/ex_radio_button_w.hpp"
#include "ex_widgets/ex_vector2d_w.hpp"

using namespace tool::ex;

struct ButtonsUiConfigParametersW::Impl{
    EyeRendererSubPart eye;
    QTabWidget tw;
    WordSpaceCanvasSubPart cameraSettings;
    ExCheckBoxW followEyeCamera{"use_eye_camera"};
    ExVector2dW pivot{"pivot"};
    ExFloatSpinBoxW distance{"distance"};
    ExSelectColorW backgroundColor{"background_color"};
    TextSubPart leftText {"left_t"};
    TextSubPart rightText {"right_t"};
    TextSubPart topText {"top_t"};
    TextSubPart bottomText {"bottom_t"};
};


ButtonsUiConfigParametersW::ButtonsUiConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}


void ButtonsUiConfigParametersW::insert_widgets(){

    layout()->setContentsMargins(0,0,0,0);
    add_sub_part_widget(m_p->eye);
    add_widget(&m_p->tw);

    {
        QWidget *tW = new QWidget();
        QVBoxLayout *tL = new QVBoxLayout();
        tW->setLayout(tL);
        tL->setContentsMargins(2,2,2,2);

        m_p->tw.addTab(tW, "Container");
        tL->addWidget(ui::F::gen(ui::L::HB(), {m_p->followEyeCamera()}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
        tL->addWidget(m_p->cameraSettings.frame);
        tL->addWidget(ui::F::gen(ui::L::HB(), {m_p->pivot(), ui::W::txt("Distance"),  m_p->distance()}, LStretch{true}, LMargins{true}, QFrame::Box));
        tL->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("Background color"),  m_p->backgroundColor()}, LStretch{true}, LMargins{true}, QFrame::Box));
        tL->addStretch();
    }

    {
        QWidget *tW = new QWidget();
        QVBoxLayout *tL = new QVBoxLayout();
        tW->setLayout(tL);
        tL->setContentsMargins(2,2,2,2);

        m_p->tw.addTab(tW, "Buttons");
    }

    m_p->tw.addTab(m_p->leftText.textW, "Left text");
    m_p->tw.addTab(m_p->rightText.textW, "Right text");
    m_p->tw.addTab(m_p->topText.textW, "Top text");
    m_p->tw.addTab(m_p->bottomText.textW, "Bottom text");
}

void ButtonsUiConfigParametersW::init_and_register_widgets(){

    Vector2dSettings pivotSettings= {
        {MinV<qreal>{-5}, V<qreal>{0.5}, MaxV<qreal>{5}, StepV<qreal>{0.01}, 2},
        {MinV<qreal>{-5}, V<qreal>{0.5}, MaxV<qreal>{5}, StepV<qreal>{0.01}, 2}
    };
    DsbSettings distanceSettings= {MinV<qreal>{0}, V<qreal>{1.}, MaxV<qreal>{1000.}, StepV<qreal>{0.1}, 2};
    add_input_ui(m_p->pivot.init_widget("Pivot", pivotSettings));
    add_input_ui(m_p->distance.init_widget(distanceSettings));
    add_input_ui(m_p->followEyeCamera.init_widget("Text always in front of the eyes camera", true));
    add_input_ui(m_p->backgroundColor.init_widget("Select background color", QColor(255,255,255,255)));

    map_sub_part(m_p->eye.init_widget());
    map_sub_part(m_p->cameraSettings.init_widget());

    map_sub_part(m_p->leftText.init_widget("..."));
    map_sub_part(m_p->rightText.init_widget("..."));
    map_sub_part(m_p->topText.init_widget("..."));
    map_sub_part(m_p->bottomText.init_widget("..."));
}

void ButtonsUiConfigParametersW::create_connections(){
    connect(m_p->followEyeCamera(), &QCheckBox::toggled, this, [&](bool checked){
        m_p->pivot.w->setEnabled(checked);
        m_p->distance.w->setEnabled(checked);
        m_p->cameraSettings.set_position_enable_state(!checked,!checked,!checked);
    });
}

void ButtonsUiConfigParametersW::late_update_ui(){
    m_p->pivot.w->setEnabled(m_p->followEyeCamera()->isChecked());
    m_p->distance.w->setEnabled(m_p->followEyeCamera()->isChecked());

    bool state = !m_p->followEyeCamera()->isChecked();
    m_p->cameraSettings.set_position_enable_state(state,state,state);
}
