

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "check_joypad_ndm.hpp"

using namespace tool::ex;

void CheckJoypadButtonEmbeddedW::initialize(){

    // init widget
    QStringList items;
    for(const auto &buttonName : input::Joypad::buttons.tuple_column<1>()){
        items << from_view(buttonName);
    }
    w->init_widget(items);

    // set widget connections
    connect(w.get(), &ExComboBoxTextW::ui_change_signal, this, [=]{
        auto button = input::Joypad::get_button(w->w->currentText().toStdString());
        if(button.has_value()){
            emit update_internal_data_signal({0}, {std::make_shared<IntData>(static_cast<int>(button.value()))});
            emit compute_data_signal();
        }
    });

    // add widget to ui
    add_row_in_dialog(QSL("Joypad button: "), w->w.get());
}

void CheckJoypadButtonNodeDataModel::compute(){

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
    auto data = dcast<JoypadButtonEventData>(inputs[0]);
    if(!data){
        set_invalid_cast();
        return;
    }


    auto interD = dcast<JoypadButtonEventData>(interData[0]);
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

QString CheckJoypadButtonNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

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

void CheckJoypadAxisEmbeddedW::initialize(){

    // init widget
    QStringList items;
    for(const auto &axisName : input::Joypad::axes.tuple_column<1>()){
        items << from_view(axisName);
    }
    w->init_widget(items);

    // set widget connections
    connect(w.get(), &ExComboBoxTextW::ui_change_signal, this, [=]{
        auto axis = input::Joypad::get_axis(w->w->currentText().toStdString());
        if(axis.has_value()){
            emit update_internal_data_signal({0}, {std::make_shared<IntData>(static_cast<int>(axis.value()))});
            emit compute_data_signal();
        }
    });

    // add widget to ui
    add_row_in_dialog(QSL("Joypad axis: "), w->w.get());
}

void CheckJoypadAxisNodeDataModel::compute(){

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
                std::make_shared<FloatData>(),
                std::make_shared<RealData>()
            });
        set_embedded_widget_text(embedded_w()->w->w->currentText());
        return;
    }

    // cast
    auto data = dcast<JoypadAxisEventData>(inputs[0]);
    if(!data){
        set_invalid_cast();
        return;
    }

    auto interD = dcast<JoypadAxisEventData>(interData[0]);
    if(data->value().code == interD->value().code){

        // propagate
        float value    = data->value().value;

        propagate_data(
            embedded_w()->w->w->currentText(),
            {
                std::make_shared<FloatData>(value),
                std::make_shared<RealData>(0)
            } );

    }else{
        set_embedded_widget_text(embedded_w()->w->w->currentText());
    }
}


QString CheckJoypadAxisNodeDataModel::portCaption(QtNodes::PortType t, QtNodes::PortIndex i) const{

    auto c = ConnectorNodeDataModel::portCaption(t,i);
    if(t == QtNodes::PortType::In){        
        return QSL("in (") % c % QSL(")");
    }else{
        if( i == 0){
            return QSL("[0-1] (") % c % QSL(")");
        }else{
            return QSL("trigger exp time ms (") % c % QSL(")");
        }
    }
}



#include "moc_check_joypad_ndm.cpp"
