
# /*******************************************************************************
# ** exvr-designer                                                              **
# ** No license (to be defined)                                                 **
# ** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
# ********************************************************************************/

####################################### repo
EXVR_REPOSITORY_DIR      = $$PWD"/../.."

####################################### PRI
# defines compiling options
include(../exvr-settings.pri)
# defines projects paths and variables
include(../exvr-projects.pri)
# defines thirdparty includes and libs
include(../exvr-thirdparty.pri)

####################################### TARGET
equals(CFG, "debug"){
    TARGET = ExVR-designerd
}
equals(CFG, "release"){
    TARGET = ExVR-designer
}

####################################### TEMPLATE
equals(EXVR_DESIGNER_TARGET, "app"){
    TEMPLATE = app
    CONFIG += console precompile_header
    DEFINES += QT_MESSAGELOGCONTEXT
    PRECOMPILED_HEADER = stable.h
}

####################################### BUILD FILES
OBJECTS_DIR = $$EXVR_DESIGNER_OBJ
MOC_DIR     = $$EXVR_DESIGNER_MOC
RCC_DIR     = $$EXVR_DESIGNER_RCC
UI_DIR      = $$EXVR_DESIGNER_UI
DESTDIR     = $$EXVR_DESIGNER_DEST

####################################### CONFIG
QT  += core gui network concurrent widgets opengl
DEFINES += QWT_DLL

####################################### INCLUDES

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER  = stable.h

INCLUDEPATH += \
    # local
    $$EXVR_DESIGNER_MOC \
    utility \
    IO \
    data \
    experiment \
    flow \
    widgets \
    widgets/components \
    widgets/components/config_parameters \
    widgets/components/config_parameters/audio \
    widgets/components/config_parameters/avatar \
    widgets/components/config_parameters/image \
    widgets/components/config_parameters/input \
    widgets/components/config_parameters/interaction \
    widgets/components/config_parameters/model \
    widgets/components/config_parameters/network \
    widgets/components/config_parameters/output \
    widgets/components/config_parameters/scene \
    widgets/components/config_parameters/script \
    widgets/components/config_parameters/text \
    widgets/components/config_parameters/ui \
    widgets/components/config_parameters/video \
    widgets/components/config_parameters/tracking \
    widgets/components/config_parameters/settings \
    widgets/components/config_parameters/environment \
    widgets/components/config_parameters/camera \
    widgets/components/config_parameters/cloud \
    widgets/components/config_parameters/resource \
    widgets/components/config_parameters/viewer \
    widgets/elements \
    widgets/routines \
    widgets/ex_items \
    widgets/ex_items/base \
    widgets/ex_items/items \
    resources \
    # base
    $$BASE_INCLUDES \
    # qt-utility
    $$QT_UTILITY_INCLUDES \
    # third-party
    $$QWT_INCLUDES \
    $$NODES_INCLUDES \
    $$MAGIC_ENUM_INCLUDES\
#    $$QMARKDOWN_TEXT_EDIT_INCLUDES\

####################################### LIBRAIRIES


LIBS +=  \
    # base
    $$BASE_LIB \
    # qt-utility
    $$QT_UTILITY_LIB \
    # third-party
    $$QWT_LIBS \
    $$NODES_LIB \

#    $$QMARKDOWN_TEXT_EDIT_LIBS\

####################################### PROJECT FILES


