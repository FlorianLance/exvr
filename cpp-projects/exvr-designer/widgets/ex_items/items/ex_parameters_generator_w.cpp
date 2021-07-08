
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_parameters_generator_w.hpp"

// local
#include "items/ex_color_frame_w.hpp"
#include "items/ex_label_w.hpp"
#include "items/ex_line_edit_w.hpp"
#include "items/ex_select_color_w.hpp"
#include "items/ex_slider_w.hpp"
#include "items/ex_transformation_w.hpp"
#include "items/ex_list_labels_w.hpp"
#include "items/ex_spin_box_w.hpp"
#include "items/ex_checkbox_w.hpp"
#include "items/ex_combo_box_index_w.hpp"
#include "items/ex_combo_box_text_w.hpp"
#include "items/ex_text_edit_w.hpp"
#include "items/ex_radio_button_w.hpp"
#include "items/ex_curve_w.hpp"
#include "items/ex_curve_x_w.hpp"
#include "items/ex_tab_w.hpp"
#include "items/ex_vector2d_w.hpp"
#include "items/ex_resource_w.hpp"
#include "items/ex_resources_list_w.hpp"
#include "items/ex_component_w.hpp"
#include "items/ex_components_list_w.hpp"

#include "generation/gen_ui_item_dialog.hpp"

using namespace tool;
using namespace tool::ex;


ExParametersGeneratorWidgetW::ExParametersGeneratorWidgetW() : ExItemW<QWidget>(UiType::Generator){

    ui::W::init(&m_pbAddParam, "Add");
    ui::W::init(&m_pbMoveUp, "Move up");
    ui::W::init(&m_pbMoveDown, "Move down");
    ui::W::init(&m_pbRemoveParam, "Remove");
    m_lwParameters.set_widget_selection(true);

    QStringList items;
    for (auto& t : get_ui_types()) {
        if(is_generative(t)){
            items << from_view(get_name(t));
        }
    }
    ui::W::init(&m_cbTypeParam, items);

    auto l = new QVBoxLayout();
    l->setContentsMargins(5,5,5,5);
    w->setLayout(l);
    w->layout()->addWidget(ui::F::gen(ui::L::HB(),{
        ui::W::txt("Parameter to add "),&m_cbTypeParam}, LStretch{true}, LMargins{false}));
    w->layout()->addWidget(ui::F::gen(ui::L::HB(),{
        &m_pbAddParam, &m_pbMoveUp, &m_pbMoveDown, &m_pbRemoveParam}, LStretch{true}, LMargins{false}));
    w->layout()->addWidget(&m_lwParameters);

    connect(&m_pbAddParam, &QPushButton::clicked, this, [&]{
        auto txt = m_cbTypeParam.currentText().toStdString();
        add_ui_element(get_ui_type(txt).value(), "", -1, true);
    });

    connect(&m_pbMoveUp, &QPushButton::clicked, this, [&]{

        int id = m_lwParameters.current_selected_widget_id();
        if(id <= 0 || id >= m_namesParameters.count()){
            return;
        }

        QString prevName = m_namesParameters.at(id-1);
        QString name  = m_namesParameters.at(id);

        auto item1 = (*m_inputUiElements)[prevName];
        auto item2 = (*m_inputUiElements)[name];
        (*m_inputUiElements)[name]     = item1;
        (*m_inputUiElements)[prevName] = item2;

        m_lwParameters.move_from_to(id-1, id);
        m_lwParameters.set_selected_widget(id -1);

        m_namesParameters.swapItemsAt(id-1, id);

        emit move_up_ui_signal(prevName, name);
    });

    connect(&m_pbMoveDown, &QPushButton::clicked, this, [&]{

        int id = m_lwParameters.current_selected_widget_id();
        if(id < 0 || id >= m_namesParameters.count()-1){
            return;
        }

        QString name  = m_namesParameters.at(id);
        QString nextName = m_namesParameters.at(id+1);

        auto item1 = (*m_inputUiElements)[name];
        auto item2 = (*m_inputUiElements)[nextName];
        (*m_inputUiElements)[nextName] = item1;
        (*m_inputUiElements)[name]     = item2;

        m_lwParameters.move_from_to(id, id+1);
        m_lwParameters.set_selected_widget(id +1);

        m_namesParameters.swapItemsAt(id, id+1);

        emit move_down_ui_signal(nextName, name);
    });

    connect(&m_pbRemoveParam, &QPushButton::clicked, this, [&]{

        int id = m_lwParameters.current_selected_widget_id();
        if(id < 0 || id >= m_namesParameters.count()){
            return;
        }

        QString name = m_namesParameters.at(id);
        m_inputUiElements->erase(name);
        m_lwParameters.delete_at(id);
        m_namesParameters.removeAt(id);

        emit remove_ui_signal(name);
    });
}

