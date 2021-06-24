
/*******************************************************************************
** exvr-export                                                                **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

#define DECL_EXPORT __declspec(dllexport)
//#ifdef OS_WINDOWS
//    #define DECL_EXPORT __declspec(dllexport)
//#else
//    #define DECL_EXPORT __attribute__((visibility("default")))
//#endif
