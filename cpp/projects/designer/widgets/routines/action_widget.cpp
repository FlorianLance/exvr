
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "action_widget.hpp"

// Qt
#include <QDebug>
#include <QMimeData>
#include <QDrag>

// base
#include "utility/types_utility.hpp"

// qt-utility
#include "widgets/custom_combobox_w.hpp"

// local
#include "component.hpp"
#include "config.hpp"
#include "global_signals.hpp"

using namespace tool;
using namespace tool::ex;

ActionW::ActionW(ElementKey routineKey, ConditionKey conditionKey, Action *action) :
      m_routineKey(routineKey), m_conditionKey(conditionKey), m_actionKey(ActionKey{action->key()}){

    m_ui.setupUi(this);    

    auto icon = QIcon(from_view(Component::get_icon_path(action->component->type)));
    m_ui.tbIcon->setIconSize(QSize(70,70));
    m_ui.tbIcon->setIcon(icon);

    m_ui.pbMinimizedIcon->setIconSize(QSize(20,20));
    m_ui.pbMinimizedIcon->setIcon(icon);

    m_ui.cbConfig->setFocusPolicy(Qt::StrongFocus);
    delete m_ui.cbConfig;
    m_ui.cbConfig = new ui::NoScrollFocusWidget<QComboBox>(nullptr);
    m_ui.hlTop->insertWidget(5, m_ui.cbConfig);

    setObjectName(QSL("action"));
    setStyleSheet(QSL("QWidget[objectName=\"action\"] {background-color:white;}"));

    // generate widgets
    auto opt = Component::get_timeline_opt(action->component->type);
    if(opt == Component::TimelineO::Update || opt == Component::TimelineO::Both){
        m_timelineUpdateW = new TimelineW(routine_key(), condition_key(), action_key(), action->timelineUpdate.get(), opt == Component::TimelineO::Update, true);
        m_ui.vlTimeline->addWidget(m_timelineUpdateW);
    }    

    if(opt == Component::TimelineO::Visibility || opt == Component::TimelineO::Both){
        m_timelineVisibilityW = new TimelineW(routine_key(), condition_key(), action_key(), action->timelineVisibility.get(), true, false);
        m_ui.vlTimeline->addWidget(m_timelineVisibilityW);
    }

    if(opt == Component::TimelineO::None){
        m_ui.pbFill->setEnabled(false);
        m_ui.pbClean->setEnabled(false);
        m_ui.cbVisibility->setEnabled(false);
        m_ui.cbUpdate->setEnabled(false);
        m_ui.laApplyTo->setEnabled(false);
    }

    // others connections
    connect(m_ui.pbUp, &QPushButton::clicked, this, [&](){
        emit GSignals::get()->move_action_up_signal(routine_key(), condition_key(),action_key());
    });
    connect(m_ui.pbDown, &QPushButton::clicked, this, [&](){
        emit GSignals::get()->move_action_down_signal(routine_key(), condition_key(),action_key());
    });
    connect(m_ui.cbConfig, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index){
        emit GSignals::get()->select_config_signal(routine_key(), condition_key(), action_key(), RowId{index});
    });
    connect(m_ui.pbDelete, &QPushButton::clicked, this, [=]{
        emit GSignals::get()->delete_action_signal(routine_key(), condition_key(),action_key());
    });
    connect(m_ui.pbFill, &QPushButton::clicked, this, [=]{

        bool update = false, visibility = false;
        if(m_ui.cbUpdate->isChecked()     && (opt == Component::TimelineO::Update || opt == Component::TimelineO::Both)){
            update = true;
        }
        if(m_ui.cbVisibility->isChecked() && (opt == Component::TimelineO::Visibility || opt == Component::TimelineO::Both)){
            visibility = true;
        }
        emit GSignals::get()->fill_action_signal(routine_key(), condition_key(),action_key(), update, visibility);
    });
    connect(m_ui.pbClean, &QPushButton::clicked, this, [=]{
        bool update = false, visibility = false;
        if(m_ui.cbUpdate->isChecked()     && (opt == Component::TimelineO::Update || opt == Component::TimelineO::Both)){
            update = true;
        }
        if(m_ui.cbVisibility->isChecked() && (opt == Component::TimelineO::Visibility || opt == Component::TimelineO::Both)){
            visibility = true;
        }
        emit GSignals::get()->clean_action_signal(routine_key(), condition_key(),action_key(), update, visibility);
    });
    connect(m_ui.pbMinimizeExtend, &QPushButton::clicked, this, [=]{
        set_minimized_state(!m_minimized);
    });
    m_ui.pbMinimizedIcon->setVisible(false);

    // set stretch
    m_ui.hlTop->setStretch(0, 1);
    m_ui.hlTop->setStretch(1, 1);
    m_ui.hlTop->setStretch(2, 1);
    m_ui.hlTop->setStretch(3, 1);
    m_ui.hlTop->setStretch(4, 1);
    m_ui.hlTop->setStretch(5, 100);
    m_ui.hlTop->setStretch(6, 100);
    m_ui.hlTop->setStretch(7, 1);
    m_ui.hlTop->setStretch(8, 1);
    m_ui.hlTop->setStretch(9, 1);
    m_ui.hlTop->setStretch(10, 1);
    m_ui.hlTop->setStretch(11, 1);
    m_ui.hlTop->setStretch(12, 1);
    m_ui.hlTop->setStretch(613, 1);
}

