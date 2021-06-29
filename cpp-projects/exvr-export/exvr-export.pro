
# /*******************************************************************************
# ** exvr-export                                                                **
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
    TARGET = exvr-exportd
}
equals(CFG, "release"){
    TARGET = exvr-export
}

####################################### TEMPLATE
equals(EXVR_EXPORT_TARGET, "dll"){
    TEMPLATE = lib
    CONFIG += dll
    CONFIG -= console
}
equals(EXVR_EXPORT_TARGET, "app"){
    TEMPLATE = app
    CONFIG += console
}

####################################### BUILD FILES
OBJECTS_DIR = $$EXVR_EXPORT_OBJ
DESTDIR     = $$EXVR_EXPORT_DEST

####################################### CONFIG
CONFIG -= qt

######################################## INCLUDES
INCLUDEPATH += \
    # base
    $$BASE_INCLUDES \
    # exvr-components
    $$EXVR_COMPONENTS_INCLUDES \
    # local
    ex_components\
    utility\
    # opencv
    $$OPENCV_INCLUDES \
    # boost
    $$BOOST_INCLUDES \
    # signals
    $$SIGNALS_INCLUDES \
    # PYTHON
    $$PYTHON_INCLUDES \

######################################## LIBRAIRIES


LIBS +=  \
    # base
    $$BASE_LIB \
    # exvr-components
    $$EXVR_COMPONENTS_LIB \
    # opencv
    $$OPENCV_LIBS \
    # windows
    $$WINDOWS_LIBS \
    # python
    $$PYTHON_LIBS \
    # boost
    $$BOOST_LIBS \
    # turbojpg
    $$TURBOJPG_LIBS \
    # fastfor
    $$FASTPFOR_LIBS \

######################################## PROJECT FILES

HEADERS += \
    # ex_components
    ex_components/python_component_export.hpp \
    ex_components/ex_component_export.hpp \
    ex_components/video_saver_component_export.hpp \
    # utility
    utility/export_utility.hpp \

SOURCES += \
    # ex_components
    ex_components/python_component_export.cpp \
    ex_components/ex_component_export.cpp \
    ex_components/video_saver_component_export.cpp \
    # main
    main.cpp \


