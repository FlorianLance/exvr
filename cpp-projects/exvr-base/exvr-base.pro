

# /***********************************************************************************
# ** exvr-base                                                                      **
# ** MIT License                                                                    **
# ** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
# ** Permission is hereby granted, free of charge, to any person obtaining a copy   **
# ** of this software and associated documentation files (the "Software"), to deal  **
# ** in the Software without restriction, including without limitation the rights   **
# ** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
# ** copies of the Software, and to permit persons to whom the Software is          **
# ** furnished to do so, subject to the following conditions:                       **
# **                                                                                **
# ** The above copyright notice and this permission notice shall be included in all **
# ** copies or substantial portions of the Software.                                **
# **                                                                                **
# ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
# ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
# ** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
# ** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
# ** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
# ** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
# ** SOFTWARE.                                                                      **
# ************************************************************************************/

####################################### repo
EXVR_REPOSITORY_DIR      = $$PWD"/../.."

####################################### TARGET/TEMPMATE/CONFIG
TARGET = exvr-base
TEMPLATE = lib
CONFIG += staticlib
CONFIG -= console

####################################### PRI
include(../exvr-settings.pri)
include(../exvr-projects.pri)
include(../exvr-thirdparty.pri)
include(../exvr-dependencies.pri)

####################################### PROJECT FILES
HEADERS += \
    ex_component.hpp \
    ex_element.hpp \
    ex_experiment.hpp \
    ex_logger.hpp \
    ex_resource.hpp \

SOURCES += \
    ex_component.cpp \
    ex_element.cpp \
    ex_experiment.cpp \
    ex_logger.cpp \
    ex_resource.cpp \

FORMS += \

RESOURCES += \
