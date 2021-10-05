
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "decimal_counter_ndm.hpp"

using namespace tool::ex;


void DecimalCounterConfigNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();
    if(!inputs[0] && !inputs[1]){
        set_invalid_state(QSL("Missing 1 entree."));
        unknow_value_text();
        invalidate_data();
        return;
    }

    set_valid_state();
    runtime_value_text();
    propagate_default_runtime({std::make_shared<DecimalData>(Decimal(0))});
}

void DecimalCounterConfigNodeDataModel::init_ports_caption(){

    const auto io = Connector::get_io(m_type);
    inPortsInfo[0].caption = QSL("add (") % get_name(io.inTypes[0]) % QSL(")");
    inPortsInfo[1].caption = QSL("sub (") % get_name(io.inTypes[1]) % QSL(")");
    inPortsInfo[2].caption = QSL("reset (") % get_name(io.inTypes[2]) % QSL(")");

    outPortsInfo[0].caption = QSL("count (") % get_name(io.outTypes[0]) % QSL(")");
}


#include "moc_decimal_counter_ndm.cpp"