HEADERS += \
    # global    
    data/ex_widgets_types.hpp \
    data/states.hpp \
    experiment/global_signals.hpp \
    forward.hpp \
    # controller
    controller/exvr_controller.hpp \
    # utility
    utility/path_utility.hpp \
    # IO
    IO/xml_io_manager.hpp \
    # settings
    settings/display.hpp \
    # launcher    
    launcher/exp_launcher.hpp \
    launcher/exp_launcher_communication.hpp \
    launcher/exp_launcher_process.hpp \
    # data
    data/components_manager.hpp \
    data/gui.hpp \
    data/set.hpp \
    data/connection_node.hpp \
    data/connector.hpp \
    data/element.hpp \
    data/interval.hpp \
    data/routine.hpp \
    data/isi.hpp \
    data/loop.hpp \
    data/component.hpp \
    data/timeline.hpp \
    data/condition.hpp \
    data/config.hpp \
    data/settings.hpp \
    data/action.hpp \
    data/argument.hpp \
    data/connection.hpp \
    data/id_key.hpp \
    data/node_flow.hpp \
    # resources
    resources/resource.hpp \
    resources/resources_manager.hpp \
    # flow
    flow/loop_flow_element.hpp \
    flow/node_flow_element.hpp \
    flow/routine_flow_element.hpp \
    flow/isi_flow_element.hpp \
    flow/flow_sequence.hpp \
    flow/add_flow_element.hpp \
    flow/remove_flow_element.hpp \
    flow/move_flow_element.hpp \
    flow/movable_flow_element.hpp \
    flow/flow_element.hpp \
    # experiment
    experiment/experiment.hpp \
    experiment/randomizer.hpp \
    experiment/instance.hpp \
    # controller
    # widgets    
    ## main                           
    widgets/components/config_parameters/scene/asset_bundle_pw.hpp \
    widgets/components/config_parameters/scene/multi_ab_pw.hpp \
    widgets/components/config_parameters/tracking/biopac_pw.hpp \
    widgets/components/config_parameters/tracking/fop_robot_pw.hpp \
    widgets/components/config_parameters/viewer/blend_fade_viewer_pw.hpp \
    widgets/connections/data_models/connectors/convertor/transform_to_vectors_ndm.hpp \
    widgets/connections/data_models/connectors/convertor/vectors_to_transform_ndm.hpp \
    widgets/connections/data_models/connectors/event/keyboard_ndm.hpp \
    widgets/connections/data_models/connectors/generator/transform_ndm.hpp \
    widgets/connections/data_models/connectors/link/check_str_ndm.hpp \
    widgets/connections/data_models/connectors/link/pass_value_trigger_ndm.hpp \
    widgets/connections/data_models/connectors/link/pass_values_ndm.hpp \
    widgets/designer_window.hpp\
    ## elements
    widgets/dialogs/benchmark_dialog.hpp \
    widgets/dialogs/copy_to_conditions_dialog.hpp \
    widgets/elements/flow_diagram_widget.hpp \
    widgets/elements/element_viewer_widget.hpp \
    ## components
    widgets/components/component_config_dialog.hpp \
    widgets/components/components_manager_widget.hpp \
    widgets/components/component_widget.hpp \
    widgets/components/config_widget.hpp \
    ### parameters widgets
    widgets/components/config_parameters/sub_parts_pw.hpp \
    widgets/components/config_parameters/config_pw.hpp \
    #### environment
    widgets/components/config_parameters/environment/sky_pw.hpp \
    #### avatar
    widgets/components/config_parameters/avatar/humanoid_controller_pw.hpp \
    #### viewer
    widgets/components/config_parameters/viewer/text_viewer_pw.hpp \
    widgets/components/config_parameters/viewer/fixation_cross_viewer_pw.hpp \
    widgets/components/config_parameters/viewer/image_viewer_pw.hpp \
    widgets/components/config_parameters/viewer/webcam_viewer_pw.hpp \
    widgets/components/config_parameters/viewer/fov_simulator_pw.hpp \
    #### scene
    widgets/components/config_parameters/scene/falling_spheres_pw.hpp \
    widgets/components/config_parameters/scene/mirror_pw.hpp \
    widgets/components/config_parameters/scene/flashing_dot_pw.hpp \
    widgets/components/config_parameters/scene/mri_pw.hpp \
    #### camera
    widgets/components/config_parameters/camera/camera_target_pw.hpp \
    widgets/components/config_parameters/camera/camera_trajectory_pw.hpp \
    widgets/components/config_parameters/camera/camera_trajectory_file_pw.hpp \
    widgets/components/config_parameters/camera/camera_pw.hpp \
    #### script
    widgets/components/config_parameters/script/python_script_pw.hpp \
    widgets/components/config_parameters/script/csharp_script_pw.hpp \
    #### tracking
    widgets/components/config_parameters/tracking/sonceboz_sg_pw.hpp \
    widgets/components/config_parameters/tracking/duo_tracking_pw.hpp \
    widgets/components/config_parameters/tracking/scene_scaner_pw.hpp \
    widgets/components/config_parameters/tracking/leap_motion_arms_display_pw.hpp \
    widgets/components/config_parameters/tracking/attach_object_to_hand_pw.hpp \
    widgets/components/config_parameters/tracking/kinect_body_tracking_pw.hpp \
    widgets/components/config_parameters/tracking/thera_trainer_platform_pw.hpp \
    widgets/components/config_parameters/tracking/thera_trainer_tracking_pw.hpp \
    widgets/components/config_parameters/tracking/kinect_manager_pw.hpp \
    widgets/components/config_parameters/tracking/qualisys_tracking_pw.hpp \
    ### cloud
    widgets/components/config_parameters/cloud/cloud_pw.hpp \
    widgets/components/config_parameters/cloud/scaner_video_pw.hpp \
    #### audio
    widgets/components/config_parameters/audio/microphone_pw.hpp \
    widgets/components/config_parameters/audio/audio_source_pw.hpp \
    #### input
    widgets/components/config_parameters/input/mouse_pw.hpp \
    widgets/components/config_parameters/input/joypad_pw.hpp \
    widgets/components/config_parameters/input/keyboard_pw.hpp \
    #### network
    widgets/components/config_parameters/network/serial_port_writer_pw.hpp \
    widgets/components/config_parameters/network/udp_reader_pw.hpp \
    widgets/components/config_parameters/network/udp_writer_pw.hpp \
    widgets/components/config_parameters/network/parallel_port_writer_pw.hpp \
    #### output
    widgets/components/config_parameters/output/logger_pw.hpp \
    #### resource
    widgets/components/config_parameters/resource/text_resource_pw.hpp \
    widgets/components/config_parameters/resource/image_resource_pw.hpp \
    widgets/components/config_parameters/resource/plot_resource_pw.hpp \
    #### video
    widgets/components/config_parameters/video/video_file_pw.hpp \
    widgets/components/config_parameters/video/webcam_pw.hpp \
    widgets/components/config_parameters/video/video_generator_pw.hpp \
    widgets/components/config_parameters/video/video_file_camera_pw.hpp \
    #### ui
    widgets/components/config_parameters/ui/slider_ui_pw.hpp \
    #### model
    widgets/components/config_parameters/model/primitives_model_pw.hpp \
    #### interaction
    widgets/components/config_parameters/interaction/target_to_grab_pw.hpp \
    widgets/components/config_parameters/interaction/mark_to_clean_pw.hpp \
    #### settings
    ## ex_items    
    ### base    
    ### generation
    widgets/ex_items/base/ex_base_w.hpp \
    widgets/ex_items/base/ex_item_w.hpp \
    widgets/ex_items/generation/gen_ex_widget.hpp \
    widgets/ex_items/generation/gen_ui_item_dialog.hpp \
    ### items
    widgets/ex_items/items/ex_camera_target_w.hpp \
    widgets/ex_items/items/ex_checkbox_w.hpp \
    widgets/ex_items/items/ex_color_frame_w.hpp \
    widgets/ex_items/items/ex_combo_box_index_w.hpp \
    widgets/ex_items/items/ex_combo_box_text_w.hpp \
    widgets/ex_items/items/ex_component_w.hpp \
    widgets/ex_items/items/ex_components_list_w.hpp \
    widgets/ex_items/items/ex_config_w.hpp \
    widgets/ex_items/items/ex_curve_w.hpp \
    widgets/ex_items/items/ex_curve_x_w.hpp \
    widgets/ex_items/items/ex_double_spin_box_w.hpp \
    widgets/ex_items/items/ex_float_spin_box_w.hpp \
    widgets/ex_items/items/ex_label_w.hpp \
    widgets/ex_items/items/ex_line_edit_w.hpp \
    widgets/ex_items/items/ex_list_labels_w.hpp \
    widgets/ex_items/items/ex_parameters_generator_w.hpp \
    widgets/ex_items/items/ex_radio_button_w.hpp \
    widgets/ex_items/items/ex_resource_w.hpp \
    widgets/ex_items/items/ex_select_color_w.hpp \
    widgets/ex_items/items/ex_slider_w.hpp \
    widgets/ex_items/items/ex_spin_box_w.hpp \
    widgets/ex_items/items/ex_tab_w.hpp \
    widgets/ex_items/items/ex_text_edit_w.hpp \
    widgets/ex_items/items/ex_time_source_w.hpp \
    widgets/ex_items/items/ex_transformation_w.hpp \
    widgets/ex_items/items/ex_vector2d_w.hpp \
    widgets/ex_items/items/ex_pushbutton_w.hpp \
    widgets/ex_items/items/ex_resources_list_w.hpp \
    ## dialogs
    widgets/dialogs/generate_instances_dialog.hpp \
    widgets/dialogs/resources_manager_dialog.hpp \
    widgets/dialogs/documentation_dialog.hpp \
    widgets/dialogs/settings_dialog.hpp \
    ## routines
    widgets/ex_items/items/ex_vector3d_w.hpp \
    widgets/routines/timeline_widget.hpp \
    widgets/routines/action_widget.hpp \
    widgets/routines/condition_widget.hpp \
    widgets/routines/routine_tab_widget.hpp \
    widgets/routines/routines_manager_tab_widget.hpp \
    ## connections
    widgets/connections/ex_flow_view_widget.hpp \
    widgets/connections/connections_widget.hpp \    
    ### data models
    widgets/connections/data_models/base_embedded_widget.hpp \
    widgets/connections/data_models/base_node_data_model.hpp \
    widgets/connections/data_models/data/nodes_data_converters.hpp \
    widgets/connections/data_models/all_node_data_models.hpp \
    #### data
    widgets/connections/data_models/data/nodes_data.hpp \
    #### connectors
    widgets/connections/data_models/connectors/connector_node_data_model.hpp \    
    ##### component
    widgets/connections/data_models/connectors/component/component_node_data_model.hpp \
    ##### convertor
    widgets/connections/data_models/connectors/convertor/reals_to_vector2_ndm.hpp \
    widgets/connections/data_models/connectors/convertor/reals_to_vector3_ndm.hpp \
    widgets/connections/data_models/connectors/convertor/vector2_to_reals_ndm.hpp \
    widgets/connections/data_models/connectors/convertor/vector3_to_reals_ndm.hpp \    
    widgets/connections/data_models/connectors/convertor/string_list_to_id_any_ndm.hpp \
    ##### generator
    widgets/connections/data_models/connectors/generator/boolean_ndm.hpp \
    widgets/connections/data_models/connectors/generator/id_any_ndm.hpp \
    widgets/connections/data_models/connectors/generator/integer_ndm.hpp \
    widgets/connections/data_models/connectors/generator/real_ndm.hpp \
    widgets/connections/data_models/connectors/generator/string_ndm.hpp \
    widgets/connections/data_models/connectors/generator/vector3_ndm.hpp \
    widgets/connections/data_models/connectors/generator/string_any_ndm.hpp \
    ##### event
    widgets/connections/data_models/connectors/event/check_joypad_ndm.hpp \
    widgets/connections/data_models/connectors/event/check_mouse_ndm.hpp \
    ##### link
    widgets/connections/data_models/connectors/link/conditional_trigger_ndm.hpp \
    widgets/connections/data_models/connectors/link/conditional_gate_ndm.hpp \
    widgets/connections/data_models/connectors/link/check_id_ndm.hpp \
    ##### operator
    widgets/connections/data_models/connectors/operator/string_operation_ndm.hpp \
    widgets/connections/data_models/connectors/operator/decimal_operation_ndm.hpp \
    widgets/connections/data_models/connectors/operator/binary_operation_ndm.hpp \
    ##### function
    widgets/connections/data_models/connectors/function/variable_delay_ndm.hpp \
    widgets/connections/data_models/connectors/function/decimal_trigo_ndm.hpp \
    widgets/connections/data_models/connectors/function/delay_ndm.hpp \
    widgets/connections/data_models/connectors/function/decimal_counter_ndm.hpp \
    ##### display
    widgets/connections/data_models/connectors/display/logger_ndm.hpp \
    widgets/connections/data_models/connectors/display/curve_x_ndm.hpp \
    ##### action
    widgets/connections/data_models/connectors/action/basic_ndm.hpp \
    ##### flow
    widgets/connections/data_models/connectors/flow/time_ndm.hpp \
    widgets/connections/data_models/connectors/flow/flow_routine_ndm.hpp \

