
# /*******************************************************************************
# ** exvr-components                                                            **
# ** No license (to be defined)                                                 **
# ** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
# ********************************************************************************/

####################################### repo
EXVR_REPOSITORY_DIR      = $$PWD"/../.."

####################################### PRI
# defines compiling options
include(../exvr-settings.pri)
# defines projects paths and variables
include(../exvr-projects.pri)
# defines thirdparty includes and libs
include(../exvr-thirdparty.pri)

####################################### TARGET
equals(CFG, "debug"){
    TARGET = exvr-componentsd
}
equals(CFG, "release"){
    TARGET = exvr-components
}

####################################### TEMPLATE
equals(EXVR_COMPONENTS_TARGET, "lib"){
    TEMPLATE = lib
    CONFIG += staticlib
    CONFIG -= console
}
equals(EXVR_COMPONENTS_TARGET, "app"){
    TEMPLATE = app
    CONFIG += console
}

####################################### BUILD FILES
OBJECTS_DIR = $$EXVR_COMPONENTS_OBJ
DESTDIR     = $$EXVR_COMPONENTS_DEST

####################################### CONFIG
CONFIG -= qt

####################################### INCLUDES
INCLUDEPATH += \
    # base
    $$BASE_INCLUDES\
    # local
    ex_components \
    # third party
    $$OPENCV_INCLUDES \
    $$BOOST_INCLUDES \
    $$PYTHON_INCLUDES \
    $$BOOST_INCLUDES \
    $$SIGNALS_INCLUDES \

####################################### LIBRAIRIES

LIBS +=  \
    $$BASE_LIB \
    # third party
    $$OPENCV_LIBS \
    $$PYTHON_LIBS \
    $$BOOST_LIBS \

####################################### PROJECT FILES

HEADERS += \
    # ex_components
    ex_components/duo_camera_component.hpp \
    ex_components/python_script_component.hpp \
    ex_components/video_saver_component.hpp \

SOURCES += \
    # ex_components
    ex_components/duo_camera_component.cpp \
    ex_components/python_script_component.cpp \
    ex_components/video_saver_component.cpp \
    # main
    main.cpp \


