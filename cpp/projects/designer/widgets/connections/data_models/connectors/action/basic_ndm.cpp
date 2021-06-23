
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "basic_ndm.hpp"


using namespace tool::ex;

void NextNodeDataModel::compute(){
}

QString NextNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}

void PreviousNodeDataModel::compute(){
}

QString PreviousNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}

void StopNodeDataModel::compute(){
}

QString StopNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}

void PauseNodeDataModel::compute(){
}

QString PauseNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}

void NextWithNameEmbeddedW::initialize(){

    // init widget
    w->init_widget("default routine");

    // set widget connections
    w->init_connection("");
    connect(w.get(), &ExLineEditW::ui_change_signal, this, &NextWithNameEmbeddedW::compute_data_signal);

    // add widget to ui
    add_row_in_dialog("Element name: ", w->w.get());
}

void NextWithNameNodeDataModel::compute(){
    set_embedded_widget_text(embedded_w()->w->w->text());
}

QString NextWithNameNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}

void PreviousWithNameEmbeddedW::initialize(){

    // init widget
    w->init_widget("default routine");

    // set widget connections
    w->init_connection("");
    connect(w.get(), &ExLineEditW::ui_change_signal, this, &PreviousWithNameEmbeddedW::compute_data_signal);

    // add widget to ui
    add_row_in_dialog("Element name: ", w->w.get());
}

void PreviousWithNameNodeDataModel::compute(){
    set_embedded_widget_text(embedded_w()->w->w->text());
}

QString PreviousWithNameNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}

void NextWithCondEmbeddedW::initialize(){
    // init widget
    w->init_widget("default condition");

    // set widget connections
    w->init_connection("");
    connect(w.get(), &ExLineEditW::ui_change_signal, this, &NextWithCondEmbeddedW::compute_data_signal);

    // add widget to ui
    add_row_in_dialog("Condition name: ", w->w.get());
}

void NextWithCondNodeDataModel::compute(){
    set_embedded_widget_text(embedded_w()->w->w->text());
}

QString NextWithCondNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}

void PreviousWithCondEmbeddedW::initialize(){

    // init widget
    w->init_widget("default condition");

    // set widget connections
    w->init_connection("");
    connect(w.get(), &ExLineEditW::ui_change_signal, this, &PreviousWithCondEmbeddedW::compute_data_signal);

    // add widget to ui
    add_row_in_dialog("Condition name: ", w->w.get());
}

void PreviousWithCondNodeDataModel::compute(){
    set_embedded_widget_text(embedded_w()->w->w->text());
}

QString PreviousWithCondNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}


void ForceComponentConfigW::initialize(){

    // init widget
    w->init_widget();

    // set widget connections
    w->init_connection("");

    connect(w.get(), &ExConfigW::ui_change_signal,       this, &ForceComponentConfigW::compute_data_signal);
    connect(w.get(), &ExConfigW::update_from_components_signal, this, &ForceComponentConfigW::compute_data_signal);

    // add widget to ui
    add_row_in_dialog("", w->w.get());
}

void ForceComponentConfigNodeDataModel::compute(){
    set_embedded_widget_text(embedded_w()->w->display());
}

QString ForceComponentConfigNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{
    auto c = ConnectorNodeDataModel::portCaption(t,i);
    return QSL("in (") % c % QSL(")");
}



#include "moc_basic_ndm.cpp"
