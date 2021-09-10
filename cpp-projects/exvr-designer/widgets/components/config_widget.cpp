
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "config_widget.hpp"

// base
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
#include "humanoid_avatar_pw.hpp"
#include "fpp_avatar_camera_pw.hpp"

using namespace tool::ex;

ConfigW::ConfigW(Config *config, Component *component, bool initConfig, std::unordered_map<QStringView,Arg*> &argsByName) :
      configKey(ConfigKey{config->key()}), componentKey(ComponentKey{component->key()}), name(config->name){

    Bench::start("[ConfigW generate widget]"sv, false);
        p = generate_parameters(component->type, initConfig);
        p->set_infos(componentKey, configKey, initConfig);
        p->insert_widgets();
        p->init_and_register_widgets();        
        p->create_connections();
        p->init_from_args(argsByName);
        p->late_update_ui();
        p->end_stretch();        
    Bench::stop();

    setLayout(new QHBoxLayout());
    layout()->addWidget(p);
    p->setVisible(true);
    p->update_from_resources();
    p->update_from_components();
}

void ConfigW::update_from_config(Config *config){

    name = config->name;

    Bench::start("[ConfigW::update_from_resources]"sv);
        p->update_from_resources();
    Bench::stop();

    Bench::start("[ConfigW::update_from_components]"sv);
        p->update_from_components();
    Bench::stop();
}

void ConfigW::update_with_info(QStringView id, QStringView value){
    p->update_with_info(id, value);
}

void ConfigW::reset_args(){
    p->reset_args();
}

