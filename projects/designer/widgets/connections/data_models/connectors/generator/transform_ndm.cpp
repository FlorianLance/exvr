/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "transform_ndm.hpp"

using namespace tool::ex;

void TransformEmbeddedW::initialize(){

    // init widget
    w->init_widget(QSL("Default tr"));

    // set widget connections
    w->init_connection("");
    connect(w.get(), &ExTransformationW::ui_change_signal, this, [=]{

        emit update_internal_data_signal(
            {0},
            {
                std::make_shared<TransformData>(Transform{
                        geo::Pt3<float>(w->trX.w->value(),w->trY.w->value(),w->trZ.w->value()),
                        geo::Pt3<float>(w->rotX.w->value(),w->rotY.w->value(),w->rotZ.w->value()),
                        geo::Pt3<float>(w->scX.w->value(),w->scY.w->value(),w->scZ.w->value())
                    }
                )
            });

        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog("", w->w.get());
}

void TransformNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        propagate_default_runtime({std::make_shared<TransformData>()});
        lock_embedded_widget();
        return;
    }

    // if all inputs data
    if(inputs[0]){
        lock_embedded_widget();
    }else{
        unlock_embedded_widget();
    }

    if(!inputs[0]){
        inputs[0] = interData[0];
    }

    // cast
    auto data1 = dcast<TransformData>(inputs[0]);
    if(!data1){
        set_invalid_cast();
        return;
    }

    // propagate
    Transform transform = data1->value();
    propagate_data(
        str::Convertor::to_str(transform),
        {
            std::make_shared<TransformData>(std::move(transform))
        } );
}

QString TransformNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}


#include "moc_transform_ndm.cpp"
