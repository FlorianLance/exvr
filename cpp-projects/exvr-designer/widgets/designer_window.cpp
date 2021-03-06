
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


// Qt
#include <QProcessEnvironment>
#include <QPushButton>
#include <QMessageBox>
#include <QLocalSocket>
#include <QtConcurrent>
#include <QScrollArea>
#include <QDoubleSpinBox>
#include <QTimer>
#include <QWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QScreen>
#include <QDesktopServices>

// base
#include "utility/benchmark.hpp"

// qt-utility
#include "qt_ui.hpp"

// local
#include "designer_window.hpp"
#include "utility/path_utility.hpp"
#include "connections/data_models/all_node_data_models.hpp"
#include "connections/data_models/connectors/connector_node_data_model.hpp"
#include "experiment/global_signals.hpp"

// debug
#include <QDebug>

using namespace tool::ex;

DesignerWindow::DesignerWindow(bool lncoComponents, QWidget *parent) : QMainWindow(parent){

    // define designer ui
    m_ui.setupUi(this);        
    setAcceptDrops(true);

    create_flow_diagram();
    create_components_manager(lncoComponents);
    create_routines_manager();
    create_element_viewer();

    // create widgets
    create_logger();

    // create toolbar/menu
    create_actions();
    create_menu();
    create_toolbar();

    // status bar
    m_ui.statusBar->addPermanentWidget(m_statusTxt  = new QLabel(), 10);
    m_ui.statusBar->addPermanentWidget(m_loadingBar = new QProgressBar(), 1);
    connect(&m_statusTimer, &QTimer::timeout, this, [&]{
        m_statusTxt->setText("");
    });

    // settings
    set_window_settings();
}

void DesignerWindow::set_window_settings(){

//    QDesktopWidget dw;
    QSize sizeWindow(1920,1080);
    auto screens = QGuiApplication::screens();
    QRect rectScreen = screens[0]->geometry();//dw.availableGeometry();
    if(rectScreen.width() > 0){
        if(rectScreen.width() < sizeWindow.width()){
            sizeWindow.setWidth(rectScreen.width());
        }
        if(rectScreen.height() < sizeWindow.height()){
            sizeWindow.setHeight(rectScreen.height());
        }
    }

    resize(sizeWindow);
}

void DesignerWindow::close_program(){

    blockSignals(true);

    // timers
    m_logTimer.stop();
    while(m_logTimer.isActive()){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
    }

    // close widgets
    m_componentsW->close_all_configs_dialogs();
    m_routinesW->close_all_windows();

    m_flowDiagramW    = nullptr;
    m_elementViewerW  = nullptr;
    m_componentsW     = nullptr;
    m_routinesW       = nullptr;


    blockSignals(false);
}

void DesignerWindow::update_from_experiment(Experiment *experiment, int update){

    bool display = false;
    if(update & ResetUI){
        Bench::start("[Reset ui]"sv, display);
        m_componentsW->reset();
        m_routinesW->reset();
        m_flowDiagramW->reset();
        m_elementViewerW->reset();
        Bench::stop();
    }

    if(update & UpdateComponents){ // update experiment components
        Bench::start("[Update components]"sv, display);
        m_componentsW->update_from_components_manager(ComponentsManager::get());
        Bench::stop();
    }

    if(update & UpdateFlow){ // update flow
        Bench::start("[Update flow]"sv, display);
        m_flowDiagramW->update_from_experiment(experiment);
        Bench::stop();
    }

    if(update & UpdateSelection){ // update selected element
        Bench::start("[Update selected element]"sv, display);
        m_elementViewerW->update_from_current_element(experiment->selectedElement);
        Bench::stop();
    }

    if(update & UpdateRoutines){ // update routines
        Bench::start("[Update routines]"sv, display);
        m_routinesW->update_from_experiment(experiment);
        Bench::stop();             
    }

    if(update & UpdateUI){
        Bench::start("[Update main ui]"sv, false);
        update_main_ui(experiment);
        Bench::stop();
    }

    setWindowTitle(QSL("ExVR [VERSION: ") % experiment->states.numVersion %
        QSL("]  [EXP: ") % experiment->states.currentName % QSL("]  [INSTANCE: ") % experiment->states.currentInstanceName % QSL("]"));
}

void DesignerWindow::display_status(QString status, int ms){
    m_statusTxt->setText(status);
    m_statusTimer.start(ms);
}

void DesignerWindow::insert_log_from_ui(QStringView log){
    logs.append(log.toUtf8());
}

