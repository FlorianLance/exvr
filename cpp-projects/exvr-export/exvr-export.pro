
# /*******************************************************************************
# ** exvr-export                                                                **
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
TARGET = exvr-export
TEMPLATE = lib
CONFIG += dll
CONFIG -= console
CONFIG -= qt

####################################### PRI
include(../exvr-settings.pri)
include(../exvr-projects.pri)
include(../exvr-thirdparty.pri)
include(../exvr-dependencies.pri)

######################################## PROJECT FILES
HEADERS += \
    # ex_components
    ex_components/dc_manager_ex_component.hpp \
    ex_components/ex_component_export.hpp \
    # ex_resources
    ex_components/k2_manager_ex_component.hpp \
    ex_components/k2_manager_ex_component_export.hpp \
    ex_components/k4_manager_ex_component_export.hpp \
    ex_components/k4_volumetric_video_ex_component.hpp \
    ex_components/k4_volumetric_video_ex_component_export.hpp \
    ex_components/python_script_ex_component.hpp \
    ex_components/python_script_ex_component_export.hpp \
    ex_components/video_saver_ex_component.hpp \
    ex_components/video_saver_ex_component_export.hpp \
    ex_element_export.hpp \
    ex_experiment_export.hpp \
    ex_resources/ex_resource_export.hpp \
    ex_resources/k2_volumetric_video_ex_resource.hpp \
    ex_resources/k2_volumetric_video_ex_resource_export.hpp \
    ex_resources/k4_volumetric_video_ex_resource.hpp \
    ex_resources/k4_volumetric_video_ex_resource_export.hpp

SOURCES += \
    # ex_components
    ex_components/dc_manager_ex_component.cpp \
    ex_components/ex_component_export.cpp \
    # ex_resources
    ex_components/k2_manager_ex_component.cpp \
    ex_components/k2_manager_ex_component_export.cpp \
    ex_components/k4_manager_ex_component_export.cpp \
    ex_components/k4_volumetric_video_ex_component_export.cpp \
    ex_components/python_script_ex_component.cpp \
    ex_components/python_script_ex_component_export.cpp \
    ex_components/video_saver_ex_component.cpp \
    ex_components/video_saver_ex_component_export.cpp \
    ex_element_export.cpp \
    ex_experiment_export.cpp \
    ex_resources/ex_resource_export.cpp \
    # main    
    ex_resources/k2_volumetric_video_ex_resource.cpp \
    ex_resources/k2_volumetric_video_ex_resource_export.cpp \
    ex_resources/k4_volumetric_video_ex_resource_export.cpp \

