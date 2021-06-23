
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "global_signals.hpp"

using namespace tool::ex;

void GSignals::init(){
    if(m_signals == nullptr){
        m_signals = std::make_unique<GSignals>();
    }
}

GSignals *GSignals::get(){
    if(m_signals != nullptr){
        return m_signals.get();
    }
    return nullptr;
}
