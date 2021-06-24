

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "humanoid_controller_pw.hpp"


using namespace tool::ex;

void HumanoidControllerInitConfigParametersW::insert_widgets(){

    auto bundle = ui::F::gen(ui::L::HB(), {humanoidAssetBundle()}, LStretch{false}, LMargins{true}, QFrame::NoFrame);
    auto skin = ui::F::gen(ui::L::HB(), {ui::W::txt("Skin:"), skinColor()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto colors = ui::F::gen(ui::L::HB(), {ui::W::txt("Shirt:"), shirtColor(), ui::W::txt("Pants:"), pantsColor()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    add_widget(
        ui::F::gen(ui::L::VB(), {
            bundle,
            ui::W::horizontal_line(),
            ui::W::txt("Colors"),
            skin,
            colors,
            ui::W::horizontal_line(),
            callStartRoutineOnce(),
            addHmdMesh(),
        },
        LStretch{false}, LMargins{true}, QFrame::Box)
    );
}

void HumanoidControllerInitConfigParametersW::init_and_register_widgets(){
    m_inputUiElements["humanoid"] = humanoidAssetBundle.init_widget(Resource::Type::AssetBundle, "Humanoid asset bundle resource: ");
    QStringList items;
    items << "Warl ivory" << "Sienna" << "Honey" << "Umber" << "Sand" << "Limestone" << "Band" << "Golden"
          << "Pale ivory" << "Beige" << "Almond" << "Espresso" << "Rose beige" << "Amber" << "Bronze" << "Chocolate" << "Original";
    m_inputUiElements["skin_color"] = skinColor.init_widget(items, 16);
    m_inputUiElements["shirt_color"] = shirtColor.init_widget("Choose shirt color to apply on texture", QColor(255,255,255,255));
    m_inputUiElements["pants_color"] = pantsColor.init_widget("Choose Pants color to apply on texture", QColor(255,255,255,255));
    m_inputUiElements["add_hmd_mesh"]    = addHmdMesh.init_widget("Add VR HMD mesh on head:", false);
    m_inputUiElements["only_call_start_routine_once"]    = callStartRoutineOnce.init_widget("Call start_routine only once", false);

}

void HumanoidControllerInitConfigParametersW::create_connections(){
}

void HumanoidControllerInitConfigParametersW::late_update_ui(){}

void HumanoidControllerConfigParametersW::insert_widgets(){

    // tab
    add_widget(tabPositionsW = new QTabWidget());
    tabPositionsW->setTabPosition(QTabWidget::TabPosition::North);
    tabPositionsW->addTab(globalW = new QWidget(), "Global");
    tabPositionsW->addTab(stiffnessW = new QWidget(), "Stiffness");
    tabPositionsW->addTab(spineW = new QWidget(), "Spine");
    tabPositionsW->addTab(armsW = new QWidget(), "Arms");
    tabPositionsW->addTab(legsW = new QWidget(), "Legs");
    tabPositionsW->addTab(leftFingersW = new QWidget(), "L. fingers");
    tabPositionsW->addTab(rightFingersW = new QWidget(), "R. fingers");

    // global
    QVBoxLayout *globalL = nullptr;
    globalW->setLayout(globalL = ui::L::VB());
    globalL->addWidget(ui::F::gen(ui::L::HB(), {enableInverseKinematics(),ui::W::txt("Global IK weight: "), globalIkWeight()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    globalL->addWidget(ui::W::horizontal_line());
    globalL->addWidget(transform.frame);
    globalL->addWidget(ui::F::gen(ui::L::HB(), {moveTransformsToTargets()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    globalL->addWidget(ui::F::gen(ui::L::HB(), {moveEyeCameraToHead()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    globalL->addWidget(ui::W::horizontal_line());
    globalL->addWidget(
        ui::F::gen(ui::L::VB(), {
            updateHeadWithEyeCamera(),
            updateHeadWithRelativeEyeCamera(),
            ui::F::gen(ui::L::HB(), {ui::W::txt("  "), useInputForMovingHeadCameraToRelativeEye()}, LStretch{true}, LMargins{false}, QFrame::NoFrame),
            updateEyeCameraWithHead(),
            doNotMove()
        },
        LStretch{true}, LMargins{false}, QFrame::NoFrame)
    );

    globalL->addWidget(ui::W::horizontal_line());
    globalL->addWidget(ui::F::gen(ui::L::HB(), {headTrackingOffsetPos()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    globalL->addWidget(ui::F::gen(ui::L::HB(), {headTrackingOffsetRot()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    globalL->addWidget(ui::W::horizontal_line());
    globalL->addWidget(ui::F::gen(ui::L::HB(), {displayTargets()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    globalL->addWidget(ui::F::gen(ui::L::VB(), {pitchYawRollRot(), yawRollPitchRot()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    globalL->addStretch();

    // stiffness
    QVBoxLayout *stiffnessL = nullptr;
    stiffnessW->setLayout(stiffnessL = ui::L::VB());
    stiffnessL->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("<b>Determines how much: </b>")}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    stiffnessL->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("... the body will follow the position of the head: "), m_bodyPosStiffness()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    stiffnessL->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("... the body will follow the rotation of the head: "), m_bodyRotStiffness()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    stiffnessL->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("... the chest will rotate to the rotation of the head: "), m_neckStiffness()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    stiffnessL->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("... the pelvis maintain it's animated position: "), m_maintainPelvisPosition()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    stiffnessL->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("Max head rotation angle before turning root: "), m_maxRootAngle()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    stiffnessL->addStretch();

    // spine
    QVBoxLayout *spineL = nullptr;
    spineW->setLayout(spineL = ui::L::VB());
    spineL->addWidget(m_head.frame);
    spineL->addWidget(
        ui::F::gen(ui::L::HB(), {
            ui::W::txt("<b>Head weights</b>"),
            ui::W::txt("position: "), m_headPositionWeight(),
            ui::W::txt("rotation: "), m_headRotationWeight()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
    spineL->addWidget(m_pelvis.frame);
    spineL->addWidget(
        ui::F::gen(ui::L::HB(), {
            ui::W::txt("<b>Pelvis weights</b>"),
            ui::W::txt("position: "), m_pelvisPositionWeight(),
            ui::W::txt("rotation: "), m_pelvisRotationWeight()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
    spineL->addWidget(ui::F::gen(ui::L::HB(), {m_chestGoal(), ui::W::txt("weight: "), m_chestGoalWeight()}, LStretch{true}, LMargins{true}, QFrame::Box));
    spineL->addStretch();

    // arms
    QVBoxLayout *amrsL = nullptr;
    armsW->setLayout(amrsL = ui::L::VB());
    amrsL->addWidget(m_leftArm.frame);
    amrsL->addWidget(
        ui::F::gen(ui::L::HB(), {
            ui::W::txt("<b>Left arm weights</b>"),
            ui::W::txt("position: "), m_leftArmPositionWeight(),
            ui::W::txt("rotation: "), m_leftArmRotationWeight()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
    amrsL->addWidget(
        ui::F::gen(ui::L::HB(), {
            ui::W::txt("Left shoulder rot weight: "), m_leftShoulderRotationWeight(),
            ui::W::txt("Left swivel rot offset: "), m_leftSwivelRotationOffset()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );

    amrsL->addWidget(
        ui::F::gen(ui::L::HB(), {
            m_leftArmBend(),
            ui::W::txt("weight: "), m_leftArmBendWeight()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );

    amrsL->addWidget(m_rightArm.frame);
    amrsL->addWidget(
        ui::F::gen(ui::L::HB(), {
            ui::W::txt("<b>Right arm weights</b>"),
            ui::W::txt("position: "), m_rightArmPositionWeight(),
            ui::W::txt("rotation: "), m_rightArmRotationWeight()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
    amrsL->addWidget(
        ui::F::gen(ui::L::HB(), {
            ui::W::txt("Right shoulder rot weight: "), m_rightShoulderRotationWeight(),
            ui::W::txt("Right swivel rot offset: "), m_rightSwivelRotationOffset()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );

    amrsL->addWidget(
        ui::F::gen(ui::L::HB(), {
            m_rightArmBend(),
            ui::W::txt("weight: "), m_rightArmBendWeight()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
    amrsL->addStretch();

    // legs
    QVBoxLayout *legsL = nullptr;
    legsW->setLayout(legsL = ui::L::VB());
    legsL->addWidget(m_leftLeg.frame);
    legsL->addWidget(
        ui::F::gen(ui::L::HB(), {
            ui::W::txt("<b>Left leg weights</b>"),
            ui::W::txt("position: "), m_leftLegPositionWeight(),
            ui::W::txt("rotation: "), m_leftLegRotationWeight()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
    legsL->addWidget(
        ui::F::gen(ui::L::HB(), {
            m_leftLegBend(),
            ui::W::txt("weight: "), m_leftLegBendWeight()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );

    legsL->addWidget(m_rightLeg.frame);
    legsL->addWidget(
        ui::F::gen(ui::L::HB(), {
            ui::W::txt("<b>Right leg weights</b>"),
            ui::W::txt("position: "), m_rightLegPositionWeight(),
            ui::W::txt("rotation: "), m_rightLegRotationWeight()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
    legsL->addWidget(
        ui::F::gen(ui::L::HB(), {
            m_rightLegBend(),
            ui::W::txt("weight: "), m_rightLegBendWeight()
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
    legsL->addStretch();

    // left fingers
    QVBoxLayout *leftFingersL = nullptr;
    leftFingersW->setLayout(leftFingersL = ui::L::VB());

    auto leftIndex = ui::F::gen(ui::L::VB(), {
        m_leftIndexRot1(),
        m_leftIndexRot2(),
        m_leftIndexRot3()
    }, LStretch{true}, LMargins{false}, QFrame::NoFrame);

    auto leftMiddle = ui::F::gen(ui::L::VB(), {
        m_leftMiddleRot1(),
        m_leftMiddleRot2(),
        m_leftMiddleRot3()
    }, LStretch{true}, LMargins{false}, QFrame::NoFrame);

    auto leftRing = ui::F::gen(ui::L::VB(), {
        m_leftRingRot1(),
        m_leftRingRot2(),
        m_leftRingRot3()
    }, LStretch{true}, LMargins{false}, QFrame::NoFrame);

    auto leftPinky = ui::F::gen(ui::L::VB(), {
        m_leftPinkyRot1(),
        m_leftPinkyRot2(),
        m_leftPinkyRot3()
    }, LStretch{true}, LMargins{false}, QFrame::NoFrame);

    auto leftThumb = ui::F::gen(ui::L::VB(), {
        m_leftThumbRot1(),
        m_leftThumbRot2(),
        m_leftThumbRot3()
    }, LStretch{true}, LMargins{false}, QFrame::NoFrame);

    leftFingersL->addWidget(
        ui::F::gen(ui::L::VB(), {
            ui::W::txt("<b>Left fingers rotations: </b>"),
            leftIndex,
            ui::W::horizontal_line(),
            leftMiddle,
            ui::W::horizontal_line(),
            leftRing,
            ui::W::horizontal_line(),
            leftPinky,
            ui::W::horizontal_line(),
            leftThumb,
            ui::F::gen(ui::L::HB(), {
               ui::W::txt("<b>Weight: </b>"), m_leftFingersWeight()
            },
            LStretch{true}, LMargins{false}, QFrame::NoFrame)
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );

    // right fingers
    QVBoxLayout *rightFingersL = nullptr;
    rightFingersW->setLayout(rightFingersL = ui::L::VB());

    auto rightIndex = ui::F::gen(ui::L::VB(), {
        m_rightIndexRot1(),
        m_rightIndexRot2(),
        m_rightIndexRot3()
    }, LStretch{true}, LMargins{false}, QFrame::NoFrame);

    auto rightMiddle = ui::F::gen(ui::L::VB(), {
        m_rightMiddleRot1(),
        m_rightMiddleRot2(),
        m_rightMiddleRot3()
    }, LStretch{true}, LMargins{false}, QFrame::NoFrame);

    auto rightRing = ui::F::gen(ui::L::VB(), {
        m_rightRingRot1(),
        m_rightRingRot2(),
        m_rightRingRot3()
    }, LStretch{true}, LMargins{false}, QFrame::NoFrame);

    auto rightPinky = ui::F::gen(ui::L::VB(), {
        m_rightPinkyRot1(),
        m_rightPinkyRot2(),
        m_rightPinkyRot3()
    }, LStretch{true}, LMargins{false}, QFrame::NoFrame);

    auto rightThumb = ui::F::gen(ui::L::VB(), {
        m_rightThumbRot1(),
        m_rightThumbRot2(),
        m_rightThumbRot3()
    }, LStretch{true}, LMargins{false}, QFrame::NoFrame);

    rightFingersL->addWidget(
        ui::F::gen(ui::L::VB(), {
            ui::W::txt("<b>Right fingers rotations: </b>"),
            rightIndex,
            ui::W::horizontal_line(),
            rightMiddle,
            ui::W::horizontal_line(),
            rightRing,
            ui::W::horizontal_line(),
            rightPinky,
            ui::W::horizontal_line(),
            rightThumb,
            ui::F::gen(ui::L::HB(), {
               ui::W::txt("<b>Weight: </b>"),m_rightFingersWeight()
            },
            LStretch{true}, LMargins{false}, QFrame::NoFrame)
        },
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
}

void HumanoidControllerConfigParametersW::init_and_register_widgets(){

    map_sub_part(transform.init_widget());
    m_inputUiElements["display_targets"]                       = displayTargets.init_widget("Display targets", false);
    m_inputUiElements["move_transforms_to_targets"]            = moveTransformsToTargets.init_widget("Move avatar to fit targets (called at routine start)", true);
    m_inputUiElements["move_eye_camera_to_head"]               = moveEyeCameraToHead.init_widget("Move eye camera to fit avatar head with neutral position (called at routine start)", false);
    m_inputUiElements["update_head_with_eye_camera"]           = updateHeadWithEyeCamera.init_widget("Update avatar head with eye camera (called every frame)", false);
    m_inputUiElements["update_head_with_relative_eye_camera"]  = updateHeadWithRelativeEyeCamera.init_widget("Update avatar head with relative eye camera (called every frame)", false);
    m_inputUiElements["update_eye_camera_with_head"]           = updateEyeCameraWithHead.init_widget("Update eye camera with avatar head (called every frame)", false);
    m_inputUiElements["use_input_connection"]                  = useInputForMovingHeadCameraToRelativeEye.init_widget("Use input connections instead of eye camera", false);
    m_inputUiElements["do_not_move"]                           = doNotMove.init_widget("Do not move head/eye camera", true);
    m_inputUiElements["pitch_yaw_roll"]                        = pitchYawRollRot.init_widget("Use Pitch/Yaw/Roll axis order", true);
    m_inputUiElements["yaw_roll_pitch"]                        = yawRollPitchRot.init_widget("Use Yaw/Roll/Pitch axis order", false);

    DsbSettings offsetS{MinV<qreal>{-2.},V<qreal>{0.},MaxV<qreal>{2.},StepV<qreal>{0.01}, 2};
    m_inputUiElements["head_tracking_offset_pos"] = headTrackingOffsetPos.init_widget("Head offset position:", Vector3dSettings{offsetS,offsetS,offsetS});
    headTrackingOffsetPos.x.w->setValue(0);
    headTrackingOffsetPos.y.w->setValue(0.1);
    headTrackingOffsetPos.z.w->setValue(0.1);

    DsbSettings offsetRot{MinV<qreal>{-180.},V<qreal>{0.},MaxV<qreal>{180.},StepV<qreal>{0.1}, 2};
    Vector3dSettings offsetVecRot = {offsetRot,offsetRot,offsetRot};
    m_inputUiElements["head_tracking_offset_rot"] = headTrackingOffsetRot.init_widget("Head offset rotation:", offsetVecRot);

    map_sub_part(m_head.init_widget("Head target transform","head_transform"));
    m_head.tr.set_enable_state(true,true,false);
    map_sub_part(m_pelvis.init_widget("Pelvis target transform","pelvis_transform"));
    m_pelvis.tr.set_enable_state(true,true,false);
    map_sub_part(m_leftArm.init_widget("Left arm target transform","left_arm_transform"));
    m_leftArm.tr.set_enable_state(true,true,false);
    map_sub_part(m_rightArm.init_widget("Right arm target transform","right_arm_transform"));
    m_rightArm.tr.set_enable_state(true,true,false);
    map_sub_part(m_leftLeg.init_widget("Left leg target transform","left_leg_transform"));
    m_leftLeg.tr.set_enable_state(true,true,false);
    map_sub_part(m_rightLeg.init_widget("Right leg target transform","right_leg_transform"));
    m_rightLeg.tr.set_enable_state(true,true,false);

    m_inputUiElements["chest"]                  = m_chestGoal.init_widget("<b>Chest goal</b>"); // translation
    m_inputUiElements["left_arm_bend_goal"]     = m_leftArmBend.init_widget("<b>Left arm bend goal</b>"); // translation
    m_inputUiElements["right_arm_bend_goal"]    = m_rightArmBend.init_widget("<b>Right arm bend goal</b>"); // translation
    m_inputUiElements["left_leg_bend_goal"]     = m_leftLegBend.init_widget("<b>Left leg bend goal</b>"); // translation
    m_inputUiElements["right_leg_bend_goal"]    = m_rightLegBend.init_widget("<b>Right leg bend goal</b>"); // translation

    m_inputUiElements["left_swivel_rotation_offset"]   = m_leftSwivelRotationOffset.init_widget(offsetRot);
    m_inputUiElements["right_swivel_rotation_offset"]  = m_rightSwivelRotationOffset.init_widget(offsetRot);

    DsbSettings factorS{MinV<qreal>{0.},V<qreal>{1.},MaxV<qreal>{1.},StepV<qreal>{0.05}, 2};

    m_inputUiElements["left_shoulder_rotation_weight"]  = m_leftShoulderRotationWeight.init_widget(factorS);
    m_inputUiElements["right_shoulder_rotation_weight"] = m_rightShoulderRotationWeight.init_widget(factorS);

    m_inputUiElements["enable_ik"] = enableInverseKinematics.init_widget("Enable inverser kinematics", true);
    m_inputUiElements["global_ik_w"] = globalIkWeight.init_widget(factorS);

    m_inputUiElements["head_rot_w"] = m_headRotationWeight.init_widget(factorS);
    m_inputUiElements["head_pos_w"] = m_headPositionWeight.init_widget(factorS);
    m_inputUiElements["pelvis_rot_w"] = m_pelvisRotationWeight.init_widget(factorS);
    m_inputUiElements["pelvis_pos_w"] = m_pelvisPositionWeight.init_widget(factorS);
    m_inputUiElements["chest_goal_w"] = m_chestGoalWeight.init_widget(factorS);
    m_chestGoalWeight.w->setValue(0.);

    m_inputUiElements["body_pos_stiffness"]         = m_bodyPosStiffness.init_widget(DsbSettings{MinV<qreal>{0.},V<qreal>{0.55},MaxV<qreal>{1.},StepV<qreal>{0.01}, 2});
    m_inputUiElements["body_rot_stiffness"]         = m_bodyRotStiffness.init_widget(DsbSettings{MinV<qreal>{0.},V<qreal>{0.1},MaxV<qreal>{1.},StepV<qreal>{0.01}, 2});
    m_inputUiElements["neck_stiffness"]             = m_neckStiffness.init_widget(DsbSettings{MinV<qreal>{0.},V<qreal>{0.2},MaxV<qreal>{1.},StepV<qreal>{0.01}, 2});
    m_inputUiElements["maintain_pelvis_position"]   = m_maintainPelvisPosition.init_widget(DsbSettings{MinV<qreal>{0.},V<qreal>{0.2},MaxV<qreal>{1.},StepV<qreal>{0.01}, 2});
    m_inputUiElements["max_root_angle"]             = m_maxRootAngle.init_widget(DsbSettings{MinV<qreal>{0.},V<qreal>{25.},MaxV<qreal>{180.},StepV<qreal>{0.1}, 2});

    m_inputUiElements["left_leg_rot_w"] = m_leftLegRotationWeight.init_widget(factorS);
    m_inputUiElements["left_leg_pos_w"] = m_leftLegPositionWeight.init_widget(factorS);
    m_inputUiElements["left_leg_bend_w"] = m_leftLegBendWeight.init_widget(factorS);
    m_leftLegBendWeight.w->setValue(0.);
    m_inputUiElements["right_leg_rot_w"] = m_rightLegRotationWeight.init_widget(factorS);
    m_inputUiElements["right_leg_pos_w"] = m_rightLegPositionWeight.init_widget(factorS);
    m_inputUiElements["right_leg_bend_w"] = m_rightLegBendWeight.init_widget(factorS);
    m_rightLegBendWeight.w->setValue(0.);

    m_inputUiElements["left_arm_rot_w"] = m_leftArmRotationWeight.init_widget(factorS);
    m_inputUiElements["left_arm_pos_w"] = m_leftArmPositionWeight.init_widget(factorS);
    m_inputUiElements["left_arm_bend_w"] = m_leftArmBendWeight.init_widget(factorS);
    m_leftArmBendWeight.w->setValue(0.);
    m_inputUiElements["right_arm_rot_w"] = m_rightArmRotationWeight.init_widget(factorS);
    m_inputUiElements["right_arm_pos_w"] = m_rightArmPositionWeight.init_widget(factorS);
    m_inputUiElements["right_arm_bend_w"] = m_rightArmBendWeight.init_widget(factorS);
    m_rightArmBendWeight.w->setValue(0.);

    m_inputUiElements["left_hand_index_1"] = m_leftIndexRot1.init_widget("<b>Index</b> bone 1:", offsetVecRot);
    m_inputUiElements["left_hand_index_2"] = m_leftIndexRot2.init_widget("<b>Index</b> bone 2:", offsetVecRot);
    m_inputUiElements["left_hand_index_3"] = m_leftIndexRot3.init_widget("<b>Index</b> bone 3:", offsetVecRot);
    m_leftIndexRot1.set_enable_state({true,false,true});
    m_leftIndexRot2.set_enable_state({true,false,false});
    m_leftIndexRot3.set_enable_state({true,false,false});

    m_inputUiElements["left_hand_middle_1"] = m_leftMiddleRot1.init_widget("<b>Middle</b> bone 1: ", offsetVecRot);
    m_inputUiElements["left_hand_middle_2"] = m_leftMiddleRot2.init_widget("<b>Middle</b> bone 2: ", offsetVecRot);
    m_inputUiElements["left_hand_middle_3"] = m_leftMiddleRot3.init_widget("<b>Middle</b> bone 3: ", offsetVecRot);
    m_leftMiddleRot1.set_enable_state({true,false,true});
    m_leftMiddleRot2.set_enable_state({true,false,false});
    m_leftMiddleRot3.set_enable_state({true,false,false});

    m_inputUiElements["left_hand_ring_1"] = m_leftRingRot1.init_widget("<b>Ring</b> bone 1: ", offsetVecRot);
    m_inputUiElements["left_hand_ring_2"] = m_leftRingRot2.init_widget("<b>Ring</b> bone 2: ", offsetVecRot);
    m_inputUiElements["left_hand_ring_3"] = m_leftRingRot3.init_widget("<b>Ring</b> bone 3: ", offsetVecRot);
    m_leftRingRot1.set_enable_state({true,false,true});
    m_leftRingRot2.set_enable_state({true,false,false});
    m_leftRingRot3.set_enable_state({true,false,false});

    m_inputUiElements["left_hand_pinky_1"] = m_leftPinkyRot1.init_widget("<b>Pinky</b> bone 1: ", offsetVecRot);
    m_inputUiElements["left_hand_pinky_2"] = m_leftPinkyRot2.init_widget("<b>Pinky</b> bone 2: ", offsetVecRot);
    m_inputUiElements["left_hand_pinky_3"] = m_leftPinkyRot3.init_widget("<b>Pinky</b> bone 3: ", offsetVecRot);
    m_leftPinkyRot1.set_enable_state({true,false,true});
    m_leftPinkyRot2.set_enable_state({true,false,false});
    m_leftPinkyRot3.set_enable_state({true,false,false});

    m_inputUiElements["left_hand_thumb_1"] = m_leftThumbRot1.init_widget("<b>Thumb</b> bone 1: ", offsetVecRot);
    m_inputUiElements["left_hand_thumb_2"] = m_leftThumbRot2.init_widget("<b>Thumb</b> bone 2: ", offsetVecRot);
    m_inputUiElements["left_hand_thumb_3"] = m_leftThumbRot3.init_widget("<b>Thumb</b> bone 3: ", offsetVecRot);
    m_leftThumbRot1.set_enable_state({true,false,true});
    m_leftThumbRot2.set_enable_state({true,false,false});
    m_leftThumbRot3.set_enable_state({true,false,false});

    m_inputUiElements["right_hand_index_1"] = m_rightIndexRot1.init_widget("<b>Index</b> bone 1: ", offsetVecRot);
    m_inputUiElements["right_hand_index_2"] = m_rightIndexRot2.init_widget("<b>Index</b> bone 2: ", offsetVecRot);
    m_inputUiElements["right_hand_index_3"] = m_rightIndexRot3.init_widget("<b>Index</b> bone 3: ", offsetVecRot);
    m_rightIndexRot1.set_enable_state({true,false,true});
    m_rightIndexRot2.set_enable_state({true,false,false});
    m_rightIndexRot3.set_enable_state({true,false,false});

    m_inputUiElements["right_hand_middle_1"] = m_rightMiddleRot1.init_widget("<b>Middle</b> bone 1: ", offsetVecRot);
    m_inputUiElements["right_hand_middle_2"] = m_rightMiddleRot2.init_widget("<b>Middle</b> bone 2: ", offsetVecRot);
    m_inputUiElements["right_hand_middle_3"] = m_rightMiddleRot3.init_widget("<b>Middle</b> bone 3: ", offsetVecRot);
    m_rightMiddleRot1.set_enable_state({true,false,true});
    m_rightMiddleRot2.set_enable_state({true,false,false});
    m_rightMiddleRot3.set_enable_state({true,false,false});

    m_inputUiElements["right_hand_ring_1"] = m_rightRingRot1.init_widget("<b>Ring</b> bone 1: ", offsetVecRot);
    m_inputUiElements["right_hand_ring_2"] = m_rightRingRot2.init_widget("<b>Ring</b> bone 2: ", offsetVecRot);
    m_inputUiElements["right_hand_ring_3"] = m_rightRingRot3.init_widget("<b>Ring</b> bone 3: ", offsetVecRot);
    m_rightRingRot1.set_enable_state({true,false,true});
    m_rightRingRot2.set_enable_state({true,false,false});
    m_rightRingRot3.set_enable_state({true,false,false});

    m_inputUiElements["right_hand_pinky_1"] = m_rightPinkyRot1.init_widget("<b>Pinky</b> bone 1: ", offsetVecRot);
    m_inputUiElements["right_hand_pinky_2"] = m_rightPinkyRot2.init_widget("<b>Pinky</b> bone 2: ", offsetVecRot);
    m_inputUiElements["right_hand_pinky_3"] = m_rightPinkyRot3.init_widget("<b>Pinky</b> bone 3: ", offsetVecRot);
    m_rightPinkyRot1.set_enable_state({true,false,true});
    m_rightPinkyRot2.set_enable_state({true,false,false});
    m_rightPinkyRot3.set_enable_state({true,false,false});

    m_inputUiElements["right_hand_thumb_1"] = m_rightThumbRot1.init_widget("<b>Thumb</b> bone 1: ", offsetVecRot);
    m_inputUiElements["right_hand_thumb_2"] = m_rightThumbRot2.init_widget("<b>Thumb</b> bone 2: ", offsetVecRot);
    m_inputUiElements["right_hand_thumb_3"] = m_rightThumbRot3.init_widget("<b>Thumb</b> bone 3: ", offsetVecRot);
    m_rightThumbRot1.set_enable_state({true,false,true});
    m_rightThumbRot2.set_enable_state({true,false,false});
    m_rightThumbRot3.set_enable_state({true,false,false});


    m_inputUiElements["left_fingers_w"]     = m_leftFingersWeight.init_widget(factorS);
    m_inputUiElements["right_fingers_w"]    = m_rightFingersWeight.init_widget(factorS);
}

void HumanoidControllerConfigParametersW::create_connections(){

    connect(updateHeadWithEyeCamera.w.get(), &QRadioButton::clicked, this, [&]{
        useInputForMovingHeadCameraToRelativeEye.w->setEnabled(updateHeadWithRelativeEyeCamera.w->isChecked());

    });
    connect(updateHeadWithRelativeEyeCamera.w.get(), &QRadioButton::clicked, this, [&]{
        useInputForMovingHeadCameraToRelativeEye.w->setEnabled(updateHeadWithRelativeEyeCamera.w->isChecked());

    });
    connect(doNotMove.w.get(), &QRadioButton::clicked, this, [&]{
        useInputForMovingHeadCameraToRelativeEye.w->setEnabled(updateHeadWithRelativeEyeCamera.w->isChecked());

    });
}

void HumanoidControllerConfigParametersW::late_update_ui(){
    useInputForMovingHeadCameraToRelativeEye.w->setEnabled(updateHeadWithRelativeEyeCamera.w->isChecked());
}
