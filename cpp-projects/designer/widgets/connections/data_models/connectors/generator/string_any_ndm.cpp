
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "string_any_ndm.hpp"

using namespace tool::ex;

void StringAnyEmbeddedW::initialize(){

    // init widget
    w->init_widget(QSL("default"));

    // set widget connections
    w->init_connection("");
    connect(w.get(), &ExLineEditW::ui_change_signal, this, [=]{
        emit update_internal_data_signal({0}, {std::make_shared<StringData>(w->w->text())});
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Str: "), w->w.get());
}

void StringAnyNodeDataModel::compute(){

    auto interV = std::dynamic_pointer_cast<StringData>(interData[0]);
    const QString str = interV->value();
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
        propagate_default_runtime({
            std::make_shared<StringAnyData>(StringAny{str, nullptr})}
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
            std::make_shared<StringAnyData>(StringAny{str,data->value()})
        });
}

QString StringAnyNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}


#include "moc_string_any_ndm.cpp"
