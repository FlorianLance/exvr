
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "vector3_to_reals_ndm.hpp"

using namespace tool::ex;

void Vector3ToRealsNodeDataModel::compute(){

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
                std::make_shared<RealData>(0.0),
                std::make_shared<RealData>(0.0),
                std::make_shared<RealData>(0.0)
            });
        return;
    }

    // cast
    auto data = dcast<Vector3Data>(inputs[0]);
    if(!data){
        set_invalid_cast();
        return;
    }

    // propagate
    geo::Vec3f vec = data->value();
    propagate_data(
        str::Convertor::to_str(vec),
        {
            std::make_shared<RealData>(vec.x()),
            std::make_shared<RealData>(vec.y()),
            std::make_shared<RealData>(vec.z())
        }
    );
}

QString Vector3ToRealsNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::Out){
        if(i == 0){
            return QSL("x (") % c % QSL(")");
        }else if(i == 1){
            return QSL("y (") % c % QSL(")");
        }else{
            return QSL("z (") % c % QSL(")");
        }
    }
    return QSL("xyz (") % c % QSL(")");
}

#include "moc_vector3_to_reals_ndm.cpp"
