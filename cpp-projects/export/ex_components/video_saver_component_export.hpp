
/*******************************************************************************
** exvr-export                                                                **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// components
#include "ex_components/video_saver_component.hpp"

// local
#include "export_utility.hpp"

extern "C"{

    DECL_EXPORT tool::ex::VideoSaverComponent* create_video_saver_component();
    DECL_EXPORT void delete_video_saver_component(tool::ex::VideoSaverComponent *videoGeneratorComponent);
    DECL_EXPORT int add_frame_video_saver_component(tool::ex::VideoSaverComponent *videoGeneratorComponent, int width, int height, char *data, const char *format, int dataType);
}
