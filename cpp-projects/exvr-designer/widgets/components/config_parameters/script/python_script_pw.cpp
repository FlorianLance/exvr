
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "python_script_pw.hpp"

// Qt
#include <QDesktopServices>

// local
#include "path_utility.hpp"

using namespace tool::ex;

void PythonScriptInitConfigParametersW::insert_widgets(){

    add_widget(m_tab = new QTabWidget());
    m_tab->setTabPosition(QTabWidget::TabPosition::North);

    m_tab->addTab(m_pySettings = new QWidget(), "Settings");
    m_pySettings->setLayout(ui::L::VB());
    auto pythonModuleFrame = ui::F::gen(ui::L::HB(), {ui::W::txt("Python module path:"), m_leModulePath(), &m_pbSetModulePath}, LStretch{true}, LMargins{false}, QFrame::NoFrame);
    auto classNameFrame = ui::F::gen(ui::L::HB(),{ui::W::txt("Class name:"),m_leClassName()},  LStretch{false},LMargins{true}, QFrame::NoFrame);
    auto actionsFrames = ui::F::gen(ui::L::HB(),{&m_pbOpenScript, &m_pbGenerateFile},  LStretch{true},LMargins{true}, QFrame::NoFrame);
    auto pythonLibFrame = ui::F::gen(ui::L::HB(), {ui::W::txt("Python 3.7 lib path (optional):"), m_lePythonLibPath(), &m_pbSetPythonLibPath}, LStretch{true}, LMargins{false}, QFrame::NoFrame);
    m_pySettings->layout()->addWidget(ui::F::gen(ui::L::VB(),{pythonModuleFrame, classNameFrame, actionsFrames, pythonLibFrame},  LStretch{true},LMargins{true}, QFrame::Box));

    m_tab->addTab(m_pyParameters = new QWidget(), "Parameters");
    m_pyParameters->setLayout(ui::L::VB());
    m_pyParameters->layout()->addWidget(ui::F::gen(ui::L::VB(),{m_pgGenerator()},  LStretch{true},LMargins{true}, QFrame::Box));
}

void PythonScriptInitConfigParametersW::init_and_register_widgets(){

    m_inputUiElements["path_module"]        = m_leModulePath.init_widget("");
    m_inputUiElements["class_name"]         = m_leClassName.init_widget("DefaultComponent");
    m_inputUiElements["path_lib"]           = m_lePythonLibPath.init_widget("");
    m_inputNonUiArguments["paths_python"]   = Arg::generate_non_ui_arg(Paths::scriptsPythonDir + "|" + Paths::scriptsPythonDir + "/lib", "|");
    m_generatorsUiElements["generator"]     = m_pgGenerator.init_widget(&m_inputUiElements, "generator");

    ui::W::init(&m_pbSetModulePath, "Set");
    ui::W::init(&m_pbSetPythonLibPath, "Set");
    ui::W::init(&m_pbOpenScript, "Open current script");
    ui::W::init(&m_pbGenerateFile, "Generate new script");
}

void PythonScriptInitConfigParametersW::create_connections(){

    connect(&m_pbGenerateFile, &QPushButton::clicked, this, [&]{
        QString path = QFileDialog::getSaveFileName(nullptr, "Choose script name", Paths::scriptsPythonDir, "PY (*.py)");
        if(path.length() > 0 && QFileInfo::exists(Paths::templatePythonScript)){
            QFile::copy(Paths::templatePythonScript, path);
        }
    });
    connect(&m_pbSetModulePath, &QPushButton::clicked, this, [&]{
        // select python file
        QString path = QFileDialog::getOpenFileName(nullptr, "Python file", Paths::scriptsPythonDir, "PY (*.py)");
        if(path.size() > 0){
            m_leModulePath.w->setText(path);
            emit m_leModulePath.w->textChanged(m_leModulePath.w->text());
        }

        m_pbOpenScript.setEnabled(QFile(m_leModulePath.w->text()).exists());
    });
    connect(&m_pbOpenScript, &QPushButton::clicked, this, [&]{
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_leModulePath.w->text()));
    });
    connect(m_leModulePath(), &QLineEdit::textChanged, this, [&]{
        m_pbOpenScript.setEnabled(QFile(m_leModulePath.w->text()).exists());
    });
}

void PythonScriptInitConfigParametersW::late_update_ui(){
    m_pbOpenScript.setEnabled(QFile(m_leModulePath.w->text()).exists());
}

void PythonScriptConfigParametersW::insert_widgets(){
    add_widget(ui::F::gen(ui::L::HB(), {m_pgGenerator()},  LStretch{false},LMargins{false}, QFrame::Box));
}

void PythonScriptConfigParametersW::init_and_register_widgets(){
    m_generatorsUiElements["generator"]             = m_pgGenerator.init_widget(&m_inputUiElements, "generator");
}


//#include "moc_python_script_pw.cpp"
