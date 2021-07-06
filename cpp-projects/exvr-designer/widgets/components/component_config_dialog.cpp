
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "component_config_dialog.hpp"

// Qt
#include <QIcon>
#include <QImage>
#include <QToolButton>
#include <QLineEdit>
#include <QMessageBox>

// base
#include "utility/types_utility.hpp"
#include "utility/benchmark.hpp"

// local
#include "global_signals.hpp"

// # parameters
#include "fixation_cross_viewer_pw.hpp"
#include "python_script_pw.hpp"
#include "csharp_script_pw.hpp"
#include "duo_tracking_pw.hpp"
#include "asset_bundle_pw.hpp"
#include "slider_ui_pw.hpp"
#include "camera_target_pw.hpp"
#include "audio_source_pw.hpp"
#include "udp_reader_pw.hpp"
#include "udp_writer_pw.hpp"
#include "webcam_viewer_pw.hpp"
#include "joypad_pw.hpp"
#include "logger_pw.hpp"
#include "microphone_pw.hpp"
#include "scene_scaner_pw.hpp"
#include "mouse_pw.hpp"
#include "text_resource_pw.hpp"
#include "leap_motion_arms_display_pw.hpp"
#include "serial_port_writer_pw.hpp"
#include "falling_spheres_pw.hpp"
#include "mirror_pw.hpp"
#include "text_viewer_pw.hpp"
#include "video_file_camera_pw.hpp"
#include "camera_pw.hpp"
#include "camera_trajectory_pw.hpp"
#include "camera_trajectory_file_pw.hpp"
#include "keyboard_pw.hpp"
#include "flashing_dot_pw.hpp"
#include "primitives_model_pw.hpp"
#include "mark_to_clean_pw.hpp"
#include "target_to_grab_pw.hpp"
#include "attach_object_to_hand_pw.hpp"
#include "biopac_pw.hpp"
#include "thera_trainer_tracking_pw.hpp"
#include "thera_trainer_platform_pw.hpp"
#include "video_file_pw.hpp"
#include "webcam_pw.hpp"
#include "image_viewer_pw.hpp"
#include "image_resource_pw.hpp"
#include "video_generator_pw.hpp"
#include "sky_pw.hpp"
#include "parallel_port_writer_pw.hpp"
#include "cloud_pw.hpp"
#include "scaner_video_pw.hpp"
#include "humanoid_controller_pw.hpp"
#include "kinect_manager_pw.hpp"
#include "kinect_body_tracking_pw.hpp"
#include "plot_resource_pw.hpp"
#include "qualisys_tracking_pw.hpp"
#include "mri_pw.hpp"
#include "fov_simulator_pw.hpp"
#include "sonceboz_sg_pw.hpp"
#include "multi_ab_pw.hpp"
#include "fop_robot_pw.hpp"
#include "blend_fade_viewer_pw.hpp"
#include "flag_pole_pw.hpp"

// debug
#include <QDebug>


using namespace tool::ex;

