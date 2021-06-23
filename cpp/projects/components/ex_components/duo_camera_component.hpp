
/*******************************************************************************
** exvr-components                                                            **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

//#pragma once

//// std
//#include <memory>
//#include <mutex>
//#include <atomic>

//// duo
//#include <DUOLib.h>
//#include <Dense3DMT.h>

//// expy
//#include "geometry/point4.hpp"

//namespace duo{

//struct DuoFrame{

//    int time = 0;
//    int count = 0;

//    std::mutex mutex;

//    // data
//    std::vector<char> grayScale;
//    std::vector<float> pts;
//    std::vector<bool> mask;

//    std::vector<float> colors;
//    std::vector<float> vertices;

//    // parameters
//    std::atomic<int> minColor = 27;
//    std::atomic<int> maxColor = 255;
//    std::atomic<float> distMin = 10.;
//    std::atomic<float> distMax = 1000.;
//    std::atomic<float> factorColor = 1.4f;

//    geo::Point4<float> startRangeColor = {255/255.f,224/255.f,189/255.f,1};
//    geo::Point4<float> endRangeColor   = {255/255.f,173/255.f,96/255.f,1};

//    int hue = 22;//32;

//    geo::Point4<float> HSV2RGB(float hue, float sat, float val)
//    {
//        float x, y, z;

//        if(hue == 1){
//            hue = 0;
//        }
//        else         hue *= 6;

//        int i = static_cast<int>(floorf(hue));
//        float f = hue - i;
//        float p = val * (1 - sat);
//        float q = val * (1 - (sat * f));
//        float t = val * (1 - (sat * (1 - f)));

//        switch(i)
//        {
//            case 0: x = val; y = t; z = p; break;
//            case 1: x = q; y = val; z = p; break;
//            case 2: x = p; y = val; z = t; break;
//            case 3: x = p; y = q; z = val; break;
//            case 4: x = t; y = p; z = val; break;
//            case 5: x = val; y = p; z = q; break;
//        }
//        return geo::Point4(x,y,z,1.f);
//    }


//};

//class DuoDevice{

//public :

//    ~DuoDevice();

//    bool initialize(unsigned int width,unsigned int height, double fps);

//    void set_exposure(double value);
//    void set_gain(double value);
//    void set_led(double value);
//    void set_horizontal_flip(bool hFlip);
//    void set_vertical_flip(bool vFlip);

//    bool update_dense_params();

//    // Hue map for colorizing the disparity map
////    Vec3b HSV2RGB(float hue, float sat, float val)
////    {
////        float x, y, z;

////        if(hue == 1) hue = 0;
////        else         hue *= 6;

////        int i = static_cast(floorf(hue));
////        float f = hue - i;
////        float p = val * (1 - sat);
////        float q = val * (1 - (sat * f));
////        float t = val * (1 - (sat * (1 - f)));

////        switch(i)
////        {
////            case 0: x = val; y = t; z = p; break;
////            case 1: x = q; y = val; z = p; break;
////            case 2: x = p; y = val; z = t; break;
////            case 3: x = p; y = q; z = val; break;
////            case 4: x = t; y = p; z = val; break;
////            case 5: x = val; y = p; z = q; break;
////        }
////        return Vec3b((uchar)(x * 255), (uchar)(y * 255), (uchar)(z * 255));
////    }

////    Mat colorLut = Mat(cv::Size(256, 1), CV_8UC3);
////    for(int i = 0; i < 256; i++)
////        colorLut.at(i) = (i==0) ? Vec3b(0, 0, 0) : HSV2RGB(i/256.0f, 1, 1);



//private :

//    DUOInstance m_duoInstance = nullptr;
//    Dense3DMTInstance dense3d;

//public :

//    Dense3DParams params;
//    DuoFrame frame;
//};

///// Duo 3D sdk wrapper.
//class DuoTracking{

//    public:

//    bool reset();
//    bool init_point_cloud(unsigned int width,unsigned int height, double fps);

//    DuoDevice* acquisition();

//public:

//    const unsigned int width = 752;
//    const unsigned int height = 480;
//    const double fps = 30.;
//    std::atomic_bool isAlive = false;

//private:

////    std::thread m_updateLoopThread;
//    std::unique_ptr<DuoDevice> m_acquisition = nullptr;
//};
//}

