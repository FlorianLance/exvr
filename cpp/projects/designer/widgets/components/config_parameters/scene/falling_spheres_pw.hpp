
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"

namespace tool::ex {


class FallingSpheresInitConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_sbNbSpheres;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Max nb spheres :"), m_sbNbSpheres()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    }
    void init_and_register_widgets() override{
        m_inputUiElements["max_number_spheres"]   = m_sbNbSpheres.init_widget(MinV<int>{0}, V<int>{15}, MaxV<int>{1000}, StepV<int>{1});
    }
    void create_connections() override{}
    void late_update_ui() override{}
};


class FallingSpheresConfigParametersW : public ConfigParametersW{

public :


    ExVector3dW m_v3dPos;

    ExFloatSpinBoxW m_dsbInnerCircle;
    ExFloatSpinBoxW m_dsbExternCircle;

    ExSpinBoxW m_sbDurationTime;
    ExSpinBoxW m_sbSpawnTime;
    ExSpinBoxW m_sbNbSpheres;

    ExFloatSpinBoxW m_dsbGravityFactor;
    ExFloatSpinBoxW m_dsbSizeSpheres;

    ExCheckBoxW m_cbCollisionsEnabled;
    ExFloatSpinBoxW m_dsbGravityExtraForce;

    ExCheckBoxW m_cbDisplaySpawner;


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
        m_inputUiElements["position"]             = m_v3dPos.init_widget("Position spawner: ");
        m_inputUiElements["inner_circle_ray"]     = m_dsbInnerCircle.init_widget(MinV<qreal>{0.}, V<qreal>{0.5}, MaxV<qreal>{1000.}, StepV<qreal>{0.05}, 2);
        m_inputUiElements["extern_circle_ray"]    = m_dsbExternCircle.init_widget(MinV<qreal>{0.}, V<qreal>{2.}, MaxV<qreal>{1000.}, StepV<qreal>{0.05}, 2);
        m_inputUiElements["size_spheres"]         = m_dsbSizeSpheres.init_widget(MinV<qreal>{0.01}, V<qreal>{0.1}, MaxV<qreal>{10.}, StepV<qreal>{0.01}, 2);
        m_inputUiElements["duration_time_sphere"] = m_sbDurationTime.init_widget(MinV<int>{0}, V<int>{1000}, MaxV<int>{10000}, StepV<int>{100});
        m_inputUiElements["spawn_time"]           = m_sbSpawnTime.init_widget(MinV<int>{0}, V<int>{100}, MaxV<int>{10000}, StepV<int>{100});
        m_inputUiElements["collisions_enabled"]   = m_cbCollisionsEnabled.init_widget("Enable collisions", true);
        m_inputUiElements["gravity_extra_force"]  = m_dsbGravityExtraForce.init_widget(MinV<qreal>{-10.}, V<qreal>{0.0}, MaxV<qreal>{10.}, StepV<qreal>{0.01}, 2);
        m_inputUiElements["display_spawner"]      = m_cbDisplaySpawner.init_widget("Display spawner", true);

    }

    void create_connections() override{}
    void late_update_ui() override{}
};

}
