
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"


namespace tool::ex {

class AttachObjectToHandInitConfigParametersW : public ConfigParametersW{

public :

//    ExLineEditW m_leLeapMotionTrackingComponent;

    void insert_widgets() override{
//        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Leap motion tracking component: "),m_leLeapMotionTrackingComponent()}, LStretch{true}, LMargins{true},QFrame::Box));
    }

    void init_and_register_widgets() override{
//        m_inputUiElements["leap_motion_component"]  = m_leLeapMotionTrackingComponent.init_widget("");
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class AttachObjectToHandConfigParametersW : public ConfigParametersW{

public :

//    DefaultTransformSubPart m_transfo;
//    ExComboBoxTextW m_armToAttach;
//    ExComboBoxTextW m_fingerToAttach;


    void insert_widgets() override{
//        add_sub_part_to_layout(m_transfo);
//        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Arm to attach: "),      m_armToAttach()}, LStretch{true}, LMargins{true},QFrame::Box));
//        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Finger to attach: "),   m_fingerToAttach()}, LStretch{true}, LMargins{true},QFrame::Box));
    }

    void init_and_register_widgets() override{

//        add_sub_part_to_map(m_transfo.init_widget("sponge_transform"));
//        m_transfo.tr.set_rotation_values({180.,0.,90.});
//        m_inputUiElements["arm"]    = m_armToAttach.init_widget({"Left","Right"});
//        m_inputUiElements["finger"] = m_fingerToAttach.init_widget({"Thumb","Index", "Pinky", "Middle", "Ring"});
    }

    void create_connections() override{}
    void late_update_ui() override{}
};
}
