

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

#include <QGroupBox>
#include <QButtonGroup>

// local
#include "config_pw.hpp"
#include "ex_radio_button_w.hpp"
#include "ex_line_edit_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_curve_w.hpp"

namespace tool::ex {

class CameraTargetInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};


class CameraTargetConfigParametersW : public ConfigParametersW{

public :

    // settings
    ExFloatSpinBoxW m_duration;
    ExCheckBoxW m_sphericalInterpolation;    
    ExSpinBoxW m_nbInterPositions;

    ExCheckBoxW m_pitch;
    ExCheckBoxW m_yaw;
    ExCheckBoxW m_roll;

    // # choice
    QButtonGroup   m_buttonGroup1;
    ExRadioButtonW m_moveToTarget;
    ExRadioButtonW m_moveBack;
    ExRadioButtonW m_doNothing;

    QButtonGroup   m_buttonGroup2;
    ExRadioButtonW m_useNeutralCamera;
    ExRadioButtonW m_useEyeCamera;

    // # move to target
    ExLineEditW m_componentName;
    QButtonGroup   m_buttonGroup3;
    ExRadioButtonW m_relatetiveToEye;
    ExRadioButtonW m_absolute;
    ExVector3dW m_targetPos;
    ExVector3dW m_targetRot;

    QButtonGroup   m_buttonGroup4;
    ExRadioButtonW m_usingTime;
    ExRadioButtonW m_usingFactor;

    // curves
    QTabWidget m_curves;
    ExCurveW m_speedCurve;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};

}
