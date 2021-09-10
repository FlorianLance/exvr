

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "keyboard_pw.hpp"

// base
#include "utility/keyboard_utility.hpp"

using namespace tool::ex;

struct KeyboardInitConfigParametersW::Impl{
    ExComboBoxTextW keys;
    ExLineEditW code;
    ExSpinBoxW value;
    ExLineEditW lastKeys;
};

KeyboardInitConfigParametersW::KeyboardInitConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void KeyboardInitConfigParametersW::insert_widgets(){

    QStringList keysList;
    for(const auto &buttonName : input::Keyboard::buttons.tuple_column<1>()){
        keysList << from_view(buttonName);
    }
    m_p->keys.w->addItems(keysList);

    auto l2 = ui::F::gen(ui::L::HB(), {ui::W::txt("Keyboard buttons names:"), m_p->keys()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto l3 = ui::F::gen(ui::L::HB(), {ui::W::txt("C# key code:"), m_p->code()}, LStretch{false}, LMargins{true}, QFrame::NoFrame);
    auto l4 = ui::F::gen(ui::L::HB(), {ui::W::txt("Value:"), m_p->value()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto l5 = ui::F::gen(ui::L::VB(), {ui::W::txt("Last buttons pressed:"), m_p->lastKeys()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    add_widget(ui::F::gen(ui::L::VB(), {l2,l3,l4,l5}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
}

void KeyboardInitConfigParametersW::init_and_register_widgets(){
    m_p->code.w->setReadOnly(true);
    m_p->value.w->setReadOnly(true);
    m_p->value.w->setMaximum(1000);
    m_p->lastKeys.w->setReadOnly(true);
}

void KeyboardInitConfigParametersW::create_connections(){
    connect(m_p->keys.w.get(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
        auto button = input::Keyboard::get_button(m_p->keys.w->currentText().toStdString());
        if(button.has_value()){
            m_p->value.w->setValue(static_cast<int>(button.value()));
        }
        m_p->code.w->setText(QSL("KeyCode.") % m_p->keys.w->currentText());
    });
}

void KeyboardInitConfigParametersW::late_update_ui(){
    emit m_p->keys.w->currentIndexChanged(0);
}

void KeyboardInitConfigParametersW::update_with_info(QStringView id, QStringView value){

    if(id == QSL("buttons_state_info")){

        QString keys;
        for(const auto &split : value.split(',')){
            auto buttonName = input::Keyboard::get_name(split.toInt());
            if(buttonName.has_value()){
                keys += from_view(buttonName.value()) % QSL(" ");
            }
        }
        m_p->lastKeys.w->setText(keys);
    }
}
