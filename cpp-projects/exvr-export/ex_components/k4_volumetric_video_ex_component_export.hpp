
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

#pragma once

// local
#include "k4_volumetric_video_ex_component.hpp"

extern "C"{

    DECL_EXPORT tool::ex::K4VolumetricVideoExComponent *create_k4_volumetric_video_ex_component(
        tool::ex::K4VolumetricVideoExResource *resourceExport);

    DECL_EXPORT int uncompress_frame_c4f_k4_volumetric_video_ex_component(
        tool::ex::K4VolumetricVideoExComponent *vvC,
        int idC, int idFrame,
        tool::geo::Pt3f *vertices, tool::geo::Pt4f *colors);

    DECL_EXPORT int uncompress_frame_c3i_k4_volumetric_video_ex_component(
        tool::ex::K4VolumetricVideoExComponent *vvC,
        int idC, int idFrame,
        tool::geo::Pt3f *vertices, tool::geo::Pt4<std::uint8_t> *colors);

    DECL_EXPORT int uncompress_frame_vmd_k4_volumetric_video_ex_component(
        tool::ex::K4VolumetricVideoExComponent *vvC,
        int idC, int idFrame,
        tool::camera::K4VertexMeshData *vertices);

    DECL_EXPORT int process_audio_k4_volumetric_video_ex_component(
        tool::ex::K4VolumetricVideoExComponent *vvC, int idCamera);

    DECL_EXPORT void copy_audio_samples_k4_volumetric_video_ex_component(
        tool::ex::K4VolumetricVideoExComponent *vvC, int idCamera, float *audioSamples);
}