

include(../toolbox/cpp-projects/tb-thirdparty.pri)

########################################################### DIRECTORIES
############################# third-party headers only libraries
############################# third-party others
PYTHON_DIR                           = $$EXVR_CPP_THIRDPARTY_DIR"/Python37"


########################################################### INCLUDES

############################# PYTHON
PYTHON_INCLUDES =\
    $$PYTHON_DIR"/include"\


equals(COMPILER, "vs"){

########################################################### DEBUG LIBS
    equals(CFG, "debug"){

############################# PYTHON

    }

########################################################### RELEASE LIBS
    equals(CFG, "release"){

############################# PYTHON
        PYTHON_LIBS =\
            -L$$PYTHON_DIR"/libs" \
            -lpython37 \

    }
}
