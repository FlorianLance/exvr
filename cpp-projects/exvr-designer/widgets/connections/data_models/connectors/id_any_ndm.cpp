
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "id_any_ndm.hpp"

using namespace tool::ex;

void IdAnyEmbeddedW::initialize(){

    // init widget
    w->init_widget(MinV<int>{0},V<int>{0},MaxV<int>{1000}, StepV<int>{1});

    // set widget connections
    connect(w.get(), &ExSpinBoxW::ui_change_signal, this, [=]{
        emit update_internal_data_signal({0}, {std::make_shared<IntData>(w->w->value())});
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Id: "), w->w.get());
}

void IdAnyNodeDataModel::compute(){

    auto interV = std::dynamic_pointer_cast<IntData>(interData[0]);
    const int id = interV->value();
    const QString txt = interV->value_as_text();
    set_embedded_widget_text(txt);

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();    

    // no inputs
    if(!has_inputs(inputs)){
        set_embedded_widget_text(txt);
        set_invalid_state(QSL("Missing 1 entree."));
        return;
    }

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        propagate_default_runtime(
            {std::make_shared<IdAnyData>(IdAny{id, nullptr})}
        );
        set_embedded_widget_text(txt);
        return;
    }

    // cast
    auto data = dcast<AnyData>(inputs[0]);
    if(!data){
        set_invalid_cast();
        return;
    }

    // propagate
    propagate_data(
        txt,
        {
            std::make_shared<IdAnyData>(IdAny{id,data->value()})
        });
}

QString IdAnyNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}


#include "moc_id_any_ndm.cpp"
