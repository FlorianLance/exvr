/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "vector3_ndm.hpp"

using namespace tool::ex;

void Vector3EmbeddedW::initialize(){

    // init widget
    w->init_widget("");

    // set widget connections
    connect(w.get(), &ExVector3dW::ui_change_signal, this, [=]{
        const auto x = static_cast<float>(w->x.w->value());
        const auto y = static_cast<float>(w->y.w->value());
        const auto z = static_cast<float>(w->z.w->value());
        emit update_internal_data_signal({0}, {std::make_shared<Vector3Data>(geo::Pt3f{x,y,z})});
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("V: "), w->w.get());
}

void Vector3NodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        propagate_default_runtime({std::make_shared<Vector3Data>()});
        lock_embedded_widget();
        return;
    }

    // if no input data
    if(!inputs[0]){
        unlock_embedded_widget();
        inputs[0] = interData[0];
    }else{
        lock_embedded_widget();
    }

    // cast
    auto data1 = dcast<Vector3Data>(inputs[0]);
    if(!data1){
        set_invalid_cast();
        return;
    }


    // propagate
    geo::Pt3f value = data1->value();
    propagate_data(
        str::Convertor::to_str(value),
        {
            std::make_shared<Vector3Data>(std::move(value))
        } );
}

QString Vector3NodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}


#include "moc_vector3_ndm.cpp"
