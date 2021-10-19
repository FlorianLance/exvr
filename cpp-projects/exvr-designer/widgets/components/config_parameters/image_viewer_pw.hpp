
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_vector2d_w.hpp"
#include "ex_widgets/ex_double_spin_box_w.hpp"
#include "ex_widgets/ex_checkbox_w.hpp"

// local
#include "ex_widgets/ex_resource_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {

class ImageViewerInitConfigParametersW : public ConfigParametersW{
};


class ImageViewerConfigParametersW : public ConfigParametersW{

public :

    ImageViewerConfigParametersW();



    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;


private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

}