ExParametersGeneratorWidgetW::~ExParametersGeneratorWidgetW(){

    if(m_inputUiElements != nullptr){

        for(auto &inputUiElement : *m_inputUiElements){
            if(inputUiElement.second->generatorName == generatorName){
                delete inputUiElement.second;
                inputUiElement.second = nullptr;
            }
        }
    }
}

ExParametersGeneratorWidgetW *ExParametersGeneratorWidgetW::init_widget(std::map<QString, ExBaseW *> *inputUiElements, QString genName, bool enabled){

    m_inputUiElements = inputUiElements;
    generatorName = genName;
    w->setEnabled(enabled);
    return this;
}


void ExParametersGeneratorWidgetW::init_connection(const QString &nameParam){
    Q_UNUSED(nameParam)
}

void ExParametersGeneratorWidgetW::update_from_arg(const Arg &arg){

    if(!m_inputUiElements->count(arg.name)){
        add_ui_element_from_arg(arg);
    }
    (*m_inputUiElements)[arg.name]->update_from_arg(arg);
}

void ExParametersGeneratorWidgetW::update_from_resources(){
    for(const auto &name : qAsConst(m_namesParameters)){
        (*m_inputUiElements)[name]->update_from_resources();
    }
}

void ExParametersGeneratorWidgetW::update_from_components(){
    for(const auto &name : qAsConst(m_namesParameters)){
        (*m_inputUiElements)[name]->update_from_components();
    }
}

Arg ExParametersGeneratorWidgetW::convert_to_arg() const{
    return ExItemW::convert_to_arg();
}

void ExParametersGeneratorWidgetW::add_ui_element_from_arg(const Arg &arg){
    add_ui_element(arg.associated_ui_type(), arg.name, arg.generator.order, false);
}

