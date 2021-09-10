
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "boolean_ndm.hpp"

using namespace tool::ex;

void BooleanEmbeddedW::initialize() {

    // init widget
    w->init_widget("", true);

    // set widget connections
    connect(w.get(), &ExCheckBoxW::ui_change_signal, this, [=]{
        emit update_internal_data_signal({0}, {std::make_shared<BoolData>(w->w->isChecked())});
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Value: "), w->w.get());
}

void BooleanNodeDataModel::setInData(std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port){

    if(port == 0){ // value
        inputData[0] = nodeData;
    }else{ // trigger
        inputData[1] = nodeData;
    }

    compute();
}

void BooleanNodeDataModel::inputConnectionCreated(const QtNodes::Connection &c){
    int id = c.getPortIndex(QtNodes::PortType::In);
    if(id == 0){
        lock_embedded_widget();
    }
}

void BooleanNodeDataModel::inputConnectionDeleted(const QtNodes::Connection &c){
    int id = c.getPortIndex(QtNodes::PortType::In);
    if(id == 0){
        unlock_embedded_widget();
    }
}

QString BooleanNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        if(i == 0){
            return QSL("in (") % c % QSL(")");
        }else{
            return QSL("toggle (") % c % QSL(")");
        }
    }else{
        return QSL("out (") % c % QSL(")");
    }
}

void BooleanNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        propagate_default_runtime({std::make_shared<BoolData>()});
        return;
    }

    // if no input data
    if(!inputs[0]){
        inputs[0] = interData[0];
    }

    // cast
    auto data1 = dcast<BoolData>(inputs[0]);
    if(!data1){
        set_invalid_cast();
        return;
    }

    // propagate
    bool value = data1->value();
    propagate_data(
        str::Convertor::to_str(value),
        {
            std::make_shared<BoolData>(std::move(value))
        } );
}


#include "moc_boolean_ndm.cpp"

