
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "conditional_gate_ndm.hpp"

using namespace tool::ex;

void ConditionalGateEmbeddedW::initialize() {

    // init widget
    w->init_widget("", true);

    // set widget connections
    connect(w.get(), &ExCheckBoxW::ui_change_signal, this, [=]{
        emit update_internal_data_signal({0}, {std::make_shared<BoolData>(w->w->isChecked())});
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Gate opened: "), w->w.get());
}

void ConditionalGateNodeDataModel::compute(){

    auto inputs = get_inputs();
    if(inputs[1]){
        lock_embedded_widget();
    }else{
        unlock_embedded_widget();
        inputs[1] = interData[0];
    }

    auto data2 = dcast<BoolData>(inputs[1]);
    if(!data2){
        invalidate_data();
        set_error_state(QSL("Invalid cast."));
        return;
    }

    const bool gate = data2->value();
    const QString text = gate ? QSL("Opened") : QSL("Closed");
    set_embedded_widget_text(text);

    if(check_infinity_loop(false)){
        return;
    }

    if(!inputs[0]){
        set_invalid_state(QSL("Missing entree #1."));
        invalidate_data();
        return;
    }

    // runtime inputs
    if(is_runtime(inputs[0])){
        set_valid_state();
        propagate_default_runtime({generate_default_runtime_any_data()});
        return;
    }

    // cast
    auto data1 = dcast<AnyData>(inputs[0]);
    if(!data1){
        invalidate_data();
        set_error_state(QSL("Invalid cast."));
        return;
    }

    // propagate
    if(gate){
        propagate_data(
            text,
            {
                data1
            } );
    }
}

QString ConditionalGateNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        if(i == 0){
            return QSL("in (") % c % QSL(")");
        }else {
            return QSL("state (") % c % QSL(")");
        }
    }else{
        return QSL("out (") % c % QSL(")");
    }
}

#include "moc_conditional_gate_ndm.cpp"

