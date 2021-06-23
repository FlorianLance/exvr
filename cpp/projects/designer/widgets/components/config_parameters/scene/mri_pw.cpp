

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "mri_pw.hpp"

using namespace tool::ex;

void MriInitConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("Avatar to use in the MRI:"), humanoidController()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("Keyboard used for catching MRI triggers:"), keyboard()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Trigger key:"), triggerKey()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("Write trigger line to theses loggers:"),loggersList()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));    
    no_end_stretch();
}

void MriInitConfigParametersW::init_and_register_widgets(){

    QStringList items;
    for(const auto &keyName : input::Keyboard::buttons.tuple_column<1>()){
        items << from_view(keyName);
    }

    m_inputUiElements["humanoid_controller"] = humanoidController.init_widget(Component::Type::Humanoid_controller, "Humanoid controller:");
    m_inputUiElements["keyboard"]            = keyboard.init_widget(Component::Type::Keyboard, "Keyboard");
    m_inputUiElements["trigger_key"]         = triggerKey.init_widget(items);    
    m_inputUiElements["loggers"]             = loggersList.init_widget(Component::Type::Logger, "Loggers");
}

void MriInitConfigParametersW::create_connections(){
}

void MriInitConfigParametersW::late_update_ui(){}

void MriConfigParametersW::insert_widgets(){

    add_sub_part_widget(transform);
    add_widget(ui::F::gen(ui::L::HB(), {goNextWhenTrigger()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("Action:"), solve(), dissolve(), move_table_inside(), move_table_outside(), move_table_qualisys(), nothing()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::W::horizontal_line());
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Duration:"), duration()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Distance:"), distance()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Objects to be solved/dissolved:"), room(), magnet()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::W::horizontal_line());
    add_widget(ui::F::gen(ui::L::HB(), {initQualisysPositions()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {enableQualisysArmsTracking()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::W::horizontal_line());
    add_widget(ui::F::gen(ui::L::HB(), {targetHeadTrOffset()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
    add_widget(ui::F::gen(ui::L::HB(), {targetHeadRotOffset()}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
}

void MriConfigParametersW::init_and_register_widgets(){

    map_sub_part(transform.init_widget());
    m_inputUiElements["solve"]                  = solve.init_widget("solve", false);
    m_inputUiElements["dissolve"]               = dissolve.init_widget("dissolve", false);
    m_inputUiElements["move_table_inside"]      = move_table_inside.init_widget("move table inside", false);
    m_inputUiElements["move_table_outside"]     = move_table_outside.init_widget("move table outside", false);
    m_inputUiElements["move_table_qualisys"]    = move_table_qualisys.init_widget("move table using qualisys", false);
    m_inputUiElements["nothing"]                = nothing.init_widget("nothing", true);
    m_inputUiElements["duration"]               = duration.init_widget(MinV<qreal>{0.01},V<qreal>{5.},MaxV<qreal>{25.},StepV<qreal>{0.01}, 2);
    m_inputUiElements["distance"]               = distance.init_widget(MinV<qreal>{0.00},V<qreal>{1.0},MaxV<qreal>{2.5},StepV<qreal>{0.01}, 2);
    m_inputUiElements["process_room"]           = room.init_widget("room", true);
    m_inputUiElements["process_magnet"]         = magnet.init_widget("magnet", true);
    m_inputUiElements["init_qualisys"]          = initQualisysPositions.init_widget("Init Qualisys positions", false);
    m_inputUiElements["qualisys_arms_tracking"] = enableQualisysArmsTracking.init_widget("Enable Qualisys arms tracking", false);
    m_inputUiElements["trigger_go_next"]        = goNextWhenTrigger.init_widget("Go next when receive trigger", false);

    DsbSettings offsetTr{MinV<qreal>{-2.},V<qreal>{0.},MaxV<qreal>{2.},StepV<qreal>{0.01}, 2};
    auto offsetVecTr = Vector3dSettings{offsetTr,offsetTr,offsetTr};
    m_inputUiElements["target_head_tr_offset"] = targetHeadTrOffset.init_widget("Target head translation offset", offsetVecTr);

    DsbSettings offsetRot{MinV<qreal>{-180.},V<qreal>{0.},MaxV<qreal>{180.},StepV<qreal>{0.1}, 2};
    Vector3dSettings offsetVecRot = {offsetRot,offsetRot,offsetRot};
    m_inputUiElements["target_head_rot_offset"] = targetHeadRotOffset.init_widget("Target head rotation offset", offsetVecRot);
}

void MriConfigParametersW::create_connections(){}

void MriConfigParametersW::late_update_ui(){}
