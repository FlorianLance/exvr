

# lib
## exvr-components
#EXVR_COMPONENTS_T   = "app" # debug
EXVR_COMPONENTS_T   = "lib"

# dll
## exvr-export
#EXVR_EXPORT_T       = "app" # debug
EXVR_EXPORT_T       = "dll"

# app
## exvr-designer
EXVR_DESIGNER_T          = "app"

# projects list
TOOLBOX_CPP_PROJECTS +=\
    BASE:base \
    QT_UTILITY:qt-utility \
    NODES:nodes \

EXVR_CPP_PROJECTS +=\
    EXVR_COMPONENTS:exvr-components \
    EXVR_EXPORT:exvr-export \
    EXVR_DESIGNER:exvr-designer \
