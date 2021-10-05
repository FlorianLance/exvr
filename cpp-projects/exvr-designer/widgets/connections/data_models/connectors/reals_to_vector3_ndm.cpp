/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "reals_to_vector3_ndm.hpp"

using namespace tool::ex;

void RealsToVector3NodeDataModel::compute(){

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
        propagate_default_runtime({std::make_shared<Vector3Data>(geo::Vec3f{})});
        return;
    }

    // cast
    auto data1 = dcast<RealData>(inputs[0]);
    auto data2 = dcast<RealData>(inputs[1]);
    auto data3 = dcast<RealData>(inputs[2]);
    if(!data1 || !data2 || !data3){
        set_invalid_cast();
        return;
    }

    // propagate
    geo::Vec3f vec{
        scast<float>(data1->value()),
        scast<float>(data2->value()),
        scast<float>(data3->value())
    };

    propagate_data(
        str::Convertor::to_str(vec),
        {
            std::make_shared<Vector3Data>(std::move(vec))
        } );
}

void RealsToVector3NodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    inPortsInfo[0].caption = QSL("x (") % get_name(io.inTypes[0]) % QSL(")");
    inPortsInfo[1].caption = QSL("y (") % get_name(io.inTypes[1]) % QSL(")");
    inPortsInfo[2].caption = QSL("z (") % get_name(io.inTypes[2]) % QSL(")");
    outPortsInfo[0].caption = QSL("xyz (") % get_name(io.outTypes[0]) % QSL(")");
}

#include "moc_reals_to_vector3_ndm.cpp"
