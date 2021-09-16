/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "decimal_operation_ndm.hpp"

using namespace tool::ex;

void DecimalOperationEmbeddedW::initialize(){

    // init widget
    QStringList items = {QSL("  Add  "), QSL("Substract"), QSL("Multiply"), QSL("Divide"),
                         QSL("Modulo"), QSL("Inferior?"), QSL("Inferior or equal?"),
                         QSL("Superior?"), QSL("Superior or equal?"), QSL(" Equal? "), QSL("Not equal?")};
    w->init_widget(items);

    // set widget connections
    connect(w.get(), &ExComboBoxTextW::ui_change_signal, this, [=]{
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Operator: "), w->w.get());
}

void DecimalOperationNodeDataModel::compute(){

    const int index = embedded_w()->w->w->currentIndex();

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();
    if(!inputs[0] && !inputs[1]){
        set_invalid_state(QSL("Missing 2 entrees."));
        invalidate_data();
        return;
    }

    if(!inputs[0] || !inputs[1]){
        set_invalid_state(QSL("Missing 1 entrees."));
        invalidate_data();
        return;
    }

    // runtime inputs
    if(is_runtime(inputs[0]) || is_runtime(inputs[1])){
        set_valid_state();
        runtime_value_text();
        if(embedded_w()->w->w->currentIndex() < 5){
            propagate_default_runtime({std::make_shared<DecimalData>()});
        }else{
            propagate_default_runtime({std::make_shared<BoolData>()});
        }
        return;
    }

    // cast
    auto data1 = dcast<DecimalData>(inputs[0]);
    auto data2 = dcast<DecimalData>(inputs[1]);
    if(!data1 || !data2){
        invalidate_data();
        set_error_state(QSL("Invalid cast."));
        return;
    }

    auto v1 = data1->value();
    auto v2 = data1->value();

    std::variant<Decimal, bool> out;

    if(index == 0){ // Add
        out = Decimal::add(v1,v2);
    }else if(index == 1){ // Sub
        out = Decimal::sub(v1,v2);
    }else if(index == 2){ // Mult
        out = Decimal::mul(v1,v2);
    }else if(index == 3){ // Div
         if(almost_equal<double>(v2.to_double(), 0.)){
             invalidate_data();
            set_invalid_state(QSL("B is null"));
            return;
         }else{
            out = Decimal::div(v1,v2);
         }
    }else if(index == 4){ // mod
        if(almost_equal<double>(v2.to_double(), 0.)){
            invalidate_data();
            set_invalid_state(QSL("B is null"));
            return;
        }else{
            out = Decimal::mod(v1,v2);
        }
    }else if(index == 5){ // <
        out = Decimal::inferior(v1,v2);
    }else if(index == 6){ // <=
        out = Decimal::inferior_or_equal(v1,v2);
    }else if(index == 7){ // >
        out = Decimal::superior(v1,v2);
    }else if(index == 8){ // >=
        out = Decimal::superior_or_equal(v1,v2);
    }else if(index == 9){ // =
        out = Decimal::equal(v1,v2);
    }else{ // !=
        out = Decimal::no_equal(v1,v2);
    }

    if(auto pval = std::get_if<bool>(&out)){

        propagate_data(
            str::Convertor::to_str(*pval),
            {
                std::make_shared<BoolData>(std::move(*pval))
            } );

    }else if(auto pval = std::get_if<Decimal>(&out)){

        propagate_data(
            str::Convertor::to_str(*pval),
            {
                std::make_shared<DecimalData>(std::move(*pval))
            } );
    }
}

QString DecimalOperationNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        if(i == 0){
            return QSL("A (") % c % QSL(")");
        }else if(i == 1){
            return QSL("B (") % c % QSL(")");
        }
    }

    if(embedded_w()->w->w->currentIndex() < 5){
        return QSL("out (") % from_view(ConnectionNode::get_name(ConnectionNode::Type::decimal_t)) % QSL(")");
    }else{
        return QSL("out (") % from_view(ConnectionNode::get_name(ConnectionNode::Type::boolean_t)) % QSL(")");
    }
}

QString DecimalOperationNodeDataModel::caption() const{
    return embedded_w()->w->w->currentText();
}

QtNodes::NodeDataType DecimalOperationNodeDataModel::dataType(QtNodes::PortType t, QtNodes::PortIndex i) const{

    if(t == PortType::In){
        return ConnectorNodeDataModel::dataType(t,i);
    }

    return embedded_w()->w->w->currentIndex() < 5 ?
                DecimalData().type() :
                BoolData().type();
}


#include "moc_decimal_operation_ndm.cpp"