ComponentConfigDialog::ComponentConfigDialog(QWidget *parent, Component *component){

    // set base ui of the dialog
    m_ui.setupUi(this);


    m_ui.tabConfigs->setMovable(true);
    m_ui.pbReset->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_ui.pbPin->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_ui.pbHelp->setFocusPolicy(Qt::FocusPolicy::NoFocus);


    setModal(false);
    m_parent = parent;
    defaultFlags = windowFlags() & ~Qt::WindowContextHelpButtonHint;
    setWindowFlags(defaultFlags);

    Bench::start("[ComponentsConfigDialog init 1]"sv, false);
    componentKey = ComponentKey{component->key()};
    m_ui.leName->setText(component->name());

    // init widget
    setWindowTitle(QSL("[") % from_view(Component::get_full_name(component->type)) % QSL("] component settings"));
    setWindowIcon(QIcon(from_view(Component::get_icon_path(component->type))));

    // change component name
    connect(m_ui.leName, &QLineEdit::textChanged, this, [=](QString text){
       emit GSignals::get()->component_name_changed_signal(componentKey, text);
    });

    // remove selected config
    connect(m_ui.pbRemoveConfig, &QPushButton::clicked, this, [=]{
        auto id = m_ui.tabConfigs->currentIndex();
        if(id >= 0 && id < m_ui.tabConfigs->count()){
            m_ui.tabConfigs->removeTab(id);
            emit GSignals::get()->remove_config_signal(componentKey, RowId{id});
        }
    });

    // add a new config
    connect(m_ui.pbInsertNewConfig, &QPushButton::clicked, this, [&]{

        // create a dialog for choosing the configuration name
        QDialog configNameDialog;
        configNameDialog.setWindowTitle(QSL("Add new config"));
        configNameDialog.setModal(true);
        configNameDialog.setLayout(new QHBoxLayout());
        configNameDialog.layout()->addWidget(new QLabel(QSL("Name: ")));

        QLineEdit *le = new QLineEdit(QSL("Config ") % QString::number(m_ui.tabConfigs->count()));
        configNameDialog.layout()->addWidget(le);
        QPushButton *pbV = new QPushButton(QSL("Ok"));
        QPushButton *pbC = new QPushButton(QSL("Cancel"));
        connect(pbV, &QPushButton::clicked, this, [&]{
           configNameDialog.done(1);
        });
        connect(pbC, &QPushButton::clicked, this, [&]{
           configNameDialog.done(0);
        });
        configNameDialog.layout()->addWidget(pbV);
        configNameDialog.layout()->addWidget(pbC);
        le->setFocus();

        int res = configNameDialog.exec();
        if(res == 1){ // if config validated
            int id = m_ui.tabConfigs->currentIndex();
            if(id == -1){
                id = 0;
            }
            emit GSignals::get()->insert_config_signal(componentKey, RowId{id}, le->text());
        }
    });

    connect(m_ui.pbDuplicate, &QPushButton::clicked, this, [&]{

        // create a dialog for choosing the configuration name
        QDialog configNameDialog;
        configNameDialog.setWindowTitle(QSL("Duplicate selected config"));
        configNameDialog.setModal(true);
        configNameDialog.setLayout(new QHBoxLayout());
        configNameDialog.layout()->addWidget(new QLabel(QSL("Name: ")));

        QLineEdit *le = new QLineEdit(m_ui.tabConfigs->tabText(m_ui.tabConfigs->currentIndex()) % QSL("(copy)"));
        configNameDialog.layout()->addWidget(le);
        QPushButton *pbV = new QPushButton(QSL("Ok"));
        QPushButton *pbC = new QPushButton(QSL("Cancel"));
        connect(pbV, &QPushButton::clicked, this, [&]{
           configNameDialog.done(1);
        });
        connect(pbC, &QPushButton::clicked, this, [&]{
           configNameDialog.done(0);
        });
        configNameDialog.layout()->addWidget(pbV);
        configNameDialog.layout()->addWidget(pbC);
        le->setFocus();

        int res = configNameDialog.exec();
        if(res == 1){ // if config validated
            int id = m_ui.tabConfigs->currentIndex();
            if(id == -1){
                id = 0;
            }
            emit GSignals::get()->copy_config_signal(componentKey, RowId{id}, le->text());
        }
    });

    connect(m_ui.pbRenameConfig, &QPushButton::clicked, this, [&]{

        // create a dialog for choosing the configuration name
        QDialog configNameDialog;
        configNameDialog.setWindowTitle(QSL("Rename config"));
        configNameDialog.setModal(true);
        configNameDialog.setLayout(new QHBoxLayout());
        configNameDialog.layout()->addWidget(new QLabel(QSL("Name: ")));
        QLineEdit *le = new QLineEdit(m_ui.tabConfigs->tabText(m_ui.tabConfigs->currentIndex()));
                configNameDialog.layout()->addWidget(le);
        QPushButton *pbV = new QPushButton(QSL("Ok"));
        QPushButton *pbC = new QPushButton(QSL("Cancel"));
        connect(pbV, &QPushButton::clicked, this, [&]{
           configNameDialog.done(1);
        });
        connect(pbC, &QPushButton::clicked, this, [&]{
           configNameDialog.done(0);
        });
        configNameDialog.layout()->addWidget(pbV);
        configNameDialog.layout()->addWidget(pbC);
        le->setFocus();

        int res = configNameDialog.exec();
        if(res == 1){ // if config validated
            int id = m_ui.tabConfigs->currentIndex();
            if(id == -1){
                id = 0;
            }
            emit GSignals::get()->rename_config_signal(componentKey, RowId{id}, le->text());
        }
    });

    auto componentType = component->type;
    connect(m_ui.pbHelp, &QPushButton::clicked, this, [=]{
        emit GSignals::get()->display_component_help_window_signal(componentType);
    });

    connect(m_ui.pbPin, &QPushButton::clicked, this, [=] {
        if(!pinned){
            setParent(m_parent);
            setWindowFlags(Qt::Dialog);
            setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
            m_ui.pbPin->setIcon(QIcon(":/icons/Unpin"));
        }else{
            setParent(nullptr);
            setWindowFlags(defaultFlags);
            m_ui.pbPin->setIcon(QIcon(":/icons/Pin"));
        }
        pinned = !pinned;
        show();
    });

    connect(m_ui.pbReset, &QPushButton::clicked, this, [&]{

        const bool resetInitConfig  = m_ui.twAllConfigs->currentIndex() == 0;
        const int idCurrentConfig   = m_ui.tabConfigs->currentIndex();
        ConfigW *configW = nullptr;
        if(resetInitConfig){
            configW = get_init_config_widget();
        }else{
            configW = get_config_widget(idCurrentConfig);
        }

        QDialog resetConfigDialog;
        resetConfigDialog.setWindowTitle(QSL("Reset config"));
        resetConfigDialog.setModal(true);
        resetConfigDialog.setLayout(new QHBoxLayout());
        resetConfigDialog.layout()->addWidget(new QLabel(QSL("You are going to reset ") %
            QString(resetInitConfig ? QSL("init") : QSL("current selected")) % QSL(" config values.")));

        QPushButton *pbV = new QPushButton(QSL("Ok"));
        QPushButton *pbC = new QPushButton(QSL("Cancel"));
        connect(pbV, &QPushButton::clicked, this, [&]{
           resetConfigDialog.done(1);
        });
        connect(pbC, &QPushButton::clicked, this, [&]{
           resetConfigDialog.done(0);
        });
        resetConfigDialog.layout()->addWidget(pbV);
        resetConfigDialog.layout()->addWidget(pbC);

        if(resetConfigDialog.exec() == 1){ // if validated
            configW->p->reset_args();
        }
    });

    // move config
    connect(m_ui.tabConfigs->tabBar(), &QTabBar::tabMoved, this, [&](int from, int to){
       emit GSignals::get()->move_config_signal(componentKey, RowId{from}, RowId{to});
    });

    Bench::stop();
    Bench::start("[ComponentsConfigDialog init 2]"sv, false);


    // add init config widget
    m_initConfigW = new ConfigW(component->initConfig.get(),generate_parameters(component->type, true));
    m_ui.vlInitConfig->addWidget(m_initConfigW);
    ConfigKey configKey = ConfigKey{m_initConfigW->key};
    connect(m_initConfigW->p, &ConfigParametersW::arg_updated_signal, this, [=](QString name, Arg arg){
       emit GSignals::get()->arg_updated_signal(componentKey, configKey, name, std::move(arg), true);
    });
    connect(m_initConfigW->p, &ConfigParametersW::move_arg_up_signal, this, [=](QString prevName, QString name){
        emit GSignals::get()->move_arg_up_signal(componentKey, configKey, prevName, name, true);
    });
    connect(m_initConfigW->p, &ConfigParametersW::move_arg_down_signal, this, [=](QString nextName, QString name){
        emit GSignals::get()->move_arg_down_signal(componentKey, configKey, nextName, name, true);
    });
    connect(m_initConfigW->p, &ConfigParametersW::arg_removed_signal, this, [=](QString name){
       emit GSignals::get()->arg_removed_signal(componentKey, configKey, name, true);
    });
    connect(m_initConfigW->p, &ConfigParametersW::new_arg_signal, this, [=](QString name, Arg arg){
       emit GSignals::get()->new_arg_signal(componentKey, configKey, name, std::move(arg), true);
    });
    connect(m_initConfigW->p, &ConfigParametersW::action_signal, this, [=](QString name){
        emit GSignals::get()->action_signal(componentKey, configKey, name, true);
    });

    Bench::stop();
    Bench::start("[ComponentsConfigDialog init 3]"sv, false);


    m_initConfigW->p->update_from_args(component->initConfig->args);

    Bench::stop();
    Bench::start("[ComponentsConfigDialog init 4]"sv, false);

    m_initConfigW->p->late_update_ui();

    Bench::stop();
    Bench::start("[ComponentsConfigDialog init 5]"sv, false);

    // enable configurations
    auto configOpt = Component::get_config_opt(component->type);
    m_ui.twAllConfigs->setEnabled(configOpt !=  Component::ConfigO::None);
    m_ui.twAllConfigs->setTabEnabled(0,configOpt == Component::ConfigO::Initalization || configOpt ==  Component::ConfigO::Both);
    m_ui.twAllConfigs->setTabEnabled(1,configOpt == Component::ConfigO::Condition      || configOpt ==  Component::ConfigO::Both);

    if(m_ui.twAllConfigs->isTabEnabled(0)){
        m_ui.twAllConfigs->setCurrentIndex(0);
    }

    Bench::stop();
    Bench::start("[ComponentsConfigDialog init 6]"sv, false);

    update_from_component(component);

    Bench::stop();
}


