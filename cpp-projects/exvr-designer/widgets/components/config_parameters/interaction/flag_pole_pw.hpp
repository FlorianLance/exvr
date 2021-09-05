
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_resource_w.hpp"

namespace tool::ex {

class FlagPoleInitConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo;
    ExFloatSpinBoxW m_flagWidth;
    ExFloatSpinBoxW m_flagHeight;
    ExFloatSpinBoxW m_poleHeight;
    ExSpinBoxW m_flagNbVerticesH;
    ExSpinBoxW m_flagNbVerticesV;

    void insert_widgets() override{

        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Pole height: "), m_poleHeight()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Flag width: "), m_flagWidth()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Flag height: "), m_flagHeight()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Flag horizontal vertices number: "), m_flagNbVerticesH()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Flag vertical vertices number: "), m_flagNbVerticesV()}, LStretch{true}, LMargins{true}));
        add_sub_part_widget(m_transfo);
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget(QSL("Init transform</b> (applied when experiment starts)<b>"), QSL("init_transform")));
        m_inputUiElements["pole_height"]            = m_poleHeight.init_widget(MinV<qreal>{0.0}, V<qreal>{4.0}, MaxV<qreal>{10.}, StepV<qreal>{0.01},2);
        m_inputUiElements["flag_width"]             = m_flagWidth.init_widget(MinV<qreal>{0.0}, V<qreal>{0.62}, MaxV<qreal>{10.}, StepV<qreal>{0.01},2);
        m_inputUiElements["flag_height"]            = m_flagHeight.init_widget(MinV<qreal>{0.0}, V<qreal>{0.925}, MaxV<qreal>{10.}, StepV<qreal>{0.01},2);
        m_inputUiElements["flag_nb_vertices_horiz"] = m_flagNbVerticesH.init_widget(MinV<int>{4}, V<int>{13}, MaxV<int>{50}, StepV<int>{1});
        m_inputUiElements["flag_nb_vertices_verti"] = m_flagNbVerticesV.init_widget(MinV<int>{4}, V<int>{20}, MaxV<int>{50}, StepV<int>{1});
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class FlagPoleConfigParametersW : public ConfigParametersW{

public :

    TransformSubPart m_transfo;
    ExResourceW m_currentTexture;
    ExFloatSpinBoxW m_currentHeight;
    ExFloatSpinBoxW m_currentClothMaxDistance;

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
        add_widget(ui::F::gen(ui::L::HB(), {m_currentTexture()}, LStretch{false}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Flag position: "), m_currentHeight()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Cloth max dist: "), m_currentClothMaxDistance()}, LStretch{false}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget(QSL("Config transform</b> (applied when routine starts)<b>"), QSL("transform")));
        m_inputUiElements["flag_image"]     = m_currentTexture.init_widget(Resource::Type::Image, "Flag texture");
        m_inputUiElements["height"]         = m_currentHeight.init_widget(MinV<qreal>{0.0}, V<qreal>{0.0}, MaxV<qreal>{1.}, StepV<qreal>{0.01},2);
        m_inputUiElements["cloth_max_dist"] = m_currentClothMaxDistance.init_widget(MinV<qreal>{0.0}, V<qreal>{0.3}, MaxV<qreal>{1.}, StepV<qreal>{0.01},2);
    }

    void create_connections() override{
        // ...
    }

    void late_update_ui() override{}
};

}
