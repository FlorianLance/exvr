
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "base_embedded_widget.hpp"

// base
#include "utility/benchmark.hpp"

using namespace tool::ex;

const QString BaseNodeContainerW::buttonStyle1 =
    "QPushButton#settingButton {\
        background-color: rgb(0, 128, 192);\
        border-style: outset;\
        border-width: 2px;\
        border-color: black;\
        border-radius: 5px;\
    }\
    QPushButton#settingButton:pressed {\
        background-color: rgb(72, 196, 255);\
        border-style: inset;\
    }\
    QPushButton#settingButton:hover:!pressed {\
        background-color: rgb(155, 222, 255);\
        border-style: inset;\
    }";

const QString BaseNodeContainerW::buttonStyle2 =
    "QPushButton#settingButton {\
        background-color: rgb(192, 128, 0);\
        border-style: outset;\
        border-width: 2px;\
        border-color: black;\
        border-radius: 5px;\
    }\
    QPushButton#settingButton:pressed {\
        background-color: rgb(255, 196, 72);\
        border-style: inset;\
    }\
    QPushButton#settingButton:hover:!pressed {\
        background-color: rgb(255, 222, 155);\
        border-style: inset;\
    }";

NodeDataDisplayDialog::NodeDataDisplayDialog(QString caption, bool popup) : m_popup(popup){

    layout = new QVBoxLayout(this);
    setWindowTitle(caption);

    if(m_popup){
        setWindowFlags(Qt::Popup);
    }else{
        setWindowFlag(Qt::Window);
    }
}

void NodeDataDisplayDialog::add_row_in_dialog(QString name, QWidget *w, bool horizontalLayout){

    // store it
    if(name.length() > 0){
        auto formW = new QWidget();

        if(horizontalLayout){
            auto hl = ui::L::HB();
            hl->setContentsMargins(0,0,0,0);
            hl->setStretch(0, 1);
            hl->setStretch(1, 20);
            hl->addWidget(new QLabel(name));
            hl->addWidget(w);
            formW->setLayout(hl);
        }else{
            auto vl = ui::L::VB();
            vl->setContentsMargins(0,0,0,0);
            vl->setStretch(0, 1);
            vl->setStretch(1, 20);
            vl->addWidget(new QLabel(name));
            vl->addWidget(w);
            formW->setLayout(vl);
        }
        layout->addWidget(formW);

    }else{
        layout->addWidget(w);
    }
}

bool NodeDataDisplayDialog::node_settings_execute(QPoint pos){

    move(pos);
    if(m_popup){
        return exec() == QDialog::Accepted;
    }else{
        show();
        raise();
        setFocus();
        return true;
    }
}


void BaseNodeContainerW::initialize_container(QString caption, bool popup){

    setContentsMargins(0,0,0,0);
    setObjectName("parent-widget");
    setStyleSheet("#parent-widget {background-color: rgba(0,0,0,0)}");

    m_dataDisplayD = std::make_unique<NodeDataDisplayDialog>(caption, popup);

    m_valueText.setTextFormat(Qt::PlainText);
    //m_valueText.setFrameStyle(QFrame::Panel | QFrame::Sunken);

    // test
//    m_valueText.setReadOnly(true);
//    QFontMetrics metrics(m_valueText.font());
//    int lineHeight = metrics.lineSpacing();
//    m_valueText.setFixedHeight(lineHeight*2);
//    m_valueText.setFixedWidth(100);

    // layout
    setLayout(new QHBoxLayout());
    layout()->addWidget(&m_openDialogButton);
    layout()->addWidget(&m_valueText);
    layout()->setContentsMargins(0,0,0,0);

    m_openDialogButton.setText("");
    m_helpButton.setText("");

    QSize sizeB(20,20);
    m_openDialogButton.setMaximumSize(sizeB);
    m_helpButton.setMaximumSize(sizeB);

    // m_valueText.setFixedSize(100,20);

    m_openDialogButton.setObjectName("settingButton");
    m_openDialogButton.setStyleSheet(buttonStyle1);
    connect(&m_openDialogButton, &QPushButton::clicked, this, [&]{
//        if(m_dataDisplayD == nullptr){
//            Bench::start("BaseNodeContainerW_1"sv);
//            m_dataDisplayD = std::make_unique<NodeDataDisplayDialog>(caption, popup);
//            for(auto &row : m_dialogWidgetsRows){
//                m_dataDisplayD->add_row_in_dialog(std::get<0>(row),std::get<1>(row),std::get<2>(row));
//            }
//            Bench::stop();
//        }

        m_dataDisplayD->node_settings_execute(QCursor::pos()+ QPoint(0,10));
    });
}


BaseNodeContainerW::~BaseNodeContainerW(){
    close();
}

void BaseNodeContainerW::close(){
    m_dataDisplayD->close();
    m_dataDisplayD->hide();
}


void BaseNodeContainerW::add_row_in_dialog(QString name, QWidget *w, bool horizontalLayout){
    m_dataDisplayD->add_row_in_dialog(name,w, horizontalLayout);
}

bool BaseNodeContainerW::set_text_value(QStringView value){

//    bool askForResize = m_valueText.text().size() != value.size();
//    m_valueText.blockSignals(true);

    Bench::start("BaseNodeContainerW::set_text_value");
    m_valueText.setText(value.toString());
    Bench::stop();
//    m_valueText.blockSignals(false);
    return true;
//    return askForResize;
}

void BaseNodeContainerW::disable(){
    setEnabled(false);
    m_openDialogButton.setStyleSheet(buttonStyle2);
}

void BaseNodeContainerW::enable(){
    setEnabled(true);
    m_openDialogButton.setStyleSheet(buttonStyle1);
}

void BaseNodeContainerW::set_title(QString title){
    m_dialogTitle = title;
    m_dataDisplayD->setWindowTitle(title);
}

bool BaseNodeContainerW::update_with_info(QStringView value){
    return set_text_value(value);
}

void BaseNodeContainerW::paintEvent(QPaintEvent *event){
    tool::Bench::start("BaseNodeContainerW::paintEvent");
    QWidget::paintEvent(event);
    tool::Bench::stop();
}

#include "moc_base_embedded_widget.cpp"

