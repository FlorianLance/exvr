
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_radio_button_w.hpp"
#include "ex_line_edit_w.hpp"

namespace tool::ex {


class LoggerInitConfigParametersW : public ConfigParametersW{

    ExResourceW m_resource;

    ExCheckBoxW m_streamToFile;
    ExCheckBoxW m_addCurrentInstanceToFileName;
    ExCheckBoxW m_addDateToFileName;
    ExCheckBoxW m_dontWriteIfFileExists;
    ExCheckBoxW m_insertNewRoutineInfo;

    ExRadioButtonW m_addToEndIfFileExists;
    ExRadioButtonW m_replaceIfFileExists;

    ExLineEditW m_baseFileName;
    ExLineEditW m_dateTimeFormat;
    ExLineEditW m_fileExtension;

    ExCheckBoxW m_addHeaderLine;
    ExLineEditW m_headerLine;

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

    ExResourceW m_resource;

    ExCheckBoxW m_streamToFile;
    ExCheckBoxW m_addCurrentInstanceToFileName;
    ExCheckBoxW m_addDateToFileName;
    ExCheckBoxW m_dontWriteIfFileExists;

    ExRadioButtonW m_addToEndIfFileExists;
    ExRadioButtonW m_replaceIfFileExists;

    ExLineEditW m_baseFileName;
    ExLineEditW m_dateTimeFormat;
    ExLineEditW m_fileExtension;

    ExCheckBoxW m_addHeaderLine;
    ExLineEditW m_headerLine;

    ExLineEditW m_separator;
    ExCheckBoxW m_writeAtEnfOfEachFrame;

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

    ExResourceW m_resource;

    ExCheckBoxW m_streamToFile;
    ExCheckBoxW m_dontWriteIfFileExists;
    ExCheckBoxW m_addCurrentInstanceToFileName;

    ExRadioButtonW m_addRoutineName;
    ExRadioButtonW m_addConditionName;
    ExRadioButtonW m_addBoth;

    ExRadioButtonW m_addToEndIfFileExists;
    ExRadioButtonW m_replaceIfFileExists;

    ExLineEditW m_baseFileName;
    ExLineEditW m_fileExtension;

    ExCheckBoxW m_addHeaderLine;
    ExLineEditW m_headerLine;

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
