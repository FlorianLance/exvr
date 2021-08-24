
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

// local
#include "config_pw.hpp"
#include "path_utility.hpp"
#include "ex_line_edit_w.hpp"
#include "ex_label_w.hpp"

#include "widgets/dialogs/documentation_dialog.hpp"

namespace tool::ex {

class CSharpFunctionInitConfigParametersW : public ConfigParametersW{
public:

    ExLabelW start;
    ExTextEditW code;
    ExLabelW end;

    CSharpHighlighter *csharpHighlighter = nullptr;

    void insert_widgets() override{
        m_layout->addWidget(start());
        m_layout->addWidget(code());
        m_layout->addWidget(end());
        no_end_stretch();
    }
    void init_and_register_widgets() override{

        CSharpHighlighter *csharpHighlighter = nullptr;
        start.init_widget("namespace Ex{\n   public class TestCode{\n      public static object foo(object value){\n         object result = null;");
        m_inputUiElements["code"] = code.init_widget("UnityEngine.Debug.Log(\"Test\");");
        csharpHighlighter = new CSharpHighlighter(code.w->document());
        end.init_widget("         return result;\n      }\n   }\n}");
    }
    void create_connections() override{}
    void late_update_ui() override{}
};

class CSharpFunctionConfigParametersW : public ConfigParametersW{
public:
    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}
};

class CSharpScriptInitConfigParametersW : public ConfigParametersW{

public :

    ExLineEditW m_className;
    ExParametersGeneratorWidgetW m_generator;

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
        m_generatorsUiElements["generator"]         = m_generator.init_widget(&m_inputUiElements, "generator");
        m_inputUiElements["component_class_name"]   = m_className.init_widget("TemplateComponent");
    }

    void create_connections() override{
    }

    void late_update_ui() override{}
};

class CSharpScriptConfigParametersW : public ConfigParametersW{

public :

    ExParametersGeneratorWidgetW m_generator;


    void insert_widgets() override{
        m_layout->addWidget(ui::F::gen(ui::L::HB(), {m_generator()},  LStretch{false},LMargins{false}, QFrame::Box));
        m_layout->setStretch(0,10);
    }

    void init_and_register_widgets() override{
        m_generatorsUiElements["generator"] = m_generator.init_widget(&m_inputUiElements, "generator");
    }


    void create_connections() override{}
    void late_update_ui() override{}
};

}
