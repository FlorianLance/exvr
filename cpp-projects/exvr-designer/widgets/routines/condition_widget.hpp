
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDoubleSpinBox>
#include <QDebug>
#include <QStyledItemDelegate>

// qt-utility
#include "widgets/custom_combobox_w.hpp"

// local
// # ui
#include "ui_condition.h"
// # actions
#include "action_widget.hpp"
// # components
#include "widgets/components/components_manager_widget.hpp"
// connections
#include "widgets/connections/connections_widget.hpp"
// # data
#include "data/condition.hpp"
#include "data/gui.hpp"

namespace tool::ex {

class OnlyFocusScrollSpinBox : public ui::NoScrollFocusWidget<QDoubleSpinBox>{
    Q_OBJECT
public:
    OnlyFocusScrollSpinBox(QWidget* parent = Q_NULLPTR) : ui::NoScrollFocusWidget<QDoubleSpinBox>(parent){
        Q_UNUSED(parent)
    }
};
class ScaleSpinBox : public ui::NoScrollFocusWidget<QDoubleSpinBox>{

    Q_OBJECT

public:

    ScaleSpinBox(QWidget* parent = Q_NULLPTR);

public slots:

    void stepBy(int steps);
};



class ConditionW : public QWidget{
    Q_OBJECT

public :

    ConditionW(ElementKey routineKey, Condition *condition);
    void update_from_condition(GUI *gui, Condition *condition);
    void update_from_connector_info(ConnectorKey connectorKey, QStringView id, QStringView value);

    // connections
    void clean();
    void close_all_connectors_windows();
    ConnectionsW *connections_widget();

    void separate_panels(bool state);

    constexpr ElementKey routine_key() const noexcept{return m_routineKey;}
    constexpr ConditionKey condition_key() const noexcept{return m_conditionKey;}

protected:

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

public slots:

    void update_ui_from_current_tab(int index);
    void update_timeline();

private:

    ElementKey m_routineKey;
    ConditionKey m_conditionKey;

    // actions
    ui::ListWidget m_actionsListW;

    bool m_minimzed = false;

    // connections
    std::unique_ptr<ConnectionsW> m_connectionsW = nullptr;

    // ui
    OnlyFocusScrollSpinBox *dsbDuration = nullptr;
    OnlyFocusScrollSpinBox *dsbUiFactorSize = nullptr;
    ScaleSpinBox *dsbScale = nullptr;
    Ui::ConditionUiW m_ui;

    qreal m_prevScaleValue;
    qreal m_prevFactorSizeValue;

    QVBoxLayout *lActions = nullptr;
    QVBoxLayout *lConnections = nullptr;
    QHBoxLayout *lBoth = nullptr;

};
}
