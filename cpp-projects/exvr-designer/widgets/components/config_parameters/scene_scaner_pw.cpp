
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

#include "scene_scaner_pw.hpp"

using namespace tool::ex;

void SceneScanerInitConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::HB(), {m_kinectManager()}, LStretch{false}, LMargins{true}, QFrame::Box));
}

void SceneScanerInitConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_kinectManager.init_widget(Component::Type::Kinect_manager, "Kinect manager component: "));
}

void SceneScanerConfigParametersW::insert_widgets(){
    add_sub_part_widget(m_tr);
    add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Size points: "),m_sizePoints()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(),{m_displayClouds()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(),{m_displayColliders()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(),{m_moveEyeToHeadPosition()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
}

void SceneScanerConfigParametersW::init_and_register_widgets(){

    map_sub_part(m_tr.init_widget("Global model transform"));
    add_input_ui(m_sizePoints.init_widget(MinV<qreal>{0.0001}, V<qreal>{0.0030}, MaxV<qreal>{0.05}, StepV<qreal>{0.0001},4));
    add_input_ui(m_displayClouds.init_widget("Display clouds ", true));
    add_input_ui(m_displayColliders.init_widget("Display colliders ", false));
    add_action_ui(m_moveEyeToHeadPosition.init_widget("Move eye camera to fit tracked head"));

}
