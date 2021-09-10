/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "ex_line_edit_w.hpp"
#include "ex_spin_box_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {

class SoncebozSgInitConfigParametersW : public ConfigParametersW{

public :

    ExLineEditW m_readingAddress{"reading_address"};
    ExLineEditW m_writingAddress{"writing_address"};
    ExSpinBoxW m_readingPort{"reading_port"};
    ExSpinBoxW m_writingPort{"writing_port"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};


class SoncebozSgConfigParametersW : public ConfigParametersW{

public :

    ExCheckBoxW applyCommand{"apply_command_list"};
    ExResourceW commandList{"command_list_file"};

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};

}
