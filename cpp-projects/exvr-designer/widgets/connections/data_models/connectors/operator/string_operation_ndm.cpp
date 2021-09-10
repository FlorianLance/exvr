/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "string_operation_ndm.hpp"

using namespace tool::ex;

void StringOperationEmbeddedW::initialize(){

    // init widget
    w->init_widget({QSL("Add"), QSL("Remove"), QSL("Contains"), QSL("Do not contains"),
                    QSL("Equals"), QSL("Do not equals"), QSL("Starts with"), QSL("Ends with"), QSL("Splits with")});

    // set widget connections
    connect(w.get(), &ExComboBoxTextW::ui_change_signal, this, [=]{
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Operator: "), w->w.get());
}

void StringOperationNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();
    const int index = embedded_w()->w->w->currentIndex();

    if(check_if_missing_inputs(inputs)){
        return;
    }

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        set_valid_state();
        if(index < 2){
            propagate_default_runtime({std::make_shared<StringData>()});
        }else if(index < 8){
            propagate_default_runtime({std::make_shared<BoolData>()});
        }else{
            propagate_default_runtime({std::make_shared<StringListData>()});
        }
        return;
    }


    auto data1 = dcast<StringData>(inputs[0]);
    auto data2 = dcast<StringData>(inputs[1]);
    if(!data1 || !data2){
        set_invalid_cast();
        return;
    }

    auto v1 = data1->value();
    auto v2 = data2->value();

    std::variant<QString,bool,QStringList> output;
    QString txt;
    if(index == 0){ // Add
        output = v1 + v2;
        txt = std::get<QString>(output);
        if(txt.size() > 15){
            txt = txt.left(15) + "...";
        }
    }else if (index == 1){ // remove
        output = v1.remove(v2);
        txt = std::get<QString>(output);
        if(txt.size() > 15){
            txt = txt.left(15) + "...";
        }
    }else if (index == 2){ // contains
        output = v1.contains(v2);
        txt = str::Convertor::to_str(std::get<bool>(output));
    }else if (index == 3){ // do not contains
        output = !v1.contains(v2);
        txt = str::Convertor::to_str(std::get<bool>(output));
    }else if (index == 4){ // equals
        output = v1 == v2;
        txt = str::Convertor::to_str(std::get<bool>(output));
    }else if (index == 5){ // do not equals
        output = v1 != v2;
        txt = str::Convertor::to_str(std::get<bool>(output));
    }else if (index == 6){ // starts with
        output = v1.startsWith(v2);
        txt = str::Convertor::to_str(std::get<bool>(output));
    }else if (index == 7){ // ends with
        output = v1.endsWith(v2);
        txt = str::Convertor::to_str(std::get<bool>(output));
    }else if (index == 8){ // splits with
        output = v1.split(v2);
        txt = QSL("Size: ") % str::Convertor::to_str(std::get<QStringList>(output).size());
    }

    if(auto pval = std::get_if<QString>(&output)){
        propagate_data(txt,{std::make_shared<StringData>(*pval)} );
    }else if(auto pval = std::get_if<bool>(&output)){
        propagate_data(txt,{std::make_shared<BoolData>(*pval)} );
    }else if(auto pval = std::get_if<QStringList>(&output)){
        propagate_data(txt,{std::make_shared<StringListData>(*pval)} );
    }
}

QString StringOperationNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        if(i == 0){
            return QSL("A (") % c % QSL(")");
        }else if(i == 1){
            return QSL("B (") % c % QSL(")");
        }
    }

    if(embedded_w()->w->w->currentIndex() < 2){
        return QSL("out (") % from_view(ConnectionNode::get_name(ConnectionNode::Type::string_t)) % QSL(")");
    }else if(embedded_w()->w->w->currentIndex() < 8){
        return QSL("out (") % from_view(ConnectionNode::get_name(ConnectionNode::Type::boolean_t)) % QSL(")");
    }else{
        return QSL("out (") % from_view(ConnectionNode::get_name(ConnectionNode::Type::string_list_t)) % QSL(")");
    }
}

QString StringOperationNodeDataModel::caption() const{
    return embedded_w()->w->w->currentText();
}

QtNodes::NodeDataType StringOperationNodeDataModel::dataType(QtNodes::PortType t, QtNodes::PortIndex i) const{

    if(t == PortType::In){
        return ConnectorNodeDataModel::dataType(t,i);
    }

    if(embedded_w()->w->w->currentIndex() < 2){
        return StringData().type();
    }else if(embedded_w()->w->w->currentIndex() < 8){
        return BoolData().type();
    }else{
        return StringListData().type();
    }
}

unsigned int StringOperationNodeDataModel::nPorts(QtNodes::PortType t) const{
    if(t == PortType::In){
        return 2;
    }else{
        return 1;
    }
}

#include "moc_string_operation_ndm.cpp"
