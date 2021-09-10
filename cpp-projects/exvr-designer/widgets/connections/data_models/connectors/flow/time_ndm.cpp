/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "time_ndm.hpp"

using namespace tool::ex;

void TimeEmbeddedW::initialize(){

    // init widget
    w->init_widget();

    // set widget connections
    connect(w.get(), &ExTimeW::ui_change_signal, this, [=]{
        emit update_internal_data_signal({0}, {std::make_shared<IntData>(0)});
        emit compute_data_signal();
    });

    // add widget to ui
    add_row_in_dialog(QSL("Time settings: "), w->w.get(), false);
}


bool TimeEmbeddedW::set_text_value(QStringView value){

    //bool askForResize = m_valueText.text().size() != value.size();
    m_valueText.blockSignals(true);
    m_valueText.setText(value.toString() % QSL("ms"));
    m_valueText.blockSignals(false);
    //return askForResize;
    return false;
}


void TimeNodeDataModel::compute(){

    set_valid_state();
    propagate_default_runtime({std::make_shared<RealData>(0)});
}

QString TimeNodeDataModel::caption() const{
    return embedded_w()->w->typeT.w->currentText() % QSL(" (") % QString::number(embedded_w()->w->frequency.w->value()) % QSL(")");
}

QString TimeNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("ms (") % c % QSL(")");
}


#include "moc_time_ndm.cpp"
