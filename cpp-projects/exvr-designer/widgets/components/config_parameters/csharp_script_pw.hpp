
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDesktopServices>
#include <QDirIterator>
#include <QDir>
#include <QListWidget>

// qt-utility
#include "widgets/text_widget_highlighter.hpp"
#include "ex_widgets/ex_text_edit_w.hpp"
#include "ex_widgets/ex_code_editor_w.hpp"
#include "ex_widgets/ex_line_edit_w.hpp"

// local
#include "utility/path_utility.hpp"
#include "data/component.hpp"
#include "config_pw.hpp"


namespace tool::ex {

class CSharpFunctionInitConfigParametersW : public ConfigParametersW{
public:
    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

class CSharpFunctionConfigParametersW : public ConfigParametersW{
public:

    QTabWidget *tab = nullptr;

    ExTextEditW startFunction{"start"};
    ExCodeEditorW contentFunction{"function"};
    ExTextEditW endFunction{"end"};

    ExCodeEditorW extraContent{"extra"};

    void insert_widgets() override{

        tab = new QTabWidget();
        add_widget(tab);

        auto functionF = ui::F::gen(ui::L::VB(), {ui::W::txt("Define the content of the function below:"), startFunction(), contentFunction(), endFunction()},
                LStretch{false},LMargins{true}, QFrame::NoFrame);
        auto functionL = dynamic_cast<QVBoxLayout*>(functionF->layout());
        functionL->setStretch(0,1);
        functionL->setStretch(1,5);
        functionL->setStretch(2,50);
        functionL->setStretch(3,5);
        tab->addTab(functionF, "Function");

        auto extraF = ui::F::gen(ui::L::VB(), {ui::W::txt("Define extra static content accesible for the function (variables, functions...)"), extraContent()},
            LStretch{false},LMargins{true}, QFrame::NoFrame);
        auto extraL = dynamic_cast<QVBoxLayout*>(extraF->layout());
        extraL->setStretch(0,1);
        extraL->setStretch(1,50);
        tab->addTab(extraF, "Extra");

        no_end_stretch();
    }

    void init_and_register_widgets() override{

        QStringList classNames;
        for(const auto &unityStr : Component::components.tuple_column<Component::ColUnityStr>()){
            classNames << QString(from_view(unityStr) % QSL("Component"));
        }

        // init widgets
        startFunction.init_widget_as_csharp_editor(classNames, QColor(80,80,80), "public static object function(object input){\n   object output = null;");
        add_input_ui(contentFunction.init_widget_as_csharp_editor(classNames, QColor(30,30,30), " "));
        endFunction.init_widget_as_csharp_editor(classNames, QColor(80,80,80), "   return output;\n}");
        add_input_ui(extraContent.init_widget_as_csharp_editor(classNames, QColor(30,30,30), ""));

        startFunction.w->setReadOnly(true);
        endFunction.w->setReadOnly(true);
    }

    void create_connections() override{

        connect(&extraContent, &ExCodeEditorW::ui_change_signal, this, [&]{
            auto content = extraContent.w->toPlainText();
            if(content.length() == 0){
                contentFunction.w->offsetLineCounter = 0;
            }else{
                int nbLines = content.count('\n');
                contentFunction.w->offsetLineCounter = nbLines + 1;
            }
        });
    }

    void late_update_ui() override{
        auto content = extraContent.w->toPlainText();
        if(content.length() == 0){
            contentFunction.w->offsetLineCounter = 0;
        }else{
            int nbLines = content.count('\n');
            contentFunction.w->offsetLineCounter = nbLines + 1;
        }
    }
};

class CSharpScriptInitConfigParametersW : public ConfigParametersW{

public :

    ExLineEditW m_className{"component_class_name"};
    ExParametersGeneratorWidgetW m_generator{"generator"};

    void insert_widgets() override{

        auto l1 = ui::L::HB();
        m_layout->addWidget(ui::F::gen(l1, {ui::W::txt("Component class to load:"),m_className()},  LStretch{true},LMargins{true}, QFrame::Box));
        l1->setStretch(0,1);
        l1->setStretch(1,10);
        l1->setStretch(2,1);

        m_layout->addWidget(ui::F::gen(ui::L::HB(), {m_generator()},  LStretch{false},LMargins{false}, QFrame::Box));
        m_layout->setStretch(0,1);
        m_layout->setStretch(1,50);
    }

    void init_and_register_widgets() override{
        add_generator_ui(m_generator.init_widget(input_ui_widgets()));
        add_input_ui(m_className.init_widget("TemplateComponent"));
    }

    void create_connections() override{
    }

    void late_update_ui() override{}
};

class CSharpScriptConfigParametersW : public ConfigParametersW{

public :

    ExParametersGeneratorWidgetW m_generator{"generator"};

    void insert_widgets() override{
        m_layout->addWidget(ui::F::gen(ui::L::HB(), {m_generator()},  LStretch{false},LMargins{false}, QFrame::Box));
        m_layout->setStretch(0,10);
    }

    void init_and_register_widgets() override{
        add_generator_ui(m_generator.init_widget(input_ui_widgets()));
    }


    void create_connections() override{}
    void late_update_ui() override{}
};

}