void DesignerWindow::update_main_ui(Experiment *experiment){

    const auto expLauncherState = experiment->states.explauncherState;
    const auto expState = experiment->states.expState;
    QString expStateDescription = from_view(get_description(expState));

    bool canStartLauncher = false;
    bool canExitLauncher  = false;
    bool canLoadExp  = false;
    bool canPlayExp  = false;
    bool canPauseExp = false;
    bool canGotoExp  = false;
    bool canStopExp  = false;

    QString elementName = QSL("-");
    bool displayElementCurrentTime = false;
    bool diplayProgresssbar = false;
    QString currentTime = QSL("Time: 0 (s)");
    QString expTime = "";
    int progressbarValue = 0;

    switch (expLauncherState) {
        case ExpLauncherState::NotStarted:
            canStartLauncher = true;
        break;
        case ExpLauncherState::Starting:
            canExitLauncher = true;
        break;
        case ExpLauncherState::LoadingExperiment:
            canExitLauncher = true;
        break;
        case ExpLauncherState::Closing:
        break;
        case ExpLauncherState::Idle:{

            canExitLauncher = true;
            switch (expState) {
                case ExpState::NotLoaded:
                    canLoadExp = true;
                break;
                case ExpState::Loaded:
                    canPlayExp = true;
                    canLoadExp = true;
                break;
                case ExpState::Running:
                    canPauseExp = true;
                    canGotoExp = true;
                    canStopExp = true;
                break;
                case ExpState::Paused:
                    canPlayExp = true;
                    canStopExp = true;                    
                break;
                default:
                break;
            }

            if(expState == ExpState::Paused || expState == ExpState::Running){

                auto nbCallsSplit = experiment->states.nbCalls.split(";");

                QString n = QSL("<b>") % experiment->states.currentElementName % QSL("</b> (T: ") % nbCallsSplit[0] % QSL(")");

                if(experiment->states.currentElementType == Element::Type::Routine){
                    elementName = QSL("Routine: ")      % n %
                                  QSL(" - Condition: <b>") % experiment->states.currentTypeSpecificInfo % QSL("</b> (T: ") % nbCallsSplit[1] %
                                  QSL(") - ")            % experiment->states.currentOrder;
                }else{

                    elementName = QSL("ISI: ")          % n %
                                  QSL(" - Duration: <b>")  % experiment->states.currentTypeSpecificInfo %
                                  QSL("</b> - ")            % experiment->states.currentOrder;
                }

                currentTime = QSL("Time: ") % QString::number(experiment->states.currentElementTimeS) % QSL(" / ") % QString::number(experiment->states.currentIntervalEndTimeS) % QSL("(s)");
                expTime = QSL("Total exp time: ") % QString::number(experiment->states.experimentTimeS) % QSL("(s)");
                progressbarValue = static_cast<int>((experiment->states.currentElementTimeS/experiment->states.currentIntervalEndTimeS)*100);
                displayElementCurrentTime = true;
                diplayProgresssbar = true;
            }
        }break;
        default:
        break;
    }

    bool designMode = designMode = experiment->states.currentMode == "designer";

    // update buttons
    m_playExperimentAct.setEnabled(canPlayExp);

    m_pauseExperimentAct.setEnabled(canPauseExp);

    m_stopExperimentAct.setEnabled(canStopExp);

    m_nextAct.setEnabled(canGotoExp);
    m_gotoCurrentAct.setEnabled(canGotoExp);
    m_gotoAct.setEnabled(canGotoExp);
    m_previousAct.setEnabled(canGotoExp);

    m_playPauseAct.setEnabled(canPlayExp);
    m_playDelayAct.setEnabled(canPlayExp);

    m_exitExpLauncherAct.setEnabled(true);
    m_startExperimentLauncherAct.setEnabled(true);

    m_loadFullExpWithSpecificInstanceAct.setEnabled(canLoadExp);

    bool loadAndDesign = canLoadExp && designMode;
    m_loadFullExpWithDefaultInstanceAct.setEnabled(loadAndDesign);
    m_loadSelectedRoutineWithDefaultInstanceAct.setEnabled(loadAndDesign);
    m_loadFromSelectedRoutineWithDefaultInstanceAct.setEnabled(loadAndDesign);
    m_loadUntilSelectedRoutineWithDefaultInstanceAct.setEnabled(loadAndDesign);

    if(!experiment->states.followsCurrentCondition){
        m_toggleFollowConditionAct.setIcon(QIcon(":/icons/Follow_condition"));
        m_toggleFollowConditionAct.setToolTip("Follow current condition");
    }else{
        m_toggleFollowConditionAct.setIcon(QIcon(":/icons/Do_not_follow_condition"));
        m_toggleFollowConditionAct.setToolTip("Stop following current condition");
    }

    // update current element info
    m_ui.laExpState->setText(expStateDescription);
    m_ui.laElementName->setText(elementName);
    m_ui.laElementCurrentTime->setVisible(displayElementCurrentTime);
    m_ui.pgbElementCurrentTIme->setVisible(diplayProgresssbar);
    m_ui.laElementCurrentTime->setText(currentTime);
    m_ui.pgbElementCurrentTIme->setValue(progressbarValue);
    m_ui.laExpTime->setText(expTime);

    // update actions
    m_saveExperimentAct.setEnabled(experiment->states.currentExpfilePath.size() > 0);
}

