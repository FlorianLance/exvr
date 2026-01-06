

# /*******************************************************************************
# ** exvr-test                                                                  **
# ** MIT License                                                                **
# ** Copyright (c) [2018] [Florian Lance]                                       **
# **                                                                            **
# ** Permission is hereby granted, free of charge, to any person obtaining a    **
# ** copy of this software and associated documentation files (the "Software"), **
# ** to deal in the Software without restriction, including without limitation  **
# ** the rights to use, copy, modify, merge, publish, distribute, sublicense,   **
# ** and/or sell copies of the Software, and to permit persons to whom the      **
# ** Software is furnished to do so, subject to the following conditions:       **
# **                                                                            **
# ** The above copyright notice and this permission notice shall be included in **
# ** all copies or substantial portions of the Software.                        **
# **                                                                            **
# ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR **
# ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   **
# ** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    **
# ** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER **
# ** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    **
# ** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        **
# ** DEALINGS IN THE SOFTWARE.                                                  **
# **                                                                            **
# ********************************************************************************/

####################################### repo
EXVR_REPOSITORY_DIR      = $$PWD"/../.."

####################################### TARGET/TEMPMATE/CONFIG
TARGET = exvr-test
TEMPLATE = app
CONFIG += console
QT  += core gui network concurrent widgets opengl

####################################### PRI
include(../exvr-settings.pri)
include(../exvr-projects.pri)
include(../exvr-thirdparty.pri)
include(../exvr-dependencies.pri)

####################################### INCLUDES

EXVR_TEST_DEP_INCLUDEPATH =\
    #
    $$EXVR_TEST_THIRDPARTY_INCLUDES\
    $$EXVR_DESIGNER_THIRDPARTY_INCLUDES\
    $$EXVR_BASE_THIRDPARTY_INCLUDES\
    $$TS_QT_THIRDPARTY_INCLUDES\
    $$TS_QT_NODES_THIRDPARTY_INCLUDES\
    $$TS_BASE_THIRDPARTY_INCLUDES\
    #
    $$EXVR_DESIGNER_INCLUDES\
    $$EXVR_BASE_INCLUDES\
    $$TS_QT_INCLUDES\
    $$TS_QT_NODES_INCLUDES\
    $$TS_BASE_INCLUDES\

####################################### LIBS


EXVR_TEST_DEP_LIBS =\
    #
    $$EXVR_TEST_THIRDPARTY_LIBS\
    $$EXVR_DESIGNER_THIRDPARTY_LIBS\
    $$EXVR_BASE_THIRDPARTY_LIBS\
    $$TS_QT_THIRDPARTY_LIBS\
    $$TS_BASE_THIRDPARTY_LIBS\
    #
    $$EXVR_DESIGNER_OBJ_FILES\
    $$EXVR_DESIGNER_MOC_OBJ_FILES\
    $$EXVR_BASE_LIB\
    $$TS_QT_LIB\
    $$TS_QT_NODES_LIB\
    $$TS_BASE_LIB\
    # $$TS_QT_NODES_LIB\

    # $$EXVR_BASE_LIB\
    # $$TS_QT_LIB\

message("APP")
message($$EXVR_BASE_MOC_OBJ_FILES)

####################################### DEP

EXVR_TEST_PRE_TARGETDEPS =\
    $$EXVR_BASE_LIB_FILE\
    $$TS_QT_LIB_FILE\
    $$TS_QT_NODES_FILE\
    $$TS_BASE_LIB_FILE\

####################################### GENERATE VARIABLES

include(../exvr-gen-var.pri)

######################################## PROJECT FILES
HEADERS += \

SOURCES += \
    exvr-test-main.cpp \
    exvr-designer_tests.cpp \


