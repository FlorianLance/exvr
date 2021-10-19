
/*******************************************************************************
** exvr-export                                                                **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "python_component_script_export.hpp"


using namespace tool::ex;

PythonScriptComponent *create_python_script_component(){
    return new PythonScriptComponent();
}

void delete_python_script_component(PythonScriptComponent *pyComponent){
    delete pyComponent;
}


