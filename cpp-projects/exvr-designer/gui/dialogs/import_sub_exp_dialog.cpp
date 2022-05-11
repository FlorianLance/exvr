
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

#include "import_sub_exp_dialog.hpp"

// qt-utility
#include "qt_logger.hpp"
#include "gui/widgets/list_widget.hpp"

// local
#include "data/components_manager.hpp"
#include "experiment/experiment.hpp"
#include "IO/xml_io_manager.hpp"

using namespace tool;
using namespace tool::ex;

ImportSubExpDialog::ImportSubExpDialog(QString path){

    validatedConfigs.clear();

    setWindowTitle(QSL("Import experiment sub-parts"));
    setModal(true);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);

    setLayout(new QVBoxLayout());

    auto exp = ExperimentManager::get()->current();

    ExperimentManager::get()->init_imported(exp->states.numVersion);
    auto importedExp = ExperimentManager::get()->imported();

    XmlIoManager xmlR(importedExp);
    QtLogger::message("exp read");
    if(!xmlR.load_experiment_file(path)){
        QtLogger::error(QSL("Cannot load exp ") % path);
        return;
    }

    QTabWidget *tw = new QTabWidget();
    layout()->addWidget(tw);


    ui::ListWidget *lwComponents = new ui::ListWidget();
    lwComponents->set_margins(2,2,2,2,2);
    tw->addTab(lwComponents, "Components");
    for(const auto &component : importedExp->compM.components){
//        QtLogger::message(QSL("component ") %component->name());
        auto compL = new QLabel(component->name() % QSL(" [") % from_view(Component::get_full_name(component->type)) % QSL("] ") % QSL("(") % QString::number(component->key()) % QSL(")"));
        lwComponents->add_widget(compL);
        for(const auto &config : component->configs){
            auto configCb = new QCheckBox(config->name);
            lwComponents->add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("\t"), configCb}, LStretch{true}, LMargins{false},QFrame::NoFrame));
            validatedConfigs[component->c_key()][ConfigKey{config->key()}] = configCb;
        }
    }

    auto pbValidate = new QPushButton("Import selection");
    auto pbCancel   = new QPushButton("Cancel");
    layout()->addWidget(ui::F::gen(ui::L::HB(),{pbValidate, pbCancel}, LStretch{true}, LMargins{false},QFrame::NoFrame));


    // settings dialog
    connect(pbValidate, &QPushButton::clicked, this,&ImportSubExpDialog::accept);
    connect(pbCancel,  &QPushButton::clicked, this,  &ImportSubExpDialog::reject);

    connect(this, &ImportSubExpDialog::finished, this, [&](int result){

        if(result != 1){
            QtLogger::message("CANCEL");
            return;
        }

        for(const auto &componentConfigs : validatedConfigs){

            std::vector<ConfigKey> configsKeys;
            for(const auto &config : componentConfigs.second){
                if(config.second->isChecked()){
                    configsKeys.push_back(config.first);
                }
            }
            if(configsKeys.size() == 0){
                continue;
            }

            auto ie = ExperimentManager::get()->imported();
            auto iComponent = ie->compM.get_component(componentConfigs.first);
//            ExperimentManager::get()->current()->add_component(Component::copy_with_new_element_id(*iComponent, iComponent->name() % QSL("(imported)"), configsKeys), RowId{0});
        }

        ExperimentManager::get()->clean_imported();
        QtLogger::message("OK");
    });

}
