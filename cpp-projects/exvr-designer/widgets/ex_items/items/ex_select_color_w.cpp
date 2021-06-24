
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_select_color_w.hpp"

using namespace tool::str;
using namespace tool::ex;

ExSelectColorW::ExSelectColorW() : ExItemW<QPushButton>(UiType::Color_pick){
//    m_colDialog.setOption(QColorDialog::ShowAlphaChannel);
    connect(w.get(), &QPushButton::clicked, &m_colDialog, &QColorDialog::show);
    w->setMinimumSize(QSize(50,50));
    w->setMaximumSize(QSize(50,50));
//    hintHeightSize = 70;
}

ExSelectColorW::~ExSelectColorW(){
    m_colDialog.close();
}

QColor ExSelectColorW::current_color() const{
    return m_colDialog.currentColor();
}

ExSelectColorW *ExSelectColorW::init_widget(QString dialogName, QColor color, bool enabled){

    m_colDialog.setCurrentColor(color);
    m_colDialog.setWindowTitle(dialogName);
    m_colDialog.setOptions(QColorDialog::ShowAlphaChannel | QColorDialog::NoButtons);
    m_colDialog.setModal(true);
    w->setEnabled(enabled);

    QPixmap p(50,50);
    p.fill(color);
    w->setIcon(QIcon(p));
    w->setIconSize(QSize(40,40));

    return this;
}

std::optional<Arg> ExSelectColorW::generate_init_arg_from_dialog(QStringList othersParameters){

    GenUIItemDialog genD(QSL("Add ") % from_view(get_name(type)));
    if(genD.show_dialog(std::move(othersParameters))){
        Arg arg = Arg::generate_init_ui_arg(UiElementKey{key()}, type, genD.name());
        arg.set_value(Convertor::to_str(m_colDialog.currentColor()));
        arg.set_separator("");
        return {arg};
    }

    return {};
}

void ExSelectColorW::init_connection(const QString &nameParam){
    connect(&m_colDialog, &QColorDialog::currentColorChanged, this, [&,nameParam](const QColor &c){
        QPixmap p(50,50);
        p.fill(c);
        w->setIcon(QIcon(p));
        w->setIconSize(QSize(40,40));
        emit ui_change_signal(nameParam);}
    );
}

void ExSelectColorW::update_from_arg(const Arg &arg){

    ExItemW::update_from_arg(arg);

    w->blockSignals(true);

    QColor c = arg.to_color_value();
    m_colDialog.setCurrentColor(c);

    QPixmap p(50,50);
    p.fill(c);
    w->setIcon(QIcon(p));
    w->setIconSize(QSize(40,40));

    if(generatorName.length() > 0){
        // ...
    }

    w->blockSignals(false);
}

Arg ExSelectColorW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();
    arg.init_from(m_colDialog.currentColor());

    // generator
    if(generatorName.length() > 0){
        // ...
    }
    return arg;
}

void ExSelectColorW::close(){
    m_colDialog.close();
}
#include "moc_ex_select_color_w.cpp"
