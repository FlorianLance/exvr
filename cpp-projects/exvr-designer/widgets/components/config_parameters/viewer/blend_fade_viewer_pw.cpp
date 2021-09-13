
#include "blend_fade_viewer_pw.hpp"

using namespace tool::ex;

void BlendFadeViewerConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::HB(), {blendAndFade(), onlyBlend()},  LStretch{true}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Start color"), startColor(), ui::W::txt("End color"), endColor()},  LStretch{true}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Duration blend"), durationBlend()},  LStretch{true}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Duration fade"), durationFade()},  LStretch{true}, LMargins{true}, QFrame::NoFrame));
}

void BlendFadeViewerConfigParametersW::init_and_register_widgets(){

    add_inputs_ui(
        ExRadioButtonW::init_group_widgets(group1,
            {&blendAndFade, &onlyBlend},
            {
                "Blend and fade",
                "Only blend",
            },
            {true,false}
        )
    );

    DsbSettings s = {MinV<qreal>{0.0}, V<qreal>{1.0}, MaxV<qreal>{1000.0}, StepV<qreal>{0.1}, 2};
    add_input_ui(durationBlend.init_widget(s));
    add_input_ui(durationFade.init_widget(s));
    add_input_ui(startColor.init_widget("Select start color" , QColor(0,0,0,0)));
    add_input_ui(endColor.init_widget("Select end color" , QColor(0,0,0,255)));
}

void BlendFadeViewerConfigParametersW::create_connections(){
}

void BlendFadeViewerConfigParametersW::late_update_ui(){
}