SOURCES += \
    # main
    data/connector.cpp \
    data/isi.cpp \
    designer_main.cpp \
    experiment/global_signals.cpp \
    launcher/exp_launcher_communication.cpp \
    launcher/exp_launcher_process.cpp \
    # settings
    settings/display.cpp \
    # IO
    IO/xml_io_manager.cpp \
    # data
    data/timeline.cpp \
    data/component.cpp \
    data/condition.cpp \
    data/id_key.cpp \
    data/action.cpp \
    data/interval.cpp \
    data/argument.cpp \
    data/components_manager.cpp \
    data/config.cpp \
    data/loop.cpp \
    data/routine.cpp \
    # experiment
    experiment/instance.cpp \
    # controller
    controller/exvr_controller.cpp \
    # launcher
    launcher/exp_launcher.cpp \
    # flow
    flow/add_flow_element.cpp \
    flow/move_flow_element.cpp \
    flow/remove_flow_element.cpp \
    flow/loop_flow_element.cpp \
    flow/isi_flow_element.cpp \
    flow/node_flow_element.cpp \
    flow/flow_sequence.cpp \
    flow/routine_flow_element.cpp \
    flow/movable_flow_element.cpp \
    flow/flow_element.cpp \
    # utility
    utility/path_utility.cpp \
    # resources
    resources/resources_manager.cpp \
    ## components        
    widgets/components/config_parameters/input/keyboard_pw.cpp \
    widgets/components/config_parameters/output/logger_pw.cpp \
    widgets/components/config_parameters/scene/asset_bundle_pw.cpp \
    widgets/components/config_parameters/scene/multi_ab_pw.cpp \
    widgets/components/config_parameters/viewer/blend_fade_viewer_pw.cpp \
    widgets/components/config_widget.cpp \
    widgets/components/config_parameters/sub_parts_pw.cpp \
    ### parameters widgets    
    #### resource
    widgets/components/config_parameters/resource/plot_resource_pw.cpp \
    widgets/components/config_parameters/resource/image_resource_pw.cpp \
    #### audio
    widgets/components/config_parameters/audio/audio_source_pw.cpp \
    widgets/components/config_parameters/audio/microphone_pw.cpp \
    #### avatar
    widgets/components/config_parameters/avatar/humanoid_controller_pw.cpp \
    #### camera
    widgets/components/config_parameters/camera/camera_pw.cpp \
    #### tracking
    widgets/components/config_parameters/tracking/kinect_manager_pw.cpp \
    widgets/components/config_parameters/tracking/qualisys_tracking_pw.cpp \
    widgets/components/config_parameters/tracking/scene_scaner_pw.cpp \
    widgets/components/config_parameters/tracking/thera_trainer_platform_pw.cpp \
    widgets/components/config_parameters/tracking/sonceboz_sg_pw.cpp \
    #### environment
    widgets/components/config_parameters/environment/sky_pw.cpp \
    #### viewer
    widgets/components/config_parameters/viewer/image_viewer_pw.cpp \
    widgets/components/config_parameters/viewer/text_viewer_pw.cpp \
    widgets/components/config_parameters/viewer/fixation_cross_viewer_pw.cpp \
    widgets/components/config_parameters/viewer/webcam_viewer_pw.cpp \
    widgets/components/config_parameters/viewer/fov_simulator_pw.cpp \
    #### input
    widgets/components/config_parameters/input/joypad_pw.cpp \
    #### scene
    widgets/components/config_parameters/scene/mri_pw.cpp \
    #### script
    widgets/components/config_parameters/script/python_script_pw.cpp \
    #### ui
    widgets/components/config_parameters/ui/slider_ui_pw.cpp \
    # experiment
    experiment/experiment.cpp \
    # widgets
    ## dialogs
    widgets/connections/data_models/connectors/convertor/transform_to_vectors_ndm.cpp \
    widgets/connections/data_models/connectors/convertor/vectors_to_transform_ndm.cpp \
    widgets/connections/data_models/connectors/event/keyboard_ndm.cpp \
    widgets/connections/data_models/connectors/generator/transform_ndm.cpp \
    widgets/connections/data_models/connectors/link/check_str_ndm.cpp \
    widgets/connections/data_models/connectors/link/pass_value_trigger_ndm.cpp \
    widgets/connections/data_models/connectors/link/pass_values_ndm.cpp \
    widgets/dialogs/benchmark_dialog.cpp \
    widgets/dialogs/copy_to_conditions_dialog.cpp \
    widgets/dialogs/resources_manager_dialog.cpp \
    widgets/dialogs/documentation_dialog.cpp \
    ## ex_items
    widgets/ex_items/generation/gen_ex_widget.cpp \
    widgets/ex_items/generation/gen_ui_item_dialog.cpp \
    widgets/ex_items/items/ex_camera_target_w.cpp \
    widgets/ex_items/items/ex_checkbox_w.cpp \
    widgets/ex_items/items/ex_color_frame_w.cpp \
    widgets/ex_items/items/ex_combo_box_index_w.cpp \
    widgets/ex_items/items/ex_combo_box_text_w.cpp \
    widgets/ex_items/items/ex_component_w.cpp \
    widgets/ex_items/items/ex_components_list_w.cpp \
    widgets/ex_items/items/ex_config_w.cpp \
    widgets/ex_items/items/ex_curve_w.cpp \
    widgets/ex_items/items/ex_curve_x_w.cpp \
    widgets/ex_items/items/ex_double_spin_box_w.cpp \
    widgets/ex_items/items/ex_float_spin_box_w.cpp \
    widgets/ex_items/items/ex_label_w.cpp \
    widgets/ex_items/items/ex_line_edit_w.cpp \
    widgets/ex_items/items/ex_list_labels_w.cpp \
    widgets/ex_items/items/ex_parameters_generator_w.cpp \
    widgets/ex_items/items/ex_pushbutton_w.cpp \
    widgets/ex_items/items/ex_radio_button_w.cpp \
    widgets/ex_items/items/ex_resource_w.cpp \
    widgets/ex_items/items/ex_select_color_w.cpp \
    widgets/ex_items/items/ex_slider_w.cpp \
    widgets/ex_items/items/ex_spin_box_w.cpp \
    widgets/ex_items/items/ex_text_edit_w.cpp \
    widgets/ex_items/items/ex_time_source_w.cpp \
    widgets/ex_items/items/ex_transformation_w.cpp \
    widgets/ex_items/items/ex_vector2d_w.cpp \
    widgets/ex_items/items/ex_tab_w.cpp \
    widgets/ex_items/items/ex_resources_list_w.cpp \
    ## main
    widgets/designer_window.cpp \
    ## elements
    widgets/elements/flow_diagram_widget.cpp \
    widgets/elements/element_viewer_widget.cpp \
    ## components
    widgets/components/component_widget.cpp \
    widgets/components/components_manager_widget.cpp \
    widgets/components/component_config_dialog.cpp \
    ### parameters widgets
    widgets/components/config_parameters/config_pw.cpp \
    #### camera
    widgets/components/config_parameters/camera/camera_target_pw.cpp \
    widgets/components/config_parameters/camera/camera_trajectory_pw.cpp \
    ## routines
    widgets/ex_items/items/ex_vector3d_w.cpp \
    widgets/routines/timeline_widget.cpp \
    widgets/routines/action_widget.cpp \
    widgets/routines/condition_widget.cpp \
    widgets/routines/routine_tab_widget.cpp \
    widgets/routines/routines_manager_tab_widget.cpp \
    ## connections
    widgets/connections/connections_widget.cpp \
    widgets/connections/ex_flow_view_widget.cpp \
    ### data models
    widgets/connections/data_models/all_node_data_models.cpp \
    widgets/connections/data_models/base_embedded_widget.cpp \
    #### data
    widgets/connections/data_models/data/nodes_data_converters.cpp \
    #### connectors
    widgets/connections/data_models/base_node_data_model.cpp \
    widgets/connections/data_models/connectors/connector_node_data_model.cpp \
    ##### component
    widgets/connections/data_models/connectors/component/component_node_data_model.cpp \
    ##### convertor
    widgets/connections/data_models/connectors/convertor/reals_to_vector2_ndm.cpp \
    widgets/connections/data_models/connectors/convertor/reals_to_vector3_ndm.cpp \
    widgets/connections/data_models/connectors/convertor/vector2_to_reals_ndm.cpp \
    widgets/connections/data_models/connectors/convertor/vector3_to_reals_ndm.cpp \
    widgets/connections/data_models/connectors/convertor/string_list_to_id_any_ndm.cpp \
    ##### generator
    widgets/connections/data_models/connectors/generator/boolean_ndm.cpp \
    widgets/connections/data_models/connectors/generator/id_any_ndm.cpp \
    widgets/connections/data_models/connectors/generator/integer_ndm.cpp \
    widgets/connections/data_models/connectors/generator/real_ndm.cpp \
    widgets/connections/data_models/connectors/generator/string_ndm.cpp \
    widgets/connections/data_models/connectors/generator/vector3_ndm.cpp \
    widgets/connections/data_models/connectors/generator/string_any_ndm.cpp \
    ##### event
    widgets/connections/data_models/connectors/event/check_joypad_ndm.cpp \
    widgets/connections/data_models/connectors/event/check_mouse_ndm.cpp \
    ##### link
    widgets/connections/data_models/connectors/link/conditional_trigger_ndm.cpp \
    widgets/connections/data_models/connectors/link/conditional_gate_ndm.cpp \
    widgets/connections/data_models/connectors/link/check_id_ndm.cpp \
    ##### operator
    widgets/connections/data_models/connectors/operator/string_operation_ndm.cpp \
    widgets/connections/data_models/connectors/operator/decimal_operation_ndm.cpp \
    widgets/connections/data_models/connectors/operator/binary_operation_ndm.cpp \
    ##### function
    widgets/connections/data_models/connectors/function/variable_delay_ndm.cpp \
    widgets/connections/data_models/connectors/function/decimal_trigo_ndm.cpp \
    widgets/connections/data_models/connectors/function/delay_ndm.cpp \
    widgets/connections/data_models/connectors/function/decimal_counter_ndm.cpp \
    ##### display
    widgets/connections/data_models/connectors/display/logger_ndm.cpp \
    widgets/connections/data_models/connectors/display/curve_x_ndm.cpp \
    ##### action
    widgets/connections/data_models/connectors/action/basic_ndm.cpp \
    ##### flow
    widgets/connections/data_models/connectors/flow/time_ndm.cpp \
    widgets/connections/data_models/connectors/flow/flow_routine_ndm.cpp \

FORMS += \
    # elements
    forms/about_dialog.ui \
    forms/copy_to_conditions.ui \
    forms/routine.ui \
    forms/isi.ui \
    forms/loop.ui \
    # timelines
    forms/action.ui \
    forms/condition.ui \
    # dialogs
    forms/generate_instances_dialog.ui \
    # main
    forms/designer_main_window.ui \
    # unity
    forms/base_component_config_widget.ui \
    forms/settings.ui \
    forms/resources_manager_dialog.ui \
    forms/resource_type.ui

RESOURCES += \
    $$EXVR_CPP_RESOURCES_DIR"/resources.qrc" \


RC_ICONS = ExVR_logo.ico
