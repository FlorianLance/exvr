
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "sonceboz_sg_pw.hpp"

using namespace tool::ex;

void SoncebozSgInitConfigParametersW::insert_widgets(){
    add_stretched_horizontal_widgets({ui::W::txt("Reading address:"), m_readingAddress()});
    add_stretched_horizontal_widgets({ui::W::txt("Reading port:"),    m_readingPort()});
    add_stretched_horizontal_widgets({ui::W::txt("Writing address:"), m_writingAddress()});
    add_stretched_horizontal_widgets({ui::W::txt("Writing port:"),    m_writingPort()});
}

void SoncebozSgInitConfigParametersW::init_and_register_widgets(){
    m_inputUiElements["reading_address"] = m_readingAddress.init_widget("127.0.0.1");
    m_inputUiElements["writing_address"] = m_writingAddress.init_widget("127.0.0.1");
    m_inputUiElements["reading_port"]    = m_readingPort.init_widget(MinV<int>{6000},V<int>{6558}, MaxV<int>{44000}, StepV<int>{1});
    m_inputUiElements["writing_port"]    = m_writingPort.init_widget(MinV<int>{6000},V<int>{6557}, MaxV<int>{44000}, StepV<int>{1});
}

void SoncebozSgConfigParametersW::insert_widgets(){    
    add_horizontal_widgets({applyCommand()});
    add_horizontal_widgets({commandList()});
}

void SoncebozSgConfigParametersW::init_and_register_widgets(){
    m_inputUiElements["apply_command_list"] = applyCommand.init_widget("Apply command list", false);
    m_inputUiElements["command_list_file"] = commandList.init_widget(Resource::Type::Text, "Commands list txt file");
}
