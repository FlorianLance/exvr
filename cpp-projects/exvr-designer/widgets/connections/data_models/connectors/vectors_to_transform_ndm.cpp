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

void VectorsToTransformNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);

    inPortsInfo[0].caption = QSL("trans (") % get_name(io.inTypes[0]) % QSL(")");
    inPortsInfo[1].caption = QSL("rot (") % get_name(io.inTypes[1]) % QSL(")");
    inPortsInfo[2].caption = QSL("scale (") % get_name(io.inTypes[2]) % QSL(")");

    for(size_t ii = 0; ii < io.outNb; ++ii){
        outPortsInfo[ii].caption = QSL("in (") % get_name(io.outTypes[ii]) % QSL(")");
    }
}

#include "moc_vectors_to_transform_ndm.cpp"
