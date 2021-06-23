
# /*******************************************************************************
# ** exvr-export                                                                **
# ** No license (to be defined)                                                 **
# ** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
# ********************************************************************************/

####################################### TARGET
TARGET = exvr-export

####################################### PRI
# defines projects settings
include(../../projects.pri)
# defines compiling options
include(../settings.pri)
# generate paths
include(../paths.pri)
# defines thirdparty includes and libs
include(../thirdparty.pri)


####################################### TEMPLATE
equals(EXPORT_T, "dll"){
    TEMPLATE = lib
    CONFIG += dll
    CONFIG -= console
}
equals(EXPORT_T, "app"){
    TEMPLATE = app
    CONFIG += console
}

OBJECTS_DIR = $$EXPORT_OBJ
DESTDIR     = $$EXPORT_DEST

####################################### CONFIG
CONFIG -= qt

######################################## INCLUDES
INCLUDEPATH += \
    # base
    $$BASE_INCLUDES \
    # components
    $$COMPONENTS_INCLUDES \
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
    # components
    $$COMPONENTS_LIB \
    # opencv
    $$OPENCV_LIBS \
    # windows
    $$WINDOWS_LIBS \
    # python
    $$PYTHON_LIBS \
    # boost
    $$BOOST_LIBS \

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

DISTFILES += \
    ../config.pri

