
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "sub_parts_pw.hpp"

namespace tool::ex {

class ConfigParametersW : public QWidget{

    Q_OBJECT

public :

    ConfigParametersW();
    virtual ~ConfigParametersW(){}

    void set_infos(ComponentKey componentKey, ConfigKey configKey, bool initConfig);

    virtual void update_with_info(QStringView id, QStringView value){ Q_UNUSED(id) Q_UNUSED(value)}
    virtual void insert_widgets(){}
    virtual void init_and_register_widgets(){}
    virtual void create_connections(){}
    virtual void late_update_ui(){}

    // # stretch
    void no_end_stretch();
    void end_stretch();
    void set_stretch(int id, int value);
    // # widgets
    void add_widget(QWidget *w);
    void add_horizontal_widgets(std::vector<QWidget*> widgets,
        LMargins margins = LMargins{false}, QFrame::Shape shape = QFrame::NoFrame, QFrame::Shadow shadow = QFrame::Raised);
    void add_stretched_horizontal_widgets(std::vector<QWidget*> widgets,
        LMargins margins = LMargins{false}, QFrame::Shape shape = QFrame::NoFrame, QFrame::Shadow shadow = QFrame::Raised);
    void add_vertical_widgets(std::vector<QWidget*> widgets,
        LMargins margins = LMargins{false}, QFrame::Shape shape = QFrame::NoFrame, QFrame::Shadow shadow = QFrame::Raised);
    void add_stretched_vertical_widgets(std::vector<QWidget*> widgets,
        LMargins margins = LMargins{false}, QFrame::Shape shape = QFrame::NoFrame, QFrame::Shadow shadow = QFrame::Raised);

    void add_sub_part_widget(ConfigParametersSubPart &subPart);
    void map_sub_part(ConfigParametersSubPart *subPart);

    // # update
    void init_from_args(std::unordered_map<QStringView,Arg*> &argsByName);
    void update_from_resources();
    void update_from_components();
    void reset_args();

    void add_input_ui(ExBaseW *w);
    void add_action_ui(ExBaseW *w);
    void add_non_ui_arg(Arg arg);
    void add_generator_ui(ExParametersGeneratorWidgetW *g);

    inline std::unordered_map<UiElementKey, ExBaseW*> *input_ui_widgets(){
        return &m_inputUiElements;
    }

public:

    bool initConfig;
    ComponentKey componentKey;
    ConfigKey configKey;

protected:

    QVBoxLayout *m_layout = nullptr;

private:

    std::unordered_map<UiElementKey, ExBaseW*> m_inputUiElements;
    std::unordered_map<QStringView, ExBaseW*> m_inputUiElementsNames;

    std::unordered_map<UiElementKey, ExBaseW*> m_actionUiElements;
    std::unordered_map<UiElementKey, Arg> m_inputNonUiArguments;
    std::unordered_map<UiElementKey, ExParametersGeneratorWidgetW*> m_generatorsUiElements;

    bool endStretch = true;
};
}
