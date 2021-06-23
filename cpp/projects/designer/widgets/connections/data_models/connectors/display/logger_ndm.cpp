
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "logger_ndm.hpp"

using namespace tool::ex;

void LoggerNodeDataModel::compute(){
}

QString LoggerNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}


#include "moc_logger_ndm.cpp"
