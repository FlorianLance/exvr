
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "path_utility.hpp"


using namespace tool::ex;


void Paths::initialize_paths(){

    exeDir                  = QApplication::applicationDirPath();
    exe                     = exeDir % QSL("/ExVR.exe");
    dataDir                 = exeDir % QSL("/data");
    expLauncherDir          = exeDir % QSL("/exp-launcher");
    // exp launcher
    expLauncherVR           = expLauncherDir % QSL("/ExVR-exp.exe");
    // data
    expDir                  = dataDir % QSL("/experiments");    
    assetsBundlesDir        = dataDir % QSL("/assetsBundles");
    tempDir                 = dataDir % QSL("/temp");
    documentsDir            = dataDir % QSL("/documentation");
    // log
    logsDir                 = exeDir  % QSL("/logs");
    designerLogFile         = logsDir % QSL("/designer_log.html");
    expLogFile              = logsDir % QSL("/exp_log.txt");
    // doc
    generalDocFile          = documentsDir % QSL("/general.md");
    experimentDocFile       = documentsDir % QSL("/experiment.md");
    elementsDocFile         = documentsDir % QSL("/elements.md");
    randomizationDocFile    = documentsDir % QSL("/randomization.md");
    componentsDocDir        = documentsDir % QSL("/components");
    connectorsDocDir        = documentsDir % QSL("/connectors");
    interfaceDocFile        = documentsDir % QSL("/interface.md");
    expLauncherDocFile      = documentsDir % QSL("/expLauncher.md");
    logsDocFile             = documentsDir % QSL("/logs.md");
    settingsDocFile         = documentsDir % QSL("/settings.md");

    // temp
    tempExp                 = tempDir % QSL("/exp.xml");
    tempInstance            = tempDir % QSL("/debug-instance.xml");
    // scripts
    // # python
    scriptsPythonDir        = dataDir % QSL("/scripts/python");
    templatePythonScript    = scriptsPythonDir % QSL("/template/default.py");
    // # csharp
    scriptsCSharpDir        = dataDir % QSL("/scripts/csharp");
    templateCSharpScript    = scriptsCSharpDir % QSL("/template/default.cs");
    // others
    documentsDir            = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).value(0);
    desktopDir              = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).value(0);
}

