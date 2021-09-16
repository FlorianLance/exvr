
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_checkbox_w.hpp"
#include "ex_widgets/ex_radio_button_w.hpp"
#include "ex_widgets/ex_line_edit_w.hpp"

// local
#include "ex_widgets/ex_resource_w.hpp"
#include "config_pw.hpp"

namespace tool::ex {


class LoggerInitConfigParametersW : public ConfigParametersW{

    ExResourceW m_resource{"directory"};

    ExCheckBoxW m_streamToFile{"stream_to_file"};
    ExCheckBoxW m_addCurrentInstanceToFileName{"add_current_instance_to_file_name"};
    ExCheckBoxW m_addDateToFileName{"add_date_to_file_name"};
    ExCheckBoxW m_dontWriteIfFileExists{"dont_write_if_file_exists"};
    ExCheckBoxW m_insertNewRoutineInfo{"insert_new_routine_infos"};

    QButtonGroup group1;
    ExRadioButtonW m_addToEndIfFileExists{"add_to_end_if_file_exists"};
    ExRadioButtonW m_replaceIfFileExists{"replace_if_file_exists"};

    ExLineEditW m_baseFileName{"base_file_name"};
    ExLineEditW m_dateTimeFormat{"date_time_format"};
    ExLineEditW m_fileExtension{"file_extension"};

    ExCheckBoxW m_addHeaderLine{"add_header_line"};
    ExLineEditW m_headerLine{"header_line"};

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};


class LoggerConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

class LoggerColumnsInitConfigParametersW : public ConfigParametersW{

    ExResourceW m_resource{"directory"};

    ExCheckBoxW m_streamToFile{"stream_to_file"};
    ExCheckBoxW m_addCurrentInstanceToFileName{"add_current_instance_to_file_name"};
    ExCheckBoxW m_addDateToFileName{"add_date_to_file_name"};
    ExCheckBoxW m_dontWriteIfFileExists{"dont_write_if_file_exists"};

    QButtonGroup group1;
    ExRadioButtonW m_addToEndIfFileExists{"add_to_end_if_file_exists"};
    ExRadioButtonW m_replaceIfFileExists{"replace_if_file_exists"};

    ExLineEditW m_baseFileName{"base_file_name"};
    ExLineEditW m_dateTimeFormat{"date_time_format"};
    ExLineEditW m_fileExtension{"file_extension"};

    ExCheckBoxW m_addHeaderLine{"add_header_line"};
    ExLineEditW m_headerLine{"header_line"};

    ExLineEditW m_separator{"separator"};
    ExCheckBoxW m_writeAtEnfOfEachFrame{"write_each_frame"};

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};


class LoggerColumnsConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};


class LoggerConditionInitConfigParametersW : public ConfigParametersW{

    ExResourceW m_resource{"directory"};

    ExCheckBoxW m_streamToFile{"stream_to_file"};
    ExCheckBoxW m_dontWriteIfFileExists{"dont_write_if_file_exists"};
    ExCheckBoxW m_addCurrentInstanceToFileName{"add_current_instance_to_file_name"};

    QButtonGroup group1;
    ExRadioButtonW m_addRoutineName{"add_routine"};
    ExRadioButtonW m_addConditionName{"add_condition"};
    ExRadioButtonW m_addBoth{"add_both"};

    QButtonGroup group2;
    ExRadioButtonW m_addToEndIfFileExists{"add_to_end_if_file_exists"};
    ExRadioButtonW m_replaceIfFileExists{"replace_if_file_exists"};

    ExLineEditW m_baseFileName{"base_file_name"};
    ExLineEditW m_fileExtension{"file_extension"};

    ExCheckBoxW m_addHeaderLine{"add_header_line"};
    ExLineEditW m_headerLine{"header_line"};

public :

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};


class LoggerConditionConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

}
