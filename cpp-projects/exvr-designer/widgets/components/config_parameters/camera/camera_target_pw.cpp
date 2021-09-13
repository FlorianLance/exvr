
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "camera_target_pw.hpp"

using namespace tool::ex;

void CameraTargetConfigParametersW::insert_widgets(){

    add_widget(ui::W::txt("<b>Action</b>"));
    add_widget(ui::F::gen(ui::L::HB(), {m_moveToTarget(), m_moveBack(), m_doNothing()}, LStretch{true}, LMargins{false},QFrame::NoFrame));

    add_widget(ui::W::txt("<b>Camera</b>"));
    add_widget(ui::F::gen(ui::L::HB(), {m_useNeutralCamera(), m_useEyeCamera()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_pitch(), m_yaw(), m_roll()},LStretch{true}, LMargins{false},QFrame::NoFrame));

    add_widget(ui::W::txt("<b>Progress</b>"));
    add_widget(ui::F::gen(ui::L::HB(), {m_usingTime(), ui::W::txt("Movement duration: "), m_duration()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_usingFactor()}, LStretch{true}, LMargins{false},QFrame::NoFrame));

    add_widget(ui::W::txt("<b>Interpolation</b>"));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Nb intermediary positions (if \"1\"-> instant teleportation): "), m_nbInterPositions()}, LStretch{false}, LMargins{false},QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {m_sphericalInterpolation()}, LStretch{true}, LMargins{false},QFrame::NoFrame));

    add_widget(ui::W::txt("<b>Target</b>"));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Name of the component position to match: "), m_componentName()}, LStretch{false}, LMargins{false}));
    add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("If name empty, use position and rotation below:"), m_targetPos(), m_targetRot()}, LStretch{false}, LMargins{false}));
    add_widget(ui::F::gen(ui::L::HB(), {m_absolute(), m_relatetiveToEye()}, LStretch{true}, LMargins{false}));
    add_widget(&m_curves);

    m_curves.addTab(m_speedCurve(), "Factor curve");
}


void CameraTargetConfigParametersW::init_and_register_widgets(){

    // settings
    add_input_ui(m_duration.init_widget(MinV<qreal>{0}, V<qreal>{5.}, MaxV<qreal>{500.}, StepV<qreal>{0.1}, 2, true));
    add_input_ui(m_sphericalInterpolation.init_widget("Use spherical linear interpolation ", true));
    add_input_ui(m_nbInterPositions.init_widget(MinV<int>{1}, V<int>{200}, MaxV<int>{5000}, StepV<int>{1}, true));

    // axies
    add_input_ui(m_pitch.init_widget("Use pitch", false));
    add_input_ui(m_yaw.init_widget("Use yaw", true));
    add_input_ui(m_roll.init_widget("use roll", false));

    // actions
    add_inputs_ui(
        ExRadioButtonW::init_group_widgets(m_buttonGroup1,
            {&m_moveToTarget, &m_moveBack, &m_doNothing},
            {
                "Move to target",
                "Move back to previous target",
                "Do nothing"
            },
            {true, false, false}
        )
    );

    add_inputs_ui(
        ExRadioButtonW::init_group_widgets(m_buttonGroup3,
            {&m_relatetiveToEye, &m_absolute},
            {
                "Relative to eye",
                "Absolute"
            },
            {false, true}
        )
    );

    // cameras
    add_inputs_ui(
        ExRadioButtonW::init_group_widgets(m_buttonGroup2,
            {&m_useNeutralCamera, &m_useEyeCamera},
            {
                "Use start neutral camera",
                "Use eye camera"
            },
            {true, false}
        )
    );

    // progress
    add_inputs_ui(
        ExRadioButtonW::init_group_widgets(m_buttonGroup4,
            {&m_usingTime, &m_usingFactor},
            {
                "Use elapsed time",
                "Use input factor [0-1]"
            },
            {true, false}
        )
    );

    // move to target
    add_input_ui(m_componentName.init_widget(""));
    DsbSettings s1 = {MinV<qreal>{-10000.}, V<qreal>{0.},MaxV<qreal>{10000.}, StepV<qreal>{0.1}, 3};
    add_input_ui(m_targetPos.init_widget("Position: ", Vector3dSettings{s1,s1,s1}, true));
    add_input_ui(m_targetRot.init_widget("Rotation: ", Vector3dSettings{s1,s1,s1}, true));

    // curves
    add_input_ui(m_speedCurve.init_widget("Factor speed curve"));
    m_speedCurve.minX.w->setEnabled(false);
    m_speedCurve.maxX.w->setEnabled(false);
    m_speedCurve.minY.w->setEnabled(false);
    m_speedCurve.maxY.w->setEnabled(false);
    m_speedCurve.firstY.w->setMinimum(0.);
    m_speedCurve.firstY.w->setMaximum(1.);
    m_speedCurve.lastY.w->setMinimum(0.);
    m_speedCurve.lastY.w->setMaximum(1.);
    m_speedCurve.currentCurveId.w->setEnabled(false);
    m_speedCurve.currentCurveId.w->setValue(0);
}
