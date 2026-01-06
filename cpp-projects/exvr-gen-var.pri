
# /*******************************************************************************
# ** exvr                                                                       **
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

########################################################### FIND CURRENT PROJECT FROM LIST
PROJECT_FOUND="NULL"
for(project, EXVR_CPP_PROJECTS):{
    debug_project = $$project"d"
    TLOW = $$lower($$TARGET)

    equals(TLOW, $$project){
        PROJECT_FOUND = $$project
    }
    equals(TLOW, $$debug_project){
        PROJECT_FOUND = $$project
    }
}

########################################################### GENERATE PROJECTS VARIABLES

!equals(PROJECT_FOUND, "NULL"){
    UPT = $$upper($$PROJECT_FOUND)
    UPT = $$replace(UPT, "-", "_")

    INCLUDEPATH     += $$eval($$UPT"_DEP_INCLUDEPATH")
    LIBS            += $$eval($$UPT"_DEP_LIBS")
    PRE_TARGETDEPS  += $$eval($$UPT"_PRE_TARGETDEPS")

    OBJECTS_DIR = $$eval($$UPT"_OBJ")
    DESTDIR     = $$eval($$UPT"_DEST")
    RCC_DIR     = $$eval($$UPT"_RCC")
    UI_DIR      = $$eval($$UPT"_UI")
    MOC_DIR     = $$eval($$UPT"_MOC")

    message("=================== "$$PROJECT_FOUND" ===================")
    message("DEST:"$$DESTDIR)
    # message("OBJ: "$$OBJECTS_DIR)
    # message("RCC: "$$RCC_DIR)
    # message("UI:  "$$UI_DIR)
    # message("MOC: "$$MOC_DIR)
    # message("== OTHERS == ")
    # message("INCLUDES: "$$eval($$UPT"_INCLUDES"))
    # message("OBJ FILES: "$$eval($$UPT"_OBJ_FILES"))
    # message("LIB: "$$eval($$UPT"_LIB"))
    # message("LIB FILE: "$$eval($$UPT"_LIB_FILE"))
}

