

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "delay_ndm.hpp"

using namespace tool::ex;

void DelayEmbeddedW::initialize(){

    // init widget
    w->init_widget(MinV<int>{0}, V<int>{500}, MaxV<int>{100000}, StepV<int>{1});

    // set widget connections
    w->init_connection("");
    connect(w.get(), &ExSpinBoxW::ui_change_signal, this, [=]{
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Delay: "), w->w.get());
}

void DelayNodeDataModel::compute(){

    set_embedded_widget_text(QString::number(embedded_w()->w->w->value()) % QSL(" ms"));

    if(check_infinity_loop(false)){
        return;
    }

    auto inputs = get_inputs();
    if(!inputs[0]){
        set_invalid_state(QSL("Missing 1 entree."));
        invalidate_data();
        return;
    }

    set_valid_state();
    propagate_default_runtime({generate_default_runtime_any_data()});
}


QString DelayNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }
    return QSL("out (") % c % QSL(")");
}


#include "moc_delay_ndm.cpp"
