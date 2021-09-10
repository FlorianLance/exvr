

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

    add_input_ui(m_resource.init_widget(Resource::Type::Directory, "Directory to use:"));
    add_input_ui(m_streamToFile.init_widget("Stream to file", true));
    add_input_ui(m_addCurrentInstanceToFileName.init_widget("Add current instance to name", true));
    add_input_ui(m_addDateToFileName.init_widget("Add current date to name", true));
    add_input_ui(m_dontWriteIfFileExists.init_widget("Dont write if file already exists", false));
    add_input_ui(m_insertNewRoutineInfo.init_widget("Insert info at each new routine", false));
    add_input_ui(m_replaceIfFileExists.init_widget("Replace file if exists", true));
    add_input_ui(m_addToEndIfFileExists.init_widget("Add to end of file if exists", false));
    add_input_ui(m_baseFileName.init_widget("log"));
    add_input_ui(m_dateTimeFormat.init_widget("yyyy-MM-dd_H-mm-ss"));
    add_input_ui(m_fileExtension.init_widget("txt"));

    add_input_ui(m_addHeaderLine.init_widget("Add header line", false));
    add_input_ui(m_headerLine.init_widget(""));
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

    add_input_ui(m_resource.init_widget(Resource::Type::Directory, "Directory to use:"));
    add_input_ui(m_streamToFile.init_widget("Stream to file", true));
    add_input_ui(m_addCurrentInstanceToFileName.init_widget("Add current instance to name", true));
    add_input_ui(m_addDateToFileName.init_widget("Add current date to name", true));
    add_input_ui(m_dontWriteIfFileExists.init_widget("Dont write if file already exists", false));

    add_input_ui(m_replaceIfFileExists.init_widget("Replace file if exists", true));
    add_input_ui(m_addToEndIfFileExists.init_widget("Add to end of file if exists", false));
    add_input_ui(m_baseFileName.init_widget("log"));
    add_input_ui(m_dateTimeFormat.init_widget("yyyy-MM-dd_H-mm-ss"));
    add_input_ui(m_fileExtension.init_widget("csv"));

    add_input_ui(m_addHeaderLine.init_widget("Add header line", false));
    add_input_ui(m_headerLine.init_widget(""));

    add_input_ui(m_writeAtEnfOfEachFrame.init_widget("Write columns at the end of each frame", true));
    add_input_ui(m_separator.init_widget(";"));
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

    add_input_ui(m_addRoutineName.init_widget("Add routine to file name", false));
    add_input_ui(m_addConditionName.init_widget("Add condition to file name", false));
    add_input_ui(m_addBoth.init_widget("Add both", true));

    add_input_ui(m_addCurrentInstanceToFileName.init_widget("Add current instance to name", true));
    add_input_ui(m_resource.init_widget(Resource::Type::Directory, "Directory to use:"));
    add_input_ui(m_streamToFile.init_widget("Stream to file", true));

    add_input_ui(m_dontWriteIfFileExists.init_widget("Dont write if file already exists", false));

    add_input_ui(m_replaceIfFileExists.init_widget("Replace file if exists", true));
    add_input_ui(m_addToEndIfFileExists.init_widget("Add to end of file if exists", false));
    add_input_ui(m_baseFileName.init_widget("log"));

    add_input_ui(m_fileExtension.init_widget("txt"));

    add_input_ui(m_addHeaderLine.init_widget("Add header line", false));
    add_input_ui(m_headerLine.init_widget(""));
}

void LoggerConditionInitConfigParametersW::create_connections(){
    connect(m_addHeaderLine(), &QCheckBox::clicked, this, [&](bool checked){
        m_headerLine.w->setEnabled(checked);
    });
}

void LoggerConditionInitConfigParametersW::late_update_ui(){
    m_headerLine.w->setEnabled(m_addHeaderLine.w->isChecked());
}

