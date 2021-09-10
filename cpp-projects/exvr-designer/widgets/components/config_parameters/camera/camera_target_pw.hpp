

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
    ExFloatSpinBoxW m_duration{"duration"};
    ExCheckBoxW m_sphericalInterpolation{"spherical_linear_interpolation"};
    ExSpinBoxW m_nbInterPositions{"nb_inter_pos"};

    ExCheckBoxW m_pitch{"pitch"};
    ExCheckBoxW m_yaw{"yaw"};
    ExCheckBoxW m_roll{"roll"};

    // # choice
    QButtonGroup   m_buttonGroup1;
    ExRadioButtonW m_moveToTarget{"move_to_target"};
    ExRadioButtonW m_moveBack{"move_back"};
    ExRadioButtonW m_doNothing{"do_nothing"};

    QButtonGroup   m_buttonGroup2;
    ExRadioButtonW m_useNeutralCamera {"use_neutral"};
    ExRadioButtonW m_useEyeCamera{"use_eye"};

    // # move to target
    ExLineEditW m_componentName{"target_component"};
    QButtonGroup   m_buttonGroup3;
    ExRadioButtonW m_relatetiveToEye{"relative_to_eye"};
    ExRadioButtonW m_absolute{"absolute"};
    ExVector3dW m_targetPos{"target_pos"};
    ExVector3dW m_targetRot{"target_rot"};

    QButtonGroup   m_buttonGroup4;
    ExRadioButtonW m_usingTime{"use_time"};
    ExRadioButtonW m_usingFactor{"use_factor"};

    // curves
    QTabWidget m_curves;
    ExCurveW m_speedCurve{"speed_curve"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};

}
