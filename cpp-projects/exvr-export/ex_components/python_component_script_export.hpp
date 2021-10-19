
/*******************************************************************************
** exvr-export                                                                **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// components
#include "ex_components/python_script_component.hpp"

// local
#include "export_utility.hpp"

extern "C"{

    DECL_EXPORT tool::ex::PythonScriptComponent* create_python_script_component();
    DECL_EXPORT void delete_python_script_component(tool::ex::PythonScriptComponent *pyComponent);
}
