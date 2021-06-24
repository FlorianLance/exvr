
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"

namespace tool::ex{

//shape_component



class TargetToGrabInitConfigParametersW : public ConfigParametersW{

public :

    ExLineEditW m_leTargetComponentName;
    ExFloatSpinBoxW m_dsbMaxReachableDistance;
    ExFloatSpinBoxW m_dsbStartLineDistance;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Target component name: "),       m_leTargetComponentName(), ui::W::txt("(target must be before in condition order)")}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Max reachable distance (m): "),  m_dsbMaxReachableDistance()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Start line distance (m): "),     m_dsbStartLineDistance()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["shape_component"]        = m_leTargetComponentName.init_widget("...");
        m_inputUiElements["max_distance_reachable"] = m_dsbMaxReachableDistance.init_widget(MinV<qreal>{0.1}, V<qreal>{0.5}, MaxV<qreal>{1.3}, StepV<qreal>{0.01}, 2);
        m_inputUiElements["start_distance"]         = m_dsbStartLineDistance.init_widget(MinV<qreal>{-1.0}, V<qreal>{0.1}, MaxV<qreal>{1.3}, StepV<qreal>{0.01}, 2);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class TargetToGrabConfigParametersW : public ConfigParametersW{

public :

    // general
    ExCheckBoxW m_cbDebug;
    ExCheckBoxW m_cbDisplayStartLine;

    // working zone
    DefaultTransformSubPart m_trWorkingZone;

    // target
    ExFloatSpinBoxW m_dsbDistancePercentageTarget;
    ExFloatSpinBoxW m_dsbHeightTarget;
    ExFloatSpinBoxW m_dsbAngleTarget;


    void insert_widgets() override{

        // general
        add_widget(ui::F::gen(ui::L::VB(),{new QLabel("<b>General</b>"), m_cbDebug(), m_cbDisplayStartLine()}, LStretch{true}, LMargins{true},QFrame::Box));

        // target
        auto targetDistance = ui::F::gen(ui::L::HB(),{ui::W::txt("Distance (%): "),m_dsbDistancePercentageTarget()}, LStretch{false}, LMargins{false},QFrame::NoFrame);
        auto targetAngle    = ui::F::gen(ui::L::HB(),{ui::W::txt("Angle (°): "),m_dsbAngleTarget()}, LStretch{false}, LMargins{false},QFrame::NoFrame);
        auto targetHeight   = ui::F::gen(ui::L::HB(),{ui::W::txt("Height (m): "),m_dsbHeightTarget()}, LStretch{false}, LMargins{false},QFrame::NoFrame);
        add_widget(ui::F::gen(ui::L::VB(),{new QLabel("<b>Target: </b>"), targetDistance, targetAngle, targetHeight}, LStretch{true}, LMargins{true},QFrame::Box));
        add_sub_part_widget(m_trWorkingZone);
    }

    void init_and_register_widgets() override{

        // general
        m_inputUiElements["debug"] = m_cbDebug.init_widget("Debug", false);
        m_inputUiElements["display_start_line"] = m_cbDisplayStartLine.init_widget("Display start line", true);

        // working zone
        map_sub_part(m_trWorkingZone.init_widget("Working zone transform", "working_transform"));
        m_trWorkingZone.tr.set_rotation_values({0.,0.,0.});
        m_trWorkingZone.tr.set_trans_decimals(3);
        m_trWorkingZone.tr.set_trans_steps({0.001,0.001,0.001});

        // target
        m_inputUiElements["distance_percentage_target"]  = m_dsbDistancePercentageTarget.init_widget(MinV<qreal>{10.}, V<qreal>{80.}, MaxV<qreal>{100.}, StepV<qreal>{0.1}, 1);
        m_inputUiElements["height_target"]               = m_dsbHeightTarget.init_widget(MinV<qreal>{-1.}, V<qreal>{0.}, MaxV<qreal>{1.}, StepV<qreal>{0.01}, 2.);
        m_inputUiElements["angle_target"]                = m_dsbAngleTarget.init_widget(MinV<qreal>{-50.}, V<qreal>{0.0}, MaxV<qreal>{50.}, StepV<qreal>{1.}, 1);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};
}
