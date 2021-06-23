
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

namespace tool::ex {

struct GUI{

    bool toggleActionsConnectionsSep = false;

    void reset(){
        toggleActionsConnectionsSep = false;
    }
};
}
