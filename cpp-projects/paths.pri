

# repo
EXVR_REPOSITORY_DIR         = $$PWD"/.."
TOOLBOX_REPOSITORY_DIR      = $$EXVR_REPOSITORY_DIR"/toolbox"

# toolbox
## sub dir
TOOLBOX_CPP_PROJECTS_DIR    = $$TOOLBOX_REPOSITORY_DIR"/cpp-projects"
TOOLBOX_CPP_QMAKE_DIR       = $$TOOLBOX_CPP_PROJECTS_DIR"/_qmake"
TOOLBOX_CPP_BIN_DIR         = $$TOOLBOX_CPP_PROJECTS_DIR"/_bin"
TOOLBOX_CPP_TEMP_DIR        = $$TOOLBOX_CPP_PROJECTS_DIR"/_temp"
TOOLBOX_CPP_THIRDPARTY_DIR  = $$TOOLBOX_CPP_PROJECTS_DIR"/_thirdparty"
TOOLBOX_CPP_RESOURCES_DIR   = $$TOOLBOX_CPP_PROJECTS_DIR"/resources"
## compilation directories
TOOLBOX_CPP_OBJ_DIR         = $$TOOLBOX_CPP_TEMP_DIR"/obj"
TOOLBOX_CPP_MOC_DIR         = $$TOOLBOX_CPP_TEMP_DIR"/moc"
TOOLBOX_CPP_RCC_DIR         = $$TOOLBOX_CPP_TEMP_DIR"/rcc"
TOOLBOX_CPP_UI_DIR          = $$TOOLBOX_CPP_TEMP_DIR"/ui"

# exvr
## sub dir
EXVR_CPP_PROJECTS_DIR       = $$EXVR_REPOSITORY_DIR"/cpp-projects"
EXVR_CPP_QMAKE_DIR          = $$EXVR_CPP_PROJECTS_DIR"/_qmake"
EXVR_CPP_BIN_DIR            = $$EXVR_CPP_PROJECTS_DIR"/_bin"
EXVR_CPP_TEMP_DIR           = $$EXVR_CPP_PROJECTS_DIR"/_temp"
EXVR_CPP_THIRDPARTY_DIR     = $$EXVR_CPP_PROJECTS_DIR"/_thirdparty"
EXVR_CPP_RESOURCES_DIR      = $$EXVR_CPP_PROJECTS_DIR"/resources"
## compilation directories
EXVR_CPP_OBJ_DIR             = $$EXVR_CPP_TEMP_DIR"/obj"
EXVR_CPP_MOC_DIR             = $$EXVR_CPP_TEMP_DIR"/moc"
EXVR_CPP_RCC_DIR             = $$EXVR_CPP_TEMP_DIR"/rcc"
EXVR_CPP_UI_DIR              = $$EXVR_CPP_TEMP_DIR"/ui"


# define functions
defineTest(generate_toolbox_variables) {

    # include
    eval($${1}_INCLUDES = $$TOOLBOX_CPP_PROJECTS_DIR/$${2})
    eval(export($${1}_INCLUDES))

    # objects files
    eval($${1}_OBJ = $${TOOLBOX_CPP_OBJ_DIR}/$${CFG}/$${2})
    eval(export($${1}_OBJ))

    # moc
    eval($${1}_MOC = $${TOOLBOX_CPP_MOC_DIR}/$${CFG}/$${2})
    eval(export($${1}_MOC))

    # rcc
    eval($${1}_RCC = $${TOOLBOX_CPP_RCC_DIR}/$${CFG}/$${2})
    eval(export($${1}_RCC))

    # ui generated files
    eval($${1}_UI = $${TOOLBOX_CPP_UI_DIR}/$${CFG}/$${2})
    eval(export($${1}_UI))

    # destination
    eval($${1}_DEST = $${TOOLBOX_CPP_BIN_DIR}/$${CFG}/$${2})
    eval(export($${1}_DEST))

    # lib
    eval($${1}_LIB = "-L"$${TOOLBOX_CPP_BIN_DIR}/$${CFG}/$${2} "-l"$${2})
    eval(export($${1}_LIB))
}

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
    eval($${1}_DEST = $${EXVR_CPP_BIN_DIR}/$${CFG}/$${2})
    eval(export($${1}_DEST))

    # lib
    eval($${1}_LIB = "-L"$${EXVR_CPP_BIN_DIR}/$${CFG}/$${2} "-l"$${2})
    eval(export($${1}_LIB))
}


# generate projects directory variables
for(project_dir, TOOLBOX_CPP_PROJECTS):{
    generate_toolbox_variables($$section(project_dir, :, 0, 0), $$section(project_dir, :, 1, 1))
}

for(project_dir, EXVR_CPP_PROJECTS):{
    generate_exvr_variables($$section(project_dir, :, 0, 0), $$section(project_dir, :, 1, 1))
}

