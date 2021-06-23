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

//    // runtime inputs
//    if(is_runtime(inputs[0]) || is_runtime(inputs[1])){
//        propagate_default_runtime({generate_default_runtime_any_data()});
//        set_valid_state();
//        return;
//    }

//    // cast
//    auto data1 = dcast<AnyData>(inputs[0]);
//    auto data2 = dcast<VoidData>(inputs[1]);
//    if(!data1 || !data2){
//        set_error_state(QSL("Invalid cast."));
//        return;
//    }

//    propagate_data(
//        "",
//        {
//            data1
//        } );
}

QString PassValueTriggerNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        if(i == 0){
            return QSL("in (") % c % QSL(")");
        }else{
            return QSL("pass (") % c % QSL(")");
        }
    }else{
        return QSL("out (") % c % QSL(")");
    }
}



#include "moc_pass_value_trigger_ndm.cpp"
