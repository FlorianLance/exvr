
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

# debug/release
CFG = ""
CONFIG(debug, debug|release){
    CFG = "debug"
    $$TARGET = $$TARGET"-d"
}

CONFIG(release, debug|release){
    CFG = "release"
}

# CONFIG
CONFIG += warn_on

# OS
COMPILER = ""   # vs / gcc
OS = ""         # Windows / Linux
EXT_O = ""      # .obj / .o

win32:{
    OS = "Windows"
    COMPILER = "vs"
    EXT_O = ".obj"
}

unix:!macx{
    OS = "Linux"
    COMPILER = "gcc"
    EXT_O = ".o"
}

# ARCH
equals(COMPILER, "gcc"){ # GCC (TODO)
    # FLAGS
    QMAKE_CXXFLAGS += -fopenmp -O3
    QMAKE_LFLAGS   += -fopenmp
}
equals(COMPILER, "vs"){ # Visual studio
    # set FLAGS
    ## optimizations
    QMAKE_CXXFLAGS += /O2 # maximize speed
    ## warnings
    QMAKE_CXXFLAGS_WARN_ON += -W3
    QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-function
    ## cpp version
    QMAKE_CXXFLAGS += /std:c++latest

    ## misc
    QMAKE_CXXFLAGS += /openmp # enables #pragma omp in source code.
    QMAKE_CXXFLAGS += -MP
#    QMAKE_CXXFLAGS += /LTCG
}

