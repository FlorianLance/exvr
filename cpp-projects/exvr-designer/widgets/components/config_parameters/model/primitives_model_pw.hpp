
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "path_utility.hpp"
#include "ex_spin_box_w.hpp"

namespace tool::ex {

class CubeInitConfigParametersW : public ConfigParametersW{

public :

    ExFloatSpinBoxW m_dsbSize;
    ExCheckBoxW m_transparent;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Cube size: "),m_dsbSize()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {m_transparent()}, LStretch{true}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["size"] = m_dsbSize.init_widget(MinV<qreal>{0.1}, V<qreal>{1.}, MaxV<qreal>{1000.}, StepV<qreal>{0.1},2);
        m_inputUiElements["transparent"] = m_transparent.init_widget("Is transparent?", false);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class CubeConfigParametersW : public ConfigParametersW{

public :

    DefaultTransformSubPart m_transfo;
    ExSelectColorW m_color;    
    ExFloatSpinBoxW m_metallic;
    ExFloatSpinBoxW m_smoothness;

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Color: "),m_color()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Metallic: "),m_metallic()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Smoothness: "),m_smoothness()}, LStretch{true}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget());
        m_inputUiElements["color"] = m_color.init_widget("Color", Qt::gray);
        m_inputUiElements["metallic"]   = m_metallic.init_widget(MinV<qreal>{0.0}, V<qreal>{0.0}, MaxV<qreal>{1.}, StepV<qreal>{0.01},2);
        m_inputUiElements["smoothness"] = m_smoothness.init_widget(MinV<qreal>{0.0}, V<qreal>{0.0}, MaxV<qreal>{1.}, StepV<qreal>{0.01},2);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class CylinderInitConfigParametersW : public ConfigParametersW{

public :

    ExSpinBoxW m_nbSides;
    ExFloatSpinBoxW m_radius;
    ExFloatSpinBoxW m_length;
    ExCheckBoxW m_transparent;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Number sides: "),m_nbSides()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Radius: "),m_radius()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Length: "),m_length()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {m_transparent()}, LStretch{true}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["nb_sides"] = m_nbSides.init_widget(MinV<int>{8}, V<int>{18}, MaxV<int>{100}, StepV<int>{1});
        m_inputUiElements["radius"]   = m_radius.init_widget(MinV<qreal>{0.01}, V<qreal>{0.5}, MaxV<qreal>{1000.}, StepV<qreal>{0.1},2);
        m_inputUiElements["length"]   = m_length.init_widget(MinV<qreal>{0.01}, V<qreal>{1.0}, MaxV<qreal>{1000.}, StepV<qreal>{0.1},2);
        m_inputUiElements["transparent"] = m_transparent.init_widget("Is transparent?", false);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class CylinderConfigParametersW : public ConfigParametersW{

public :

    DefaultTransformSubPart m_transfo;
    ExSelectColorW m_color;
    ExFloatSpinBoxW m_metallic;
    ExFloatSpinBoxW m_smoothness;

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Color: "),m_color()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Metallic: "),m_metallic()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Smoothness: "),m_smoothness()}, LStretch{true}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget());
        m_inputUiElements["color"] = m_color.init_widget("Color", Qt::gray);
        m_inputUiElements["metallic"]   = m_metallic.init_widget(MinV<qreal>{0.0}, V<qreal>{0.0}, MaxV<qreal>{1.}, StepV<qreal>{0.01},2);
        m_inputUiElements["smoothness"] = m_smoothness.init_widget(MinV<qreal>{0.0}, V<qreal>{0.0}, MaxV<qreal>{1.}, StepV<qreal>{0.01},2);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};



class SphereInitConfigParametersW : public ConfigParametersW{

public :