void ExParametersGeneratorWidgetW::add_ui_element(UiType uiType, QString uiName, int order, bool initFromDialog){

    // generate widget
    ExBaseW *exW = nullptr;
    QWidget *wElem = nullptr;

    switch (uiType) {
    case UiType::Line_edit :{
        wElem = dynamic_cast<ExLineEditW*>(exW = new ExLineEditW())->w.get();
    }break;
    case UiType::Slider_integer :{
        wElem = dynamic_cast<ExSliderIntegerW*>(exW = new ExSliderIntegerW())->w.get();
    }break;
    case UiType::Slider_double :{
        wElem = dynamic_cast<ExSliderFloatW*>(exW = new ExSliderFloatW())->w.get();
    }break;
    case UiType::Check_box :{
        wElem = dynamic_cast<ExCheckBoxW*>(exW = new ExCheckBoxW())->w.get();
    }break;
    case UiType::Spin_box:{
        wElem = dynamic_cast<ExSpinBoxW*>(exW = new ExSpinBoxW())->w.get();
    }break;
    case UiType::Double_spin_box:{
        wElem = dynamic_cast<ExDoubleSpinBoxW*>(exW = new ExDoubleSpinBoxW())->w.get();
    }break;
    case UiType::Float_spin_box :{
        wElem = dynamic_cast<ExFloatSpinBoxW*>(exW = new ExFloatSpinBoxW())->w.get();
    }break;
    case UiType::Text_edit:{
        wElem = dynamic_cast<ExTextEditW*>(exW = new ExTextEditW())->w.get();
    }break;
    case UiType::Color_pick:{
        wElem = dynamic_cast<ExSelectColorW*>(exW = new ExSelectColorW())->w.get();
    }break;
    case UiType::Combo_box_text:{
        wElem = dynamic_cast<ExComboBoxTextW*>(exW = new ExComboBoxTextW())->w.get();
    }break;
    case UiType::Combo_box_index:{
        wElem = dynamic_cast<ExComboBoxIndexW*>(exW = new ExComboBoxIndexW())->w.get();
    }break;
    case UiType::Label:{
        wElem = dynamic_cast<ExLabelW*>(exW = new ExLabelW())->w.get();
    }break;
    case UiType::Vector2D:{
        wElem = dynamic_cast<ExVector2dW*>(exW = new ExVector2dW())->w.get();
    }break;
    case UiType::Vector3D:{
        wElem = dynamic_cast<ExVector3dW*>(exW = new ExVector3dW())->w.get();
    }break;
    case UiType::Resource:{
        wElem = dynamic_cast<ExResourceW*>(exW = new ExResourceW())->w.get();
    }break;
    case UiType::Component:{
        wElem = dynamic_cast<ExComponentW*>(exW = new ExComponentW())->w.get();
    }break;
    case UiType::Transformation:{
        wElem = dynamic_cast<ExTransformationW*>(exW = new ExTransformationW())->w.get();
    }break;
    case UiType::ComponentsList:{
        wElem = dynamic_cast<ExComponentsListW*>(exW = new ExComponentsListW())->w.get();
    }break;
    case UiType::ResourcesList:{
        wElem = dynamic_cast<ExResourcesListW*>(exW = new ExResourcesListW())->w.get();
    }break;
    default:
        return;
    }
    exW->set_generator(generatorName);

    // init widget from dialog
    if(initFromDialog){

        QStringList names;
        for(auto &inputUiElement : *m_inputUiElements){
            names << inputUiElement.first;
        }

        GenUIItemDialog genD(type);
        genD.setMinimumWidth(500);
        genD.setMaximumWidth(900);

        switch (uiType) {
        case UiType::Slider_integer :{
            genD.add_gen_widget(new GenSpinboxW("Slider options"));
        }break;
        case UiType::Slider_double :{
            genD.add_gen_widget(new SpinboxDoubleGenW("Slider options"));
        }break;
        case UiType::Spin_box:{
             genD.add_gen_widget(new GenSpinboxW());
        }break;
        case UiType::Double_spin_box:{
             genD.add_gen_widget(new SpinboxDoubleGenW());
        }break;
        case UiType::Float_spin_box :{
            genD.add_gen_widget(new SpinboxFloatGenW());
        }break;
        case UiType::Vector2D:{
            genD.add_gen_widget(new Vector2dGenW());
        }break;
        case UiType::Vector3D:{
            genD.add_gen_widget(new Vector3dGenW());
        }break;
        case UiType::Resource:{
            genD.add_gen_widget(new ResourceGenW());
        }break;
        case UiType::Component:{
            genD.add_gen_widget(new ComponentGenW());
        }break;
        case UiType::Transformation:{
            genD.add_gen_widget(new TransformGenW());
        }break;
        case UiType::ComponentsList:{
            genD.add_gen_widget(new ComponentGenW());
        }break;
        case UiType::ResourcesList:{
            genD.add_gen_widget(new ResourceGenW());
        }break;
        case UiType::Text_edit:{
            genD.add_gen_widget(new TextGenW("Text:"));
        }break;
        case UiType::Line_edit:{
            genD.add_gen_widget(new TextGenW("Value:"));
        }break;
        case UiType::Label:{
            genD.add_gen_widget(new TextGenW("Title:"));
        }break;
        case UiType::Combo_box_text:{
            genD.add_gen_widget(new ComboTextGen());
        }break;
        case UiType::Combo_box_index:{
            genD.add_gen_widget(new ComboTextGen());
        }break;
        default:
            break;
        }


        if(!genD.show_dialog(names)){
            delete exW;
            return;
        }

        auto genUiArg = genD.generate_arg(UiElementKey{key()});
        exW->update_from_arg(genUiArg);
        uiName = genUiArg.name;
    }

    // add widget to input ui elements
    exW->itemName = uiName;
    (*m_inputUiElements)[exW->itemName] = exW;

    // set order
    if(order >= 0 ){
        currentId = order;
    }else{
        currentId++;
    }
    exW->generatorOrder = currentId;

    // generate widget line
    auto fl =  ui::L::HB();
    auto f  = ui::F::gen(fl,{ui::W::txt("<b>" + exW->itemName + "</b>"), wElem}, LStretch{false}, LMargins{true});
    fl->setStretch(0, 1);
    fl->setStretch(1, 30);

    // add item name to generator list
    bool added = false;
    for(int ii = 0; ii < m_namesParameters.size(); ++ii){
        if(currentId < (*m_inputUiElements)[m_namesParameters[ii]]->generatorOrder){
            m_namesParameters.insert(ii, exW->itemName);
            m_lwParameters.insert_widget(ii, f);
            added = true;
            break;
        }
    }

    if(!added){
        m_namesParameters << exW->itemName;
        m_lwParameters.add_widget(f);
    }

    // setup widget connections
    exW->init_connection(exW->itemName);
    connect(exW, &ExBaseW::ui_change_signal, this, &ExParametersGeneratorWidgetW::ui_change_signal);

    emit add_ui_signal(exW->itemName);
}

#include "moc_ex_parameters_generator_w.cpp"
