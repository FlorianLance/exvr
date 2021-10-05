/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "transform_to_vectors_ndm.hpp"

using namespace tool::ex;

void TransformToVectorsNodeDataModel::compute(){

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
        propagate_default_runtime(
            {
                std::make_shared<Vector3Data>(geo::Vec3f{0,0,0}),
                std::make_shared<Vector3Data>(geo::Vec3f{0,0,0}),
                std::make_shared<Vector3Data>(geo::Vec3f{1,1,1})
            }
        );
        return;
    }

    // cast
    auto data = dcast<TransformData>(inputs[0]);
    if(!data){
        set_invalid_cast();
        return;
    }

    auto pos   = data->value().position;
    auto rot   = data->value().rotation;
    auto scale = data->value().scale;

    // propagate
    propagate_data(
        str::Convertor::to_str(data->value()),
        {
            std::make_shared<Vector3Data>(std::move(pos)),
            std::make_shared<Vector3Data>(std::move(rot)),
            std::make_shared<Vector3Data>(std::move(scale))
        } );
}

void TransformToVectorsNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);

    inPortsInfo[0].caption = QSL("in (") % get_name(io.inTypes[0]) % QSL(")");

    outPortsInfo[0].caption = QSL("trans (") % get_name(io.outTypes[0]) % QSL(")");
    outPortsInfo[1].caption = QSL("rot (") % get_name(io.outTypes[1]) % QSL(")");
    outPortsInfo[2].caption = QSL("scale (") % get_name(io.outTypes[2]) % QSL(")");
}


#include "moc_transform_to_vectors_ndm.cpp"
