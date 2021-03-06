
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "camera_pw.hpp"

using namespace tool::ex;

void CameraInitConfigParametersW::insert_widgets(){

    add_widget(ui::W::txt("<b>Initialization camera</b>"));

    add_widget(
        ui::F::gen(ui::L::VB(), {
            ui::W::txt("<b>Apply to:</b>"),
            useNeutral(),
            useEye(),
            ui::W::horizontal_line(),
            ui::W::txt("<b>Apply when:</b>"),
            cbStartExperiment(),
            ui::W::horizontal_line(),
            ui::W::txt("<b>Values:</b>"),
            position(),
            rotation()
        },
        LStretch{false}, LMargins{true}, QFrame::Box)
    );
}

void CameraInitConfigParametersW::init_and_register_widgets(){

    add_inputs_ui(
        ExRadioButtonW::init_group_widgets(group1,
            {&useNeutral, &useEye},
            {
                "start neutral camera",
                "eye camera",
            },
            {true, false}
        )
    );

    add_input_ui(cbStartExperiment.init_widget("Start experiment (init cam)", true, true));

    DsbSettings offsetPos{MinV<qreal>{-1000.},V<qreal>{0.},MaxV<qreal>{1000.},StepV<qreal>{0.01}, 3};
    DsbSettings offsetRot{MinV<qreal>{-360.},V<qreal>{0.},MaxV<qreal>{360.},StepV<qreal>{0.1}, 3};
    add_input_ui(position.init_widget("position: ", {offsetPos,offsetPos,offsetPos}));
    add_input_ui(rotation.init_widget("rotation: ", {offsetRot,offsetRot,offsetRot}));
}

void CameraInitConfigParametersW::create_connections(){}

void CameraInitConfigParametersW::late_update_ui(){}

void CameraConfigParametersW::insert_widgets(){

    add_widget(ui::W::txt("<b>Config camera</b>"));


    add_widget(
        ui::F::gen(ui::L::VB(), {
            ui::W::txt("<b>Apply to:</b>"),
            useNeutral(),
            useEye(),
            ui::W::horizontal_line(),
            ui::W::txt("<b>Apply when:</b>"),
            cbStartRoutine(),
            cbUpdateOn(),
            ui::W::txt("<b>Values:</b>"),
            position(),
            rotation(),
            ui::W::horizontal_line(),
            enableDebugMouseCameraMovements()
        },
        LStretch{false}, LMargins{true}, QFrame::Box)
    );

    add_widget(
        ui::F::gen(ui::L::VB(), {
            ui::W::txt("<b>Current start neutral camera</b>"),
            currentNeutralPosition(),
            currentNeutralRotation(),
            ui::F::gen(ui::L::HB(), {copyNeutralToCurrentConfig = new QPushButton("Copy to config camera")}, LStretch{true}, LMargins{false}, QFrame::NoFrame)
        },
        LStretch{false}, LMargins{true}, QFrame::Box)
    );

    add_widget(
        ui::F::gen(ui::L::VB(), {
            ui::W::txt("<b>Current eye camera</b>"),
            currentEyePosition(),
            currentEyeRotation(),
            ui::F::gen(ui::L::HB(), {copyEyeToCurrentConfig = new QPushButton("Copy to config camera")}, LStretch{true}, LMargins{false}, QFrame::NoFrame)
        },
        LStretch{false}, LMargins{true}, QFrame::Box)
    );
}

void CameraConfigParametersW::init_and_register_widgets(){

    DsbSettings offsetPos{MinV<qreal>{-1000.},V<qreal>{0.},MaxV<qreal>{1000.},StepV<qreal>{0.01}, 3};
    Vector3dSettings offsetVecPos = {offsetPos,offsetPos,offsetPos};
    DsbSettings offsetRot{MinV<qreal>{-360.},V<qreal>{0.},MaxV<qreal>{360.},StepV<qreal>{0.1}, 3};
    Vector3dSettings offsetVecRot = {offsetRot,offsetRot,offsetRot};

    add_inputs_ui(
        ExRadioButtonW::init_group_widgets(group1,
            {&useNeutral, &useEye},
            {
                "start neutral camera",
                "eye camera",
            },
            {true, false}
        )
    );

    add_input_ui(position.init_widget("position: ", offsetVecPos));
    add_input_ui(rotation.init_widget("rotation: ", offsetVecRot));

    add_input_ui(cbStartRoutine.init_widget("Start routine (config cam)", false, true));
    add_input_ui(cbUpdateOn.init_widget("Start timeline update block (config cam)", false, true));

    position.init_widget("position: ", offsetVecPos);
    rotation.init_widget("rotation: ", offsetVecRot);
    currentNeutralPosition.init_widget("position: ", offsetVecPos, false);
    currentNeutralRotation.init_widget("rotation: ", offsetVecRot, false);
    currentEyePosition.init_widget("position: ", offsetVecPos, false);
    currentEyeRotation.init_widget("rotation: ", offsetVecRot, false);

    add_input_ui(enableDebugMouseCameraMovements.init_widget("Enable debug camera movement (move with mouse middle click, rotate with right click)", false));
}

void CameraConfigParametersW::update_with_info(QStringView id, QStringView value){

    if(id == QSL("cameras_info")){

        auto split = value.toString().remove(",").split(" ");
        if(split.size() < 12){
            return;
        }

        currentNeutralPosition.set_values({
            str::Convertor::to_double(split[0]),
            str::Convertor::to_double(split[1]),
            str::Convertor::to_double(split[2])
        });

        currentNeutralRotation.set_values({
            str::Convertor::to_double(split[3]),
            str::Convertor::to_double(split[4]),
            str::Convertor::to_double(split[5])
        });

        currentEyePosition.set_values({
            str::Convertor::to_double(split[6]),
            str::Convertor::to_double(split[7]),
            str::Convertor::to_double(split[8])
        });

        currentEyeRotation.set_values({
            str::Convertor::to_double(split[9]),
            str::Convertor::to_double(split[10]),
            str::Convertor::to_double(split[11])
        });
    }
}

void CameraConfigParametersW::create_connections(){

    connect(copyNeutralToCurrentConfig, &QPushButton::clicked, this, [&]{
        position.set_values(currentNeutralPosition.values());
        rotation.set_values(currentNeutralRotation.values());
        position.trigger_ui_change();
        rotation.trigger_ui_change();
    });

    connect(copyEyeToCurrentConfig, &QPushButton::clicked, this, [&]{
        position.set_values(currentEyePosition.values());
        rotation.set_values(currentEyeRotation.values());
        position.trigger_ui_change();
        rotation.trigger_ui_change();
    });
}

void CameraConfigParametersW::late_update_ui(){}
