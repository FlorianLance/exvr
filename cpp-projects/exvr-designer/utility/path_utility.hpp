
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QApplication>
#include <QStandardPaths>

// qt-utility
#include "qt_str.hpp"

namespace tool::ex{

struct Paths{

    static void initialize_paths();

    static inline QString exeDir = "";
    static inline QString exe = "";
    static inline QString dataDir = "";
    static inline QString expLauncherDir = "";
    // exp launcher
    static inline QString expLauncherExe = "";
    // data
    static inline QString expDir = "";
    static inline QString assetsBundlesDir = "";
    static inline QString tempDir = "";
    static inline QString documentationDir = "";
    // log
    static inline QString logsDir = "";
    static inline QString designerLogFile = "";
    static inline QString expLogFile = "";
    // temp
    static inline QString tempExp = "";
    static inline QString tempInstance = "";
    // scripts
    // # python
    static inline QString scriptsPythonDir = "";
    static inline QString templatePythonScript = "";
    // # csharp
    static inline QString scriptsCSharpDir = "";
    static inline QString templateCSharpScript = "";
    // others
    static inline QString documentsDir = "";
    static inline QString desktopDir= "";
};
}