void ActionW::mousePressEvent(QMouseEvent *event){

    // left click
    if(event->button()== Qt::MouseButton::LeftButton){
        QPixmap pixmap = m_ui.tbIcon->icon().pixmap(QSize(22, 22), QIcon::Normal, QIcon::On);
        QMimeData *mimeData = new QMimeData();
        mimeData->setText(QSL("action_") % QString::number(action_key().v));
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(QPoint(drag->pixmap().width()/2,drag->pixmap().height()/2));
        drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
    }
}

void ActionW::set_minimized_state(bool state){
    m_minimized = state;
    m_ui.pbMinimizeExtend->setText(m_minimized ? QSL("+") : QSL("-"));
    m_ui.wBottom->setVisible(!m_minimized);
    m_ui.pbMinimizedIcon->setVisible(m_minimized);
    m_ui.pbFill->setVisible(!m_minimized);
    m_ui.pbClean->setVisible(!m_minimized);
    m_ui.cbUpdate->setVisible(!m_minimized);
    m_ui.cbVisibility->setVisible(!m_minimized);
    m_ui.laApplyTo->setVisible(!m_minimized);
}

void ActionW::update_from_action(int id, Action *action, qreal scale, qreal factorSize, SecondsTS max){

    m_ui.laId->setText(QString::number(id) % QSL("#"));

    // init config combobox
    m_ui.cbConfig->blockSignals(true);
    m_ui.cbConfig->clear();
    m_ui.cbConfig->addItems(action->component->get_configs_name());
    m_ui.cbConfig->blockSignals(false);

    for(size_t ii = 0; ii < action->component->configs.size(); ++ii){
        if(action->config->key() == action->component->configs[ii]->key()){
            m_ui.cbConfig->setCurrentIndex(static_cast<int>(ii));
            break;
        }
    }

    m_ui.laName->setText(QSL("<b>") %  action->component->name() % QSL("</b>"));

    // update timelines
    auto opt = Component::get_timeline_opt(action->component->type);
    if(opt == Component::TimelineO::Update || opt == Component::TimelineO::Both){
        m_timelineUpdateW->update_from_timeline(action->timelineUpdate.get(), scale, factorSize, max);
    }
    if(opt == Component::TimelineO::Visibility || opt == Component::TimelineO::Both){
        m_timelineVisibilityW->update_from_timeline(action->timelineVisibility.get(), scale, factorSize, max);
    }

}
#include "moc_action_widget.cpp"
