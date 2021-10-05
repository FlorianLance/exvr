



/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "keyboard_ndm.hpp"

// base
#include "utility/keyboard_utility.hpp"

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

void CheckKeyboardButtonNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    for(size_t ii = 0; ii < io.inNb; ++ii){
        inPortsInfo[ii].caption = QSL("in (") % get_name(io.inTypes[ii]) % QSL(")");
    }
    outPortsInfo[0].caption = QSL("down (") % get_name(io.outTypes[0]) % QSL(")");
    outPortsInfo[1].caption = QSL("up (") % get_name(io.outTypes[1]) % QSL(")");
    outPortsInfo[2].caption = QSL("pressed (") % get_name(io.outTypes[2]) % QSL(")");
    outPortsInfo[3].caption = QSL("trigger exp time ms (") % get_name(io.outTypes[3]) % QSL(")");
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


void FilterKeyboardButtonNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    for(size_t ii = 0; ii < io.inNb; ++ii){
        inPortsInfo[ii].caption = QSL("in (") % get_name(io.inTypes[ii]) % QSL(")");
    }
    for(size_t ii = 0; ii < io.outNb; ++ii){
        outPortsInfo[ii].caption = QSL("out (") % get_name(io.outTypes[ii]) % QSL(")");
    }
}


#include "moc_keyboard_ndm.cpp"
