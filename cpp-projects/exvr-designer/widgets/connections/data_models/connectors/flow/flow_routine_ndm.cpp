

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "flow_routine_ndm.hpp"

using namespace tool::ex;

void StartRoutineNodeDataModel::compute(){
    set_valid_state();
    propagate_default_runtime({std::make_shared<StringData>(""),std::make_shared<StringData>("")});
}

QString StartRoutineNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(i == 0){
        return QSL("routine (") % c % QSL(")");
    }else if(i == 1){
        return QSL("condition (") % c % QSL(")");
    }else{
        return QSL("nb times called (") % c % QSL(")");
    }
}

void StopRoutineNodeDataModel::compute(){
    set_valid_state();
    propagate_default_runtime({std::make_shared<StringData>(""),std::make_shared<StringData>("")});
}

QString StopRoutineNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(i == 0){
        return QSL("routine (") % c % QSL(")");
    }else{
        return QSL("condition (") % c % QSL(")");
    }
}

void PreUpdateRoutineNodeDataModel::compute(){
    set_valid_state();
    propagate_default_runtime({std::make_shared<RealData>(0)});
}

QString PreUpdateRoutineNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("routine time ms (") % c % QSL(")");
}

void UpdateRoutineNodeDataModel::compute(){
    set_valid_state();
    propagate_default_runtime({std::make_shared<RealData>(0)});
}

QString UpdateRoutineNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("routine time ms (") % c % QSL(")");
}

void PostUpdateRoutineNodeDataModel::compute(){
    set_valid_state();
    propagate_default_runtime({std::make_shared<RealData>(0)});
}

QString PostUpdateRoutineNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("routine time ms (") % c % QSL(")");
}


#include "moc_flow_routine_ndm.cpp"
