
/***********************************************************************************
** exvr-export-app                                                                **
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


// std
#include <iostream>
#include <memory>

#include "ex_components/dc_manager_ex_component.hpp"
#include "ex_components/k4_manager_ex_component_export.hpp"

#include "ex_resources/k4_volumetric_video_ex_resource_export.hpp"
#include "ex_components/k4_volumetric_video_ex_component_export.hpp"



using namespace tool;
using namespace tool::ex;
using namespace tool::cam;



auto test_dc_manager(const std::string &networkFilePath) -> void{

    tool::ex::ExExperiment exp;
    exp.generate_logger("","");

    auto manager = create_k4_manager_ex_component();
    manager->set_exp(&exp);
    manager->set(ParametersContainer::InitConfig, "debug_bypass", 0);
    manager->set(ParametersContainer::Dynamic, "path_network_settings_file", networkFilePath);

    auto res = manager->initialize();
    std::cout << std::format("initialize ret {}\n", res);
    manager->start_experiment();
    // manager->start_routine();

    auto nbCameras = manager->get<int>(ParametersContainer::Dynamic, "nb_connections");
    std::vector<int> framesId;
    framesId.resize(nbCameras);
    std::fill(framesId.begin(), framesId.end(), 0);

    std::vector<DCVertexMeshData> meshData;
    meshData.resize(900000);

    for(int ii = 0; ii < 200; ++ii){

        manager->pre_update();
        manager->update();
        manager->post_update();

        auto nb = manager->get<int>(ParametersContainer::Dynamic, "nb_frames_received");
        std::cout << std::format("update [{}] [{}] [{}]\n", nb, nbCameras, framesId.size());

        for(size_t jj = 0; jj < nbCameras; ++jj){

            std::vector<int> states(3);
            retrieve_cloud_frame_data_k4_manager_ex_component(manager, jj, framesId[jj], meshData.data(), states.data());
            if(states[0] == 1){
                // std::cout << std::format("re c[{}] [{}][{}][{}]\n", jj, states[0], states[1], states[2]);
            }


            // auto ret = manager->get_cloud_frame_data(jj,framesId[jj], meshData.data());
            // if(std::get<0>(ret)){
            //     framesId[jj] = static_cast<int>(std::get<1>(ret));
            //     std::cout << std::format("re c[{}] [{}][{}][{}]\n", jj, std::get<0>(ret),std::get<1>(ret),std::get<2>(ret));
            // }
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(20));
    }

    manager->stop_routine();
    manager->stop_experiment();
    manager->clean();
    delete manager;
}


auto test_k4_video()  -> void{

    // auto videoResource = create_k4_volumetric_video_ex_resource();

    // Logger::no_file_init();
    // Logger::get()->message_signal.connect([&](std::string message){
    //     std::cout << message;
    // });
    // Logger::get()->error_signal.connect([&](std::string error){
    //     std::cerr << error;
    // });
    // Logger::message("initialize\n");


    // std::string path = "D:/DATA/Kinect videos/adriel.kvid";
    // std::cout << "init video from path " << path << "\n";
    // videoResource->set(ParametersContainer::Dynamic, "path_file", path);
    // if(!videoResource->initialize()){
    //     std::cerr << "Cannot initialize video from path: " << path << "\n";
    //     return;
    // }




    // int nbCameras = get_cameras_nb_k4_volumetric_video_ex_resource(videoResource);
    // std::cout << "nb cameras: " << nbCameras << "\n";
    // for(int ii = 0; ii < nbCameras; ++ii){

    //     std::cout << "model: " << videoResource->video.get_camera_data(ii)->transform << "\n";

    //     std::cout << "cam " << ii << " nb frames " << get_nb_frames_k4_volumetric_video_ex_resource(videoResource, ii) << "\n";
    //     std::cout << "duration: " << get_duration_ms_k4_volumetric_video_ex_resource(videoResource,ii) << "\n";
    // }

    // return;
    // auto videoComponent = create_k4_volumetric_video_ex_component(videoResource);


    // std::vector<tool::cam::DCVertexMeshData> data;

    // for(int idC = 0; idC < nbCameras; ++idC){
    //     for(int idF = 0; idF < get_nb_frames_k4_volumetric_video_ex_resource(videoResource, idC); ++idF){

    //         auto cData = videoResource->video.get_camera_data(idC);
    //         auto &d = cData->frames[idF];
    //         //            std::cout <<
    //         //                " idc " << d->idCapture << " vvc " << d->validVerticesCount << " " <<
    //         //                " eco " << d->encodedColorData.size() <<
    //         //                " ede " << d->encodedDepthData.size() <<
    //         //                " ein " << d->encodedInfraData.size() <<
    //         //                " pco " << d->encodedProcessedColorData.size() <<
    //         //                " ecl " << d->encodedCloudData.size() <<
    //         //                " imu " << d->imuSample.has_value() <<
    //         //                " aud " << d->audioFrames.size() <<
    //         //                " cal " << d->calibration.has_value() << "\n";


    //                     data.resize(d->validVerticesCount);;
    //         std::cout << "uncompress " << idC << " " << idF << " ";
    //         int success = uncompress_frame_vmd_k4_volumetric_video_ex_component(videoComponent, idC, idF, data.data());
    //         std::cout << "-> " << success << "\n";
    //     }
    // }


    // delete videoResource;
    // delete videoComponent;
}


int main(int, char *[]){

    std::string pathN = "D:/DEV/EPFL/lnco-exvr/exvr/toolset/cpp-projects/_build/bin/dc-manager/config/network/network_FLORIAN-PC.config";
    test_dc_manager(pathN);
    // test_k4_video();

    return 0;
}


