

include(../toolbox/projects/thirdparty.pri)


########################################################### DIRECTORIES
############################# third-party headers only libraries
############################# third-party others
PYTHON_DIR                           = $$EXVR_THIRDPARTY_DIR"/Python37"
QWT_DIR                              = $$EXVR_THIRDPARTY_DIR"/qwt-6.1.4"

########################################################### INCLUDES

############################# PYTHON
PYTHON_INCLUDES =\
    $$PYTHON_DIR"/include"\

############################# QWT
QWT_INCLUDES = \
    $$QWT_DIR"/src"

equals(COMPILER, "vs"){

########################################################### DEBUG LIBS
    CONFIG(debug, debug|release){

############################# PYTHON

############################# QWT
        QWT_LIBS =\
            -L$$QWT_DIR"/lib/debug" \
            -lqwtd\
    }

########################################################### RELEASE LIBS
    CONFIG(release, debug|release){

############################# PYTHON
        PYTHON_LIBS =\
            -L$$PYTHON_DIR"/libs" \
            -lpython37 \

############################# QWT
        QWT_LIBS =\
            -L$$QWT_DIR"/lib/release" \
            -lqwt\
    }
}
