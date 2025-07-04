
# /*******************************************************************************
# ** exvr                                                                       **
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

# TOOLSET_REPOSITORY_DIR = $$EXVR_REPOSITORY_DIR"/toolset"
TOOLSET_REPOSITORY_DIR = "D:/DEV/Perso/toolset"
# include(../toolset/cpp-projects/ts-projects.pri)
include($$TOOLSET_REPOSITORY_DIR"/cpp-projects/ts-projects.pri")

# projects list
EXVR_CPP_PROJECTS +=\    
    exvr-base \
    exvr-designer \
    exvr-test \
    exvr-export \
    exvr-export-app \

# sub dir
EXVR_CPP_PROJECTS_DIR       = $$EXVR_REPOSITORY_DIR"/cpp-projects"
EXVR_CPP_THIRDPARTY_DIR     = $$EXVR_CPP_PROJECTS_DIR"/_thirdparty"
EXVR_CPP_RESOURCES_DIR      = $$EXVR_CPP_PROJECTS_DIR"/_resources"

# generate projects variables
for(project, EXVR_CPP_PROJECTS):{

    generate_variables($$EXVR_CPP_PROJECTS_DIR, $$project)

    ##  build files
    TLOW = $$lower($$TARGET)
    equals(TLOW, $$project){

        UPT = $$upper($$project)
        UPT = $$replace(UPT, "-", "_")

        OBJECTS_DIR = $$eval($$UPT"_OBJ")
        DESTDIR     = $$eval($$UPT"_DEST")
        RCC_DIR     = $$eval($$UPT"_RCC")
        UI_DIR      = $$eval($$UPT"_UI")
        MOC_DIR     = $$eval($$UPT"_MOC")
        message("OBJ: "$$OBJECTS_DIR)
        message("DEST:"$$DESTDIR)
        message("RCC: "$$RCC_DIR)
        message("UI:  "$$UI_DIR)
        message("MOC: "$$MOC_DIR)
    }
}



