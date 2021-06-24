
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

