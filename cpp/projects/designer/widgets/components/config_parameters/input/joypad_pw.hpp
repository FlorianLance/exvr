
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_list_labels_w.hpp"
#include "ex_label_w.hpp"
#include "ex_line_edit_w.hpp"
#include "ex_color_frame_w.hpp"
#include "utility/joypad_utility.hpp"

namespace tool::ex {


class JoypadInitConfigParametersW : public ConfigParametersW{

public :

    ExListLabelsW devicesLL;

    std::map<input::Joypad::Axis, std::unique_ptr<ExLineEditW>> axesP1;
    std::map<input::Joypad::Axis, std::unique_ptr<ExLineEditW>> axesP2;

    std::map<input::Joypad::Button, std::unique_ptr<ExColorFrameW>> buttonsP1;
    std::map<input::Joypad::Button, std::unique_ptr<ExColorFrameW>> buttonsP2;

    void insert_widgets() override;

    void init_and_register_widgets() override;

public:

    virtual void update_with_info(QStringView id, QStringView value) override;

    void create_connections() override;
    void late_update_ui() override;
};


class JoypadConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
