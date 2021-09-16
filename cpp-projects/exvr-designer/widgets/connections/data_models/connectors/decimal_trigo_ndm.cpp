
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "decimal_trigo_ndm.hpp"

using namespace tool::ex;

void DecimalTrigoEmbeddedW::initialize(){

    // init widget
    w->init_widget({QSL("Cos"), QSL("Sin"), QSL("Tan"), QSL("Acos"),
                    QSL("Asin"), QSL("Atan"), QSL("Cosh"), QSL("Sinh"), QSL("Tanh")});

    // set widget connections
    connect(w.get(), &ExComboBoxTextW::ui_change_signal, this, [=]{
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Operator"), w->w.get());
}

void DecimalTrigoNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();

    if(!inputs[0]){
        set_invalid_state(QSL("Missing 1 entree."));
        invalidate_data();
        return;
    }

    // runtime inputs
    if(is_runtime(inputs[0]) ){
        set_valid_state();
        propagate_default_runtime({std::make_shared<DecimalData>()});
        return;
    }

    // cast
    auto data1 = dcast<DecimalData>(inputs[0]);
    if(!data1){
        set_invalid_cast();
        return;
    }

    // propagate
    const int index = embedded_w()->w->w->currentIndex();
    const auto v1 = data1->value();

    Decimal dec;
    if(index == 0){ // cos
        dec = Decimal::cos(v1);
    }else if(index == 1){ // sin
        dec = Decimal::sin(v1);
    }else if(index == 2){ // tan
        dec = Decimal::tan(v1);
    }else if(index == 3){ // acos
        dec = Decimal::acos(v1);
    }else if(index == 4){ // asin
        dec = Decimal::asin(v1);
    }else if(index == 5){ // atan
        dec = Decimal::atan(v1);
    }else if(index == 6){ // cosh
        dec = Decimal::cosh(v1);
    }else if(index == 7){ // sinh
        dec = Decimal::sinh(v1);
    }else if(index == 8){ // tanh
        dec = Decimal::tanh(v1);
    }

    propagate_data(
        str::Convertor::to_str(dec),
        {
            std::make_shared<DecimalData>(std::move(dec))
        } );
}

QString DecimalTrigoNodeDataModel::caption() const{
    return embedded_w()->w->w->currentText();
}

QString DecimalTrigoNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}

#include "moc_decimal_trigo_ndm.cpp"
