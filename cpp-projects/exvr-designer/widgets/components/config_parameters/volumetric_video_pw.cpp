
/***********************************************************************************
** exvr-designer                                                                  **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

#include "volumetric_video_resource_pw.hpp"

// qt-utility
#include "ex_widgets/ex_line_edit_w.hpp"
#include "ex_widgets/ex_radio_button_w.hpp"
#include "ex_widgets/ex_spin_box_w.hpp"
#include "ex_widgets/ex_float_spin_box_w.hpp"
#include "ex_widgets/ex_checkbox_w.hpp"
#include "ex_widgets/ex_text_edit_w.hpp"

// local
#include "ex_widgets/ex_resources_list_w.hpp"

using namespace tool::ex;

struct VolumetricVideoInitConfigParametersW::Impl{
    TransformSubPart transfo{"init_transform"};
    ExResourceW volumetricVideo{"volumetric_video"};
    ExTextEditW infoText;
};

VolumetricVideoInitConfigParametersW::VolumetricVideoInitConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void VolumetricVideoInitConfigParametersW::insert_widgets(){

    add_widget(ui::F::gen(ui::L::VB(), {m_p->volumetricVideo()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));

    // infos
    add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("Infos"), m_p->infoText()}, LStretch{true}, LMargins{true}, QFrame::Box));
    m_p->infoText.w->setMinimumHeight(100);

    add_sub_part_widget(m_p->transfo);
    no_end_stretch();
}

void VolumetricVideoInitConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_p->volumetricVideo.init_widget(Resource::Type::VolumetricVideo, "Volumetric video:"));
    map_sub_part(m_p->transfo.init_widget(QSL("Init transform</b> (applied when experiment starts)<b>")));
}

void VolumetricVideoInitConfigParametersW::update_with_info(QStringView id, QStringView value){
    if(id == QSL("infos")){
        m_p->infoText.w->setText("");
    }
}

struct VolumetricVideoConfigParametersW::Impl{
    TransformSubPart transfo{"transform"};
    ExCheckBoxW loop;
    ExFloatSpinBoxW startTime;
    ExFloatSpinBoxW endTime;
    ExCheckBoxW enableAudio;
    ExSpinBoxW audioCameraId;
    ExSpinBoxW volume;
};

VolumetricVideoConfigParametersW::VolumetricVideoConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void VolumetricVideoConfigParametersW::insert_widgets(){
    add_sub_part_widget(m_p->transfo);
    add_widget(ui::F::gen(ui::L::HB(), {m_p->loop()}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Duration (s), from: "), m_p->startTime(),ui::W::txt(" to: "),m_p->endTime()}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_p->enableAudio(), ui::W::txt("Audio id: "), m_p->audioCameraId()}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Volume: "), m_p->volume()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
}

void VolumetricVideoConfigParametersW::init_and_register_widgets(){
    map_sub_part(m_p->transfo.init_widget(QSL("Config transform</b> (applied when routine starts)<b>")));
    add_input_ui(m_p->startTime.init_widget(MinV<qreal>{0.0}, V<qreal>{0.0}, MaxV<qreal>{1000.}, StepV<qreal>{0.1}, 2));
    add_input_ui(m_p->endTime.init_widget(MinV<qreal>{0.0}, V<qreal>{10.0}, MaxV<qreal>{1000.}, StepV<qreal>{0.1}, 2));
    add_input_ui(m_p->enableAudio.init_widget("Enable audio", true));
    add_input_ui(m_p->volume.init_widget(MinV<int>{0}, V<int>{100}, MaxV<int>{100}, StepV<int>{1}));
}

