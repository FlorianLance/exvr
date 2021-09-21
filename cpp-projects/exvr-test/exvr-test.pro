
# /*******************************************************************************
# ** exvr-test                                                                  **
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
    TARGET = exvr-testd
}
equals(CFG, "release"){
    TARGET = exvr-test
}

####################################### TEMPLATE
equals(EXVR_TEST_TARGET, "app"){
    TEMPLATE = app
    CONFIG += console
}

####################################### BUILD FILES
OBJECTS_DIR = $$EXVR_TEST_OBJ
MOC_DIR     = $$EXVR_TEST_MOC
RCC_DIR     = $$EXVR_TEST_RCC
UI_DIR      = $$EXVR_TEST_UI
DESTDIR     = $$EXVR_TEST_DEST

####################################### CONFIG
QT  += core gui network concurrent widgets opengl

######################################## INCLUDES
INCLUDEPATH += \
    # base
    $$BASE_INCLUDES \
    # qt-utility
    $$QT_UTILITY_INCLUDES \
    # exvr-designer
    $$EXVR_DESIGNER_INCLUDES \
    # catch
    $$CATCH_INCLUDES \
    $$QWT_INCLUDES \
    $$NODES_INCLUDES \
    $$MAGIC_ENUM_INCLUDES\

######################################## LIBRAIRIES

LIBS +=  \
    # base
    $$BASE_LIB \
    # qt-utility
    $$QT_UTILITY_LIB \
    # exvr-designer
    $$EXVR_DESIGNER_OBJ"/ExVR-designer_pch.obj" \
    $$EXVR_DESIGNER_OBJ"/xml_io_manager.obj" \
#    $$EXVR_DESIGNER_OBJ"/moc_xml_io_manager.obj" \
    $$EXVR_DESIGNER_OBJ"/experiment.obj" \
    $$EXVR_DESIGNER_OBJ"/component.obj" \
    $$EXVR_DESIGNER_OBJ"/timeline.obj" \
    $$EXVR_DESIGNER_OBJ"/config.obj" \
    $$EXVR_DESIGNER_OBJ"/action.obj" \
    $$EXVR_DESIGNER_OBJ"/condition.obj" \
    $$EXVR_DESIGNER_OBJ"/routine.obj" \
    $$EXVR_DESIGNER_OBJ"/isi.obj" \
    $$EXVR_DESIGNER_OBJ"/loop.obj" \
    $$EXVR_DESIGNER_OBJ"/interval.obj" \
    $$EXVR_DESIGNER_OBJ"/components_manager.obj" \
    $$EXVR_DESIGNER_OBJ"/resources_manager.obj" \
    $$EXVR_DESIGNER_OBJ"/connector.obj" \
    $$EXVR_DESIGNER_OBJ"/path_utility.obj" \
    # third-party
    $$QWT_LIBS \
    $$NODES_LIB \


######################################## PROJECT FILES

#HEADERS += \

SOURCES += \
    exvr-test-main.cpp \
    exvr-designer_tests.cpp \


