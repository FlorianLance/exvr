
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

namespace tool::ex {

struct Settings{

    enum class ExpLauncherDisplayMode : int{
        OpenVR=0, Flat, FlatStereo
    };

    // debug
    bool debug = true;
    bool catchComponentsExceptions = false;
    bool csharpAddDebugInfo = false;

    // camera
    bool neutralX = false;
    bool neutralY = true;
    bool neutralZ = false;
    bool positionalTracking = true;

    // display
    ExpLauncherDisplayMode displayMode = ExpLauncherDisplayMode::OpenVR;
    int stereoCameraFOV = 60;
    bool fullscreen = false;
    int monitorId = 1;
    int resolutionId = 2;
    int customWidth = 1920;
    int customHeight = 1080;

    // input
    bool catchExternalKeyboardKeysEvents = false;

    void reset(){

        // debug
        debug = true;
        catchComponentsExceptions = false;
        csharpAddDebugInfo = false;

        // camera
        neutralX = false;
        neutralY = true;        
        neutralZ = false;
        positionalTracking = true;

        // display
        displayMode = ExpLauncherDisplayMode::OpenVR;
        stereoCameraFOV = 60;
        fullscreen = false;
        monitorId = 1;
        resolutionId = 2;
        customWidth = 1920;
        customHeight = 1080;
    }
};
}
