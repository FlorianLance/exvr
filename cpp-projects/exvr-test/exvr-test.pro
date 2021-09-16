
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

######################################## LIBRAIRIES


LIBS +=  \
    # base
    $$BASE_LIB \
    # qt-utility
    $$QT_UTILITY_LIB \
    # exvr-designer
    $$EXVR_DESIGNER_LIB \
    # boost
    $$BOOST_LIBS \


######################################## PROJECT FILES

#HEADERS += \

SOURCES += \
    exvr-test-main.cpp \
    exvr-designer_tests.cpp \


