
/***********************************************************************************
** exvr-designer                                                                  **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
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

#pragma once

// qt-utility
#include "gui/ex_widgets/ex_line_edit_w.hpp"
#include "gui/ex_widgets/ex_spin_box_w.hpp"
#include "gui/ex_widgets/ex_checkbox_w.hpp"
#include "gui/ex_widgets/ex_combo_box_index_w.hpp"
#include "gui/ex_widgets/ex_label_w.hpp"

// local
#include "config_pw.hpp"

namespace tool::ex {

class WebSocketClientInitConfigParametersW : public ConfigParametersW{

public :

    ExCheckBoxW m_connectAtStart{"connect_at_start"};
    ExLineEditW m_leUrl{"url"};


    void insert_widgets() override{        
        add_widget(ui::F::old_gen(ui::L::HB(), {ui::W::txt("URL:"), m_leUrl()}, LStretch{true}, LMargins{false}));
        add_widget(ui::F::old_gen(ui::L::HB(), {m_connectAtStart()}, LStretch{true}, LMargins{false}));        
    }

    void init_and_register_widgets() override{
        add_input_ui(m_leUrl.init_widget("ws://localhost:3000"));
        add_input_ui(m_connectAtStart.init_widget("Connect at start", true));
    }



    void create_connections() override{}
    void late_update_ui() override{}
};


class WebSocketClientConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};


class WebSocketServerInitConfigParametersW : public ConfigParametersW{

public :

    ExLineEditW m_leAddress{"address"};
    ExSpinBoxW m_sbPort{"port"};
    ExCheckBoxW m_cbAnyAddress{"any_address"};
    ExComboBoxIndexW m_cbFamily{"family"};
    ExCheckBoxW m_cbExclusiveAddressUse{"exclusive_address_use"};

    ExLabelW m_listeningIpAddress{"listening_ip_address"};

    void insert_widgets() override{
        add_widget(ui::F::old_gen(ui::L::HB(), {ui::W::txt("Listening address:"), m_leAddress()}, LStretch{true}, LMargins{false}));
        add_widget(ui::F::old_gen(ui::L::HB(), {ui::W::txt("Any address:"), m_cbAnyAddress(), ui::W::txt("Family:"), m_cbFamily()}, LStretch{true}, LMargins{false}));
        add_widget(ui::F::old_gen(ui::L::HB(), {ui::W::txt("Listening port:"), m_sbPort()}, LStretch{true}, LMargins{false}));        
        add_widget(ui::F::old_gen(ui::L::HB(), {ui::W::txt("Exclusive address use:"), m_cbExclusiveAddressUse()}, LStretch{true}, LMargins{false}));
        add_widget(ui::F::old_gen(ui::L::HB(), {ui::W::txt("Listening ip address:"), m_listeningIpAddress()}, LStretch{true}, LMargins{false}));
    }

    void init_and_register_widgets() override{
        add_input_ui(m_sbPort.init_widget( MinV<int>{0}, V<int>{3000}, MaxV<int>{100000}, StepV<int>{1}));
        add_input_ui(m_leAddress.init_widget("127.0.0.1"));
        add_input_ui(m_cbAnyAddress.init_widget("", false));
        add_input_ui(m_cbFamily.init_widget({"IPV4", "IPV6"},1));
        add_input_ui(m_cbExclusiveAddressUse.init_widget("", false));
        add_input_ui(m_listeningIpAddress.init_widget("", false));
        m_listeningIpAddress.init_widget("...");
    }

    void update_with_info(QStringView id, QStringView value) override{
        if(id == QSL("listening_ip_address")){
            m_listeningIpAddress.w->setText(value.toString());
        }
    }

    void create_connections() override{}
    void late_update_ui() override{}
};


class WebSocketServerConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

}
