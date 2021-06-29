

TOOLBOX_REPOSITORY_DIR = $$EXVR_REPOSITORY_DIR"/toolbox"
include(../toolbox/cpp-projects/tb-projects.pri)

# lib
## exvr-components
#EXVR_COMPONENTS_TARGET   = "app" # debug
EXVR_COMPONENTS_TARGET   = "lib"

# dll
## exvr-export
#EXVR_EXPORT_TARGET       = "app" # debug
EXVR_EXPORT_TARGET       = "dll"

# app
## exvr-designer
EXVR_DESIGNER_TARGET    = "app"

# projects list
EXVR_CPP_PROJECTS +=\
    EXVR_COMPONENTS:exvr-components:exvr-componentsd \
    EXVR_EXPORT:exvr-export:exvr-exportd \
    EXVR_DESIGNER:exvr-designer:exvr-designerd \

# sub dir
EXVR_CPP_PROJECTS_DIR       = $$EXVR_REPOSITORY_DIR"/cpp-projects"
EXVR_CPP_BIN_DIR            = $$EXVR_CPP_PROJECTS_DIR"/_build/bin"
EXVR_CPP_TEMP_DIR           = $$EXVR_CPP_PROJECTS_DIR"/_build/temp"
EXVR_CPP_THIRDPARTY_DIR     = $$EXVR_CPP_PROJECTS_DIR"/_thirdparty"
EXVR_CPP_RESOURCES_DIR      = $$EXVR_CPP_PROJECTS_DIR"/_resources"

# compilation directories
EXVR_CPP_OBJ_DIR             = $$EXVR_CPP_TEMP_DIR"/obj"
EXVR_CPP_MOC_DIR             = $$EXVR_CPP_TEMP_DIR"/moc"
EXVR_CPP_RCC_DIR             = $$EXVR_CPP_TEMP_DIR"/rcc"
EXVR_CPP_UI_DIR              = $$EXVR_CPP_TEMP_DIR"/ui"

# define functions
defineTest(generate_exvr_variables) {

    # include
    eval($${1}_INCLUDES = $$EXVR_CPP_PROJECTS_DIR/$${2})
    eval(export($${1}_INCLUDES))

    # objects files
    eval($${1}_OBJ = $${EXVR_CPP_OBJ_DIR}/$${CFG}/$${2})
    eval(export($${1}_OBJ))

    # moc
    eval($${1}_MOC = $${EXVR_CPP_MOC_DIR}/$${CFG}/$${2})
    eval(export($${1}_MOC))

    # rcc
    eval($${1}_RCC = $${EXVR_CPP_RCC_DIR}/$${CFG}/$${2})
    eval(export($${1}_RCC))

    # ui generated files
    eval($${1}_UI = $${EXVR_CPP_UI_DIR}/$${CFG}/$${2})
    eval(export($${1}_UI))

    # destination
    eval($${1}_DEST = $${EXVR_CPP_BIN_DIR}/$${2})
    eval(export($${1}_DEST))

    # lib
    equals(CFG, "debug"){
        eval($${1}_LIB = "-L"$${EXVR_CPP_BIN_DIR}/$${2} "-l"$${3})
    }
    equals(CFG, "release"){
        eval($${1}_LIB = "-L"$${EXVR_CPP_BIN_DIR}/$${2} "-l"$${2})
    }
    eval(export($${1}_LIB))
}

for(project_dir, EXVR_CPP_PROJECTS):{
    generate_exvr_variables($$section(project_dir, :, 0, 0), $$section(project_dir, :, 1, 1), $$section(project_dir, :, 2, 2))
}

