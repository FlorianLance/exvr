

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
EXVR_TEST_TARGET        = "app"

# projects list
EXVR_CPP_PROJECTS +=\
    EXVR_COMPONENTS:exvr-components:exvr-componentsd \
    EXVR_EXPORT:exvr-export:exvr-exportd \
    EXVR_DESIGNER:exvr-designer:exvr-designerd \
    EXVR_TEST:exvr-test:exvr-testd \

# sub dir
EXVR_CPP_PROJECTS_DIR       = $$EXVR_REPOSITORY_DIR"/cpp-projects"
EXVR_CPP_THIRDPARTY_DIR     = $$EXVR_CPP_PROJECTS_DIR"/_thirdparty"
EXVR_CPP_RESOURCES_DIR      = $$EXVR_CPP_PROJECTS_DIR"/_resources"

# generate projects variables
for(project_dir, EXVR_CPP_PROJECTS):{
    generate_variables($$EXVR_CPP_PROJECTS_DIR, $$section(project_dir, :, 0, 0), $$section(project_dir, :, 1, 1), $$section(project_dir, :, 2, 2))
}



