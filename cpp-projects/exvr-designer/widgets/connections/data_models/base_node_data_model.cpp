
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "base_node_data_model.hpp"

// base
#include "utility/benchmark.hpp"

using namespace tool::ex;

QtNodes::NodeValidationState BaseNodeDataModel::validationState() const{
    return modelValidationState;
}

QString BaseNodeDataModel::validationMessage() const{
    return modelValidationMessage;
}

void BaseNodeDataModel::set_valid_state(){
    modelValidationState   = QtNodes::NodeValidationState::Valid;
    emit input_connection_validity_signal(true);
}

void BaseNodeDataModel::set_invalid_state(QString warning){
    modelValidationState   = QtNodes::NodeValidationState::Warning;
    modelValidationMessage = warning;
    emit input_connection_validity_signal(false);
}

void BaseNodeDataModel::set_error_state(QString error){
    modelValidationState   = QtNodes::NodeValidationState::Error;
    modelValidationMessage = error;
    emit input_connection_validity_signal(false);
}