void DesignerWindow::closeEvent(QCloseEvent *event){
    Q_UNUSED(event)
    emit close_exvr_signal();    
}

void DesignerWindow::create_actions(){

    // new / open / save
    m_newExperimentAct.setShortcuts(QKeySequence::New);
    m_newExperimentAct.setText(tr("Create a new experiment"));
    m_newExperimentAct.setStatusTip(tr("&New experiment"));
    m_newExperimentAct.setIcon(QIcon(":/icons/New"));
    connect(&m_newExperimentAct, &QAction::triggered, this, &DesignerWindow::new_experiment_signal);

    m_saveExperimentAct.setShortcuts(QKeySequence::Save);
    m_saveExperimentAct.setStatusTip(tr("Save experiment in current file"));
    m_saveExperimentAct.setText(tr("&Save experiment"));
    m_saveExperimentAct.setIcon(QIcon(":/icons/Save"));
    connect(&m_saveExperimentAct, &QAction::triggered, this, &DesignerWindow::save_experiment_signal);

    m_saveAsExperimentAct.setShortcuts(QKeySequence::SaveAs);
    m_saveAsExperimentAct.setStatusTip(tr("Save experiment in another file"));
    m_saveAsExperimentAct.setText(tr("&Save experiment as"));
    m_saveAsExperimentAct.setIcon(QIcon(":/icons/Save"));
    connect(&m_saveAsExperimentAct, &QAction::triggered, this, &DesignerWindow::save_experiment_as_signal);

    m_exportExperimentAct.setStatusTip(tr("Export experiment with resources to"));
    m_exportExperimentAct.setText(tr("&Export experiment"));
    m_exportExperimentAct.setIcon(QIcon(":/icons/Save"));
    connect(&m_exportExperimentAct, &QAction::triggered, this, &DesignerWindow::export_experiment_as_signal);

    m_loadExperimentAct.setShortcuts(QKeySequence::Open);
    m_loadExperimentAct.setStatusTip(tr("Open experiment file"));
    m_loadExperimentAct.setText(tr("&Open experiment"));
    m_loadExperimentAct.setIcon(QIcon(":/icons/Open"));
    connect(&m_loadExperimentAct, &QAction::triggered, this, &DesignerWindow::load_experiment_signal);

    m_exitExVRAct.setShortcuts(QKeySequence::Quit);
    m_exitExVRAct.setStatusTip(tr("Exit ExVR"));
    m_exitExVRAct.setText(tr("&Exit"));    
    connect(&m_exitExVRAct, &QAction::triggered, this, &DesignerWindow::close);

    // experiment
    m_generateInstancesAct.setText(tr("&Generate randomized instances files"));
    m_generateInstancesAct.setStatusTip(tr("Generate randomized instances files"));
    m_generateInstancesAct.setIcon(QIcon(":/icons/Dices"));
    connect(&m_generateInstancesAct, &QAction::triggered, this, &DesignerWindow::generate_instances_signals);

    m_playExperimentAct.setText(tr("&Play exp"));
    m_playExperimentAct.setStatusTip(tr("Play or resume current experiment"));
    m_playExperimentAct.setIcon(QIcon(":/icons/Play"));
    connect(&m_playExperimentAct, &QAction::triggered, this, &DesignerWindow::play_experiment_signal);

    m_playPauseAct.setText(tr("&Play exp and set pause "));
    m_playPauseAct.setStatusTip(tr("Play experiment and set pause"));
    m_playPauseAct.setIcon(QIcon(":/icons/Play_pause"));
    connect(&m_playPauseAct, &QAction::triggered, this, &DesignerWindow::play_pause_experiment_signal);

    m_playDelayAct.setText(tr("&Play exp after specified time"));
    m_playDelayAct.setStatusTip(tr("Play exp after specified time"));
    m_playDelayAct.setIcon(QIcon(":/icons/Play_delay"));
    connect(&m_playDelayAct, &QAction::triggered, this, &DesignerWindow::play_delay_experiment_signal);

    m_pauseExperimentAct.setText(tr("&Pause exp"));
    m_pauseExperimentAct.setStatusTip(tr("Pause current experiment"));
    m_pauseExperimentAct.setIcon(QIcon(":/icons/Pause"));
    connect(&m_pauseExperimentAct, &QAction::triggered, this, &DesignerWindow::pause_experiment_signal);

    m_stopExperimentAct.setText(tr("&Stop exp"));
    m_stopExperimentAct.setStatusTip(tr("Stop current experiment"));
    m_stopExperimentAct.setIcon(QIcon(":/icons/Stop"));
    connect(&m_stopExperimentAct, &QAction::triggered, this, &DesignerWindow::stop_experiment_signal);

    m_loadFullExpWithDefaultInstanceAct.setText(tr("&Load full experiment with default instance"));
    m_loadFullExpWithDefaultInstanceAct.setStatusTip(tr("Load full experiment with default instance"));
    m_loadFullExpWithDefaultInstanceAct.setIcon(QIcon(":/icons/Play_default_instance"));
    connect(&m_loadFullExpWithDefaultInstanceAct, &QAction::triggered, this, &DesignerWindow::load_full_exp_wtih_default_instance_signal);

    m_loadFromSelectedRoutineWithDefaultInstanceAct.setText(tr("&Load experiment from selected routine to the end with default instance"));
    m_loadFromSelectedRoutineWithDefaultInstanceAct.setStatusTip(tr("Load experiment from selected routine to the end with default instance"));
    m_loadFromSelectedRoutineWithDefaultInstanceAct.setIcon(QIcon(":/icons/Play_default_instance_since"));
    connect(&m_loadFromSelectedRoutineWithDefaultInstanceAct, &QAction::triggered, this, &DesignerWindow::load_from_selected_routine_with_default_instance_signal);

    m_loadUntilSelectedRoutineWithDefaultInstanceAct.setText(tr("&Load experiment from start to selected routine with default instance"));
    m_loadUntilSelectedRoutineWithDefaultInstanceAct.setStatusTip(tr("Load experiment from start to selected routine with default instance"));
    m_loadUntilSelectedRoutineWithDefaultInstanceAct.setIcon(QIcon(":/icons/Play_default_instance_until"));
    connect(&m_loadUntilSelectedRoutineWithDefaultInstanceAct, &QAction::triggered, this, &DesignerWindow::load_until_selected_routine_with_default_instance_signal);

    m_loadFullExpWithSpecificInstanceAct.setText(tr("&Load full experiment with a specific instance"));
    m_loadFullExpWithSpecificInstanceAct.setStatusTip(tr("Load full experiment with a specific instance"));
    m_loadFullExpWithSpecificInstanceAct.setIcon(QIcon(":/icons/Dice"));
    connect(&m_loadFullExpWithSpecificInstanceAct, &QAction::triggered, this, &DesignerWindow::load_full_exp_with_specific_instance_signal);

    m_loadSelectedRoutineWithDefaultInstanceAct.setText(tr("&Load selected routine with selected condition and default instance"));
    m_loadSelectedRoutineWithDefaultInstanceAct.setStatusTip(tr("Load selected routine with selected condition and default instance"));
    m_loadSelectedRoutineWithDefaultInstanceAct.setIcon(QIcon(":/icons/Play_routine"));
    connect(&m_loadSelectedRoutineWithDefaultInstanceAct, &QAction::triggered, this, &DesignerWindow::load_selected_routine_with_default_instance_signal);

    m_startExperimentLauncherAct.setText(tr("&Start Experiment launcher"));
    m_startExperimentLauncherAct.setStatusTip(tr("Start Experiment launcher"));
    m_startExperimentLauncherAct.setIcon(QIcon(":/icons/Launch_exvr_exp"));
    connect(&m_startExperimentLauncherAct, &QAction::triggered, this, &DesignerWindow::start_experiment_launcher_signal);

    m_exitExpLauncherAct.setText(tr("&Close Experiment launcher"));
    m_exitExpLauncherAct.setStatusTip(tr("Close Experiment launcher"));
    m_exitExpLauncherAct.setIcon(QIcon(":/icons/Close_unity"));
    connect(&m_exitExpLauncherAct, &QAction::triggered, this, &DesignerWindow::exit_experiment_launcher_signal);

    m_nextAct.setText(tr("Next element"));
    m_nextAct.setStatusTip(tr("Next element"));
    m_nextAct.setIcon(QIcon(":/icons/Next"));
    connect(&m_nextAct, &QAction::triggered, this, &DesignerWindow::next_element_signal);

    m_gotoCurrentAct.setText(tr("Go to current selected element from current loaded instance"));
    m_gotoCurrentAct.setStatusTip(tr("Go to specific element from current loaded instance"));
    m_gotoCurrentAct.setIcon(QIcon(":/icons/Go_to_current"));
    connect(&m_gotoCurrentAct, &QAction::triggered, this, &DesignerWindow::go_to_current_element_signal);

    m_gotoAct.setText(tr("Go to specific element from current loaded instance"));
    m_gotoAct.setStatusTip(tr("Go to specific element from current loaded instance"));
    m_gotoAct.setIcon(QIcon(":/icons/Go_to"));
    connect(&m_gotoAct, &QAction::triggered, this, &DesignerWindow::go_to_specific_element_signal);

    m_previousAct.setText(tr("&Previous element"));
    m_previousAct.setStatusTip(tr("Previous element"));
    m_previousAct.setIcon(QIcon(":/icons/Previous"));
    connect(&m_previousAct, &QAction::triggered, this, &DesignerWindow::previous_element_signal);

    m_settingsAct.setText(tr("&Settings"));
    m_settingsAct.setStatusTip(tr("Settings"));
    m_settingsAct.setIcon(QIcon(":/icons/Settings"));
    connect(&m_settingsAct, &QAction::triggered, GSignals::get(), &GSignals::show_settings_dialog_signal);

    m_benchmarkAct.setText(tr("&Benchmark"));
    m_benchmarkAct.setStatusTip(tr("Benchmark"));
    connect(&m_benchmarkAct, &QAction::triggered, GSignals::get(), &GSignals::show_benchmark_dialog_signal);

    m_clearLogsAct.setText(tr("&Erase logs"));
    m_clearLogsAct.setStatusTip(tr("Erase logs"));
    m_clearLogsAct.setIcon(QIcon(":/icons/Eraser"));
    connect(&m_clearLogsAct, &QAction::triggered, this, [&]{
        m_ui.tbLogs->clear();
    });

    m_showHelpAct.setText(tr("&Show help"));
    m_showHelpAct.setStatusTip(tr("Show help"));
    m_showHelpAct.setIcon(QIcon(":/icons/Help"));
    connect(&m_showHelpAct, &QAction::triggered, GSignals::get(), &GSignals::show_documentation_signal);

    m_switchModeAct.setText(tr("&Switch between designer and experiment mode"));
    m_switchModeAct.setStatusTip(tr("Switch between designer and experiment UI mode"));
    connect(&m_switchModeAct, &QAction::triggered, this, [&]{
        emit GSignals::get()->toggle_mode_signal();
    });

    m_saveExpToTempAct.setText(tr("&Save current exp to temp"));
    m_saveExpToTempAct.setStatusTip(tr("Save current exp to temp"));
    m_saveExpToTempAct.setIcon(QIcon(":/icons/Save"));
    connect(&m_saveExpToTempAct, &QAction::triggered, this, &DesignerWindow::save_experiment_to_temp_signal);

    m_openTempExpAct.setText(tr("&Open current temp exp xml file"));
    m_openTempExpAct.setStatusTip(tr("Open current temp exp xml file"));
    m_openTempExpAct.setIcon(QIcon(":/icons/Open"));
    connect(&m_openTempExpAct, &QAction::triggered, this, &DesignerWindow::open_temp_experiment_file_signal);

    m_openExpDirectoryAct.setText(tr("&Open experiments directory"));
    m_openExpDirectoryAct.setStatusTip(tr("Open default experiments directory"));
    m_openExpDirectoryAct.setIcon(QIcon(":/icons/Open"));
    connect(&m_openExpDirectoryAct, &QAction::triggered, this, &DesignerWindow::open_experiment_directory_signal);

    m_openTempInstanceAct.setText(tr("&Open current temp instance xml file"));
    m_openTempInstanceAct.setStatusTip(tr("Open current instance exp xml file"));
    m_openTempInstanceAct.setIcon(QIcon(":/icons/Open"));
    connect(&m_openTempInstanceAct, &QAction::triggered, this, &DesignerWindow::open_temp_instance_file_signal);    

    m_openLogsDirectoryAct.setText(tr("&Open logs directory"));
    m_openLogsDirectoryAct.setStatusTip(tr("Open logs directory"));
    m_openLogsDirectoryAct.setIcon(QIcon(":/icons/Open"));
    connect(&m_openLogsDirectoryAct, &QAction::triggered, this, &DesignerWindow::open_log_directory_signal);

    m_openCurrentDesignerLogAct.setText(tr("&Open current designer log file"));
    m_openCurrentDesignerLogAct.setStatusTip(tr("Open current designer log file"));
    m_openCurrentDesignerLogAct.setIcon(QIcon(":/icons/Open"));
    connect(&m_openCurrentDesignerLogAct, &QAction::triggered, this, &DesignerWindow::open_current_designer_log_file_signal);

    m_openCurrentExpLauncherLogAct.setText(tr("&Open current exp-launcher log file"));
    m_openCurrentExpLauncherLogAct.setStatusTip(tr("Open current exp-launcher log file"));
    m_openCurrentExpLauncherLogAct.setIcon(QIcon(":/icons/Open"));
    connect(&m_openCurrentExpLauncherLogAct, &QAction::triggered, this, &DesignerWindow::open_current_exp_launcher_log_file_signal);

    m_showDocumentationEditorAct.setText(tr("&Display documentation"));
    m_showDocumentationEditorAct.setStatusTip(tr("Display documentation"));
    m_showDocumentationEditorAct.setIcon(QIcon(":/icons/Help"));
    connect(&m_showDocumentationEditorAct, &QAction::triggered, GSignals::get(), &GSignals::show_documentation_signal);

    m_aboutAct.setText(tr("&About ExVR"));
    m_aboutAct.setStatusTip(tr("About ExVR"));
    connect(&m_aboutAct, &QAction::triggered, GSignals::get(), &GSignals::show_about_signal);

    m_showResourcesManagerDialogAct.setText(tr("&Display resources manager"));
    m_showResourcesManagerDialogAct.setStatusTip(tr("Display resources manager"));
    m_showResourcesManagerDialogAct.setIcon(QIcon(":/icons/Resources"));
    connect(&m_showResourcesManagerDialogAct, &QAction::triggered, [&]{
        GSignals::get()->show_resources_manager_dialog_signal();
    });

    m_showCSharpScriptDirectoryAct.setText(tr("&Show C# scripts directory"));
    m_showCSharpScriptDirectoryAct.setStatusTip(tr("Show C# scripts default directory"));
    m_showCSharpScriptDirectoryAct.setIcon(QIcon(":/icons/Open"));
    connect(&m_showCSharpScriptDirectoryAct, &QAction::triggered, this, [=]{
       QDesktopServices::openUrl(QUrl(Paths::scriptsCSharpDir, QUrl::TolerantMode));
    });

    m_focusFlowAct.setText(tr("&Display only flow panel"));
    m_focusFlowAct.setStatusTip(tr("Display only flow panel"));
    m_focusFlowAct.setIcon(QIcon(":/icons/FocusFlow"));
    connect(&m_focusFlowAct, &QAction::triggered, this, [&]{
        m_ui.wFlow->setVisible(true);
        m_ui.wRoutines->setVisible(false);
        m_focusFlowButton.setEnabled(false);
        m_focusRoutinesButton.setEnabled(true);
        m_focusBothButton.setEnabled(true);
    });
    m_focusRoutinesAct.setText(tr("&Display only routines panel"));
    m_focusRoutinesAct.setStatusTip(tr("Display only routines panel"));
    m_focusRoutinesAct.setIcon(QIcon(":/icons/FocusRoutines"));
    connect(&m_focusRoutinesAct, &QAction::triggered, this, [&]{
        m_ui.wFlow->setVisible(false);
        m_ui.wRoutines->setVisible(true);
        m_focusFlowButton.setEnabled(true);
        m_focusRoutinesButton.setEnabled(false);
        m_focusBothButton.setEnabled(true);
    });
    m_focusBothAct.setText(tr("&Display both panels"));
    m_focusBothAct.setStatusTip(tr("Display both panels"));
    m_focusBothAct.setIcon(QIcon(":/icons/FocusBoth"));
    connect(&m_focusBothAct, &QAction::triggered, this, [&]{
        m_ui.wFlow->setVisible(true);
        m_ui.wRoutines->setVisible(true);
        m_focusFlowButton.setEnabled(true);
        m_focusRoutinesButton.setEnabled(true);
        m_focusBothButton.setEnabled(false);
    });

    m_toggleFollowConditionAct.setText(tr("&Toggle follow current experiment condition mode"));
    m_toggleFollowConditionAct.setStatusTip(tr("Toggle follow current experiment condition mode"));
    connect(&m_toggleFollowConditionAct, &QAction::triggered, GSignals::get(), &GSignals::toggle_follow_condition_mode_signal);

    m_toggleActionsConnectionsSeparationAct.setText(tr("&Toggle Actions/Connections panel separation"));
    m_toggleActionsConnectionsSeparationAct.setStatusTip(tr("Toggle Actions/Connections panel separation"));
    m_toggleActionsConnectionsSeparationAct.setIcon(QIcon(":/icons/Actions_connections_split"));
    connect(&m_toggleActionsConnectionsSeparationAct, &QAction::triggered, this, &DesignerWindow::toggle_actions_connections_separation_signal);

}