    ExFloatSpinBoxW m_dsbRadius;
    ExSpinBoxW m_sbLong;
    ExSpinBoxW m_sbLat;
    ExCheckBoxW m_transparent;

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Sphere radius: "),m_dsbRadius()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Long nb triangles: "),m_sbLong()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Lat nb triangles: "),m_sbLat()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {m_transparent()}, LStretch{true}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["radius"] = m_dsbRadius.init_widget(MinV<qreal>{0.01}, V<qreal>{0.05}, MaxV<qreal>{1000.}, StepV<qreal>{0.01},2);
        m_inputUiElements["nb_log"] = m_sbLong.init_widget(MinV<int>{12}, V<int>{24}, MaxV<int>{100}, StepV<int>{1},1);
        m_inputUiElements["nb_lat"] = m_sbLat.init_widget(MinV<int>{8}, V<int>{16}, MaxV<int>{100}, StepV<int>{1},1);
        m_inputUiElements["transparent"] = m_transparent.init_widget("Is transparent?", false);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class SphereConfigParametersW : public ConfigParametersW{

public :

    DefaultTransformSubPart m_transfo;
    ExSelectColorW m_color;    
    ExFloatSpinBoxW m_metallic;
    ExFloatSpinBoxW m_smoothness;

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Color: "),m_color()}, LStretch{true}, LMargins{true}));        
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Metallic: "),m_metallic()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Smoothness: "),m_smoothness()}, LStretch{true}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget());
        m_inputUiElements["color"] = m_color.init_widget("Color", Qt::gray);        
        m_inputUiElements["metallic"]   = m_metallic.init_widget(MinV<qreal>{0.0}, V<qreal>{0.0}, MaxV<qreal>{1.}, StepV<qreal>{0.01},2);
        m_inputUiElements["smoothness"] = m_smoothness.init_widget(MinV<qreal>{0.0}, V<qreal>{0.0}, MaxV<qreal>{1.}, StepV<qreal>{0.01},2);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};

class TorusInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Outer radius: "),m_outerRadius()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Inner radius: "),m_innerRadius()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Sides count: "),m_sidesCount()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Rings count: "),m_ringsCount()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {m_transparent()}, LStretch{true}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["outer_radius"] = m_outerRadius.init_widget(MinV<qreal>{0.01}, V<qreal>{0.3}, MaxV<qreal>{1000.}, StepV<qreal>{0.01},2);
        m_inputUiElements["inner_radius"] = m_innerRadius.init_widget(MinV<qreal>{0.01}, V<qreal>{0.15}, MaxV<qreal>{1000.}, StepV<qreal>{0.01},2);
        m_inputUiElements["sides_count"] = m_sidesCount.init_widget(MinV<int>{12}, V<int>{24}, MaxV<int>{1000}, StepV<int>{1},1);
        m_inputUiElements["rings_count"] = m_ringsCount.init_widget(MinV<int>{12}, V<int>{24}, MaxV<int>{1000}, StepV<int>{1},1);
        m_inputUiElements["transparent"] = m_transparent.init_widget("Is transparent?", false);
    }

    void create_connections() override{}
    void late_update_ui() override{}

private:
    ExFloatSpinBoxW m_outerRadius;
    ExFloatSpinBoxW m_innerRadius;
    ExSpinBoxW m_sidesCount;
    ExSpinBoxW m_ringsCount;
    ExCheckBoxW m_transparent;
};


class TorusConfigParametersW : public ConfigParametersW{

public :

    DefaultTransformSubPart m_transfo;
    ExSelectColorW m_color;    
    ExFloatSpinBoxW m_metallic;
    ExFloatSpinBoxW m_smoothness;

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Color: "),m_color()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Metallic: "),m_metallic()}, LStretch{true}, LMargins{true}));
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Smoothness: "),m_smoothness()}, LStretch{true}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget());
        m_inputUiElements["color"] = m_color.init_widget("Color", Qt::gray);
        m_inputUiElements["metallic"]   = m_metallic.init_widget(MinV<qreal>{0.0}, V<qreal>{0.0}, MaxV<qreal>{1.}, StepV<qreal>{0.01},2);
        m_inputUiElements["smoothness"] = m_smoothness.init_widget(MinV<qreal>{0.0}, V<qreal>{0.0}, MaxV<qreal>{1.}, StepV<qreal>{0.01},2);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class LinesInitConfigParametersW : public ConfigParametersW{
public :
    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};


class LinesConfigParametersW : public ConfigParametersW{

public :

    DefaultTransformSubPart m_transfo;

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget());
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class LandmarkInitConfigParametersW : public ConfigParametersW{
public :
    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

class LandmarkConfigParametersW : public ConfigParametersW{

public :

    DefaultTransformSubPart m_transfo;
    ExSelectColorW m_color;

    void insert_widgets() override{
        add_sub_part_widget(m_transfo);
        add_widget(ui::F::gen(ui::L::HB(), {ui::W::txt("Color: "),m_color()}, LStretch{true}, LMargins{true}));
    }

    void init_and_register_widgets() override{
        map_sub_part(m_transfo.init_widget());
        m_inputUiElements["color"] = m_color.init_widget("Color", Qt::gray);
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


}
