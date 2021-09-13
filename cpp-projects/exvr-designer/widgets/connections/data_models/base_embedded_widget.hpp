
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QPainter>
#include <QFontMetrics>
#include <QPlainTextEdit>

// base
#include "utility/benchmark.hpp"

// local
#include "ex_label_w.hpp"
#include "argument.hpp"
#include "qt_str.hpp"
#include "ex_base_w.hpp"
#include "connections/data_models/data/nodes_data.hpp"

namespace tool::ex{

class NodeDataDisplayDialog : public QDialog {

Q_OBJECT

public:

    NodeDataDisplayDialog(QString caption, bool popup);

    void add_row_in_dialog(QString name, QWidget *w, bool horizontalLayout);
    bool node_settings_execute(QPoint pos);

    QVBoxLayout *layout = nullptr;

private:
    bool m_popup = true;
};


class BaseNodeContainerW : public QWidget{

Q_OBJECT
public:

    ~BaseNodeContainerW();

    void initialize_container(QString caption, bool popup);

    void close();
    void add_row_in_dialog(QString name, QWidget *w, bool horizontalLayout = true);

    virtual bool set_text_value(QStringView value);
    void disable();
    void enable();
    void set_title(QString title);

    virtual bool update_with_info(QStringView value);
    virtual void update_from_arg(const Arg &arg) = 0;
    virtual void update_from_components(){}
    virtual Arg convert_to_arg() = 0;

    virtual void trigger_signals() = 0;

    virtual void paintEvent(QPaintEvent *event) override;

signals:

    void update_internal_data_signal(std_v1<size_t> indexes, std_v1<std::shared_ptr<NodeData>> nodes);
    void compute_data_signal();
    void ask_node_to_update();

protected:

//    QPlainTextEdit m_valueText;
    QLabel m_valueText;
    QPushButton m_openDialogButton;
    QPushButton m_helpButton;

    std::optional<QString> m_dialogTitle;
    std_v1<std::tuple<QString, QWidget*, bool>> m_dialogWidgetsRows;
    std::unique_ptr<NodeDataDisplayDialog> m_dataDisplayD = nullptr;


    static const QString buttonStyle1;
    static const QString buttonStyle2;
};

template <typename W>
class NodeContainerW : public BaseNodeContainerW{

public:
    NodeContainerW(){
        w = std::make_unique<W>("value");
    }    

    virtual void initialize(){}

    virtual void update_from_arg(const Arg &arg) override{
        w->update_from_arg(arg);

    }
    virtual Arg convert_to_arg() override{
        return w->convert_to_arg();
    }

    void trigger_signals() override{
        emit w->trigger_ui_change();
    }

    std::unique_ptr<W> w = nullptr;
};


class PlaceHolderEmbeddedW : public NodeContainerW<ExLabelW>{

Q_OBJECT
public:

    void initialize() override{

        // init widget
        w->init_widget("");

        // set widget connections
        connect(w.get(), &ExLabelW::ui_change_signal, this, [=]{
            emit compute_data_signal();
        });
    }
};

}

