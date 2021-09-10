
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_combo_box_index_w.hpp"

namespace tool::ex {

class LeapMotionArmsDisplayInitConfigParametersW : public ConfigParametersW{

public :

    ExComboBoxTextW m_cbtModel{"model"};
    ExCheckBoxW m_cbTrackFingers{"track_fingers"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(),{new QLabel("Model: "), m_cbtModel()}, LStretch{false}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(),{m_cbTrackFingers()}, LStretch{false}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        add_input_ui(m_cbtModel.init_widget(
            {"Man black hand", "Man black arm", "Man white hand", "Man white arm"})); // , "Low poly"
        add_input_ui(m_cbTrackFingers.init_widget("Track fingers", true));
    }

    void create_connections() override{

    }

    void late_update_ui() override{}
};


class LeapMotionArmsDisplayConfigParametersW : public ConfigParametersW{


public :

    TransformSubPart m_tr{"model_transform"};
    ExComboBoxIndexW m_cbtPartToDisplay{"part_to_display"};
    ExCheckBoxW m_cbDisplayColliders{"display_colliders"};

    void insert_widgets() override{

        add_sub_part_widget(m_tr);        
        QFrame *frame2 = ui::F::gen(ui::L::HB(),{new QLabel("Part to display: "), m_cbtPartToDisplay()}, LStretch{false}, LMargins{true});
        QFrame *frame3 = ui::F::gen(ui::L::HB(),{m_cbDisplayColliders()}, LStretch{false}, LMargins{true});
        add_widget(ui::F::gen(ui::L::VB(),{frame2, frame3}, LStretch{true}, LMargins{false},QFrame::Box));
    }

    void init_and_register_widgets() override{
        add_input_ui(m_cbtPartToDisplay.init_widget({"Both", "Left", "Right", "None"}));
        add_input_ui(m_cbDisplayColliders.init_widget("Display colliders", false));
        map_sub_part(m_tr.init_widget("Model transform"));
    }

    void create_connections() override{
        // ...
    }


    void late_update_ui() override{}
};

}