void DesignerWindow::create_menu(){

    // file
    QMenu *menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(&m_newExperimentAct);
    menu->addSeparator();
    menu->addAction(&m_saveExperimentAct);
    menu->addAction(&m_saveAsExperimentAct);
    menu->addSeparator();
    menu->addAction(&m_loadExperimentAct);
    menu->addAction(&m_openExpDirectoryAct);
    menu->addSeparator();
    menu->addAction(&m_exportExperimentAct);
    menu->addSeparator();
    menu->addAction(&m_exitExVRAct);
    // experiment
    menu = menuBar()->addMenu(tr("&Exp launcher"));
    menu->addAction(&m_startExperimentLauncherAct);
    menu->addAction(&m_exitExpLauncherAct);
    menu->addSeparator();
    menu->addAction(&m_loadFullExpWithSpecificInstanceAct);
    menu->addSeparator();
    menu->addAction(&m_loadFullExpWithDefaultInstanceAct);
    menu->addAction(&m_loadFromSelectedRoutineWithDefaultInstanceAct);
    menu->addAction(&m_loadUntilSelectedRoutineWithDefaultInstanceAct);
    menu->addAction(&m_loadSelectedRoutineWithDefaultInstanceAct);
    menu->addSeparator();
    menu->addAction(&m_switchModeAct);
    // resources
    menu = menuBar()->addMenu(tr("&Resources"));
    menu->addAction(&m_showResourcesManagerDialogAct); 
    menu->addAction(&m_showCSharpScriptDirectoryAct);
    // logs
    menu = menuBar()->addMenu(tr("&Logs"));
    menu->addAction(&m_openLogsDirectoryAct);
    menu->addAction(&m_openCurrentDesignerLogAct);
    menu->addAction(&m_openCurrentExpLauncherLogAct);
    // debug
    menu = menuBar()->addMenu(tr("&Debug"));
    menu->addAction(&m_saveExpToTempAct);
    menu->addSeparator();
    menu->addAction(&m_openTempExpAct);
    menu->addAction(&m_openTempInstanceAct);
    menu->addSeparator();
    menu->addAction(&m_benchmarkAct);
    // doc
    menu = menuBar()->addMenu(tr("&?"));
    menu->addAction(&m_showDocumentationEditorAct);
    menu->addAction(&m_aboutAct);
}

