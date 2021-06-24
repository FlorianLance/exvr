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

//    std_v1<size_t> indexes;
//    std_v1<std::shared_ptr<BaseNodeData>> outputs;
//    if(inputs[0]){
//        auto data = dcast<AnyData>(inputs[0]);
//        if(!data){
//            set_invalid_cast();
//            return;
//        }

//        indexes.emplace_back(0);
//        outputs.emplace_back(data);
//    }
//    if(inputs[1]){

//        auto data = dcast<AnyData>(inputs[1]);
//        if(!data){
//            set_invalid_cast();
//            return;
//        }

//        indexes.emplace_back(0);
//        outputs.emplace_back(data);
//    }
//    if(inputs[2]){

//        auto data = dcast<AnyData>(inputs[2]);
//        if(!data){
//            set_invalid_cast();
//            return;
//        }

//        indexes.emplace_back(0);
//        outputs.emplace_back(data);
//    }
//    if(inputs[3]){

//        auto data = dcast<AnyData>(inputs[3]);
//        if(!data){
//            set_invalid_cast();
//            return;
//        }

//        indexes.emplace_back(0);
//        outputs.emplace_back(data);
//    }

//    propagate_data(
//        "",
//        outputs,
//        indexes
//    );
}

QString PassValuesNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}



#include "moc_pass_values_ndm.cpp"
