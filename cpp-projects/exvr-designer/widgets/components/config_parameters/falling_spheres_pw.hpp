
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_spin_box_w.hpp"
#include "ex_widgets/ex_checkbox_w.hpp"
#include "ex_widgets/ex_float_spin_box_w.hpp"
#include "ex_widgets/ex_vector3d_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {


class FallingSpheresInitConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_sbNbSpheres{"max_number_spheres"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Max nb spheres :"), m_sbNbSpheres()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    }
    void init_and_register_widgets() override{        
        add_input_ui(m_sbNbSpheres.init_widget(MinV<int>{0}, V<int>{15}, MaxV<int>{1000}, StepV<int>{1}));
    }
    void create_connections() override{}
    void late_update_ui() override{}
};


class FallingSpheresConfigParametersW : public ConfigParametersW{

public :

    ExVector3dW m_v3dPos{"position"};

    ExFloatSpinBoxW m_dsbInnerCircle{"inner_circle_ray"};
    ExFloatSpinBoxW m_dsbExternCircle{"extern_circle_ray"};

    ExSpinBoxW m_sbDurationTime{"duration_time_sphere"};
    ExSpinBoxW m_sbSpawnTime{"spawn_time"};
    ExSpinBoxW m_sbNbSpheres{""};

    ExFloatSpinBoxW m_dsbGravityFactor{""};
    ExFloatSpinBoxW m_dsbSizeSpheres{"size_spheres"};

    ExCheckBoxW m_cbCollisionsEnabled{"collisions_enabled"};
    ExFloatSpinBoxW m_dsbGravityExtraForce{"gravity_extra_force"};

    ExCheckBoxW m_cbDisplaySpawner{"display_spawner"};


    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(),{m_v3dPos()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Inner circle ray: "), m_dsbInnerCircle(),
                                                 ui::W::txt("Extern circle ray: "), m_dsbExternCircle()}, LStretch{true}, LMargins{false},QFrame::NoFrame));

        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Sizes spheres :"), m_dsbSizeSpheres()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Duration time (ms) :"), m_sbDurationTime()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Spawn interval time (ms) :"), m_sbSpawnTime()}, LStretch{true}, LMargins{false},QFrame::NoFrame));

        add_widget(ui::F::gen(ui::L::HB(),{m_cbCollisionsEnabled(), ui::W::txt("Gravity extra force :"),
                                                 m_dsbGravityExtraForce()}, LStretch{true}, LMargins{false},QFrame::NoFrame));

        add_widget(ui::F::gen(ui::L::HB(),{m_cbDisplaySpawner()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    }

    void init_and_register_widgets() override{
        add_input_ui(m_v3dPos.init_widget("Position spawner: "));
        add_input_ui(m_dsbInnerCircle.init_widget(MinV<qreal>{0.}, V<qreal>{0.5}, MaxV<qreal>{1000.}, StepV<qreal>{0.05}, 2));
        add_input_ui(m_dsbExternCircle.init_widget(MinV<qreal>{0.}, V<qreal>{2.}, MaxV<qreal>{1000.}, StepV<qreal>{0.05}, 2));
        add_input_ui(m_dsbSizeSpheres.init_widget(MinV<qreal>{0.01}, V<qreal>{0.1}, MaxV<qreal>{10.}, StepV<qreal>{0.01}, 2));
        add_input_ui(m_sbDurationTime.init_widget(MinV<int>{0}, V<int>{1000}, MaxV<int>{10000}, StepV<int>{100}));
        add_input_ui(m_sbSpawnTime.init_widget(MinV<int>{0}, V<int>{100}, MaxV<int>{10000}, StepV<int>{100}));
        add_input_ui(m_cbCollisionsEnabled.init_widget("Enable collisions", true));
        add_input_ui(m_dsbGravityExtraForce.init_widget(MinV<qreal>{-10.}, V<qreal>{0.0}, MaxV<qreal>{10.}, StepV<qreal>{0.01}, 2));
        add_input_ui(m_cbDisplaySpawner.init_widget("Display spawner", true));
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

}
