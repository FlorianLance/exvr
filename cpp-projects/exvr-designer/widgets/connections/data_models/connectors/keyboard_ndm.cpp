



/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "keyboard_ndm.hpp"

using namespace tool::ex;

void KeyboardButtonEmbeddedW::initialize(){

    // init widget
    QStringList items;
    for(const auto &keyName : input::Keyboard::buttons.tuple_column<1>()){
        items << from_view(keyName);
    }
    w->init_widget(items);

    // set widget connections
    connect(w.get(), &ExComboBoxTextW::ui_change_signal, this, [=]{
        auto button = input::Keyboard::get_button(w->w->currentText().toStdString());
        if(button.has_value()){
            auto v1 = std::make_shared<IntData>(static_cast<int>(button.value()));
            emit update_internal_data_signal({0}, {v1});
            emit compute_data_signal();
        }
    });

    // add widget to ui
    add_row_in_dialog(QSL("Keyboard button: "), w->w.get());
}

void CheckKeyboardButtonNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();

    // no inputs
    if(!has_inputs(inputs)){
        set_embedded_widget_text(embedded_w()->w->w->currentText());
        set_invalid_state(QSL("Missing 1 entree."));
        return;
    }

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        propagate_default_runtime(
            {
                std::make_shared<VoidData>(),
                std::make_shared<VoidData>(),
                std::make_shared<VoidData>(),
                std::make_shared<RealData>()
            });
        set_embedded_widget_text(embedded_w()->w->w->currentText());
        return;
    }

    // cast
    auto data = dcast<KeyboardButtonEventData>(inputs[0]);
    if(!data){
        set_invalid_cast();
        return;
    }

    auto interD = dcast<KeyboardButtonEventData>(interData[0]);
    if(data->value().code == interD->value().code){

        // propagate
        bool down    = data->value().firstFrameDown;
        bool up      = data->value().firstFrameUp;
        bool pressed = data->value().pressed;

        std::vector<size_t> indices;
        std::vector<std::shared_ptr<BaseNodeData>> outputs;
        if(down){
            indices.emplace_back(0);
            outputs.emplace_back(std::make_shared<VoidData>());
        }
        if(up){
            indices.emplace_back(1);
            outputs.emplace_back(std::make_shared<VoidData>());
        }
        if(pressed){
            indices.emplace_back(2);
            outputs.emplace_back(std::make_shared<VoidData>());
        }

        if(down || up || pressed){
            indices.emplace_back(3);
            outputs.emplace_back(std::make_shared<RealData>());
        }

        propagate_data(embedded_w()->w->w->currentText(), std::move(outputs), std::move(indices));
    }else{
        set_embedded_widget_text(embedded_w()->w->w->currentText());
    }
}

QString CheckKeyboardButtonNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == QtNodes::PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        if(i == 0){
            return QSL("down (") % c % QSL(")");
        }else if(i == 1){
            return QSL("up (") % c % QSL(")");
        }else if(i == 2){
            return QSL("pressed (") % c % QSL(")");
        }else{
            return QSL("trigger exp time ms (") % c % QSL(")");
        }
    }
}


void FilterKeyboardButtonNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();

    // no inputs
    if(!has_inputs(inputs)){
        set_embedded_widget_text(embedded_w()->w->w->currentText());
        set_invalid_state(QSL("Missing 1 entree."));
        return;
    }

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        propagate_default_runtime(
            {
                std::make_shared<KeyboardButtonEventData>()
            });
        set_embedded_widget_text(embedded_w()->w->w->currentText());
        return;
    }

    // cast
    auto data = dcast<KeyboardButtonEventData>(inputs[0]);
    if(!data){
        set_invalid_cast();
        return;
    }

    auto interD = dcast<KeyboardButtonEventData>(interData[0]);
    if(data->value().code == interD->value().code){
        // ...
    }else{
        set_embedded_widget_text(embedded_w()->w->w->currentText());
    }
}
QString FilterKeyboardButtonNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == QtNodes::PortType::In){
        return QSL("in (") % c % QSL(")");
    }else{
        return QSL("out (") % c % QSL(")");
    }
}

//#include "moc_keyboard_ndm.cpp"
