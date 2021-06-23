
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

QString DecimalCounterConfigNodeDataModel::portCaption(PortType t, PortIndex i ) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        switch (i) {
            case 0:
                return QSL("add (") % c % QSL(")");
            case 1:
                return QSL("sub (") % c % QSL(")");
            case 2:
                return QSL("reset (") % c % QSL(")");
        }
    }

    return QSL("count (") % c % QSL(")");
}


#include "moc_decimal_counter_ndm.cpp"
