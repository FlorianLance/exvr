/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "pass_values_ndm.hpp"

using namespace tool::ex;


void PassValuesNodeDataModel::compute(){

    if(check_infinity_loop(false)){
        return;
    }

    auto inputs = get_inputs();
    if(!inputs[0] && !inputs[1] && !inputs[2] && !inputs[3]){
        set_invalid_state(QSL("Missing 1 entree."));
        invalidate_data();
        return;
    }

    set_valid_state();
    propagate_default_runtime({generate_default_runtime_any_data()});
}

void PassValuesNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    for(size_t ii = 0; ii < io.inNb; ++ii){
        inPortsInfo[ii].caption = QSL("in (") % get_name(io.inTypes[ii]) % QSL(")");
    }
    for(size_t ii = 0; ii < io.outNb; ++ii){
        outPortsInfo[ii].caption = QSL("out (") % get_name(io.outTypes[ii]) % QSL(")");
    }
}

#include "moc_pass_values_ndm.cpp"
