
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "camera_target_pw.hpp"

using namespace tool::ex;

void CameraTargetConfigParametersW::insert_widgets(){

    m_buttonGroup1.addButton(m_moveToTarget());
    m_buttonGroup1.addButton(m_moveBack());
    m_buttonGroup1.addButton(m_doNothing());

    m_buttonGroup2.addButton(m_useNeutralCamera());
    m_buttonGroup2.addButton(m_useEyeCamera());

    m_buttonGroup3.addButton(m_relatetiveToEye());
    m_buttonGroup3.addButton(m_absolute());

    m_buttonGroup4.addButton(m_usingTime());
    m_buttonGroup4.addButton(m_usingFactor());

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

    add_widget(ui::W::txt("<b>Speed</b>"));
    m_curves.addTab(m_speedCurve(), "Factor curve");
}

void CameraTargetConfigParametersW::init_and_register_widgets(){

    // settings
    m_inputUiElements["duration"]                       = m_duration.init_widget(MinV<qreal>{0}, V<qreal>{5.}, MaxV<qreal>{500.}, StepV<qreal>{0.1}, 2, true);
    m_inputUiElements["spherical_linear_interpolation"] = m_sphericalInterpolation.init_widget("Use spherical linear interpolation ", true);
    m_inputUiElements["nb_inter_pos"]                   = m_nbInterPositions.init_widget(MinV<int>{1}, V<int>{200}, MaxV<int>{5000}, StepV<int>{1}, true);

    // axies
    m_inputUiElements["pitch"]  = m_pitch.init_widget("Use pitch", false);
    m_inputUiElements["yaw"]    = m_yaw.init_widget("Use yaw", true);
    m_inputUiElements["roll"]   = m_roll.init_widget("use roll", false);

    // actions
    m_inputUiElements["move_to_target"]  = m_moveToTarget.init_widget("Move to target", true);
    m_inputUiElements["move_back"]       = m_moveBack.init_widget("Move back to previous target", false);
    m_inputUiElements["do_nothing"]      = m_doNothing.init_widget("Do nothing", false);
    m_inputUiElements["relative_to_eye"] = m_relatetiveToEye.init_widget("Relative to eye", false);
    m_inputUiElements["absolute"]        = m_absolute.init_widget("Absolute", true);

    // cameras
    m_inputUiElements["use_neutral"]    = m_useNeutralCamera.init_widget("Use start neutral camera", true);
    m_inputUiElements["use_eye"]        = m_useEyeCamera.init_widget("Use eye camera", false);

    // progress
    m_inputUiElements["use_time"]    = m_usingTime.init_widget("Use elapsed time", true);
    m_inputUiElements["use_factor"]  = m_usingFactor.init_widget("Use input factor [0-1]", false);

    // move to target
    m_inputUiElements["target_component"] = m_componentName.init_widget("");
    DsbSettings s1 = {MinV<qreal>{-10000.}, V<qreal>{0.},MaxV<qreal>{10000.}, StepV<qreal>{0.1}, 3};
    m_inputUiElements["target_pos"]       = m_targetPos.init_widget("Position: ", Vector3dSettings{s1,s1,s1}, true);
    m_inputUiElements["target_rot"]       = m_targetRot.init_widget("Rotation: ", Vector3dSettings{s1,s1,s1}, true);

    // curves
    m_inputUiElements["speed_curve"] = m_speedCurve.init_widget("Factor speed curve");
    m_speedCurve.minX.w->setEnabled(false);
    m_speedCurve.maxX.w->setEnabled(false);
    m_speedCurve.minY.w->setEnabled(false);
    m_speedCurve.maxY.w->setEnabled(false);
    m_speedCurve.firstY.w->setMinimum(0.);
    m_speedCurve.firstY.w->setMaximum(1.);
    m_speedCurve.lastY.w->setMinimum(0.);
    m_speedCurve.lastY.w->setMaximum(1.);
}
