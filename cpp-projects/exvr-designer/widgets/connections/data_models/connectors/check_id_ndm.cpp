
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "check_id_ndm.hpp"

using namespace tool::ex;

void CheckIdEmbeddedW::initialize(){

    // init widget
    w->init_widget(MinV<int>{0},V<int>{0},MaxV<int>{1000}, StepV<int>{1});

    // set widget connections
    connect(w.get(), &ExSpinBoxW::ui_change_signal, this, [=]{
        emit update_internal_data_signal({0}, {std::make_shared<IntData>(w->w->value())});
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("If Id ==: "), w->w.get());
}

void CheckIdNodeDataModel::compute(){

    auto idData = std::dynamic_pointer_cast<IntData>(interData[0]);
    QString text =QSL("== ") % idData->value_as_text();
    set_embedded_widget_text(text);

    if(check_infinity_loop(false)){
        return;
    }

    auto inputs = get_inputs();
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
    auto data1 = dcast<IdAnyData>(inputs[0]);
    if(!data1){
        invalidate_data();
        set_error_state(QSL("Invalid cast."));
        return;
    }

    // propagate
    if(data1->value().id == idData->value()){
        propagate_data(
            text,
            {
                std::make_shared<AnyData>(data1->value().data)
            } );
    }else{
        invalidate_data();
    }
}

QString CheckIdNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}

#include "moc_check_id_ndm.cpp"
