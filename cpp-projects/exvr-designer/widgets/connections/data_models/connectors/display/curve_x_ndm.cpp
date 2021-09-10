

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "curve_x_ndm.hpp"

using namespace tool::ex;


void CurveXEmbeddedW::initialize(){

    // init widget
    w->init_widget(curveTitle);
    set_title(curveTitle);
    set_text_value(curveTitle);

    // set widget connections
    connect(w.get(), &ExCurveXW::ui_change_signal, this, &CurveXEmbeddedW::compute_data_signal);
    connect(w.get(), &ExCurveXW::name_changed_signal, this, [&](QString name){
        curveTitle = name;
        set_title(curveTitle);
        set_text_value(curveTitle);
    });

    // add widget to ui
    add_row_in_dialog("", w->w.get());    
}

bool CurveXEmbeddedW::update_with_info(QStringView value){
    w->w->curve.add_values(str::Convertor::to_double_list(value.toString()));
    return false;
}

void CurveXNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    set_embedded_widget_text(embedded_w()->curveTitle);
}

QString CurveXNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}


#include "moc_curve_x_ndm.cpp"