void ComponentConfigDialog::update_from_component(Component *component){

    Bench::start("[ComponentsConfigDialog 0]"sv);

    get_init_config_widget()->update_from_config(component->initConfig.get());

    Bench::stop();
    Bench::start("[ComponentsConfigDialog 1]"sv);

    // remove inused configs
    for(int ii = m_ui.tabConfigs->count()-1; ii >= 0; --ii){

        auto configW = get_config_widget(ii);
        bool found = false;
        for(const auto &config : component->configs){
            if(config->key() == configW->key){
                found = true;
                configW->update_from_config(config.get());
                break;
            }
        }
        if(!found){
            m_ui.tabConfigs->removeTab(ii);
        }
    }

    Bench::stop();
    Bench::start("[ComponentsConfigDialog 2]"sv);

    // reorder
    for(int ii = 0; ii < to_signed(component->configs.size()); ++ii){
        for(int jj = 0; jj < m_ui.tabConfigs->count(); ++jj){

            auto cw = get_config_widget(jj);
            if(cw->key == component->configs[to_unsigned(ii)]->key()){
                if(ii != jj){
                    m_ui.tabConfigs->tabBar()->moveTab(jj,ii);
                }
                break;
            }
        }
    }

    Bench::stop();


    // add new configs
    for(size_t ii = 0; ii < component->configs.size(); ++ii){
        bool found = false;
        for(int jj = 0; jj < m_ui.tabConfigs->count(); ++jj){
            if(component->configs[ii]->key() == get_config_widget(jj)->key){
                found = true;
                break;
            }
        }

        if(!found){ // insert tab for the new config

            Config *config = component->configs[ii].get();
            auto parametersW = generate_parameters(component->type, false);
            parametersW->initParametersW = m_initConfigW->p;
            ConfigW *configW = new ConfigW(config, parametersW);

            ConfigKey configKey = ConfigKey{configW->key};
            connect(configW->p, &ConfigParametersW::arg_updated_signal, this, [=](QString name, Arg arg){
               emit GSignals::get()->arg_updated_signal(componentKey, configKey, name, std::move(arg), false);
            });
            connect(configW->p, &ConfigParametersW::arg_removed_signal, this, [=](QString name){
               emit GSignals::get()->arg_removed_signal(componentKey, configKey, name, false);
            });
            connect(configW->p, &ConfigParametersW::move_arg_up_signal, this, [=](QString previousName, QString name){
                emit GSignals::get()->move_arg_up_signal(componentKey, configKey, previousName, name, false);
            });
            connect(configW->p, &ConfigParametersW::move_arg_down_signal, this, [=](QString nextName, QString name){
                emit GSignals::get()->move_arg_down_signal(componentKey, configKey, nextName, name, false);
            });
            connect(configW->p, &ConfigParametersW::new_arg_signal, this, [=](QString name, Arg arg){
               emit GSignals::get()->new_arg_signal(componentKey, configKey, name, std::move(arg), false);
            });
            connect(configW->p, &ConfigParametersW::action_signal, this, [=](QString name){
               emit GSignals::get()->action_signal(componentKey, configKey, name, false);
            });
            configW->p->update_from_args(config->args);
            configW->p->late_update_ui();

            m_ui.tabConfigs->insertTab(to_signed(ii), configW, configW->name);
        }
    }



    // update tab textes with configs name
    for(size_t ii = 0; ii < component->configs.size(); ++ii){
        m_ui.tabConfigs->setTabText(to_signed(ii), component->configs[ii]->name);
    }
    m_ui.pbRemoveConfig->setEnabled(m_ui.tabConfigs->count() > 1);

}

