

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "csharp_pw.hpp"


// qt-utility
#include "widgets/text_widget_highlighter.hpp"
#include "ex_widgets/ex_text_edit_w.hpp"
#include "ex_widgets/ex_code_editor_w.hpp"
#include "ex_widgets/ex_line_edit_w.hpp"

// local
#include "data/component.hpp"

using namespace tool::ex;

struct CSharpFunctionInitConfigParametersW::Impl{

    ExCodeEditorW extraContent{"extra"};
};


CSharpFunctionInitConfigParametersW::CSharpFunctionInitConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void CSharpFunctionInitConfigParametersW::insert_widgets(){

    add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("Define extra content accesible for each function of each config\n (ex: variables, enum, struct/class, functions...)"), m_p->extraContent()},
            LStretch{false},LMargins{true}, QFrame::NoFrame));

        no_end_stretch();
}

void CSharpFunctionInitConfigParametersW::init_and_register_widgets(){

    QStringList classNames;
    for(const auto &unityStr : Component::components.tuple_column<Component::ColUnityStr>()){
        classNames << QString(from_view(unityStr) % QSL("Component"));
    }

    add_input_ui(m_p->extraContent.init_widget_as_csharp_editor(classNames, QColor(30,30,30), ""));
}

struct CSharpFunctionConfigParametersW::Impl{

    QTabWidget *tab = nullptr;
    ExTextEditW startFunction{"start"};
    ExCodeEditorW contentFunction{"function"};
    ExTextEditW endFunction{"end"};
    ExCodeEditorW extraContent{"extra"};
};


CSharpFunctionConfigParametersW::CSharpFunctionConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void CSharpFunctionConfigParametersW::insert_widgets(){

    m_p->tab = new QTabWidget();
    add_widget(m_p->tab);

    auto functionF = ui::F::gen(ui::L::VB(), {ui::W::txt("Define the content of the function below:"), m_p->startFunction(), m_p->contentFunction(), m_p->endFunction()},
                                LStretch{false},LMargins{true}, QFrame::NoFrame);
    auto functionL = dynamic_cast<QVBoxLayout*>(functionF->layout());
    functionL->setStretch(0,1);
    functionL->setStretch(1,5);
    functionL->setStretch(2,50);
    functionL->setStretch(3,5);
    m_p->tab->addTab(functionF, "Function");

    auto extraF = ui::F::gen(ui::L::VB(), {ui::W::txt("Define extra content accesible in the function for this config \n (ex: variables, enum, struct/class, functions...)"), m_p->extraContent()},
                             LStretch{false},LMargins{true}, QFrame::NoFrame);
    auto extraL = dynamic_cast<QVBoxLayout*>(extraF->layout());
    extraL->setStretch(0,1);
    extraL->setStretch(1,50);
    m_p->tab->addTab(extraF, "Extra");

    no_end_stretch();
}

void CSharpFunctionConfigParametersW::init_and_register_widgets(){

    QStringList classNames;
    for(const auto &unityStr : Component::components.tuple_column<Component::ColUnityStr>()){
        classNames << QString(from_view(unityStr) % QSL("Component"));
    }

    // init widgets
    m_p->startFunction.init_widget_as_csharp_editor(classNames, QColor(80,80,80), "public static object function(object input){\n   object output = null;");
    add_input_ui(m_p->contentFunction.init_widget_as_csharp_editor(classNames, QColor(30,30,30), " "));
    m_p->endFunction.init_widget_as_csharp_editor(classNames, QColor(80,80,80), "   return output;\n}");
    add_input_ui(m_p->extraContent.init_widget_as_csharp_editor(classNames, QColor(30,30,30), ""));

    m_p->startFunction.w->setReadOnly(true);
    m_p->endFunction.w->setReadOnly(true);
}

void CSharpFunctionConfigParametersW::create_connections(){

    connect(&m_p->extraContent, &ExCodeEditorW::ui_change_signal, this, [&]{
        auto content = m_p->extraContent.w->toPlainText();
        if(content.length() == 0){
            m_p->contentFunction.w->offsetLineCounter = 0;
        }else{
            int nbLines = content.count('\n');
            m_p->contentFunction.w->offsetLineCounter = nbLines + 1;
        }
    });
}

void CSharpFunctionConfigParametersW::late_update_ui(){
    auto content = m_p->extraContent.w->toPlainText();
    if(content.length() == 0){
        m_p->contentFunction.w->offsetLineCounter = 0;
    }else{
        int nbLines = content.count('\n');
        m_p->contentFunction.w->offsetLineCounter = nbLines + 1;
    }
}


struct CSharpScriptInitConfigParametersW::Impl{
    ExLineEditW className{"component_class_name"};
    ExParametersGeneratorWidgetW generator{"generator"};
};


CSharpScriptInitConfigParametersW::CSharpScriptInitConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void CSharpScriptInitConfigParametersW::insert_widgets(){

    auto l1 = ui::L::HB();
    m_layout->addWidget(ui::F::gen(l1, {ui::W::txt("Component class to load:"),m_p->className()},  LStretch{true},LMargins{true}, QFrame::Box));
    l1->setStretch(0,1);
    l1->setStretch(1,10);
    l1->setStretch(2,1);

    m_layout->addWidget(ui::F::gen(ui::L::HB(), {m_p->generator()},  LStretch{false},LMargins{false}, QFrame::Box));
    m_layout->setStretch(0,1);
    m_layout->setStretch(1,50);
}

void CSharpScriptInitConfigParametersW::init_and_register_widgets(){
    add_generator_ui(m_p->generator.init_widget(input_ui_widgets()));
    add_input_ui(m_p->className.init_widget("TemplateComponent"));
}


struct CSharpScriptConfigParametersW::Impl{
    ExParametersGeneratorWidgetW generator{"generator"};
};


CSharpScriptConfigParametersW::CSharpScriptConfigParametersW():  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void CSharpScriptConfigParametersW::insert_widgets(){
    m_layout->addWidget(ui::F::gen(ui::L::HB(), {m_p->generator()},  LStretch{false},LMargins{false}, QFrame::Box));
    m_layout->setStretch(0,10);
}

void CSharpScriptConfigParametersW::init_and_register_widgets(){
    add_generator_ui(m_p->generator.init_widget(input_ui_widgets()));
}