

/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "gen_ui_item_dialog.hpp"

// Qt
#include <QDialogButtonBox>

// local
#include "qt_ui.hpp"
#include "gen_ex_widget.hpp"

using namespace tool::ex;

GenUIItemDialog::GenUIItemDialog(QString title){

    setWindowTitle(title);
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("Name parameter"), m_leName = new QLineEdit()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    m_layout->addWidget(ui::F::gen(ui::L::HB(), {m_laValid = ui::W::txt("")}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
}

GenUIItemDialog::GenUIItemDialog(UiType type) : m_type(type){

    setWindowTitle(QSL("Add ") % from_view(get_name(m_type)));
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("Name parameter"), m_leName = new QLineEdit()}, LStretch{true}, LMargins{false}, QFrame::NoFrame));
    m_layout->addWidget(ui::F::gen(ui::L::HB(), {m_laValid = ui::W::txt("")}, LStretch{true}, LMargins{false}, QFrame::NoFrame));

    switch (m_type) {
    case UiType::Component_config:
        break;
    case UiType::Check_box:
        break;
    case UiType::Text_edit:
        break;
    case UiType::Spin_box:        
        add_widget(m_genW = new GenSpinboxW());
        break;
    case UiType::Float_spin_box:
        add_widget(m_genW = new SpinboxFloatGenW());
        break;
    case UiType::Double_spin_box:
        add_widget(m_genW = new SpinboxDoubleGenW());
        break;
    case UiType::Line_edit:
        break;
    case UiType::Slider_integer:
        add_widget(m_genW = new GenSpinboxW("Slider options"));
        break;
    case UiType::Slider_double:
        add_widget(m_genW = new SpinboxDoubleGenW("Slider options"));
        break;
    case UiType::Color_pick:
        break;
    case UiType::Vector2D:
        add_widget(m_genW = new Vector2dGenW());
        break;
    case UiType::Vector3D:
        add_widget(m_genW = new Vector3dGenW());
        break;
    case UiType::Transformation:
        add_widget(m_genW = new TransformGenW());
        break;
    case UiType::Combo_box_text:
        break;
    case UiType::Combo_box_index:
        break;
    case UiType::Button:
        break;
    case UiType::Radio_button:
        break;
    case UiType::List_labels:
        break;
    case UiType::Label:
        break;
    case UiType::Color_frame:
        break;
    case UiType::Curve:
        break;
    case UiType::Camera_position:
        break;
    case UiType::PushButton:
        break;
    case UiType::Time:
        break;
    case UiType::Resource:
        add_widget(m_genW = new ResourceGenW());
        break;
    case UiType::Component:
        add_widget(m_genW = new ComponentGenW());
        break;
    case UiType::ComponentsList:
        add_widget(m_genW = new ComponentGenW());
        break;
    case UiType::ResourcesList:
        add_widget(m_genW = new ResourceGenW());
        break;
    // ################################ NO
    case UiType::Generator:
        break;
    case UiType::Non_ui_labels:
        break;
    case UiType::NonUI:
        break;
    case UiType::Tab:
        break;
    case UiType::SizeEnum:
        break;
    }
}

bool GenUIItemDialog::show_dialog(QStringList othersParameters){

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    m_layout->addWidget(buttonBox);

    m_laValid->setText(m_notEmptyStr);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &GenUIItemDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GenUIItemDialog::reject);
    connect(m_leName,   &QLineEdit::textChanged, this, [&, buttonBox]{
        const bool alreadyUsed = othersParameters.contains(m_leName->text());
        const bool empty = m_leName->text().isEmpty();
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!alreadyUsed && !empty);
        m_laValid->setText(empty ? m_notEmptyStr : (alreadyUsed ? m_aldreayUsedStr : ""));
    });
    return exec() == QDialog::Accepted;
}

void GenUIItemDialog::add_row(QString name, QWidget *w){
    m_layout->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt(name),w}, LStretch{true}, LMargins{true}, QFrame::Box));
}

void GenUIItemDialog::add_widget(QWidget *w){
    m_layout->addWidget(ui::F::gen(ui::L::HB(), {w}, LStretch{true}, LMargins{true}, QFrame::Box));
}

Arg GenUIItemDialog::generate_arg(UiElementKey key) const{
    auto arg = Arg::generate_init_ui_arg(key, m_type, name());
    dynamic_cast<BaseGenW*>(m_genW)->update_arg(arg);
    return arg;
}

QString GenUIItemDialog::name() const{
    return m_leName->text();
}