void DesignerWindow::create_toolbar(){

    QToolBar* tb = addToolBar(tr("Toolbar"));
    tb->setMovable(false);
    tb->setFloatable(false);
    tb->setAllowedAreas(Qt::ToolBarArea::TopToolBarArea);
    tb->setContextMenuPolicy(Qt::PreventContextMenu);

        m_newFileButton.setDefaultAction(&m_newExperimentAct);
        tb->addWidget(&m_newFileButton);

        m_saveAsButton.setDefaultAction(&m_saveAsExperimentAct);
        tb->addWidget(&m_saveAsButton);

        m_openButton.setDefaultAction(&m_loadExperimentAct);
        tb->addWidget(&m_openButton);

    tb->addSeparator();

        m_expLauncherButton.setDefaultAction(&m_startExperimentLauncherAct);
        tb->addWidget(&m_expLauncherButton);

        m_exitExpLauncherButton.setDefaultAction(&m_exitExpLauncherAct);
        tb->addWidget(&m_exitExpLauncherButton);

    tb->addSeparator();

        m_generateInstancesButton.setDefaultAction(&m_generateInstancesAct);
        tb->addWidget(&m_generateInstancesButton);

        m_loadFullExpWithSpecificInstanceButton.setDefaultAction(&m_loadFullExpWithSpecificInstanceAct);
        tb->addWidget(&m_loadFullExpWithSpecificInstanceButton);

    tb->addSeparator();

        m_loadFullExpWithDefaultInstanceButton.setDefaultAction(&m_loadFullExpWithDefaultInstanceAct);
        tb->addWidget(&m_loadFullExpWithDefaultInstanceButton);

        m_loadFromSelectedRoutineWithDefaultInstanceButton.setDefaultAction(&m_loadFromSelectedRoutineWithDefaultInstanceAct);
        tb->addWidget(&m_loadFromSelectedRoutineWithDefaultInstanceButton);

        m_loadUntilSelectedRoutineWithDefaultInstanceButton.setDefaultAction(&m_loadUntilSelectedRoutineWithDefaultInstanceAct);
        tb->addWidget(&m_loadUntilSelectedRoutineWithDefaultInstanceButton);

        m_loadSelectedRoutineWithDefaultInstanceButton.setDefaultAction(&m_loadSelectedRoutineWithDefaultInstanceAct);
        tb->addWidget(&m_loadSelectedRoutineWithDefaultInstanceButton);

    tb->addSeparator();

        m_playButton.setDefaultAction(&m_playExperimentAct);
        tb->addWidget(&m_playButton);

        m_playPauseButton.setDefaultAction(&m_playPauseAct);
        tb->addWidget(&m_playPauseButton);

        m_playDelayButton.setDefaultAction(&m_playDelayAct);
        tb->addWidget(&m_playDelayButton);

        m_pauseButton.setDefaultAction(&m_pauseExperimentAct);
        tb->addWidget(&m_pauseButton);

        m_stopButton.setDefaultAction(&m_stopExperimentAct);
        tb->addWidget(&m_stopButton);

    tb->addSeparator();

        m_previousButton.setDefaultAction(&m_previousAct);
        tb->addWidget(&m_previousButton);

        m_nextButton.setDefaultAction(&m_nextAct);
        tb->addWidget(&m_nextButton);

        m_gotoCurrentButton.setDefaultAction(&m_gotoCurrentAct);
        tb->addWidget(&m_gotoCurrentButton);

        m_gotoButton.setDefaultAction(&m_gotoAct);
        tb->addWidget(&m_gotoButton);

    tb->addSeparator();

        m_settingsButton.setDefaultAction(&m_settingsAct);
        tb->addWidget(&m_settingsButton);

        m_showResourcesManagerButton.setDefaultAction(&m_showResourcesManagerDialogAct);
        tb->addWidget(&m_showResourcesManagerButton);

    tb->addSeparator();

        m_focusFlowButton.setDefaultAction(&m_focusFlowAct);
        tb->addWidget(&m_focusFlowButton);

        m_focusRoutinesButton.setDefaultAction(&m_focusRoutinesAct);
        tb->addWidget(&m_focusRoutinesButton);

        m_focusBothButton.setDefaultAction(&m_focusBothAct);
        tb->addWidget(&m_focusBothButton);

        m_followButton.setDefaultAction(&m_toggleFollowConditionAct);
        tb->addWidget(&m_followButton);

    tb->addSeparator();

        m_toggleActionsConnectionsSeparationButton.setDefaultAction(&m_toggleActionsConnectionsSeparationAct);
        tb->addWidget(&m_toggleActionsConnectionsSeparationButton);

    tb->addSeparator();

        m_clearLogsButton.setDefaultAction(&m_clearLogsAct);
        tb->addWidget(&m_clearLogsButton);

    tb->addSeparator();

        m_showHelpButton.setDefaultAction(&m_showHelpAct);
        tb->addWidget(&m_showHelpButton);
}

