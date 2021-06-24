
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

    virtual void update_with_info(QStringView id, QStringView value){ Q_UNUSED(id) Q_UNUSED(value)}
    virtual void insert_widgets(){}
    virtual void init_and_register_widgets(){}
    virtual void create_connections(){}
    virtual void late_update_ui(){}

    void no_end_stretch(){
        endStretch = false;
    }
    void end_stretch();
    void set_stretch(int id, int value);
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

    void update_from_args(std::map<QString,Arg> &args);
    void update_from_resources();
    void update_from_components();

    void reset_args();

    std::map<QString, ExBaseW*> m_inputUiElements;
    std::map<QString, ExBaseW*> m_actionUiElements;

    std::map<QString, Arg> m_inputNonUiArguments;
    std::map<QString, ExParametersGeneratorWidgetW*> m_generatorsUiElements;

    ConfigParametersW *initParametersW = nullptr;

signals :

    void arg_updated_signal(QString name, tool::ex::Arg arg);
    void arg_removed_signal(QString name);
    void move_arg_up_signal(QString previousName, QString name);
    void move_arg_down_signal(QString nextName, QString name);
    void new_arg_signal(QString name, tool::ex::Arg arg);
    void action_signal(QString name);

protected:

    QVBoxLayout *m_layout = nullptr;
    bool endStretch = true;

};
}
