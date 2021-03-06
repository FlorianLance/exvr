
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_line_edit_w.hpp"
#include "ex_widgets/ex_spin_box_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {


class VideoGeneratorInitConfigParametersW : public ConfigParametersW{

public :

    ExLineEditW m_lePath{"path_video"};
    QPushButton m_pbSetPath;
    ExSpinBoxW m_sbFPS{"fps"};
    ExSpinBoxW m_sbWidth{"width"};
    ExSpinBoxW m_sbHeight{"height"};

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Path video to save: "),m_lePath(), &m_pbSetPath}, LStretch{false}, LMargins{true}, QFrame::Box));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("FPS: "), m_sbFPS()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Width: "), m_sbWidth(), ui::W::txt("Height: "), m_sbHeight()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));

    }
    void init_and_register_widgets() override{
        ui::W::init(&m_pbSetPath, "Set");        
        add_input_ui(m_lePath.init_widget("..."));
        add_input_ui(m_sbFPS.init_widget(MinV<int>{1}, V<int>{30}, MaxV<int>{120}, StepV<int>{1},  true));
        add_input_ui(m_sbWidth.init_widget(MinV<int>{100}, V<int>{1024}, MaxV<int>{1920}, StepV<int>{1},  true));
        add_input_ui(m_sbHeight.init_widget(MinV<int>{100}, V<int>{768}, MaxV<int>{1080}, StepV<int>{1},  true));
    }
    void create_connections() override{
        connect(&m_pbSetPath, &QPushButton::clicked, this, [&]{
            QString path = QFileDialog::getSaveFileName(nullptr, "Video file", "", "Video files (*.avi)");
            if(path.size() > 0){
                m_lePath.w->setText(path);
                emit m_lePath.w->textChanged(m_lePath.w->text());
            }
        });

    }
    void late_update_ui() override{}
};

class VideoGeneratorConfigParametersW : public ConfigParametersW{

public :


    void insert_widgets() override{
    }

    void init_and_register_widgets() override{
    }

    void create_connections() override{
    }

    void late_update_ui() override{
    }
};

}
