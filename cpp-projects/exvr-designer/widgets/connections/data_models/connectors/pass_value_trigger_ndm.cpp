/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "pass_value_trigger_ndm.hpp"

using namespace tool::ex;

void PassValueTriggerNodeDataModel::compute(){

    if(check_infinity_loop(false)){
        return;
    }

    auto inputs = get_inputs();
    if(!inputs[0] && !inputs[1]){
        set_invalid_state(QSL("Missing 2 entrees."));
        invalidate_data();
        return;
    }

    if(!inputs[0] || !inputs[1]){
        set_invalid_state(QSL("Missing 1 entrees."));
        invalidate_data();
        return;
    }

    propagate_default_runtime({generate_default_runtime_any_data()});
    set_valid_state();
}

void PassValueTriggerNodeDataModel::init_ports_caption(){

    const auto io = Connector::get_io(m_type);
    inPortsInfo[0].caption = QSL("in (") % get_name(io.inTypes[0]) % QSL(")");
    inPortsInfo[1].caption = QSL("pass (") % get_name(io.inTypes[1]) % QSL(")");
    outPortsInfo[0].caption = QSL("out (") % get_name(io.outTypes[0]) % QSL(")");
}

#include "moc_pass_value_trigger_ndm.cpp"