void DesignerWindow::create_logger(){

    m_ui.tbLogs->zoomIn(2);
    m_ui.tbLogs->setStyleSheet("background-color: rgb(45,45,45);");
    m_ui.tbLogs->setAcceptDrops(false);
    m_ui.tbLogs->setOpenLinks(false);
    m_ui.tbLogs->setUndoRedoEnabled(false);
    m_ui.tbLogs->setReadOnly(true);
    m_ui.tbLogs->setContextMenuPolicy(Qt::NoContextMenu);
    m_ui.tbLogs->document()->setMaximumBlockCount(400);

    // TODO: crash when quit
    connect(&m_logTimer, &QTimer::timeout, this, [&]{

        if(logs.size() == 0){
            return;
        }

        QTextBlockFormat format;
        QTextCursor cursor = m_ui.tbLogs->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.insertBlock(format);
        for(int ii = 0; ii < logs.size(); ++ii){
            //            cursor.insertHtml(std::move(logs[ii]));
            if( ii < logs.size() -1){
                cursor.insertHtml(std::move(logs[ii]) % QSL("<br>"));
            }else{
                cursor.insertHtml(std::move(logs[ii]));
            }
        }

        logs.clear();
        m_ui.tbLogs->setTextCursor(cursor); // TODO: UI settings

    });
    m_logTimer.start(1000/15);
}


void DesignerWindow::create_flow_diagram(){
    m_flowDiagramW = std::make_unique<FlowDiagramW>(m_ui.vsZoom, m_ui.pbResize);
    m_ui.hlFlows->setSizeConstraint(QLayout::SetMinAndMaxSize);
    m_ui.hlFlows->insertWidget(0,m_flowDiagramW.get());
}

void DesignerWindow::create_components_manager(bool lncoComponents){

    m_componentsW = std::make_unique<ComponentsManagerW>(lncoComponents);
    m_ui.vlComponents->addWidget(m_componentsW.get());
}

void DesignerWindow::create_routines_manager(){

    DataNodeModels::initialize();

    m_routinesW = std::make_unique<RoutinesManagerTW>();
    auto lR = ui::L::HB();
    lR->setContentsMargins(0,0,0,0);
    lR->addWidget(m_routinesW.get());
    m_ui.wRoutines->setLayout(lR);    
}

void DesignerWindow::create_element_viewer(){
    m_elementViewerW = std::make_unique<ElementViewerW>(m_ui.twSelectedElement);
}

//#include "moc_designer_window.cpp"