void ComponentConfigDialog::update_with_info(ConfigKey configKey, QStringView id, QStringView value){

    auto initConfigW = get_init_config_widget();
    if(initConfigW->key == configKey.v){
        initConfigW->p->update_with_info(id, value);
    }else{        
        for(int ii = 0; ii < m_ui.tabConfigs->count(); ++ii){
            auto configW = get_config_widget(ii);
            if(configW->key == configKey.v){
                configW->p->update_with_info(id, value);
                break;
            }
        }
    }    
}

ConfigParametersW *ComponentConfigDialog::generate_parameters(Component::Type type, bool initConfig){

    using CT = Component::Type;
    using CC = Component::Category;

    switch (type) {
    // ############################# Avatar
    case CT::Humanoid_controller:
        return initConfig ? gen_params_w<HumanoidControllerInitConfigParametersW>() : gen_params_w<HumanoidControllerConfigParametersW>();
    // ############################# Audio
    case CT::AudioSource:
        return initConfig ? gen_params_w<AudioSourceInitConfigParametersW>() : gen_params_w<AudioSourceConfigParametersW>();
    case CT::Microphone:
        return initConfig ? gen_params_w<MicrophoneInitConfigParametersW>() : gen_params_w<MicrophoneConfigParametersW>();
    // ############################# Camera
    case CT::Camera:
        return initConfig ? gen_params_w<CameraInitConfigParametersW>() : gen_params_w<CameraConfigParametersW>();
    case CT::Camera_trajectory:
        return initConfig ? gen_params_w<CameraTrajectoryInitConfigParametersW>() : gen_params_w<CameraTrajectoryConfigParametersW>();
    case CT::Camera_trajectory_file:
        return initConfig ? gen_params_w<CameraTrajectoryFileInitConfigParametersW>() : gen_params_w<CameraTrajectoryFileConfigParametersW>();
    case CT::Camera_target:
        return initConfig ? gen_params_w<CameraTargetInitConfigParametersW>() : gen_params_w<CameraTargetConfigParametersW>();
    // ############################# Cloud
    case CT::Cloud:
        return initConfig ? gen_params_w<CloudInitConfigParametersW>() : gen_params_w<CloudConfigParametersW>();
    case CT::Scaner_video:
        return initConfig ? gen_params_w<ScanerVideoInitConfigParametersW>() : gen_params_w<ScanerVideoConfigParametersW>();
    // ############################# Environment
    case CT::Sky:
        return initConfig ? gen_params_w<SkyInitConfigParametersW>() : gen_params_w<SkyConfigParametersW>();
    // ############################# Input
    case CT::Joypad:
        return initConfig ? gen_params_w<JoypadInitConfigParametersW>() : gen_params_w<JoypadConfigParametersW>();
    case CT::Keyboard:
        return initConfig ? gen_params_w<KeyboardInitConfigParametersW>() : gen_params_w<KeyboardConfigParametersW>();
    case CT::Mouse:
        return initConfig ? gen_params_w<MouseInitConfigParametersW>() : gen_params_w<MouseConfigParametersW>();
    // ############################# Interaction
    case CT::Flag_pole:
        return initConfig ? gen_params_w<FlagPoleInitConfigParametersW>() : gen_params_w<FlagPoleConfigParametersW>();
    case CT::Mark_to_clean:
        return initConfig ? gen_params_w<MarkToCleanInitConfigParametersW>() : gen_params_w<MarkToCleanConfigParametersW>();
    case CT::Target_to_grab:
        return initConfig ? gen_params_w<TargetToGrabInitConfigParametersW>() : gen_params_w<TargetToGrabConfigParametersW>();
    // ############################# Model
    case CT::Cube:
        return initConfig ? gen_params_w<CubeInitConfigParametersW>() : gen_params_w<CubeConfigParametersW>();
    case CT::Cylinder:
        return initConfig ? gen_params_w<CylinderInitConfigParametersW>() : gen_params_w<CylinderConfigParametersW>();
    case CT::Landmark:
        return initConfig ? gen_params_w<LandmarkInitConfigParametersW>() : gen_params_w<LandmarkConfigParametersW>();
    case CT::Lines:
        return initConfig ? gen_params_w<LinesInitConfigParametersW>() : gen_params_w<LinesConfigParametersW>();
    case CT::Sphere:
        return initConfig ? gen_params_w<SphereInitConfigParametersW>() : gen_params_w<SphereConfigParametersW>();
    case CT::Torus:
        return initConfig ? gen_params_w<TorusInitConfigParametersW>() : gen_params_w<TorusConfigParametersW>();
    // ############################# Network
    case CT::Parallel_port_writer:
        return initConfig ? gen_params_w<ParallelPortWriterInitConfigParametersW>() : gen_params_w<ParallelPortWriterConfigParametersW>();
    case CT::Serial_port_writer:
        return initConfig ? gen_params_w<SerialPortWriterCommonParameterW>() : gen_params_w<SerialPortWriterConfigParametersW>();
    case CT::Udp_reader:
        return initConfig ? gen_params_w<UdpReaderInitConfigParametersW>() : gen_params_w<UdpReaderConfigParametersW>();
    case CT::Udp_writer:
        return initConfig ? gen_params_w<UdpWriterInitConfigParametersW>() : gen_params_w<UdpWriterConfigParametersW>();
    // ############################# Output
    case CT::Logger:
        return initConfig ? gen_params_w<LoggerInitConfigParametersW>() : gen_params_w<LoggerConfigParametersW>();
    case CT::LoggerColumns:
        return initConfig ? gen_params_w<LoggerColumnsInitConfigParametersW>() : gen_params_w<LoggerColumnsConfigParametersW>();
    case CT::LoggerCondition:
        return initConfig ? gen_params_w<LoggerConditionInitConfigParametersW>() : gen_params_w<LoggerConditionConfigParametersW>();
    // ############################# Resource
    case CT::Image_resource:
        return initConfig ? gen_params_w<ImageResourceInitConfigParametersW>() : gen_params_w<ImageResourceConfigParametersW>();
    case CT::Plot_resource:
        return initConfig ? gen_params_w<PlotResourceInitConfigParametersW>() : gen_params_w<PlotResourceConfigParametersW>();
    case CT::Text_resource:
        return initConfig ? gen_params_w<TextResourceInitConfigParametersW>() : gen_params_w<TextResourceConfigParametersW>();
    // ############################# Scene
    case CT::Falling_spheres:
        return initConfig ? gen_params_w<FallingSpheresInitConfigParametersW>() : gen_params_w<FallingSpheresConfigParametersW>();
    case CT::Flashing_dot:
        return initConfig ? gen_params_w<FlashingDotInitConfigParametersW>() : gen_params_w<FlashingDotConfigParametersW>();
    case CT::Mirror:
        return initConfig ? gen_params_w<MirrorInitConfigParametersW>() : gen_params_w<MirrorConfigParametersW>();
    case CT::MRI:
        return initConfig ? gen_params_w<MriInitConfigParametersW>() : gen_params_w<MriConfigParametersW>();
    case CT::Multi_AB:
        return initConfig ? gen_params_w<MultiABInitConfigParametersW>() : gen_params_w<MultiABConfigParametersW>();
    case CT::Unity_asset_bundle:
        return initConfig ? gen_params_w<AssetBundleInitConfigParametersW>() : gen_params_w<AssetBundleConfigParametersW>();
    // ############################# Script
    case CT::CSharp_script:
        return initConfig ? gen_params_w<CSharpScriptInitConfigParametersW>() : gen_params_w<CSharpScriptConfigParametersW>();
    case CT::Python_script:
        return initConfig ? gen_params_w<PythonScriptInitConfigParametersW>() : gen_params_w<PythonScriptConfigParametersW>();
    // ############################# Tracking
    case CT::Attach_object_to_hand:
        return initConfig ? gen_params_w<AttachObjectToHandInitConfigParametersW>() : gen_params_w<AttachObjectToHandConfigParametersW>();
    case CT::Biopac:
        return initConfig ? gen_params_w<BiopacMP36InitConfigParametersW>() : gen_params_w<BiopacMP36ConfigParametersW>();
    case CT::Fop_robot:
        return initConfig ? gen_params_w<FopRobotInitConfigParametersW>() : gen_params_w<FopRobotConfigParametersW>();
    case CT::Qualisys:
        return initConfig ? gen_params_w<QualisysTrackingInitConfigParametersW>() : gen_params_w<QualisysTrackingConfigParametersW>();
    case CT::Kinect_manager:
        return initConfig ? gen_params_w<KinectManagerInitConfigParametersW>() : gen_params_w<KinectManagerConfigParametersW>();
    case CT::Kinect_body_tracking:
        return initConfig ? gen_params_w<KinectBodyTrackingInitConfigParametersW>() : gen_params_w<KinectBodyTrackingConfigParametersW>();
    case CT::Leap_motion_arms_display:
        return initConfig ? gen_params_w<LeapMotionArmsDisplayInitConfigParametersW>() : gen_params_w<LeapMotionArmsDisplayConfigParametersW>();
    case CT::Scene_scaner:
        return initConfig ? gen_params_w<SceneScanerInitConfigParametersW>() : gen_params_w<SceneScanerConfigParametersW>();
    case CT::Sonceboz_SG:
        return initConfig ? gen_params_w<SoncebozSgInitConfigParametersW>() : gen_params_w<SoncebozSgConfigParametersW>();
    case CT::Thera_trainer_tracking:
        return initConfig ? gen_params_w<TheraTrainerTrackingInitConfigParametersW>() : gen_params_w<TheraTrainerTrackingConfigParametersW>();
    case CT::Thera_trainer_platform:
        return initConfig ? gen_params_w<TheraTrainerPlatformInitConfigParametersW>() : gen_params_w<TheraTrainerPlatformConfigParametersW>();
    // ############################# UI
    case CT::Slider_ui:
        return initConfig ? gen_params_w<SliderUiInitConfigParametersW>() : gen_params_w<SliderUiConfigParametersW>();
    // ############################# Video
    case CT::Video_file:
        return initConfig ? gen_params_w<VideoFileInitConfigParametersW>() : gen_params_w<VideoFileConfigParametersW>();
    case CT::Video_saver:
        return initConfig ? gen_params_w<VideoGeneratorInitConfigParametersW>() : gen_params_w<VideoGeneratorConfigParametersW>();
    case CT::Webcam:
        return initConfig ? gen_params_w<WebcamInitConfigParametersW>() : gen_params_w<WebcamConfigParametersW>();
    // ############################# Viewer
    case CT::Blend_fade_viewer:
        return initConfig ? gen_params_w<BlendFadeViewerInitConfigParametersW>() : gen_params_w<BlendFadeViewerConfigParametersW>();
    case CT::Fixation_cross_viewer:
        return initConfig ? gen_params_w<FixationCrossViewerInitConfigParametersW>() : gen_params_w<FixationCrossViewerConfigParametersW>();
    case CT::Fov_simulator_viewer:
        return initConfig ? gen_params_w<FovSimulatorInitConfigParametersW>() : gen_params_w<FovSimulatorConfigParametersW>();
    case CT::Image_viewer:
        return initConfig ? gen_params_w<ImageViewerInitConfigParametersW>() : gen_params_w<ImageViewerConfigParametersW>();
    case CT::Text_viewer:
        return initConfig ? gen_params_w<TextViewerInitConfigParametersW>() : gen_params_w<TextViewerConfigParametersW>();
    case CT::Video_file_camera_viewer:
        return initConfig ? gen_params_w<VideoFileCameraInitConfigParametersW>() : gen_params_w<VideoFileCameraConfigParametersW>();
    case CT::Webcam_viewer:
        return initConfig ? gen_params_w<WebcamViewerInitConfigParametersW>() : gen_params_w<WebcamViewerConfigParametersW>();
    default:
        return gen_params_w<ConfigParametersW>();
    }
}

#include "moc_component_config_dialog.cpp"
