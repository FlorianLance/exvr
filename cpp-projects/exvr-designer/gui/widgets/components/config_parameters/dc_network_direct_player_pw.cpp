
/***********************************************************************************
** exvr-designer                                                                  **
** MIT License                                                                    **
** Copyright (c) [2024] [Florian Lance]                                           **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

#include "dc_network_direct_player_pw.hpp"

// qt-utility
#include "gui/ex_widgets/ex_radio_button_w.hpp"
#include "gui/ex_widgets/ex_checkbox_w.hpp"
#include "gui/ex_widgets/ex_line_edit_w.hpp"
#include "gui/ex_widgets/ex_label_w.hpp"
#include "gui/ex_widgets/ex_spin_box_w.hpp"

// local
#include "gui/ex_widgets/ex_resource_w.hpp"

using namespace tool::ex;

struct DCNetworkDirectPlayerInitConfigParametersW::Impl{

    ExResourceW networkS{"network_settings"};
    ExResourceW deviceS{"device_settings"};
    ExResourceW colorS{"color_settings"};
    ExResourceW filtersS{"filters_settings"};
    ExResourceW modelsS{"models_settings"};

    ExLineEditW devicesToUse{"devices_to_use"};
    ExCheckBoxW debugBypassDevice{"debug_bypass"};
    ExLabelW infos{"infos"};

    QString configInfos =
        "Nb connections: -\n"
        "Network settings file loaded: -\n"
        "Device settings file loaded: -\n"
        "Filters settings file loaded: -\n"
        "Color settings file loaded: -\n"
        "Models settings file loaded: -";
    QStringList grabbersInfos = {};
};

DCNetworkDirectPlayerInitConfigParametersW::DCNetworkDirectPlayerInitConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

auto DCNetworkDirectPlayerInitConfigParametersW::insert_widgets() -> void{
    
    add_widget(ui::F::old_gen(ui::L::VB(),
        {m_p->networkS(), m_p->deviceS(), m_p->colorS(),m_p->filtersS(),m_p->modelsS()}, LStretch{false}, LMargins{true}, QFrame::Box)
    );
    
    add_widget(ui::F::old_gen(ui::L::HB(), {ui::W::txt("Grabbers id to use (ex:\"0;1;2\"):"), m_p->devicesToUse()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
    add_widget(m_p->debugBypassDevice());
    add_widget(ui::F::old_gen(ui::L::VB(), {ui::W::txt("Infos:"), m_p->infos()}, LStretch{false}, LMargins{true}, QFrame::Box));
}

auto DCNetworkDirectPlayerInitConfigParametersW::init_and_register_widgets() -> void{

    add_input_ui(m_p->networkS.init_widget(Resource::Type::Text, "Network settings file: "));
    add_input_ui(m_p->deviceS.init_widget(Resource::Type::Text, "Device settings file: "));
    add_input_ui(m_p->colorS.init_widget(Resource::Type::Text, "Color settings file: "));
    add_input_ui(m_p->filtersS.init_widget(Resource::Type::Text, "Filters settings file: "));
    add_input_ui(m_p->modelsS.init_widget(Resource::Type::Text, "Models settings file: "));
    add_input_ui(m_p->devicesToUse.init_widget("0;1;2;3"));
}

auto DCNetworkDirectPlayerInitConfigParametersW::update_with_info(QStringView id, QStringView value) -> void{
    if(id == QSL("config_infos")){
        auto split = value.split('%');
        if(split.size() >= 5){

            m_p->configInfos =  QString("Nb connections: [%1]\n"
                "Network settings file loaded: [%2]\n"
                "Device settings file loaded: [%3]\n"
                "Filters settings file loaded: [%4]\n"
                "Color settings file loaded: [%5]\n"
                "Models settings file loaded: [%6]").arg(
                split[0],
                split[1] == '1' ? "YES" : "NO",
                split[2] == '1' ? "YES" : "NO",
                split[3] == '1' ? "YES" : "NO",
                split[4] == '1' ? "YES" : "NO",
                split[5] == '1' ? "YES" : "NO"
            );
            m_p->infos.w->setText(m_p->configInfos % QSL("\n") % m_p->grabbersInfos.join("\n"));
        }
    }else if(id.contains(QSL("grabber_infos_"))){
        auto splitId = id.split('_');
        if(splitId.size() == 4){
            auto id    = splitId[2].toInt();
            auto count = splitId[3].toInt();
            auto connectedState = value == QSL("1");

            while(m_p->grabbersInfos.size() < count){
                m_p->grabbersInfos.append("");
            }

            m_p->grabbersInfos[id] = connectedState ? QString("Grabber [%1] connected.").arg(id) :  QString("Grabber [%1] not connected.").arg(id);
            m_p->infos.w->setText(m_p->configInfos % QSL("\n") % m_p->grabbersInfos.join("\n"));
        }
    }
}

struct DCNetworkDirectPlayerConfigParametersW::Impl{
    ExSpinBoxW delay{"delay"};
    ExLabelW infos{"infos"};
    QStringList frameInfos = {};
};

DCNetworkDirectPlayerConfigParametersW::DCNetworkDirectPlayerConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

auto DCNetworkDirectPlayerConfigParametersW::insert_widgets() -> void {
    add_widget(ui::F::old_gen(ui::L::HB(), {ui::W::txt("Delay (ms):"), m_p->delay()}, LStretch{false}, LMargins{true}, QFrame::NoFrame));
    add_widget(ui::F::old_gen(ui::L::VB(), {ui::W::txt("Infos:"), m_p->infos()}, LStretch{false}, LMargins{true}, QFrame::Box));
}

auto DCNetworkDirectPlayerConfigParametersW::init_and_register_widgets() -> void {
    add_input_ui(m_p->delay.init_widget(MinV<int>{0}, V<int>{0}, MaxV<int>{5000}, StepV<int>{10}));
}

auto DCNetworkDirectPlayerConfigParametersW::update_with_info(QStringView id, QStringView value) -> void {

    if(id.contains(QSL("frame_infos_"))){
        auto splitId = id.split('_');
        if(splitId.size() == 4){
            auto id    = splitId[2].toInt();
            auto count = splitId[3].toInt();

            while(m_p->frameInfos.size() < count){
                m_p->frameInfos.append("");
            }

            m_p->frameInfos[id] = QString("[%1]: [%2]").arg(id).arg(value);
            m_p->infos.w->setText(m_p->frameInfos.join("\n"));
        }
    }
}

