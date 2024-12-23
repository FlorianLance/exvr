// /***********************************************************************************
// ** exvr-export                                                                    **
// ** MIT License                                                                    **
// ** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
// ** Permission is hereby granted, free of charge, to any person obtaining a copy   **
// ** of this software and associated documentation files (the "Software"), to deal  **
// ** in the Software without restriction, including without limitation the rights   **
// ** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
// ** copies of the Software, and to permit persons to whom the Software is          **
// ** furnished to do so, subject to the following conditions:                       **
// **                                                                                **
// ** The above copyright notice and this permission notice shall be included in all **
// ** copies or substantial portions of the Software.                                **
// **                                                                                **
// ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
// ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
// ** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
// ** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
// ** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
// ** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
// ** SOFTWARE.                                                                      **
// ************************************************************************************/

// #pragma once

// // base
// #include "exvr/ex_component.hpp"
// #include "depth-camera/dc_types.hpp"

// namespace tool::ex {

// class DCManagerExComponent : public ExComponent{

// public:

//     DCManagerExComponent();
//     ~DCManagerExComponent() override;

//     auto initialize() -> bool override;
//     auto clean() -> void override;
//     auto start_experiment() -> void override;
//     auto stop_experiment() -> void override;
//     auto update_from_current_config() -> void override;
//     auto update() -> void override;

//     auto read_messages() -> void;
//     auto get_cloud_frame_data(size_t idCamera, size_t currentFrameId, cam::DCVertexMeshData *vertices) -> std::tuple<bool, size_t, size_t>;

//     bool debugBypass = false;

//     std::chrono::nanoseconds startExperimentTime;

// private:
//     struct Impl;
//     std::unique_ptr<Impl> i;
// };
// }
