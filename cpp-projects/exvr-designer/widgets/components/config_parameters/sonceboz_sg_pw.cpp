
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "sonceboz_sg_pw.hpp"

// qt-utility
#include "ex_widgets/ex_line_edit_w.hpp"
#include "ex_widgets/ex_checkbox_w.hpp"
#include "ex_widgets/ex_spin_box_w.hpp"
#include "ex_widgets/ex_text_edit_w.hpp"

// local
#include "ex_widgets/ex_resource_w.hpp"

using namespace tool::ex;

struct SoncebozSgInitConfigParametersW::Impl{
    ExLineEditW readingAddress{"reading_address"};
    ExLineEditW writingAddress{"writing_address"};
    ExSpinBoxW readingPort{"reading_port"};
    ExSpinBoxW writingPort{"writing_port"};
};

SoncebozSgInitConfigParametersW::SoncebozSgInitConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){

}

void SoncebozSgInitConfigParametersW::insert_widgets(){
    add_stretched_horizontal_widgets({ui::W::txt("Reading address:"), m_p->readingAddress()});
    add_stretched_horizontal_widgets({ui::W::txt("Reading port:"),    m_p->readingPort()});
    add_stretched_horizontal_widgets({ui::W::txt("Writing address:"), m_p->writingAddress()});
    add_stretched_horizontal_widgets({ui::W::txt("Writing port:"),    m_p->writingPort()});
}

void SoncebozSgInitConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_p->readingAddress.init_widget("127.0.0.1"));
    add_input_ui(m_p->writingAddress.init_widget("127.0.0.1"));
    add_input_ui(m_p->readingPort.init_widget(MinV<int>{6000},V<int>{6558}, MaxV<int>{44000}, StepV<int>{1}));
    add_input_ui(m_p->writingPort.init_widget(MinV<int>{6000},V<int>{6557}, MaxV<int>{44000}, StepV<int>{1}));
}

struct SoncebozSgConfigParametersW::Impl{
    ExCheckBoxW applyCommand{"apply_command_list"};
    ExResourceW commandListFile{"command_list_file"};
    ExTextEditW commandListText{"command_list_text"};
};

SoncebozSgConfigParametersW::SoncebozSgConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void SoncebozSgConfigParametersW::insert_widgets(){
    add_horizontal_widgets({m_p->applyCommand()});
    add_horizontal_widgets({m_p->commandListFile()});
    add_horizontal_widgets({ui::W::txt("Commands to send (if no file selected)")});
    add_horizontal_widgets({m_p->commandListText()});
    no_end_stretch();
}

void SoncebozSgConfigParametersW::init_and_register_widgets(){    
    add_input_ui(m_p->applyCommand.init_widget("Apply command list", false));
    add_input_ui(m_p->commandListFile.init_widget(Resource::Type::Text, "Commands list txt file"));
    add_input_ui(m_p->commandListText.init_widget(""));
}
