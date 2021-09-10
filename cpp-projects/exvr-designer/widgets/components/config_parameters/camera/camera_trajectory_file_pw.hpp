
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

    ExFloatSpinBoxW duration{"duration"};
    ExCheckBoxW useSphericalInterpolation{"spherical_interpolation"};
    ExCheckBoxW inverseOrder{"inverse"};

    ExResourceW trajectoryFile{"trajectory_file"};
    ExSelectColorW startColor{"start_color"};
    ExSelectColorW endColor{"end_color"};
    ExCurveW speed{"speed"};

    void insert_widgets() override{

        add_widget(ui::F::gen(ui::L::HB(), {trajectoryFile()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Trajectory duration: "), duration()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Start color: "), startColor(), ui::W::txt("End color: "), endColor()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {useSphericalInterpolation(), inverseOrder()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));        
        add_widget(speed());
    }

    void init_and_register_widgets() override{

        add_input_ui(trajectoryFile.init_widget(Resource::Type::Text, "Trajectory file"));
        add_input_ui(duration.init_widget(MinV<qreal>{0.}, V<qreal>{3.},MaxV<qreal>{1000.}, StepV<qreal>{0.1}, 2));
        add_input_ui(startColor.init_widget("Choose start color", Qt::red));
        add_input_ui(endColor.init_widget("Choose end color", Qt::blue));
        add_input_ui(useSphericalInterpolation.init_widget("Spherical interpolation", true));
        add_input_ui(inverseOrder.init_widget("Inverse order", false));
        add_input_ui(speed.init_widget("Trajectory speed"));
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

}
