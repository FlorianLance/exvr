
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QGroupBox>
#include <QButtonGroup>
#include <QFileDialog>


// local
#include "config_pw.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_line_edit_w.hpp"
#include "ex_select_color_w.hpp"
#include "ex_curve_w.hpp"

namespace tool::ex {

class CameraTrajectoryFileInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

class CameraTrajectoryFileConfigParametersW : public ConfigParametersW{

public :

    ExFloatSpinBoxW duration;
//    ExCheckBoxW cbAddCameraPosition;
    ExCheckBoxW useSphericalInterpolation;
    ExCheckBoxW inverseOrder;

    ExResourceW trajectoryFile;
    ExSelectColorW startColor;
    ExSelectColorW endColor;
    ExCurveW speed;

    void insert_widgets() override{

        add_widget(ui::F::gen(ui::L::HB(), {trajectoryFile()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Trajectory duration: "), duration()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Start color: "), startColor(), ui::W::txt("End color: "), endColor()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
//        add_widget(ui::F::gen(ui::L::HB(), {cbAddCameraPosition(), cbSphericalInterpolation(), cbInverseOrder()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {useSphericalInterpolation(), inverseOrder()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));        
        add_widget(speed());
    }

    void init_and_register_widgets() override{

        m_inputUiElements["trajectory_file"]         = trajectoryFile.init_widget(Resource::Type::Text, "Trajectory file");
        m_inputUiElements["duration"]                = duration.init_widget(MinV<qreal>{0.}, V<qreal>{3.},MaxV<qreal>{1000.}, StepV<qreal>{0.1}, 2);
        m_inputUiElements["start_color"]             = startColor.init_widget("Choose start color", Qt::red);
        m_inputUiElements["end_color"]               = endColor.init_widget("Choose end color", Qt::blue);
//        m_inputUiElements["add_camera_position"]     = cbAddCameraPosition.init_widget("Add camera position", true);
        m_inputUiElements["spherical_interpolation"] = useSphericalInterpolation.init_widget("Spherical interpolation", true);
        m_inputUiElements["inverse"]                 = inverseOrder.init_widget("Inverse order", false);
        m_inputUiElements["speed"]                   = speed.init_widget("Trajectory speed");
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

}
