

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "flow_routine_ndm.hpp"

using namespace tool::ex;

void StartRoutineNodeDataModel::compute(){
    set_valid_state();
    propagate_default_runtime({std::make_shared<StringData>(""),std::make_shared<StringData>(""), std::make_shared<IntData>(0), std::make_shared<IntData>(0)});
}

void StartRoutineNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    outPortsInfo[0].caption = QSL("routine (") % get_name(io.outTypes[0]) % QSL(")");
    outPortsInfo[1].caption = QSL("condition (") % get_name(io.outTypes[1]) % QSL(")");
    outPortsInfo[2].caption = QSL("routine iter (") % get_name(io.outTypes[2]) % QSL(")");
    outPortsInfo[3].caption = QSL("condition iter (") % get_name(io.outTypes[3]) % QSL(")");
    outPortsInfo[4].caption = QSL("exp time ms (") % get_name(io.outTypes[4]) % QSL(")");
}

void StopRoutineNodeDataModel::compute(){
    set_valid_state();
    propagate_default_runtime({std::make_shared<StringData>(""),std::make_shared<StringData>("")});
}

void StopRoutineNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    outPortsInfo[0].caption = QSL("routine (") % get_name(io.outTypes[0]) % QSL(")");
    outPortsInfo[1].caption = QSL("condition (") % get_name(io.outTypes[1]) % QSL(")");
}

void PreUpdateRoutineNodeDataModel::compute(){
    set_valid_state();
    propagate_default_runtime({std::make_shared<RealData>(0)});
}

void PreUpdateRoutineNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    outPortsInfo[0].caption = QSL("routine time ms (") % get_name(io.outTypes[0]) % QSL(")");
}

void UpdateRoutineNodeDataModel::compute(){
    set_valid_state();
    propagate_default_runtime({std::make_shared<RealData>(0)});
}

void UpdateRoutineNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    outPortsInfo[0].caption = QSL("routine time ms (") % get_name(io.outTypes[0]) % QSL(")");
}

void PostUpdateRoutineNodeDataModel::compute(){
    set_valid_state();
    propagate_default_runtime({std::make_shared<RealData>(0)});
}

void PostUpdateRoutineNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    outPortsInfo[0].caption = QSL("routine time ms (") % get_name(io.outTypes[0]) % QSL(")");
}


#include "moc_flow_routine_ndm.cpp"
