
/***********************************************************************************
** exvr-designer                                                                  **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

#include "add_component_to_conditions_dialog.hpp"

// local
#include "experiment/experiment.hpp"
#include "experiment/global_signals.hpp"

using namespace tool;
using namespace tool::ex;

AddComponentToConditionsDialog::AddComponentToConditionsDialog(ComponentKey componentKey){

    // setup ui
    condSelUi.setupUi(this);
    setWindowTitle("Specify details for adding component:");
    setModal(true);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

    // retrieve exp and selected component
    auto exp = ExperimentManager::get()->current();
    auto component = exp->get_component(componentKey);

    // init top
    auto topL = new QVBoxLayout();
    condSelUi.wTop->setLayout(topL);
    topL->setContentsMargins(2,2,2,2);
    topL->addWidget(laApplyTo = new QLabel(QSL("Add component <b>") % component->name() % QSL("</b> of type <b>[") % from_view(Component::get_type_name(component->type)) % QSL("]</b> to:")));

    // init bottom
    auto botL = new QVBoxLayout();
    condSelUi.wBot->setLayout(botL);
    botL->setContentsMargins(2,2,2,2);

    botL->addWidget(ui::W::horizontal_line());


    cbConfigs = new QComboBox();
    cbConfigs->addItems(component->get_configs_name());
    botL->addWidget(ui::F::gen(ui::L::HB(),
        {ui::W::txt("Select config to use:"), cbConfigs}, LStretch{true}, LMargins{false}, QFrame::NoFrame));

    botL->addWidget(ui::W::horizontal_line());

    auto to = Component::get_timeline_opt(component->type);
    if (to == Component::TimelineO::Both || to == Component::TimelineO::Update){
        botL->addWidget(ui::F::gen(ui::L::HB(),
        {ui::W::txt("Update timeline: "), rbFillU = new QRadioButton("Fill"), rbEmptyU = new QRadioButton("Empty")}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
        rbFillU->setChecked(true);
    }
    if (to == Component::TimelineO::Both || to == Component::TimelineO::Visibility){
        botL->addWidget(ui::F::gen(ui::L::HB(),
        {ui::W::txt("Visibility timeline: "), rbFillV = new QRadioButton("Fill"), rbEmptyV = new QRadioButton("Empty")}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
        rbFillV->setChecked(true);
    }
    botL->addWidget(ui::W::horizontal_line());
    botL->addWidget(laApplyTo = new QLabel());

    // update middle
    condSelUi.twRoutines->addTab(new QWidget(), QSL("Routines:"));
    condSelUi.twRoutines->setTabEnabled(0, false);

    QStringList routinesName;
    for(const auto &routine : exp->get_elements_from_type<Routine>()){

        routinesName << routine->name();

        auto lw = std::make_unique<ui::ListWidget>();
        condSelUi.twRoutines->addTab(lw.get(), routine->name());
        for(const auto &condition : routine->conditions){

            auto cb = new QCheckBox(condition->name);
            cb->setObjectName(QSL("Check ") % condition->name);

            if(condition->get_component_from_key(componentKey, false) != nullptr){
                cb->setEnabled(false);
                cb->setText(cb->text() % QSL(" (already inside)"));
            }

            lw->add_widget(ui::F::gen(ui::L::HB(), {
                cb, ui::W::txt(QSL("(A: ") % QString::number(condition->actions.size()) % QSL(", C: ") %
                QString::number(condition->connectors.size()) %QSL(")"))},LStretch{false}, LMargins{false}, QFrame::NoFrame));

            connect(cb, &QCheckBox::clicked, this, [&]{
                update_selection_number();
            });
        }
        lw->set_margins(2,2,2,2,2);
        conditionsPerRoutines.emplace_back(std::make_pair(ElementKey{routine->key()}, std::move(lw)));
    }

    condSelUi.twRoutines->setCurrentIndex(1);
    condSelUi.twRoutines->update();

    condSelUi.lwRoutinesNames->clear();
    condSelUi.lwRoutinesNames->addItems(routinesName);
    condSelUi.lwRoutinesNames->setCurrentRow(0);

    connect(condSelUi.pbCheckAllConds, &QPushButton::clicked, this, [&](){

        auto id = to_unsigned(condSelUi.twRoutines->currentIndex());
        auto lw = conditionsPerRoutines[id-1].second.get();
        for(int ii = 0; ii < lw->count(); ++ii){
            auto w = lw->widget_at(ii)->layout()->itemAt(0)->widget();
            auto cb = qobject_cast<QCheckBox*>(w);
            if(cb->isEnabled()){
                cb->setChecked(true);
            }
        }
        update_selection_number();
    });

    connect(condSelUi.pbUncheckAllConds, &QPushButton::clicked, this, [&](){

        auto id = to_unsigned(condSelUi.twRoutines->currentIndex());
        auto lw = conditionsPerRoutines[id-1].second.get();
        for(int ii = 0; ii < lw->count(); ++ii){

            auto w = lw->widget_at(ii)->layout()->itemAt(0)->widget();
            auto cb = qobject_cast<QCheckBox*>(w);
            if(cb->isEnabled()){
                cb->setChecked(false);
            }
        }
        update_selection_number();
    });

    connect(condSelUi.lwRoutinesNames, &QListWidget::currentRowChanged, this, [&](int row){
        condSelUi.twRoutines->blockSignals(true);
        condSelUi.twRoutines->setCurrentIndex(row+1);
        condSelUi.twRoutines->blockSignals(false);
    });
    connect(condSelUi.twRoutines->tabBar(), &QTabBar::currentChanged, this, [&](int row){
        condSelUi.lwRoutinesNames->blockSignals(true);
        condSelUi.lwRoutinesNames->setCurrentRow(row-1);
        condSelUi.lwRoutinesNames->blockSignals(false);
    });

    connect(condSelUi.validateButtonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(condSelUi.validateButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(condSelUi.validateButtonBox, &QDialogButtonBox::accepted, this, [&,component]{

        std::vector<std::pair<ElementKey,ConditionKey>> addComponentToConditions;
        for(size_t ii = 0; ii < conditionsPerRoutines.size(); ++ii){
            auto routineKey = conditionsPerRoutines[ii].first;
            auto routine = ExperimentManager::get()->current()->get_routine(routineKey);

            auto lw = conditionsPerRoutines[ii].second.get();
            for(int ii = 0; ii < lw->count(); ++ii){
                auto w = lw->widget_at(ii)->layout()->itemAt(0)->widget();
                auto cb = qobject_cast<QCheckBox*>(w);
                if(cb->isChecked()){
                    addComponentToConditions.emplace_back(std::make_pair(
                        routineKey, ConditionKey{routine->conditions[to_unsigned(ii)]->key()}));
                }
            }
        }

        emit GSignals::get()->insert_action_to_signal(
            {component->key()},
            {component->configs[cbConfigs->currentIndex()]->key()},
            std::move(addComponentToConditions),
            rbFillU->isChecked(),
            rbFillV->isChecked()
        );
    });

    update_selection_number();
}

void AddComponentToConditionsDialog::update_selection_number(){
    size_t countR = 0;
    size_t totalCountC = 0;
    for(size_t ii = 0; ii < conditionsPerRoutines.size(); ++ii){
        size_t countC = 0;
        auto lw = conditionsPerRoutines[ii].second.get();
        for(int ii = 0; ii < lw->count(); ++ii){
            auto cb = lw->widget_at(ii)->layout()->itemAt(0)->widget();
            if(qobject_cast<QCheckBox*>(cb)->isChecked()){
                ++countC;
            }
        }
        if(countC > 0){
            ++countR;
        }
        totalCountC += countC;
    }

    QStringView r = countR > 1 ? QSL("routines") : QSL("routine");
    QStringView c = totalCountC > 1 ? QSL("conditions") : QSL("condition");

    laApplyTo->setText(QSL("Component will be added to <b>") % QString::number(totalCountC) %
                       QSL("</b> ") % c % QSL(" from <b>") % QString::number(countR) % QSL("</b> ") % r % QSL("."));
    condSelUi.validateButtonBox->setEnabled(totalCountC > 0);
}
