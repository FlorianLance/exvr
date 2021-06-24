
/*******************************************************************************
** exvr-export                                                                **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "python_component_export.hpp"


using namespace tool::ex;

PythonComponent *create_python_component(){
    return new PythonComponent();
}

void delete_python_component(PythonComponent *pyComponent){
    delete pyComponent;
}


