

# lib
## components
#COMPONENTS_T        = "app" # debug
COMPONENTS_T        = "lib"

# dll
## export
#EXPORT_T            = "app" # debug
EXPORT_T            = "dll"

# app
## designer
DESIGNER_T          = "app"

# projects list
TOOLBOX_PROJECTS +=\
    BASE:base \
    QT_UTILITY:qt-utility \
    NODES:nodes \

EXVR_PROJECTS +=\
    COMPONENTS:components \
    EXPORT:export \
    DESIGNER:designer \
