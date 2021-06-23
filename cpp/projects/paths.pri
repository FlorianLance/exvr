

# repo
TOOLBOX_REPOSITORY_DIR      = $$PWD"/../../toolbox"
EXVR_REPOSITORY_DIR         = $$PWD"/../.."

# toolbox
## cpp
TOOLBOX_CPP_DIR             = $$TOOLBOX_REPOSITORY_DIR"/cpp"
## sub dir
TOOLBOX_PROJECTS_DIR        = $$TOOLBOX_CPP_DIR"/projects"
TOOLBOX_QMAKE_DIR           = $$TOOLBOX_CPP_DIR"/qmake"
TOOLBOX_BIN_DIR             = $$TOOLBOX_CPP_DIR"/bin"
TOOLBOX_TEMP_DIR            = $$TOOLBOX_CPP_DIR"/temp"
TOOLBOX_THIRDPARTY_DIR      = $$TOOLBOX_CPP_DIR"/thirdparty"
TOOLBOX_RESOURCES_DIR       = $$TOOLBOX_PROJECTS_DIR"/resources"
## compilation directories
TOOLBOX_OBJ_DIR             = $$TOOLBOX_TEMP_DIR"/obj"
TOOLBOX_MOC_DIR             = $$TOOLBOX_TEMP_DIR"/moc"
TOOLBOX_RCC_DIR             = $$TOOLBOX_TEMP_DIR"/rcc"
TOOLBOX_UI_DIR              = $$TOOLBOX_TEMP_DIR"/ui"

# exvr
## cpp
EXVR_CPP_DIR             = $$EXVR_REPOSITORY_DIR"/cpp"
## sub dir
EXVR_PROJECTS_DIR        = $$EXVR_CPP_DIR"/projects"
EXVR_QMAKE_DIR           = $$EXVR_CPP_DIR"/qmake"
EXVR_BIN_DIR             = $$EXVR_CPP_DIR"/bin"
EXVR_TEMP_DIR            = $$EXVR_CPP_DIR"/temp"
EXVR_THIRDPARTY_DIR      = $$EXVR_CPP_DIR"/thirdparty"
EXVR_RESOURCES_DIR       = $$EXVR_PROJECTS_DIR"/resources"
## compilation directories
EXVR_OBJ_DIR             = $$EXVR_TEMP_DIR"/obj"
EXVR_MOC_DIR             = $$EXVR_TEMP_DIR"/moc"
EXVR_RCC_DIR             = $$EXVR_TEMP_DIR"/rcc"
EXVR_UI_DIR              = $$EXVR_TEMP_DIR"/ui"


# define functions
defineTest(generate_toolbox_variables) {

    # include
    eval($${1}_INCLUDES = $$TOOLBOX_PROJECTS_DIR/$${2})
    eval(export($${1}_INCLUDES))

    # objects files
    eval($${1}_OBJ = $${TOOLBOX_OBJ_DIR}/$${CFG}/$${2})
    eval(export($${1}_OBJ))

    # moc
    eval($${1}_MOC = $${TOOLBOX_MOC_DIR}/$${CFG}/$${2})
    eval(export($${1}_MOC))

    # rcc
    eval($${1}_RCC = $${TOOLBOX_RCC_DIR}/$${CFG}/$${2})
    eval(export($${1}_RCC))

    # ui generated files
    eval($${1}_UI = $${TOOLBOX_UI_DIR}/$${CFG}/$${2})
    eval(export($${1}_UI))

    # destination
    eval($${1}_DEST = $${TOOLBOX_BIN_DIR}/$${CFG}/$${2})
    eval(export($${1}_DEST))

    # lib
    eval($${1}_LIB = "-L"$${TOOLBOX_BIN_DIR}/$${CFG}/$${2} "-l"$${2})
    eval(export($${1}_LIB))
}

defineTest(generate_exvr_variables) {

    # include
    eval($${1}_INCLUDES = $$EXVR_PROJECTS_DIR/$${2})
    eval(export($${1}_INCLUDES))

    # objects files
    eval($${1}_OBJ = $${EXVR_OBJ_DIR}/$${CFG}/$${2})
    eval(export($${1}_OBJ))

    # moc
    eval($${1}_MOC = $${EXVR_MOC_DIR}/$${CFG}/$${2})
    eval(export($${1}_MOC))

    # rcc
    eval($${1}_RCC = $${EXVR_RCC_DIR}/$${CFG}/$${2})
    eval(export($${1}_RCC))

    # ui generated files
    eval($${1}_UI = $${EXVR_UI_DIR}/$${CFG}/$${2})
    eval(export($${1}_UI))

    # destination
    eval($${1}_DEST = $${EXVR_BIN_DIR}/$${CFG}/$${2})
    eval(export($${1}_DEST))

    # lib
    eval($${1}_LIB = "-L"$${EXVR_BIN_DIR}/$${CFG}/$${2} "-l"$${2})
    eval(export($${1}_LIB))
}


# generate projects directory variables
for(project_dir, TOOLBOX_PROJECTS):{
    generate_toolbox_variables($$section(project_dir, :, 0, 0), $$section(project_dir, :, 1, 1))
}

for(project_dir, EXVR_PROJECTS):{
    generate_exvr_variables($$section(project_dir, :, 0, 0), $$section(project_dir, :, 1, 1))
}

