
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_line_edit_w.hpp"

namespace tool::ex {

class PythonScriptInitConfigParametersW : public ConfigParametersW{

public :

    QPushButton m_pbGenerateFile;

    ExLineEditW m_leModulePath;
    QPushButton m_pbSetModulePath;

    ExLineEditW m_lePythonLibPath;
    QPushButton m_pbSetPythonLibPath;

    ExLineEditW m_leClassName;

    QPushButton m_pbOpenScript;

    ExParametersGeneratorWidgetW m_pgGenerator;

    QTabWidget *m_tab = nullptr;
    QWidget *m_pySettings = nullptr;
    QWidget *m_pyParameters = nullptr;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};


class PythonScriptConfigParametersW : public ConfigParametersW{

public :

    ExParametersGeneratorWidgetW m_pgGenerator;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override{}
    void late_update_ui() override{}
};

}
