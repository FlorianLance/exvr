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

QString ConditionalTriggerNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}


#include "moc_conditional_trigger_ndm.cpp"
