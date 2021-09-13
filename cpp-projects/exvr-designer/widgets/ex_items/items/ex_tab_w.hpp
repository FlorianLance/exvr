/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QGridLayout>

// local
// # data
#include "config.hpp"
// # utility
#include "qt_str.hpp"
// # widgets
#include "ex_camera_target_w.hpp"

namespace tool::ex {


template <typename T>
class ExTabW : public ExItemW<QTabWidget>{


public:

    ExTabW(QString name ="") : ExItemW<QTabWidget>(UiType::Tab, name){

        w->setMovable(true);

        // connections
        connect(&pbAddTab, &QPushButton::clicked, [&]{
            add_tab();
            pbRemoveTab.setEnabled(w->count() > 0);
            update_tab_names();
            trigger_ui_change();
        });
        connect(&pbRemoveTab, &QPushButton::clicked, [&]{
            remove_tab();
            pbRemoveTab.setEnabled(w->count() > 0);
            update_tab_names();
            trigger_ui_change();
        });
        connect(w->tabBar(), &QTabBar::tabMoved, this, [&](int from, int to){
            std::swap(widgets[from], widgets[to]);
            update_tab_names();
            trigger_ui_change();
        });
    }

    void update_tab_names(){
        for(int ii = 0; ii < w->count(); ++ii){
            if(m_addNum){
                w->setTabText(ii, m_baseName + QString::number(ii));
            }else{
                w->setTabText(ii, m_baseName);
            }
        }
    }

    ExTabW *init_widget(const QString &baseName, std_v1<std::any> parameters, QTabWidget::TabPosition tabPosition = QTabWidget::TabPosition::North, bool addNum = true, bool enabled = true){

        m_baseName = baseName;
        m_parameters = std::move(parameters);
        w->setTabPosition(tabPosition);
        m_addNum = addNum;
        w->setEnabled(enabled);
        return this;
    }

    virtual void update_from_arg(const Arg &arg) override{

        ExItemW::update_from_arg(arg);

        w->blockSignals(true);

        if(arg.count() > 0){
            auto values = arg.split_value("[#1#]");
            for(auto &value : values){
                ExBaseW *w = add_tab();
                Arg arg;
                arg.init_from_unknow(std::move(value));
//                arg.init_from_unknow(arg.uiElementKey, std::move(value));
                w->update_from_arg(arg);
            }
        }

        update_tab_names();

        w->blockSignals(false);
    }

    virtual Arg convert_to_arg() const override{

        Arg arg = ExBaseW::convert_to_arg();

        std::vector<Arg> args;
        for(const auto& w : widgets){
            args.emplace_back(w->convert_to_arg());
        }
        arg.init_from_args(std::move(args), "[#1#]");

        return arg;
    }

    virtual void set_generator(QString genName) override{
        for(auto &w : widgets){
            w->set_generator(genName);
        }
    }



private:


    ExBaseW *add_tab(){

        // create item
        auto widget = std::make_unique<T>(QSL("tab") % QString::number(widgets.size()));

        // init sub connections
        auto baseW = dynamic_cast<ExBaseW*>(widget.get());
        connect(baseW, &ExBaseW::ui_change_signal, this, [&]{
            trigger_ui_change();
        });

        // init widget
        widget->init_widget2(m_parameters);

        // add tab
        QWidget *subW = new QWidget();
        auto l = new QVBoxLayout();
        subW->setLayout(l);
        l->addWidget(widget->w.get());
        l->addStretch();
        w->addTab(subW, m_baseName + QString::number(w->count()));

        // add to container
        widgets.emplace_back(std::move(widget));
        return baseW;
    }

    void remove_tab(){
        int id = w->currentIndex();
        if(id > -1){
            w->removeTab(id);
            widgets.erase(widgets.begin()+id);
        }
    }


public:

    QPushButton pbAddTab;
    QPushButton pbRemoveTab;
    std_v1<std::unique_ptr<ExBaseW>> widgets;

private :

    bool m_addNum;
    QString m_nameParam;
    QString m_baseName;
    std_v1<std::any> m_parameters;
};

}
