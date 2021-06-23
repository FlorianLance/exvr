
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
// # data
#include "argument.hpp"
// # utility
#include "qt_str.hpp"
// # widgets
#include "widgets/list_widget.hpp"
#include "widgets/ex_items/base/ex_item_w.hpp"

// Qt
#include <QScrollArea>
#include <QScrollBar>

namespace tool::ex {


class ExParametersGeneratorWidgetW : public ExItemW<QWidget>{

    Q_OBJECT

public :

    ExParametersGeneratorWidgetW();
    ~ExParametersGeneratorWidgetW() override;
    ExParametersGeneratorWidgetW *init_widget(std::map<QString, ExBaseW*> *inputUiElements, QString genName, bool enabled = true);
    std::optional<Arg> generate_init_arg_from_dialog(QStringList othersParameters) override;
    void init_connection(const QString &nameParam) override;
    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void update_from_resources() override;
    void update_from_components() override;


    QComboBox m_cbTypeParam;
    QPushButton m_pbAddParam;
    QPushButton m_pbMoveUp;
    QPushButton m_pbMoveDown;
    QPushButton m_pbRemoveParam;

    QStringList m_namesParameters;
    ui::ListWidget m_lwParameters;

    std::map<QString, ExBaseW*> *m_inputUiElements = nullptr;

private:

    int currentId = 0;

    void add_ui_element_from_arg(const Arg &arg);
    void add_ui_element(UiType uiType, QString uiName, int order, bool initFromDialog);

signals:

    void add_ui_signal(QString nameParam);
    void move_up_ui_signal(QString prevNameParam, QString nameParam);
    void move_down_ui_signal(QString nextNameParam, QString nameParam);
    void remove_ui_signal(QString nameParam);
};

}
