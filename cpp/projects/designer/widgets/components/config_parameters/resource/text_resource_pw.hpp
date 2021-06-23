


/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QFileDialog>

// local
#include "config_pw.hpp"
#include "ex_resource_w.hpp"

namespace tool::ex {

class TextResourceInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};


class TextResourceConfigParametersW : public ConfigParametersW{

public :

    ExResourceW m_text;

    void insert_widgets() override{
        layout()->setContentsMargins(0,0,0,0);
        add_widget(ui::F::gen(ui::L::HB(), {m_text()}, LStretch{false}, LMargins{true}, QFrame::Box));
    }

    void init_and_register_widgets() override{
        m_inputUiElements["text"] = m_text.init_widget(Resource::Type::Text, "Text resource: ");
    }

    void create_connections() override{
    }

    void late_update_ui() override{
    }
};

}

