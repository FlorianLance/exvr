
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "copy_to_conditions_dialog.hpp"

// Qt
#include <QStringList>

using namespace tool;
using namespace tool::ex;

CopyToConditionDialog::CopyToConditionDialog(){

    ui.setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setModal(true);   

    connect(ui.buttonBox, &QDialogButtonBox::accepted, this, [&]{

        std_v1<std::pair<ElementKey,ConditionKey>> conditionsToBeEcrased;
        for(size_t ii = 0; ii < conditionsPerRoutines.size(); ++ii){
            auto routine = conditionsPerRoutines[ii].first;
            auto lw = conditionsPerRoutines[ii].second.get();
            for(int ii = 0; ii < lw->count(); ++ii){
                if(qobject_cast<QCheckBox*>(lw->widget_at(ii))->isChecked()){
                    conditionsToBeEcrased.emplace_back(std::make_pair(
                        ElementKey{routine->key()}, ConditionKey{routine->conditions[to_unsigned(ii)]->key()}));
                }
            }
        }

        const auto copyActions     = ui.rbCopyBoth->isChecked() || ui.rbCopyActions->isChecked();
        const auto copyConnections = ui.rbCopyBoth->isChecked() || ui.rbCopyConnections->isChecked();
        emit copy_to_conditions_signal(m_currentRoutine, m_currentCondition, std::move(conditionsToBeEcrased), copyActions, copyConnections);
    });

    connect(ui.pbCheckAllConds, &QPushButton::clicked, this, [&](){

        auto id = to_unsigned(ui.twRoutines->currentIndex());
        auto lw = conditionsPerRoutines[id-1].second.get();
        for(int ii = 0; ii < lw->count(); ++ii){
            auto cb = qobject_cast<QCheckBox*>(lw->widget_at(ii));
            if(cb->isEnabled()){
                cb->setChecked(true);
            }
        }
        update_ui_from_conditions_checkboxes();
    });

    connect(ui.pbUncheckAllConds, &QPushButton::clicked, this, [&](){

        auto id = to_unsigned(ui.twRoutines->currentIndex());
        auto lw = conditionsPerRoutines[id-1].second.get();
        for(int ii = 0; ii < lw->count(); ++ii){
            auto cb = qobject_cast<QCheckBox*>(lw->widget_at(ii));
            if(cb->isEnabled()){
                cb->setChecked(false);
            }
        }
        update_ui_from_conditions_checkboxes();
    });

    connect(ui.pbUncheckAllSets, &QPushButton::clicked, this, [&](){

        for(const auto &setPerLoop : setsPerLoops){
            auto lw = setPerLoop.second.get();
            for(int ii = 0; ii < lw->count(); ++ii){
                auto cb =  qobject_cast<QCheckBox*>(lw->widget_at(ii));
                cb->setChecked(false);
            }
        }
        update_list_from_filters();
    });

    connect(ui.cbApplyContainFilter, &QCheckBox::clicked, this, [&]{
        update_list_from_filters();
    });
    connect(ui.leContainsCondFilter, &QLineEdit::textChanged, this, [&](const QString &){
        update_list_from_filters();
    });
    connect(ui.leContainsRoutineFilter, &QLineEdit::textChanged, this, [&](const QString &){
        update_list_from_filters();
    });
    connect(ui.cbApplySetFilter, &QCheckBox::clicked, this, [&]{
        update_list_from_filters();
    });


    update_list_from_filters();
    update_ui_from_conditions_checkboxes();
}

