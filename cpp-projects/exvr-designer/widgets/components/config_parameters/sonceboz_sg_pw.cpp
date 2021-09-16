
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
    add_input_ui(m_readingAddress.init_widget("127.0.0.1"));
    add_input_ui(m_writingAddress.init_widget("127.0.0.1"));
    add_input_ui(m_readingPort.init_widget(MinV<int>{6000},V<int>{6558}, MaxV<int>{44000}, StepV<int>{1}));
    add_input_ui(m_writingPort.init_widget(MinV<int>{6000},V<int>{6557}, MaxV<int>{44000}, StepV<int>{1}));
}

void SoncebozSgConfigParametersW::insert_widgets(){    
    add_horizontal_widgets({applyCommand()});
    add_horizontal_widgets({commandList()});
}

void SoncebozSgConfigParametersW::init_and_register_widgets(){    
    add_input_ui(applyCommand.init_widget("Apply command list", false));
    add_input_ui(commandList.init_widget(Resource::Type::Text, "Commands list txt file"));
}
