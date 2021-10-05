/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "conditional_trigger_ndm.hpp"

using namespace tool::ex;

void ConditionalTriggerNodeDataModel::compute(){

    if(check_infinity_loop(false)){
        return;
    }

    auto inputs = get_inputs();

    // missing inputs
    if(!inputs[0]){
        set_invalid_state(QSL("Missing entree #1."));
        invalidate_data();
        return;
    }

    // runtime inputs
    if(is_runtime(inputs[0])){
        set_valid_state();
        propagate_default_runtime({std::make_shared<VoidData>()});
        return;
    }

    // cast
    auto data1 = dcast<BoolData>(inputs[0]);
    if(!data1){
        invalidate_data();
        set_error_state(QSL("Invalid cast."));
        return;
    }

    if(data1){
        propagate_data(
            "",
            {
                std::make_shared<VoidData>()
            } );
    }
}

void ConditionalTriggerNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    for(size_t ii = 0; ii < io.inNb; ++ii){
        inPortsInfo[ii].caption = QSL("in (") % get_name(io.inTypes[ii]) % QSL(")");
    }
    for(size_t ii = 0; ii < io.outNb; ++ii){
        outPortsInfo[ii].caption = QSL("out (") % get_name(io.outTypes[ii]) % QSL(")");
    }
}


#include "moc_conditional_trigger_ndm.cpp"
