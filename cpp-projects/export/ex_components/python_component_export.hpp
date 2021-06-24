
/*******************************************************************************
** exvr-export                                                                **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// components
#include "ex_components/python_component.hpp"

// local
#include "export_utility.hpp"

extern "C"{

    DECL_EXPORT tool::ex::PythonComponent* create_python_component();
    DECL_EXPORT void delete_python_component(tool::ex::PythonComponent *pyComponent);
}
