
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
#include "ex_widgets/base/ex_item_w.hpp"

// Qt
#include <QScrollArea>
#include <QScrollBar>

namespace tool::ex {


class ExParametersGeneratorWidgetW : public ExItemW<QWidget>{

    Q_OBJECT

public :

    ExParametersGeneratorWidgetW(QString name ="");
    ~ExParametersGeneratorWidgetW() override;
    ExParametersGeneratorWidgetW *init_widget(std::unordered_map<UiElementKey, ExBaseW*> *inputUiElements, bool enabled = true);

    void update_from_arg(const Arg &arg) override;
    Arg convert_to_arg() const override;
    void update_from_resources() override;
    void update_from_components() override;

private:

    std::pair<QWidget*,ExBaseW*> gen_ui_element(UiType uiType);
    void add_ui_element_from_dialog(UiType uiType);
    void add_ui_element_from_arg(Arg arg);

public:

    QComboBox m_cbTypeParam;
    QPushButton m_pbAddParam;
    QPushButton m_pbMoveUp;
    QPushButton m_pbMoveDown;
    QPushButton m_pbRemoveParam;
    ui::ListWidget m_lwParameters;

private:

    int currentId = 0;
    QVector<UiElementKey> elementsOrder;
    std::unordered_map<UiElementKey, ExBaseW*> generatorElements;
    std::unordered_map<UiElementKey, ExBaseW*> *m_inputUiElements = nullptr;

signals:

    void add_ui_signal(Arg arg);
    void remove_ui_signal(UiElementKey argKey);
    void swap_ui_signal(UiElementKey arg1Key, UiElementKey arg2Key);
};

}
