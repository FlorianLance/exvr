
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "logger_ndm.hpp"

using namespace tool::ex;

void LoggerNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    inPortsInfo[0].caption = QSL("in (") % get_name(io.inTypes[0]) % QSL(")");
}


