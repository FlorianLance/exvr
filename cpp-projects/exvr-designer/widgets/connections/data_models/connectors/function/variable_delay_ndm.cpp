
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "variable_delay_ndm.hpp"

using namespace tool::ex;


void VariableDelayFEmbeddedW::initialize(){

    // init widget
    set_title(QSL("Variable delay"));
    w->init_widget(QSL("Delay curve"), QSL("Time(s)"), QSL("Delay(ms)"), {0,10}, {0,1000});

    // set widget connections
    w->minX.w->setEnabled(false);
    connect(w.get(), &ExCurveW::ui_change_signal, this, &VariableDelayFEmbeddedW::compute_data_signal);

    // add widget to ui
    add_row_in_dialog("", w->w.get());
}


void VariableDelayNodeDataModel::compute(){

    unlock_embedded_widget();

    if(check_infinity_loop(false)){
        return;
    }

    auto inputs = get_inputs();
    if(!inputs[1]){
        set_invalid_state(QSL("Missing entree #2."));
        invalidate_data();
        return;
    }

    set_valid_state();
    propagate_default_runtime({generate_default_runtime_any_data()});
}


#include "moc_variable_delay_ndm.cpp"
