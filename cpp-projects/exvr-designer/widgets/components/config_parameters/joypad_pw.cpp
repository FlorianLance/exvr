
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "joypad_pw.hpp"


using namespace tool::ex;


void JoypadInitConfigParametersW::insert_widgets(){

    std::vector<QString> axisNames;
    std::vector<ExLineEditW*> axes1Le;
    std::vector<ExLineEditW*> axes2Le;

    auto axes1 = input::Joypad::axes_from_player(1);
    auto axes2 = input::Joypad::axes_from_player(2);
    for(size_t ii = 0; ii < axes1.size(); ++ii){

        auto le1 = std::make_unique<ExLineEditW>();
        axes1Le.emplace_back(le1.get());
        le1->init_widget(QSL("J1 0"), false)->init_tooltip(QSL("Joypad axis code: <b>") %  QString::number(input::Joypad::get_code(axes1[ii])) % QSL("</b>"));
        axesP1[axes1[ii]] = std::move(le1);

        auto le2 = std::make_unique<ExLineEditW>();
        axes2Le.emplace_back(le2.get());
        le2->init_widget(QSL("J2 0"), false)->init_tooltip(QSL("Joypad axis code: <b>") %  QString::number(input::Joypad::get_code(axes2[ii])) % QSL("</b>"));
        axesP2[axes2[ii]] = std::move(le2);

        axisNames.emplace_back(from_view(input::Joypad::get_name(axes1[ii])).split("_")[0]);
    }

    std::vector<QString> buttonsNames;
    std::vector<ExColorFrameW*> buttons1Cf;
    std::vector<ExColorFrameW*> buttons2Cf;

    auto buttons1 = input::Joypad::buttons_from_player(1);
    auto buttons2 = input::Joypad::buttons_from_player(2);
    for(size_t ii = 0; ii < buttons1.size(); ++ii){

        auto cf1 = std::make_unique<ExColorFrameW>();
        buttons1Cf.emplace_back(cf1.get());
        cf1->init_widget(false, false)->init_tooltip(QSL("Joypad button code: <b>") %  QString::number(input::Joypad::get_code(buttons1[ii])) % QSL("</b>"));
        buttonsP1[buttons1[ii]] = std::move(cf1);

        auto cf2 = std::make_unique<ExColorFrameW>();
        buttons2Cf.emplace_back(cf2.get());
        cf2->init_widget(false, false)->init_tooltip(QSL("Joypad button code: <b>") %  QString::number(input::Joypad::get_code(buttons2[ii])) % QSL("</b>"));
        buttonsP2[buttons2[ii]] = std::move(cf2);

        buttonsNames.emplace_back(from_view(input::Joypad::get_name(buttons1[ii])).split("_")[0]);
    }


    // insert ui elements
    add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("<b>Controllers detected:</b>"),devicesLL()}, LStretch{true}, LMargins{true}, QFrame::Box));

    QFrame *allAxes = ui::F::gen(ui::L::VB(), {ui::W::txt("<b>Axes:</b>")}, LStretch{false}, LMargins{true}, QFrame::Box);
    for(size_t ii = 0; ii < axisNames.size(); ++ii){

        QFrame *f = ui::F::gen(ui::L::HB(), {
            ui::W::txt(axisNames[ii]), axes1Le[ii]->w.get(), axes2Le[ii]->w.get()},
            LStretch{false}, LMargins{false}, QFrame::NoFrame);

        auto *hbL = qobject_cast<QHBoxLayout*>(f->layout());
        if(hbL){
            hbL->insertStretch(1);
        }
        allAxes->layout()->addWidget(f);
    }
    qobject_cast<QVBoxLayout*>(allAxes->layout())->addStretch();
    add_widget(allAxes);

    QFrame *allButtons = ui::F::gen(ui::L::VB(), {ui::W::txt("<b>Buttons:</b>")}, LStretch{false}, LMargins{true}, QFrame::Box);
    for(size_t ii = 0; ii < buttonsNames.size(); ++ii){

        QFrame *f = ui::F::gen(ui::L::HB(), {
            ui::W::txt(buttonsNames[ii]), buttons1Cf[ii]->w.get(), buttons2Cf[ii]->w.get()},
            LStretch{false}, LMargins{false}, QFrame::NoFrame);

        auto *hbL = qobject_cast<QHBoxLayout*>(f->layout());
        if(hbL){
            hbL->insertStretch(1);
        }
        allButtons->layout()->addWidget(f);
    }
    add_widget(ui::F::gen(ui::L::HB(), {allAxes,allButtons}, LStretch{false}, LMargins{false}, QFrame::NoFrame));;
}

void JoypadInitConfigParametersW::init_and_register_widgets(){
    devicesLL.init_widget(false);
}

void JoypadInitConfigParametersW::update_with_info(QStringView id, QStringView value){

    if(id == QSL("axes_state_info")){

        for(auto &axisUI : axesP1){
            axisUI.second->w->setText("0.00");
        }
        for(auto &axisUI : axesP2){
            axisUI.second->w->setText("0.00");
        }

        for(auto split : value.split('%')){

            if(split.length() == 0){
                break;
            }

            const auto subSplit   = split.split(',');
            auto axis             = input::Joypad::get_axis(subSplit[0].toInt());
            const auto value      = subSplit[1].toString();

            if(axis.has_value()){
                if(input::Joypad::get_player(axis.value()) == 1){
                    axesP1[axis.value()]->w->setText(value);
                }else{
                    axesP2[axis.value()]->w->setText(value);
                }
            }
        }

    }else if(id == QSL("buttons_state_info")){

        std::vector<input::Joypad::Button> buttons;
        if(value.length() > 0){
            for(const auto &split : value.split(',')){
                auto button = input::Joypad::get_button(split.toInt());
                if(button.has_value()){
                    buttons.emplace_back(button.value());
                }
            }
        }

        for(auto &buttonUI : buttonsP1){
            buttonUI.second->update(false);
        }
        for(auto &buttonUI : buttonsP2){
            buttonUI.second->update(false);
        }

        for(const auto &button : buttons){

            if(input::Joypad::get_player(button) == 1){
                buttonsP1[button]->update(true);
            }else{
                buttonsP2[button]->update(true);
            }
        }

    }else if(id == QSL("joysticks_info")){
        devicesLL.w->clear();
        int id = 0;
        for(const auto &split : value.split('%')){
            if(split.length() == 0){
                break;
            }
            devicesLL.w->addItem(QSL("J") % QString::number(id++) % QSL(" ") % split);
        }
    }
}

void JoypadInitConfigParametersW::create_connections(){}

void JoypadInitConfigParametersW::late_update_ui(){}

void JoypadConfigParametersW::insert_widgets(){}

void JoypadConfigParametersW::init_and_register_widgets(){}

void JoypadConfigParametersW::create_connections(){}

void JoypadConfigParametersW::late_update_ui(){}
