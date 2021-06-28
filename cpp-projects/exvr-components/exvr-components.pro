
# /*******************************************************************************
# ** exvr-components                                                            **
# ** No license (to be defined)                                                 **
# ** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
# ********************************************************************************/

####################################### TARGET
TARGET = exvr-components

####################################### PRI
# defines projects settings
include(../projects.pri)
# defines compiling options
include(../settings.pri)
# generate paths
include(../paths.pri)
# defines thirdparty includes and libs
include(../thirdparty.pri)

####################################### TEMPLATE
equals(EXVR_COMPONENTS_T, "lib"){
    TEMPLATE = lib
    CONFIG += staticlib
    CONFIG -= console
}
equals(EXVR_COMPONENTS_T, "app"){
    TEMPLATE = app
    CONFIG += console
}

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
    ex_components/python_component.hpp \
    ex_components/video_saver_component.hpp \

SOURCES += \
    # ex_components
    ex_components/duo_camera_component.cpp \
    ex_components/video_saver_component.cpp \
    ex_components/python_component.cpp \
    # main
    main.cpp \


