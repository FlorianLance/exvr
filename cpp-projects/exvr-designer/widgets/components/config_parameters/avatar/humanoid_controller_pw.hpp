
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// local
#include "config_pw.hpp"
#include "path_utility.hpp"
#include "ex_double_spin_box_w.hpp"
#include "ex_pushbutton_w.hpp"
#include "ex_components_list_w.hpp"
#include "ex_component_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_combo_box_index_w.hpp"

namespace tool::ex {

class HumanoidControllerInitConfigParametersW : public ConfigParametersW{

private:

    ExResourceW humanoidAssetBundle;
    ExComboBoxIndexW skinColor;
    ExSelectColorW shirtColor;
    ExSelectColorW pantsColor;
    ExCheckBoxW addHmdMesh;
    ExCheckBoxW callStartRoutineOnce;

public:

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

class HumanoidControllerConfigParametersW : public ConfigParametersW{

private:

    QTabWidget *tabPositionsW = nullptr;
    QWidget *globalW = nullptr;
    QWidget *stiffnessW = nullptr;
    QWidget *spineW = nullptr;
    QWidget *armsW = nullptr;
    QWidget *legsW = nullptr;
    QWidget *leftFingersW = nullptr;
    QWidget *rightFingersW = nullptr;

    // global
    ExCheckBoxW enableInverseKinematics;
    DefaultTransformSubPart transform;
    ExCheckBoxW displayTargets;
    ExCheckBoxW moveEyeCameraToHead;
    ExCheckBoxW pitch;
    ExCheckBoxW yaw;
    ExCheckBoxW roll;

    ExCheckBoxW moveTransformsToTargets;
    ExRadioButtonW updateHeadWithEyeCamera;
    ExRadioButtonW updateHeadWithRelativeEyeCamera;
    ExRadioButtonW updateEyeCameraWithHead;
    ExCheckBoxW useInputForMovingHeadCameraToRelativeEye;
    ExRadioButtonW doNotMove;
    ExFloatSpinBoxW globalIkWeight;
    ExVector3dW headTrackingOffsetPos;
    ExVector3dW headTrackingOffsetRot;

    ExRadioButtonW pitchYawRollRot;
    ExRadioButtonW yawRollPitchRot;

    // spine
    ExFloatSpinBoxW m_headRotationWeight;
    ExFloatSpinBoxW m_headPositionWeight;
    ExFloatSpinBoxW m_pelvisRotationWeight;
    ExFloatSpinBoxW m_pelvisPositionWeight;
    ExFloatSpinBoxW m_chestGoalWeight;
    ExVector3dW m_chestGoal;
    DefaultTransformSubPart m_head;
    DefaultTransformSubPart m_pelvis;

    ExFloatSpinBoxW m_bodyPosStiffness;         //  Range(0 1 0.55) Determines how much the body will follow the position of the head.
    ExFloatSpinBoxW m_bodyRotStiffness;         //  Range(0 1 0.1) Determines how much the body will follow the rotation of the head.
    ExFloatSpinBoxW m_neckStiffness;            // Range(0 1 0.2)  Determines how much the chest will rotate to the rotation of the head.
    ExFloatSpinBoxW m_maintainPelvisPosition;   // Range(0 1 0.2)  How much will the pelvis maintain it's animated position?
    ExFloatSpinBoxW m_maxRootAngle;             // Range(0 180 25) Will automatically rotate the root of the character if the head target has turned past this angle.

    // arms
    ExFloatSpinBoxW m_leftArmRotationWeight;
    ExFloatSpinBoxW m_leftArmPositionWeight;
    ExFloatSpinBoxW m_rightArmRotationWeight;
    ExFloatSpinBoxW m_rightArmPositionWeight;
    ExFloatSpinBoxW m_leftArmBendWeight;
    ExFloatSpinBoxW m_rightArmBendWeight;
    ExVector3dW m_leftArmBend;
    ExVector3dW m_rightArmBend;
    DefaultTransformSubPart m_leftArm;
    DefaultTransformSubPart m_rightArm;

    ExFloatSpinBoxW m_leftShoulderRotationWeight;
    ExFloatSpinBoxW m_rightShoulderRotationWeight;
    ExFloatSpinBoxW m_leftSwivelRotationOffset;
    ExFloatSpinBoxW m_rightSwivelRotationOffset;

    // legs
    ExFloatSpinBoxW m_leftLegRotationWeight;
    ExFloatSpinBoxW m_leftLegPositionWeight;
    ExFloatSpinBoxW m_rightLegRotationWeight;
    ExFloatSpinBoxW m_rightLegPositionWeight;
    ExFloatSpinBoxW m_leftLegBendWeight;
    ExFloatSpinBoxW m_rightLegBendWeight;
    ExVector3dW m_leftLegBend;
    ExVector3dW m_rightLegBend;
    DefaultTransformSubPart m_leftLeg;
    DefaultTransformSubPart m_rightLeg;

    // fingers
    ExFloatSpinBoxW m_leftFingersWeight;
    ExVector3dW m_leftIndexRot1;
    ExVector3dW m_leftIndexRot2;
    ExVector3dW m_leftIndexRot3;
    ExVector3dW m_leftMiddleRot1;
    ExVector3dW m_leftMiddleRot2;
    ExVector3dW m_leftMiddleRot3;
    ExVector3dW m_leftRingRot1;
    ExVector3dW m_leftRingRot2;
    ExVector3dW m_leftRingRot3;
    ExVector3dW m_leftPinkyRot1;
    ExVector3dW m_leftPinkyRot2;
    ExVector3dW m_leftPinkyRot3;
    ExVector3dW m_leftThumbRot1;
    ExVector3dW m_leftThumbRot2;
    ExVector3dW m_leftThumbRot3;
    ExFloatSpinBoxW m_rightFingersWeight;
    ExVector3dW m_rightIndexRot1;
    ExVector3dW m_rightIndexRot2;
    ExVector3dW m_rightIndexRot3;
    ExVector3dW m_rightMiddleRot1;
    ExVector3dW m_rightMiddleRot2;
    ExVector3dW m_rightMiddleRot3;
    ExVector3dW m_rightRingRot1;
    ExVector3dW m_rightRingRot2;
    ExVector3dW m_rightRingRot3;
    ExVector3dW m_rightPinkyRot1;
    ExVector3dW m_rightPinkyRot2;
    ExVector3dW m_rightPinkyRot3;
    ExVector3dW m_rightThumbRot1;
    ExVector3dW m_rightThumbRot2;
    ExVector3dW m_rightThumbRot3;


public :

    void insert_widgets() override;

    void init_and_register_widgets() override;

    void create_connections() override;
    void late_update_ui() override;
};

}