void CopyToConditionDialog::update_list_from_filters(){

    const auto containsRoutTxt = ui.leContainsRoutineFilter->text();
    const auto containsCondTxt = ui.leContainsCondFilter->text();
    const bool containFilterEnabled = ui.cbApplyContainFilter->isChecked();
    const bool setFilterEnabled     = ui.cbApplySetFilter->isChecked();

    QStringList sets;
    for(const auto &setPerLoop : setsPerLoops){
        auto lw = setPerLoop.second.get();
        for(int ii = 0; ii < lw->count(); ++ii){
            auto cb =  qobject_cast<QCheckBox*>(lw->widget_at(ii));
            if(cb->isChecked()){
                sets << cb->text();
            }
        }
    }

    size_t totalCount = 0;
    size_t filteredCount = 0;
    for(const auto &routineConditions : conditionsPerRoutines){

        auto lw = routineConditions.second.get();

//        bool routineFiltered = routineConditions.first->name().contains(containsRoutTxt);


        for(int ii = 0; ii < lw->count(); ++ii){
            auto cb =  qobject_cast<QCheckBox*>(lw->widget_at(ii));

            bool stateFromContainFilter = containFilterEnabled && !cb->text().contains(containsCondTxt);
            bool stateFromSetFilter = false;
            if(setFilterEnabled){
                stateFromSetFilter = true;
                for (const auto &set : sets) {
                    if(cb->text().contains(set)){
                        stateFromSetFilter = false;
                        break;
                    }
                }
            }

            if(stateFromContainFilter || stateFromSetFilter){
                cb->setHidden(true);
                ++filteredCount;
            }else{
                cb->setHidden(false);                
            }

            ++totalCount;
        }
    }

    ui.laFiltersCount->setText(QString::number(filteredCount) % QSL(" out of ") % QString::number(totalCount) % QSL(" conditions filtered"));
}

void CopyToConditionDialog::update_ui_from_conditions_checkboxes(){

    size_t count = 0;
    for(size_t ii = 0; ii < conditionsPerRoutines.size(); ++ii){
        auto lw = conditionsPerRoutines[ii].second.get();
        for(int ii = 0; ii < lw->count(); ++ii){
            if(qobject_cast<QCheckBox*>(lw->widget_at(ii))->isChecked()){
                ++count;
            }
        }
    }
    ui.laConditionsCount->setText(QString::number(count) % QSL(" conditions selected to be ecrased"));
    ui.buttonBox->button(QDialogButtonBox::StandardButton::Ok)->setEnabled(count > 0);
}


void CopyToConditionDialog::update_from_data(ElementKey currentRoutineKey, ConditionKey currentConditionKey, std_v1<Routine *> routines, std_v1<Loop*> loops){

    m_currentRoutine    = currentRoutineKey;
    m_currentCondition  = currentConditionKey;

    blockSignals(true);

    // clean
    conditionsPerRoutines.clear();
    while(ui.twRoutines->count() > 0){
        ui.twRoutines->removeTab(0);
    }

    setsPerLoops.clear();
    while(ui.twSets->count() > 0){
        ui.twSets->removeTab(0);
    }

    ui.cbApplyContainFilter->setChecked(false);
    ui.cbApplySetFilter->setChecked(false);
    ui.leContainsRoutineFilter->setText("");
    ui.leContainsCondFilter->setText("");

    // fils sets
    ui.twSets->addTab(new QWidget(), QSL("Loops: "));
    ui.twSets->setTabEnabled(0, false);

    for(const auto &loop : loops){

        auto lw = std::make_unique<ui::ListWidget>();
        ui.twSets->addTab(lw.get(), loop->name());
        for(const auto &set : loop->sets){
            auto cb = new QCheckBox(set.name);
            cb->setObjectName(QSL("Check ") % set.name);

            connect(cb, &QCheckBox::clicked, this, &CopyToConditionDialog::update_list_from_filters);
            lw->add_widget(cb);
        }

        lw->set_margins(2,2,2,2,2);
        setsPerLoops.emplace_back(std::make_pair(loop, std::move(lw)));
    }

    if(ui.twSets->count() > 1){
        ui.twSets->setCurrentIndex(1);
    }

    // fill conditions
    ui.twRoutines->addTab(new QWidget(), QSL("Routines:"));
    ui.twRoutines->setTabEnabled(0, false);

    for(const auto &routine : routines){

        auto lw = std::make_unique<ui::ListWidget>();
        ui.twRoutines->addTab(lw.get(), routine->name());
        for(const auto &condition : routine->conditions){
            auto cb = new QCheckBox(condition->name);
            cb->setObjectName(QSL("Check ") % condition->name);
            if(condition->key() == m_currentCondition.v){
                cb->setEnabled(false);
                cb->setText(cb->text() % QSL(" (condition to copy)"));
            }
            lw->add_widget(cb);
            connect(cb, &QCheckBox::clicked, this, &CopyToConditionDialog::update_ui_from_conditions_checkboxes);
        }
        lw->set_margins(2,2,2,2,2);
        conditionsPerRoutines.emplace_back(std::make_pair(routine, std::move(lw)));
    }

    if(ui.twRoutines->count() > 1){
        ui.twRoutines->setCurrentIndex(1);
    }

    blockSignals(false);
}

