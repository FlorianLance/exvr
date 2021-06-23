
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "path_utility.hpp"

namespace tool::ex {

class ScanerVideoInitConfigParametersW : public ConfigParametersW{

public :

    ExResourceW m_scanerVideo;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {m_scanerVideo()}, LStretch{false}, LMargins{true}, QFrame::Box));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["scaner_video"] = m_scanerVideo.init_widget(Resource::Type::ScanerVideo, "Scaner video resource: ");
    }

    void create_connections() override{}
    void late_update_ui() override{}

    virtual void update_with_info(QStringView id, QStringView value) override{

//        if(id == "buttons_state_info"){
//            if(value.length() == 0){
//                for(const auto &t : input::Keyboard::mapping){
//                    if(buttonsDsb.count(std::get<0>(t)) > 0){
//                        std::get<1>(buttonsDsb[std::get<0>(t)])->update(false);
//                        std::get<2>(buttonsDsb[std::get<0>(t)])->update(false);
//                        std::get<3>(buttonsDsb[std::get<0>(t)])->update(false);
//                    }
//                }
//                return;
//            }else{
//                const auto split = value.split("%");
//                for(const auto &button : split){
//                    const auto subSplit = button.split(",");
//                    auto buttonId = static_cast<input::Keyboard::Button>(subSplit[0].toInt());
//                    if(buttonsDsb.count(buttonId)){
//                        std::get<1>(buttonsDsb[buttonId])->update(subSplit[1] == "1");
//                        std::get<2>(buttonsDsb[buttonId])->update(subSplit[2] == "1");
//                        std::get<3>(buttonsDsb[buttonId])->update(subSplit[3] == "1");
//                    }
//                }
//            }
//        }
    }

};

class ScanerVideoConfigParametersW : public ConfigParametersW{

public :

    DefaultTransformSubPart m_transfo;
    ExFloatSpinBoxW m_sizePoints;
    ExSpinBoxW m_fps;
    ExCheckBoxW m_loop;
    ExCheckBoxW m_displayClouds;
    ExCheckBoxW m_displayColliders;
    ExSpinBoxW m_maxDiffTimeMs;


    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Size points: "),m_sizePoints()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Video ask frame rate: "), m_fps()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Max time difference (ms): "), m_maxDiffTimeMs()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{m_loop()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{m_displayClouds()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{m_displayColliders()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget("Global model transform", "global_transform"));

        m_inputUiElements["size_points"]       = m_sizePoints.init_widget(MinV<qreal>{0.0001}, V<qreal>{0.0030}, MaxV<qreal>{0.05}, StepV<qreal>{0.0001},4);
        m_inputUiElements["fps"]               = m_fps.init_widget(MinV<int>{1}, V<int>{30}, MaxV<int>{40}, StepV<int>{1});
        m_inputUiElements["max_diff_time_ms"]  = m_maxDiffTimeMs.init_widget(MinV<int>{1}, V<int>{100}, MaxV<int>{600}, StepV<int>{10});
        m_inputUiElements["loop"]              = m_loop.init_widget("Loop ", true);
        m_inputUiElements["display_clouds"]    = m_displayClouds.init_widget("Display clouds ", true);
        m_inputUiElements["display_colliders"] = m_displayColliders.init_widget("Display colliders ", false);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


}
