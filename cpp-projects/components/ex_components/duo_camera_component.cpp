
/*******************************************************************************
** exvr-components                                                            **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

//#include "duo_camera_component.hpp"

//// std
//#include <iostream>
//#include <algorithm>

//using namespace duo;

//DuoDevice::~DuoDevice(){

//    // Stop capture
//    StopDUO(m_duoInstance);

//    // Close DUO
//    CloseDUO(m_duoInstance);
//}

//bool DuoDevice::initialize(unsigned int width, unsigned int height, double fps){

//    if (!Dense3DOpen(&dense3d)){
//        std::cerr << "Could not open Dense3DMT" << std::endl;
//        return false;
//    }
//    m_duoInstance = GetDUOInstance(dense3d);

//    if (!OpenDUO(&m_duoInstance)){
//        std::cerr << "couldn't open the duo sensor" << std::endl;
//        return false;
//    }

//    char tmp[260];
//    GetDUODeviceName(m_duoInstance, tmp);
//    std::cout << "DUO Device Name: " << tmp << std::endl;
//    GetDUOSerialNumber(m_duoInstance, tmp);
//    std::cout << "DUO Serial Number: " << tmp << std::endl;
//    GetDUOFirmwareVersion(m_duoInstance, tmp);
//    std::cout << "DUO Firmware Version: " << tmp << std::endl;
//    GetDUOFirmwareBuild(m_duoInstance, tmp);
//    std::cout << "DUO Firmware Build: " << tmp << std::endl;
//    std::cout << "DUOLib Version: " << GetDUOLibVersion() << std::endl;
//    std::cout << "Dense3DMT Version: " << Dense3DGetLibVersion() << std::endl;

//    if (!SetDense3DLicense(dense3d, "CNCZR-3M4RX-QU85W-ADJVV-R7869")){ // <-- Put your Dense3D license
//        std::cerr << "Invalid or missing Dense3D license. To get your license visit https://duo3d.com/account\n" << std::endl;
//        Dense3DClose(dense3d);
//        return false;
//    }

//    if (!SetDense3DImageInfo(dense3d, width, height, fps)){
//        std::cerr << "SetDense3DImageInfo error" << std::endl;
//        Dense3DClose(dense3d);
//        return false;
//    }

//    params.scale             = 3;  // [0, 3] - [No Scale, Scale X, Scale Y, Scale X&Y]
//    params.mode              = 0;  // [0, 3] - [BM, SGBM, BM_HQ, SGBM_HQ]
//    params.preFilterCap      = 63; // [1, 63]
//    params.numDisparities    = 4;  // [2, 16]
//    params.sadWindowSize     = 10; // [2, 10]
//    params.uniqenessRatio    = 1;  // [1, 100]
//    params.speckleWindowSize = 60; // [0, 256]
//    params.speckleRange      = 20; // [0, 32]

//    if (!update_dense_params()){
//        std::cerr << "GetDense3Params error" << std::endl;
//        Dense3DClose(dense3d);
//        return false;
//    }

//    // resize frames
//    frame.grayScale.resize(width*height);
//    frame.pts.resize(width*height*3);
//    frame.mask.resize(width*height);

//    // Queue used to receive Dense3D frames
//    if (!Dense3DStart(dense3d, [](const PDense3DFrame pFrameData, void* pUserData){

//        auto start = std::chrono::high_resolution_clock::now();


//        DuoFrame *frame = reinterpret_cast<DuoFrame*>(pUserData);
//        const size_t size = pFrameData->duoFrame->width*pFrameData->duoFrame->height;

//        std::copy(pFrameData->duoFrame->leftData, pFrameData->duoFrame->leftData   + size, frame->grayScale.begin());
//        std::copy(&pFrameData->depthData->x, &(pFrameData->depthData->x) + size*3, frame->pts.begin());

//        // compute data
//        size_t countValidPts = 0;
//        std::fill(frame->mask.begin(),frame->mask.end(), false);
//        for(size_t ii = 0; ii < size; ++ii){

//            // depth filter
//            if(frame->pts[ii*3 + 2] < frame->distMin || frame->pts[ii*3 + 2] > frame->distMax){
//                continue;
//            }
//            // color filter
//            if(frame->grayScale[ii] < frame->minColor || frame->grayScale[ii] > frame->maxColor){
//                continue;
//            }
//            frame->grayScale[ii] = static_cast<char>(std::clamp(static_cast<float>(frame->factorColor*frame->grayScale[ii]), 0.f, 255.f));
//            frame->mask[ii] = true;
//            ++countValidPts;
//        }

//        frame->mutex.lock();
//        frame->vertices.resize(countValidPts*3);
//        frame->colors.resize(countValidPts*4);
//        size_t validPts = 0;
//        for(size_t ii = 0; ii < frame->mask.size(); ++ii){
//            if(frame->mask[ii]){
//                std::copy(frame->pts.begin()+ii*3, frame->pts.begin()+(ii+1)*3, frame->vertices.begin()+validPts*3);
//                size_t idStartCol = validPts*4;
//                float col = frame->grayScale[ii]/255.f;

////                auto newCol = frame->HSV2RGB(frame->hue, col, 255);// (frame->startRangeColor * col + frame->endRangeColor*(1-col))*0.5f;
////                frame->colors[idStartCol+0] = newCol[0];
////                frame->colors[idStartCol+1] = newCol[1];
////                frame->colors[idStartCol+2] = newCol[2];
////                frame->colors[idStartCol+3] = newCol[3];
//                frame->colors[idStartCol+0] = col;
//                frame->colors[idStartCol+1] = col;
//                frame->colors[idStartCol+2] = col;
//                frame->colors[idStartCol+3] = 1.f;
//                ++validPts;
//            }
//        }

//        frame->mutex.unlock();
//        ++frame->count;
//        auto end = std::chrono::high_resolution_clock::now();
//        frame->time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

//    }, &frame)){
//        std::cerr << "Dense3DStart error" << std::endl;
//        Dense3DClose(dense3d);
//        return false;
//    }

//    // Set exposure, LED brightness and camera orientation
//    SetDUOExposure(m_duoInstance, 42);
//    SetDUOGain(m_duoInstance, 0);
//    SetDUOLedPWM(m_duoInstance, 30);
//    SetDUOHFlip(m_duoInstance, false);
//    SetDUOVFlip(m_duoInstance, false);
//    SetDUOAutoExposure(m_duoInstance, false);
//    SetDUOUndistort(m_duoInstance, true);

//    DUOResolutionInfo ri;
//    GetDUOResolutionInfo(m_duoInstance, &ri);
//    double fov[4];
//    GetDUORectifiedFOV(m_duoInstance, fov);

//    std::cout << "Depth3D Duo Loaded Correctly!" << std::endl;
//    return true;
//}

//void DuoDevice::set_exposure(double value){
//    SetDUOExposure(m_duoInstance, value);//std::clamp(value, 0.,100.));
//}

//void DuoDevice::set_gain(double value){
//    SetDUOGain(m_duoInstance, value);//std::clamp(value, 0.,100.));
//}

//void DuoDevice::set_led(double value){
//    SetDUOLedPWM(m_duoInstance, value);//std::clamp(value, 0.,100.));
//}

//void DuoDevice::set_horizontal_flip(bool hFlip){
//    SetDUOHFlip(m_duoInstance, hFlip);
//}

//void DuoDevice::set_vertical_flip(bool vFlip){
//    SetDUOVFlip(m_duoInstance, vFlip);
//}

//bool DuoDevice::update_dense_params(){
//    return SetDense3Params(dense3d, params);
//}


//bool DuoTracking::reset(){
//    m_acquisition = std::make_unique<DuoDevice>();
//    return init_point_cloud(width,height,fps);
//}

//bool DuoTracking::init_point_cloud(unsigned int width, unsigned int height, double fps){

//    if(m_acquisition->initialize(width, height, fps)){
//        return true;
//    }

//    std::cerr << "Can't init point cloud\n";
//    return false;
//}



//DuoDevice *DuoTracking::acquisition(){
//    return m_acquisition.get();
//}
