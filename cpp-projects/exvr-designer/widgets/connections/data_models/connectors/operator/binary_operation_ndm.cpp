/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "binary_operation_ndm.hpp"

using namespace tool::ex;

void BinaryOperationEmbeddedW::initialize(){

    // init widget
    w->init_widget({QSL("AND"), QSL("OR"), QSL("XOR"), QSL("NOT")});

    // set widget connections
    connect(w.get(), &ExComboBoxTextW::ui_change_signal, this, [=]{
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Operator: "), w->w.get());
}

void BinaryOperationNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();
    const int index = embedded_w()->w->w->currentIndex();

    // missing inputs
    if(index != 3){
        if(check_if_missing_inputs(inputs)){
            return;
        }
    }else{
        if(!inputs[0]){
            set_invalid_state(QSL("Missing entree #1."));
            invalidate_data();
            return;
        }
    }

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        set_valid_state();
        propagate_default_runtime({std::make_shared<BoolData>()});
        return;
    }

    // cast
    bool v1, v2;
    auto data1 = dcast<BoolData>(inputs[0]);
    auto data2 = dcast<BoolData>(inputs[1]);
    if(index != 3){
        if(!data1 || !data2){
            set_invalid_cast();
            return;
        }
        v1 = data1->value();
        v2 = data2->value();
    }else{
        if(!data1){
            set_invalid_cast();
            return;
        }
        v1 = data1->value();
    }

    // propagate
    bool state = false;
    if(index == 0){ // AND
        state = v1 && v2;
    }else if(index == 1){ // OR
        state = v1 || v2;
    }else if(index == 2){ // XOR
        state = v1 != v2;
    }else if(index == 3){ // NOT
        state = !v1;
    }

    propagate_data(
        str::Convertor::to_str(state),
        {
            std::make_shared<BoolData>(state)
        } );
}

QString BinaryOperationNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        if(i == 0){
            return QSL("A (") % c % QSL(")");
        }else if(i == 1){            
            if(embedded_w()->w->w->currentIndex() == 3){
                return QSL("-");
            }else{
                return QSL("B (") % c % QSL(")");
            }
        }
    }
    return QSL("out (") % c % QSL(")");
}

QString BinaryOperationNodeDataModel::caption() const{
    return embedded_w()->w->w->currentText();
}

#include "moc_binary_operation_ndm.cpp"
