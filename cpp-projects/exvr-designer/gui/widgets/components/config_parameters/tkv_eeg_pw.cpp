
/***********************************************************************************
** exvr-designer                                                                  **
** MIT License                                                                    **
** Copyright (c) [2025] [Florian Lance]                                           **
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


#include "tkv_eeg_pw.hpp"

// qt-utility
#include "gui/ex_widgets/ex_line_edit_w.hpp"
#include "gui/ex_widgets/ex_checkbox_w.hpp"
#include "gui/ex_widgets/ex_spin_box_w.hpp"
#include "gui/ex_widgets/ex_text_edit_w.hpp"
#include "gui/ex_widgets/ex_combo_box_index_w.hpp"

// local
#include "gui/ex_widgets/ex_resource_w.hpp"
#include "gui/ex_widgets/ex_component_w.hpp"

using namespace tool::ex;

struct TkvEEGInitConfigParametersW::Impl{
    ExComponentW websocketClientC{"websocket_client_component"};
    ExResourceW electrodesColorsTextR{"electrodes_colors"};
    ExResourceW headsetElectrodesQualityImageR{"headset_electrodes_quality_image"};
    // ExLineEditW readingAddress{"reading_address"};
    // ExLineEditW writingAddress{"writing_address"};
    // ExSpinBoxW readingPort{"reading_port"};
    // ExSpinBoxW writingPort{"writing_port"};
    ExComboBoxIndexW eeqQualityRequirments{"eeg_quality_requirments"};
};

TkvEEGInitConfigParametersW::TkvEEGInitConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){

}

void TkvEEGInitConfigParametersW::insert_widgets(){
    add_horizontal_widgets({m_p->websocketClientC()});
    add_horizontal_widgets({m_p->electrodesColorsTextR()});
    add_horizontal_widgets({m_p->headsetElectrodesQualityImageR()});
    add_horizontal_widgets({ui::W::txt("EEG minimum quality requirments:"), m_p->eeqQualityRequirments()});
    // add_stretched_horizontal_widgets({ui::W::txt("Reading port:"),    m_p->readingPort()});
    // add_stretched_horizontal_widgets({ui::W::txt("Writing address:"), m_p->writingAddress()});
    // add_stretched_horizontal_widgets({ui::W::txt("Writing port:"),    m_p->writingPort()});
}

void TkvEEGInitConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_p->websocketClientC.init_widget(tool::ex::Component::Type::WebsocketClient, "Websocket client"));
    add_input_ui(m_p->electrodesColorsTextR.init_widget(tool::ex::Resource::Type::Text, "Headset electrodes colors mapping"));
    add_input_ui(m_p->headsetElectrodesQualityImageR.init_widget(tool::ex::Resource::Type::Image, "Headset electrodes quality image"));
    add_input_ui(m_p->eeqQualityRequirments.init_widget({"Poor", "OK", "Good"}));
    // add_input_ui(m_p->writingAddress.init_widget("127.0.0.1"));
    // add_input_ui(m_p->readingPort.init_widget(MinV<int>{6000},V<int>{6558}, MaxV<int>{44000}, StepV<int>{1}));
    // add_input_ui(m_p->writingPort.init_widget(MinV<int>{6000},V<int>{6557}, MaxV<int>{44000}, StepV<int>{1}));
}

struct TkvEEGConfigParametersW::Impl{
    // ExCheckBoxW applyCommand{"apply_command_list"};
    // ExResourceW commandListFile{"command_list_file"};
    // ExTextEditW commandListText{"command_list_text"};
};

TkvEEGConfigParametersW::TkvEEGConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void TkvEEGConfigParametersW::insert_widgets(){
    // add_horizontal_widgets({m_p->applyCommand()});
    // add_horizontal_widgets({m_p->commandListFile()});
    // add_horizontal_widgets({ui::W::txt("Commands to send (if no file selected)")});
    // add_horizontal_widgets({m_p->commandListText()});
    // no_end_stretch();
}

void TkvEEGConfigParametersW::init_and_register_widgets(){
    // add_input_ui(m_p->applyCommand.init_widget("Send commands", false));
    // add_input_ui(m_p->commandListFile.init_widget(Resource::Type::Text, "Commands list text file"));
    // add_input_ui(m_p->commandListText.init_widget("", Qt::TextFormat::PlainText));
}
