
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

#pragma once

// qt-utility
#include "gui/ex_widgets/ex_float_spin_box_w.hpp"
#include "gui/ex_widgets/ex_checkbox_w.hpp"
#include "gui/ex_widgets/ex_spin_box_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {

class MarkToCleanInitConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_sbWidthColliderResolution{"width_collider_resolution"};
    ExSpinBoxW m_sbHeightColliderResolution{"height_collider_resolution"};
    ExFloatSpinBoxW m_dsbMaxReachableDistance{"max_distance_reachable"};

    void insert_widgets() override{
        
        add_widget(ui::F::old_gen(ui::L::HB(),{new QLabel("Width collider resolution: "),m_sbWidthColliderResolution()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::old_gen(ui::L::HB(),{new QLabel("Height collider resolution: "),m_sbHeightColliderResolution()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::old_gen(ui::L::HB(),{ui::W::txt("Max reachable distance (m): "),m_dsbMaxReachableDistance()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    }

    void init_and_register_widgets() override{
        add_input_ui(m_sbWidthColliderResolution.init_widget(MinV<int>{10}, V<int>{250}, MaxV<int>{1000}, StepV<int>{1}));
        add_input_ui(m_sbHeightColliderResolution.init_widget(MinV<int>{10}, V<int>{250}, MaxV<int>{1000}, StepV<int>{1}));
        add_input_ui(m_dsbMaxReachableDistance.init_widget(MinV<qreal>{0.1}, V<qreal>{0.5}, MaxV<qreal>{1.3}, StepV<qreal>{0.01}, 2));
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class MarkToCleanConfigParametersW : public ConfigParametersW{

public :

    // general
    ExCheckBoxW m_cbDebug{"debug"};

    // working zone
    TransformSubPart m_trWorkingZone{"working_transform"};

    // mark
    ExFloatSpinBoxW m_distancePercentageMark{"distance_percentage_mark"};
    ExFloatSpinBoxW m_distanceErase{"distance_erase"};
    ExFloatSpinBoxW m_alphaDecrease{"alpha_decrease"};

    void insert_widgets() override{

        // general
        add_widget(ui::F::old_gen(ui::L::VB(),{new QLabel("<b>General</b>"), m_cbDebug()}, LStretch{true}, LMargins{true},QFrame::Box));

        // working zone
        add_sub_part_widget(m_trWorkingZone);

        // mark
        auto markDistance  = ui::F::old_gen(ui::L::HB(),   {ui::W::txt("Distance (%): "),        m_distancePercentageMark()}, LStretch{false}, LMargins{false},QFrame::NoFrame);
        auto eraseDistance  = ui::F::old_gen(ui::L::HB(),  {ui::W::txt("Erase distance (m): "), m_distanceErase()}, LStretch{false}, LMargins{false},QFrame::NoFrame);
        auto alphaDecrease = ui::F::old_gen(ui::L::HB(),   {ui::W::txt("Erase power: "),         m_alphaDecrease()}, LStretch{false}, LMargins{false},QFrame::NoFrame);
        add_widget(ui::F::old_gen(ui::L::VB(),{new QLabel("<b>Mark</b>"), markDistance, eraseDistance, alphaDecrease}, LStretch{true}, LMargins{true},QFrame::Box));
    }

    void init_and_register_widgets() override{

        // general
        add_input_ui(m_cbDebug.init_widget("Debug", true));

        // working zone
        map_sub_part(m_trWorkingZone.init_widget("Working zone transform"));
        m_trWorkingZone.set_rotation_values({90.,0.,0.});
        m_trWorkingZone.set_trans_decimals(3);
        m_trWorkingZone.set_trans_steps({0.001,0.001,0.001});

        // mark
        add_input_ui(m_distancePercentageMark.init_widget(MinV<qreal>{10.}, V<qreal>{80.}, MaxV<qreal>{100.}, StepV<qreal>{0.1}, 1));
        add_input_ui(m_distanceErase.init_widget(MinV<qreal>{0.001}, V<qreal>{0.015}, MaxV<qreal>{0.1}, StepV<qreal>{0.001}, 3));
        add_input_ui(m_alphaDecrease.init_widget(MinV<qreal>{0.001}, V<qreal>{0.01}, MaxV<qreal>{1.0}, StepV<qreal>{0.001}, 3));
    }

    void create_connections() override{
        // ...
    }

    void late_update_ui() override{}
};

}