ConfigParametersW *ConfigW::generate_parameters(Component::Type type, bool initConfig){

    using CT = Component::Type;
    using CC = Component::Category;

    switch (type) {
    // ############################# Avatar
    case CT::Humanoid_avatar:
        return gen_params_w<HumanoidAvatarInitConfigParametersW,HumanoidAvatarConfigParametersW>(initConfig);
    case CT::Humanoid_controller:
        return gen_params_w<HumanoidControllerInitConfigParametersW,HumanoidControllerConfigParametersW>(initConfig);
    // ############################# Audio
    case CT::AudioSource:
        return gen_params_w<AudioSourceInitConfigParametersW,AudioSourceConfigParametersW>(initConfig);
    case CT::Microphone:
        return gen_params_w<MicrophoneInitConfigParametersW,MicrophoneConfigParametersW>(initConfig);
    // ############################# Camera
    case CT::Camera:
        return gen_params_w<CameraInitConfigParametersW,CameraConfigParametersW>(initConfig);
    case CT::Camera_trajectory:
        return gen_params_w<CameraTrajectoryInitConfigParametersW,CameraTrajectoryConfigParametersW>(initConfig);
    case CT::Camera_trajectory_file:
        return gen_params_w<CameraTrajectoryFileInitConfigParametersW,CameraTrajectoryFileConfigParametersW>(initConfig);
    case CT::Camera_target:
        return gen_params_w<CameraTargetInitConfigParametersW,CameraTargetConfigParametersW>(initConfig);
    case CT::FPP_avatar_camera:
        return gen_params_w<FPPAvatarCameraInitConfigParametersW,FPPAvatarCameraConfigParametersW>(initConfig);
    // ############################# Cloud
    case CT::Cloud:
        return gen_params_w<CloudInitConfigParametersW,CloudConfigParametersW>(initConfig);
    case CT::Scaner_video:
        return gen_params_w<ScanerVideoInitConfigParametersW,ScanerVideoConfigParametersW>(initConfig);
    // ############################# Environment
    case CT::Sky:
        return gen_params_w<SkyInitConfigParametersW,SkyConfigParametersW>(initConfig);
    // ############################# Input
    case CT::Joypad:
        return gen_params_w<JoypadInitConfigParametersW,JoypadConfigParametersW>(initConfig);
    case CT::Keyboard:
        return gen_params_w<KeyboardInitConfigParametersW,KeyboardConfigParametersW>(initConfig);
    case CT::Mouse:
        return gen_params_w<MouseInitConfigParametersW,MouseConfigParametersW>(initConfig);
    // ############################# Interaction
    case CT::Flag_pole:
        return gen_params_w<FlagPoleInitConfigParametersW,FlagPoleConfigParametersW>(initConfig);
    case CT::Mark_to_clean:
        return gen_params_w<MarkToCleanInitConfigParametersW,MarkToCleanConfigParametersW>(initConfig);
    case CT::Target_to_grab:
        return gen_params_w<TargetToGrabInitConfigParametersW,TargetToGrabConfigParametersW>(initConfig);
    // ############################# Model
    case CT::Cube:
        return gen_params_w<CubeInitConfigParametersW,CubeConfigParametersW>(initConfig);
    case CT::Cylinder:
        return gen_params_w<CylinderInitConfigParametersW,CylinderConfigParametersW>(initConfig);
    case CT::Landmark:
        return gen_params_w<LandmarkInitConfigParametersW,LandmarkConfigParametersW>(initConfig);
    case CT::Lines:
        return gen_params_w<LinesInitConfigParametersW,LinesConfigParametersW>(initConfig);
    case CT::Sphere:
        return gen_params_w<SphereInitConfigParametersW,SphereConfigParametersW>(initConfig);
    case CT::Torus:
        return gen_params_w<TorusInitConfigParametersW,TorusConfigParametersW>(initConfig);
    // ############################# Network
    case CT::Parallel_port_writer:
        return gen_params_w<ParallelPortWriterInitConfigParametersW,ParallelPortWriterConfigParametersW>(initConfig);
    case CT::Serial_port_writer:
        return gen_params_w<SerialPortWriterCommonParameterW,SerialPortWriterConfigParametersW>(initConfig);
    case CT::Udp_reader:
        return gen_params_w<UdpReaderInitConfigParametersW,UdpReaderConfigParametersW>(initConfig);
    case CT::Udp_writer:
        return gen_params_w<UdpWriterInitConfigParametersW,UdpWriterConfigParametersW>(initConfig);
    // ############################# Output
    case CT::Logger:
        return gen_params_w<LoggerInitConfigParametersW,LoggerConfigParametersW>(initConfig);
    case CT::LoggerColumns:
        return gen_params_w<LoggerColumnsInitConfigParametersW,LoggerColumnsConfigParametersW>(initConfig);
    case CT::LoggerCondition:
        return gen_params_w<LoggerConditionInitConfigParametersW,LoggerConditionConfigParametersW>(initConfig);
    // ############################# Resource
    case CT::Image_resource:
        return gen_params_w<ImageResourceInitConfigParametersW,ImageResourceConfigParametersW>(initConfig);
    case CT::Plot_resource:
        return gen_params_w<PlotResourceInitConfigParametersW,PlotResourceConfigParametersW>(initConfig);
    case CT::Text_resource:
        return gen_params_w<TextResourceInitConfigParametersW,TextResourceConfigParametersW>(initConfig);
    // ############################# Scene
    case CT::Falling_spheres:
        return gen_params_w<FallingSpheresInitConfigParametersW,FallingSpheresConfigParametersW>(initConfig);
    case CT::Flashing_dot:
        return gen_params_w<FlashingDotInitConfigParametersW,FlashingDotConfigParametersW>(initConfig);
    case CT::Mirror:
        return gen_params_w<MirrorInitConfigParametersW,MirrorConfigParametersW>(initConfig);
    case CT::MRI:
        return gen_params_w<MriInitConfigParametersW,MriConfigParametersW>(initConfig);
    case CT::Multi_AB:
        return gen_params_w<MultiABInitConfigParametersW,MultiABConfigParametersW>(initConfig);
    case CT::Unity_asset_bundle:
        return gen_params_w<AssetBundleInitConfigParametersW,AssetBundleConfigParametersW>(initConfig);
    // ############################# Script
    case CT::CSharp_function:
        return gen_params_w<CSharpFunctionInitConfigParametersW,CSharpFunctionConfigParametersW>(initConfig);
    case CT::CSharp_script:
        return gen_params_w<CSharpScriptInitConfigParametersW,CSharpScriptConfigParametersW>(initConfig);
    case CT::Python_script:
        return gen_params_w<PythonScriptInitConfigParametersW,PythonScriptConfigParametersW>(initConfig);
    // ############################# Tracking
    case CT::Attach_object_to_hand:
        return gen_params_w<AttachObjectToHandInitConfigParametersW,AttachObjectToHandConfigParametersW>(initConfig);
    case CT::Biopac:
        return gen_params_w<BiopacMP36InitConfigParametersW,BiopacMP36ConfigParametersW>(initConfig);
    case CT::Fop_robot:
        return gen_params_w<FopRobotInitConfigParametersW,FopRobotConfigParametersW>(initConfig);
    case CT::Qualisys:
        return gen_params_w<QualisysTrackingInitConfigParametersW,QualisysTrackingConfigParametersW>(initConfig);
    case CT::Kinect_manager:
        return gen_params_w<KinectManagerInitConfigParametersW,KinectManagerConfigParametersW>(initConfig);
    case CT::Kinect_body_tracking:
        return gen_params_w<KinectBodyTrackingInitConfigParametersW,KinectBodyTrackingConfigParametersW>(initConfig);
    case CT::Leap_motion_arms_display:
        return gen_params_w<LeapMotionArmsDisplayInitConfigParametersW,LeapMotionArmsDisplayConfigParametersW>(initConfig);
    case CT::Scene_scaner:
        return gen_params_w<SceneScanerInitConfigParametersW,SceneScanerConfigParametersW>(initConfig);
    case CT::Sonceboz_SG:
        return gen_params_w<SoncebozSgInitConfigParametersW,SoncebozSgConfigParametersW>(initConfig);
    case CT::Thera_trainer_tracking:
        return gen_params_w<TheraTrainerTrackingInitConfigParametersW,TheraTrainerTrackingConfigParametersW>(initConfig);
    case CT::Thera_trainer_platform:
        return gen_params_w<TheraTrainerPlatformConfigParametersW,AudioSourceConfigParametersW>(initConfig);
    // ############################# UI
    case CT::Slider_ui:
        return gen_params_w<SliderUiInitConfigParametersW,SliderUiConfigParametersW>(initConfig);
    // ############################# Video
    case CT::Video_file:
        return gen_params_w<VideoFileInitConfigParametersW,VideoFileConfigParametersW>(initConfig);
    case CT::Video_saver:
        return gen_params_w<VideoGeneratorInitConfigParametersW,VideoGeneratorConfigParametersW>(initConfig);
    case CT::Webcam:
        return gen_params_w<WebcamInitConfigParametersW,WebcamConfigParametersW>(initConfig);
    // ############################# Viewer
    case CT::Blend_fade_viewer:
        return gen_params_w<BlendFadeViewerInitConfigParametersW,BlendFadeViewerConfigParametersW>(initConfig);
    case CT::Fixation_cross_viewer:
        return gen_params_w<FixationCrossViewerInitConfigParametersW,FixationCrossViewerConfigParametersW>(initConfig);
    case CT::Fov_simulator_viewer:
        return gen_params_w<FovSimulatorInitConfigParametersW,FovSimulatorConfigParametersW>(initConfig);
    case CT::Image_viewer:
        return gen_params_w<ImageViewerInitConfigParametersW,ImageViewerConfigParametersW>(initConfig);
    case CT::Text_viewer:
        return gen_params_w<TextViewerInitConfigParametersW,TextViewerConfigParametersW>(initConfig);
    case CT::Video_file_camera_viewer:
        return gen_params_w<VideoFileCameraInitConfigParametersW,VideoFileCameraConfigParametersW>(initConfig);
    case CT::Webcam_viewer:
        return gen_params_w<WebcamViewerInitConfigParametersW,WebcamViewerConfigParametersW>(initConfig);
    default:
        return new ConfigParametersW();
    }
}

#include "moc_config_widget.cpp"
