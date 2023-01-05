

/***********************************************************************************
** exvr-export                                                                    **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

#include "k4_volumetric_video_ex_resource_export.hpp"

using namespace tool::ex;
using namespace tool::geo;
using namespace tool::camera;

K4VolumetricVideoExResource *create_k4_volumetric_video_ex_resource(){
    return new K4VolumetricVideoExResource();
}

int get_cameras_nb_k4_volumetric_video_ex_resource(K4VolumetricVideoExResource *vvR){
    return static_cast<int>(vvR->resource.nb_cameras());
}

int get_nb_frames_k4_volumetric_video_ex_resource(K4VolumetricVideoExResource *vvR, int idC){
    return static_cast<int>(vvR->resource.nb_frames(idC));
}

float get_duration_ms_k4_volumetric_video_ex_resource(K4VolumetricVideoExResource *vvR, int idC){
    auto start = vvR->resource.start_time(idC);
    auto end   = vvR->resource.end_time(idC);
    return (end-start)*0.000001f;
}

void get_camera_transform_k4_volumetric_video_ex_resource(K4VolumetricVideoExResource *vvR, int idC, float *model){
    auto tr = vvR->resource.get_transform(idC).conv<float>();
    std::copy(std::begin(tr.array), std::end(tr.array), model);
}

int get_id_frame_from_time_ms_k4_volumetric_video_ex_resource(K4VolumetricVideoExResource *vvR, int idC, float timeMs){
    return static_cast<int>(vvR->resource.frame_id(idC, timeMs));
}

int get_valid_vertices_count_k4_volumetric_video_ex_resource(K4VolumetricVideoExResource *vvR, int idC, int idF){
    return static_cast<int>(vvR->resource.valid_vertices_count(idF,idC));
}

int get_audio_data_total_size_k4_volumetric_video_ex_resource(tool::ex::K4VolumetricVideoExResource *vvR, int idC){
    return static_cast<int>(vvR->resource.total_audio_frames_size(idC));
}
