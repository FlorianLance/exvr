/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "vector2_to_reals_ndm.hpp"

using namespace tool::ex;

void Vector2ToRealsNodeDataModel::compute(){

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
            std::make_shared<RealData>(0.),
            std::make_shared<RealData>(0.)
        });
        return;
    }

    // cast
    auto data = dcast<Vector2Data>(inputs[0]);
    if(!data){
        set_invalid_cast();
        return;
    }

    // propagate
    geo::Vec2f vec = data->value();

    propagate_data(
    str::Convertor::to_str(vec),
    {
        std::make_shared<RealData>(vec.x()),
        std::make_shared<RealData>(vec.y())
    });
}

void Vector2ToRealsNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);

    inPortsInfo[0].caption = QSL("xy (") % get_name(io.inTypes[0]) % QSL(")");

    outPortsInfo[0].caption = QSL("x (") % get_name(io.outTypes[0]) % QSL(")");
    outPortsInfo[1].caption = QSL("y (") % get_name(io.outTypes[1]) % QSL(")");
}


#include "moc_vector2_to_reals_ndm.cpp"
