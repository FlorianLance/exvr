

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "logger_pw.hpp"

using namespace tool::ex;

void LoggerInitConfigParametersW::insert_widgets(){

    add_widget(ui::F::gen(ui::L::VB(),{m_resource()}));
    add_widget(ui::F::gen(ui::L::VB(),
        {m_streamToFile(), m_dontWriteIfFileExists(), m_insertNewRoutineInfo(), m_replaceIfFileExists(), m_addToEndIfFileExists()},
        LStretch{true}, LMargins{true}, QFrame::Box)
    );

    auto l1 = ui::F::gen(ui::L::HB(), {ui::W::txt("Logging file name:"), m_baseFileName()}, LStretch{false}, LMargins{false});
    auto l2 = ui::F::gen(ui::L::HB(), {m_addCurrentInstanceToFileName()}, LStretch{true}, LMargins{false});
    auto l3 = ui::F::gen(ui::L::HB(), {m_addDateToFileName()}, LStretch{true}, LMargins{false});
    auto l4 = ui::F::gen(ui::L::HB(), {ui::W::txt("Date format:"),    m_dateTimeFormat()},  LStretch{true}, LMargins{false});
    auto l5 = ui::F::gen(ui::L::HB(), {ui::W::txt("File extension:"), m_fileExtension()}, LStretch{true}, LMargins{false});
    auto l6 = ui::F::gen(ui::L::HB(), {m_addHeaderLine()}, LStretch{true}, LMargins{false});
    auto l7 = ui::F::gen(ui::L::HB(), {ui::W::txt("Header line:"), m_headerLine()}, LStretch{false}, LMargins{false});

    add_widget(ui::F::gen(ui::L::VB(),
        {l1,l2,l3,l4,l5,l6,l7},
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
}

void LoggerInitConfigParametersW::init_and_register_widgets(){

    m_inputUiElements["directory"]                 = m_resource.init_widget(Resource::Type::Directory, "Directory to use:");
    m_inputUiElements["stream_to_file"]            = m_streamToFile.init_widget("Stream to file", true);
    m_inputUiElements["add_current_instance_to_file_name"]  = m_addCurrentInstanceToFileName.init_widget("Add current instance to name", true);
    m_inputUiElements["add_date_to_file_name"]     = m_addDateToFileName.init_widget("Add current date to name", true);
    m_inputUiElements["dont_write_if_file_exists"] = m_dontWriteIfFileExists.init_widget("Dont write if file already exists", false);
    m_inputUiElements["insert_new_routine_infos"]  = m_insertNewRoutineInfo.init_widget("Insert info at each new routine", false);
    m_inputUiElements["replace_if_file_exists"]    = m_replaceIfFileExists.init_widget("Replace file if exists", true);
    m_inputUiElements["add_to_end_if_file_exists"] = m_addToEndIfFileExists.init_widget("Add to end of file if exists", false);
    m_inputUiElements["base_file_name"]            = m_baseFileName.init_widget("log");
    m_inputUiElements["date_time_format"]          = m_dateTimeFormat.init_widget("yyyy-MM-dd_H-mm-ss");
    m_inputUiElements["file_extension"]            = m_fileExtension.init_widget("txt");

    m_inputUiElements["add_header_line"]           = m_addHeaderLine.init_widget("Add header line", false);
    m_inputUiElements["header_line"]               = m_headerLine.init_widget("");
}

void LoggerInitConfigParametersW::create_connections(){
    connect(m_addDateToFileName(), &QCheckBox::clicked, this, [&](bool checked){
        m_dateTimeFormat.w->setEnabled(checked);
    });
    connect(m_addHeaderLine(), &QCheckBox::clicked, this, [&](bool checked){
        m_headerLine.w->setEnabled(checked);
    });
}

void LoggerInitConfigParametersW::late_update_ui(){
    m_dateTimeFormat.w->setEnabled(m_addDateToFileName.w->isChecked());
    m_headerLine.w->setEnabled(m_addHeaderLine.w->isChecked());
}


void LoggerColumnsInitConfigParametersW::insert_widgets(){

    add_widget(ui::F::gen(ui::L::VB(),{m_resource()}));
    add_widget(ui::F::gen(ui::L::VB(),
        {m_streamToFile(), m_dontWriteIfFileExists(), m_replaceIfFileExists(), m_addToEndIfFileExists(), m_writeAtEnfOfEachFrame()},
        LStretch{true}, LMargins{true}, QFrame::Box)
    );

    auto l1 = ui::F::gen(ui::L::HB(), {ui::W::txt("Logging file name:"), m_baseFileName()}, LStretch{false}, LMargins{false});
    auto l2 = ui::F::gen(ui::L::HB(), {m_addCurrentInstanceToFileName()}, LStretch{true}, LMargins{false});
    auto l3 = ui::F::gen(ui::L::HB(), {m_addDateToFileName()}, LStretch{true}, LMargins{false});
    auto l4 = ui::F::gen(ui::L::HB(), {ui::W::txt("Date format:"),    m_dateTimeFormat()},  LStretch{true}, LMargins{false});
    auto l5 = ui::F::gen(ui::L::HB(), {ui::W::txt("File extension:"), m_fileExtension()}, LStretch{true}, LMargins{false});
    auto l6 = ui::F::gen(ui::L::HB(), {ui::W::txt("Columns separator:"), m_separator()}, LStretch{false}, LMargins{false});
    auto l7 = ui::F::gen(ui::L::HB(), {m_addHeaderLine()}, LStretch{true}, LMargins{false});
    auto l8 = ui::F::gen(ui::L::HB(), {ui::W::txt("Header line:"), m_headerLine()}, LStretch{false}, LMargins{false});

    add_widget(ui::F::gen(ui::L::VB(),
        {l1,l2,l3,l4,l5,l6,l7,l8},
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
}

void LoggerColumnsInitConfigParametersW::init_and_register_widgets(){

    m_inputUiElements["directory"]                 = m_resource.init_widget(Resource::Type::Directory, "Directory to use:");
    m_inputUiElements["stream_to_file"]            = m_streamToFile.init_widget("Stream to file", true);
    m_inputUiElements["add_current_instance_to_file_name"]  = m_addCurrentInstanceToFileName.init_widget("Add current instance to name", true);
    m_inputUiElements["add_date_to_file_name"]     = m_addDateToFileName.init_widget("Add current date to name", true);
    m_inputUiElements["dont_write_if_file_exists"] = m_dontWriteIfFileExists.init_widget("Dont write if file already exists", false);

    m_inputUiElements["replace_if_file_exists"]    = m_replaceIfFileExists.init_widget("Replace file if exists", true);
    m_inputUiElements["add_to_end_if_file_exists"] = m_addToEndIfFileExists.init_widget("Add to end of file if exists", false);
    m_inputUiElements["base_file_name"]            = m_baseFileName.init_widget("log");
    m_inputUiElements["date_time_format"]          = m_dateTimeFormat.init_widget("yyyy-MM-dd_H-mm-ss");
    m_inputUiElements["file_extension"]            = m_fileExtension.init_widget("csv");

    m_inputUiElements["add_header_line"]           = m_addHeaderLine.init_widget("Add header line", false);
    m_inputUiElements["header_line"]               = m_headerLine.init_widget("");

    m_inputUiElements["write_each_frame"]          = m_writeAtEnfOfEachFrame.init_widget("Write columns at the end of each frame", true);
    m_inputUiElements["separator"]                 = m_separator.init_widget(";");
}

void LoggerColumnsInitConfigParametersW::create_connections(){

    connect(m_addDateToFileName(), &QCheckBox::clicked, this, [&](bool checked){
        m_dateTimeFormat.w->setEnabled(checked);
    });
    connect(m_addHeaderLine(), &QCheckBox::clicked, this, [&](bool checked){
        m_headerLine.w->setEnabled(checked);
    });
}

void LoggerColumnsInitConfigParametersW::late_update_ui(){
    m_dateTimeFormat.w->setEnabled(m_addDateToFileName.w->isChecked());
    m_headerLine.w->setEnabled(m_addHeaderLine.w->isChecked());
}

void LoggerConditionInitConfigParametersW::insert_widgets(){

    add_widget(ui::F::gen(ui::L::VB(),{m_resource()}));
    add_widget(ui::F::gen(ui::L::VB(),
        {m_streamToFile(), m_dontWriteIfFileExists(), m_replaceIfFileExists(), m_addToEndIfFileExists()},
        LStretch{true}, LMargins{true}, QFrame::Box)
    );

    auto l1 = ui::F::gen(ui::L::HB(), {ui::W::txt("Logging file base name:"), m_baseFileName()}, LStretch{false}, LMargins{false});
    auto l2 = ui::F::gen(ui::L::VB(), {m_addRoutineName(), m_addConditionName(), m_addBoth(), m_addCurrentInstanceToFileName()}, LStretch{false}, LMargins{false});
    auto l3 = ui::F::gen(ui::L::HB(), {ui::W::txt("File extension:"), m_fileExtension()}, LStretch{true}, LMargins{false});
    auto l4 = ui::F::gen(ui::L::HB(), {m_addHeaderLine()}, LStretch{true}, LMargins{false});
    auto l5 = ui::F::gen(ui::L::HB(), {ui::W::txt("Header line:"), m_headerLine()}, LStretch{false}, LMargins{false});

    add_widget(ui::F::gen(ui::L::VB(),
        {l1,l2,l3,l4,l5},
        LStretch{true}, LMargins{true}, QFrame::Box)
    );
}

void LoggerConditionInitConfigParametersW::init_and_register_widgets(){


    m_inputUiElements["add_routine"]               =  m_addRoutineName.init_widget("Add routine to file name", false);
    m_inputUiElements["add_condition"]             =  m_addConditionName.init_widget("Add condition to file name", false);
    m_inputUiElements["add_both"]                  =  m_addBoth.init_widget("Add both", true);

    m_inputUiElements["add_current_instance_to_file_name"]  = m_addCurrentInstanceToFileName.init_widget("Add current instance to name", true);
    m_inputUiElements["directory"]                 = m_resource.init_widget(Resource::Type::Directory, "Directory to use:");
    m_inputUiElements["stream_to_file"]            = m_streamToFile.init_widget("Stream to file", true);

    m_inputUiElements["dont_write_if_file_exists"] = m_dontWriteIfFileExists.init_widget("Dont write if file already exists", false);

    m_inputUiElements["replace_if_file_exists"]    = m_replaceIfFileExists.init_widget("Replace file if exists", true);
    m_inputUiElements["add_to_end_if_file_exists"] = m_addToEndIfFileExists.init_widget("Add to end of file if exists", false);
    m_inputUiElements["base_file_name"]            = m_baseFileName.init_widget("log");

    m_inputUiElements["file_extension"]            = m_fileExtension.init_widget("txt");

    m_inputUiElements["add_header_line"]           = m_addHeaderLine.init_widget("Add header line", false);
    m_inputUiElements["header_line"]               = m_headerLine.init_widget("");
}

void LoggerConditionInitConfigParametersW::create_connections(){
    connect(m_addHeaderLine(), &QCheckBox::clicked, this, [&](bool checked){
        m_headerLine.w->setEnabled(checked);
    });
}

void LoggerConditionInitConfigParametersW::late_update_ui(){
    m_headerLine.w->setEnabled(m_addHeaderLine.w->isChecked());
}

