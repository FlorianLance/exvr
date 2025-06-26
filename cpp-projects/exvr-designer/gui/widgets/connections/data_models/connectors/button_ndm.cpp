

/***********************************************************************************
** exvr-designer                                                                  **
** MIT License                                                                    **
** Copyright (c) [2025] [Florian Lance][EPFL-LNCO]                                **
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

#include "button_ndm.hpp"

using namespace tool::ex;

void PushButtonEmbeddedW::initialize(){

    // init widget
    w->init_widget("Send trigger");

    // // set widget connections
    connect(w.get(), &ExPushButtonW::ui_change_signal, this, [=]{
        emit compute_data_signal();
    });
    // connect(w.get(), &ExPushButtonW::ui_change_signal, this, &PushButtonEmbeddedW::compute_data_signal);

    // add widget to ui
    add_row_in_dialog(QSL(""), w->w.get());
}


void ButtonNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    inPortsInfo[0].caption  = QSL("in (") % get_name(io.inTypes[0]) % QSL(")");
    outPortsInfo[0].caption = QSL("out (") % get_name(io.outTypes[0]) % QSL(")");
}

void ButtonNodeDataModel::compute(){

    set_valid_state();
    propagate_default_runtime({std::make_shared<VoidData>()});
}

#include "moc_button_ndm.cpp"
