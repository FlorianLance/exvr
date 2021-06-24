

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "integer_ndm.hpp"

// qt-utility
#include "qt_logger.hpp"

using namespace tool::ex;

void IntegerEmbeddedW::initialize(){

    // init widget
    w->init_widget(MinV<int>{-100000000}, V<int>{10}, MaxV<int>{100000000}, StepV<int>{1});

    // set widget connections
    w->init_connection("");
    connect(w.get(), &ExSpinBoxW::ui_change_signal, this, [=]{
        emit update_internal_data_signal({0}, {std::make_shared<IntData>(w->w->value())});
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Value: "), w->w.get());
}

void IntegerNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        propagate_default_runtime({std::make_shared<IntData>()});
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
    auto data1 = dcast<IntData>(inputs[0]);
    if(!data1){
        set_invalid_cast();
        return;
    }

    // propagate
    int value = data1->value();
    propagate_data(
        str::Convertor::to_str(value),
        {
            std::make_shared<IntData>(std::move(value))
        } );
}

QString IntegerNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}

#include "moc_integer_ndm.cpp"
