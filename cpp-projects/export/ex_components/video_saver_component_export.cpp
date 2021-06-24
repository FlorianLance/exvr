
/*******************************************************************************
** exvr-export                                                                **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "video_saver_component_export.hpp"

using namespace tool::ex;

VideoSaverComponent *create_video_saver_component(){
    return new VideoSaverComponent();
}

void delete_video_saver_component(VideoSaverComponent *videoGeneratorComponent){
    delete videoGeneratorComponent;
}

int add_frame_video_saver_component(VideoSaverComponent *videoGeneratorComponent, int width, int height, char *data, const char *format, int dataType){
    return videoGeneratorComponent->add_frame(width, height, data, format, dataType);
}
