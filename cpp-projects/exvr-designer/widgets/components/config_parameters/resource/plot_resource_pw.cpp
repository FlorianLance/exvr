

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "plot_resource_pw.hpp"


using namespace tool::ex;


void PlotResourceConfigParametersW::insert_widgets(){
    layout()->setContentsMargins(0,0,0,0);
    add_widget(ui::F::gen(ui::L::HB(), {m_plot()}, LStretch{false}, LMargins{true}, QFrame::Box));
    add_widget(ui::F::gen(ui::L::VB(), {m_randomSelection(), m_plotsList()}, LStretch{false}, LMargins{true}, QFrame::Box));
    no_end_stretch();
}

void PlotResourceConfigParametersW::init_and_register_widgets(){
    add_input_ui(m_plot.init_widget(Resource::Type::Plot, "Selected plot resource: "));
    add_input_ui(m_randomSelection.init_widget("Random resource selection from list: ", false));
    add_input_ui(m_plotsList.init_widget(Resource::Type::Plot, "Plots list"));
}

void PlotResourceConfigParametersW::create_connections(){
    connect(m_randomSelection(), &QCheckBox::clicked, this, [&]{
        m_plot.w->setEnabled(!m_randomSelection.w->isChecked());
        m_plotsList.w->setEnabled(m_randomSelection.w->isChecked());
    });
}

void PlotResourceConfigParametersW::late_update_ui(){
    m_plot.w->setEnabled(!m_randomSelection.w->isChecked());
    m_plotsList.w->setEnabled(m_randomSelection.w->isChecked());
}
