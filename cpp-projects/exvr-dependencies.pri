
# /*******************************************************************************
# ** exvr                                                                    **
# ** MIT License                                                                **
# ** Copyright (c) [2024] [Florian Lance]                                       **
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

# include(../toolset/cpp-projects/ts-dependencies.pri)
include($$TOOLSET_REPOSITORY_DIR"/cpp-projects/ts-dependencies.pri")

########################################################### EXVR-BASE
EXVR_BASE_DEP_INCLUDEPATH =\
    # base
    $$BASE_DEP_INCLUDEPATH\
    $$BASE_INCLUDES\

EXVR_BASE_DEP_LIBS =\
    # base
    $$BASE_DEP_LIBS\
    $$BASE_LIB\

EXVR_BASE_PRE_TARGETDEPS =\
    $$BASE_LIB_FILE\

########################################################### EXVR-EXPORT
EXVR_EXPORT_DEP_INCLUDEPATH =\
    # thirdparty
    $$PYTHON_INCLUDES \
    # local
    $$EXVR_BASE_DEP_INCLUDEPATH\
    $$EXVR_BASE_INCLUDES\

EXVR_EXPORT_DEP_LIBS =\
    # thirdparty
    $$PYTHON_LIBS \
    # local
    $$EXVR_BASE_DEP_LIBS\
    $$EXVR_BASE_LIB\

EXVR_EXPORT_PRE_TARGETDEPS =\
    $$EXVR_BASE_LIB_FILE\

########################################################### EXVR-EXPORT-APP
EXVR_EXPORT_APP_DEP_INCLUDEPATH =\
    $$EXVR_EXPORT_DEP_INCLUDEPATH\
    $$EXVR_EXPORT_INCLUDES\

EXVR_EXPORT_APP_DEP_LIBS =\
    $$EXVR_EXPORT_DEP_LIBS\
    $$EXVR_EXPORT_OBJ"\*.obj"\

EXVR_EXPORT_APP_PRE_TARGETDEPS =\
    $$EXVR_EXPORT_PRE_TARGETDEPS\

########################################################### EXVR-DESIGNER
EXVR_DESIGNER_DEP_INCLUDEPATH =\
    $$EXVR_BASE_DEP_INCLUDEPATH\
    $$EXVR_BASE_INCLUDES\
    $$QT_UTILITY_DEP_INCLUDEPATH\
    $$QT_UTILITY_INCLUDES\
    $$NODES_INCLUDES\

EXVR_DESIGNER_DEP_LIBS =\
    $$EXVR_BASE_DEP_LIBS\
    $$EXVR_BASE_LIB\
    $$QT_UTILITY_DEP_LIBS\
    $$QT_UTILITY_LIB\
    $$NODES_LIB\

EXVR_DESIGNER_PRE_TARGETDEPS =\
    $$EXVR_BASE_PRE_TARGETDEPS\
    $$EXVR_BASE_LIB_FILE\
    $$QT_UTILITY_PRE_TARGETDEPS\
    $$QT_UTILITY_LIB_FILE\
    $$NODES_LIB_FILE\

########################################################### EXVR-TEST
EXVR_TEST_DEP_INCLUDEPATH =\
    $$EXVR_DESIGNER_DEP_INCLUDEPATH\
    $$EXVR_DESIGNER_INCLUDES\

EXVR_TEST_DEP_LIBS =\
    $$EXVR_DESIGNER_DEP_LIBS\
    $$EXVR_DESIGNER_OBJ"/ExVR-designer_pch.obj" \
    $$EXVR_DESIGNER_OBJ"/xml_io_manager.obj" \
    $$EXVR_DESIGNER_OBJ"/experiment.obj" \
    $$EXVR_DESIGNER_OBJ"/randomizer.obj" \
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

EXVR_TEST_PRE_TARGETDEPS =\
    $$EXVR_DESIGNER_PRE_TARGETDEPS\

# generate projects variables
for(project, EXVR_CPP_PROJECTS):{

    ## deps files
    TLOW = $$lower($$TARGET)
    equals(TLOW, $$project){

        UPT = $$upper($$project)
        UPT = $$replace(UPT, "-", "_")

        INCLUDEPATH     += $$eval($$UPT"_DEP_INCLUDEPATH")
        LIBS            += $$eval($$UPT"_DEP_LIBS")
        PRE_TARGETDEPS  += $$eval($$UPT"_PRE_TARGETDEPS")
    }
}



