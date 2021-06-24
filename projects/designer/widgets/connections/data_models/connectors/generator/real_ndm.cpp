
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "real_ndm.hpp"

// base
#include "utility/benchmark.hpp"

using namespace tool::ex;

void RealEmbeddedW::initialize(){

    // init widget
    w->init_widget(min, value, max, step, 3);

    // set widget connections
    w->init_connection("");
    connect(w.get(), &ExDoubleSpinBoxW::ui_change_signal, this, [=]{
        emit update_internal_data_signal({0}, {std::make_shared<RealData>(w->w->value())});
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Value: "), w->w.get());

}

void RealNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        propagate_default_runtime({std::make_shared<RealData>()});
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
    auto data1 = dcast<RealData>(inputs[0]);
    if(!data1){
        set_invalid_cast();
        return;
    }

    // propagate
    double value = data1->value();
    propagate_data(
        str::Convertor::to_str(value),
        {
            std::make_shared<RealData>(std::move(value))
        } );
}

QString RealNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}

#include "moc_real_ndm.cpp"
