/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "vectors_to_transform_ndm.hpp"

using namespace tool::ex;

void VectorsToTransformNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();

    // missing inputs
    if(check_if_missing_inputs(inputs)){
        return;
    }

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        propagate_default_runtime({std::make_shared<TransformData>(Transform{})});
        return;
    }

    // cast
    auto data1 = dcast<Vector3Data>(inputs[0]);
    auto data2 = dcast<Vector3Data>(inputs[1]);
    auto data3 = dcast<Vector3Data>(inputs[2]);
    if(!data1 || !data2 || !data3){
        set_invalid_cast();
        return;
    }

    // propagate
    Transform tr ={
        data1->value(),
        data2->value(),
        data3->value()
    };

    propagate_data(
        str::Convertor::to_str(tr),
        {
            std::make_shared<TransformData>(
                tr
            )
        } );
}

QString VectorsToTransformNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        if(i == 0){
            return QSL("trans (") % c % QSL(")");
        }else if(i == 1){
            return QSL("rot (") % c % QSL(")");
        }else{
            return QSL("scale (") % c % QSL(")");
        }
    }
    return QSL("out (") % c % QSL(")");
}

#include "moc_vectors_to_transform_ndm.cpp"
