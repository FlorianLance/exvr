
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QObject>
#include <QDesktopWidget>

#include <QMetaEnum>

// qt-utility
#include "qt_logger.hpp"

// local
#include "experiment/global_signals.hpp"
#include "widgets/designer_window.hpp"
#include "widgets/dialogs/copy_to_conditions_dialog.hpp"
#include "widgets/dialogs/benchmark_dialog.hpp"
#include "IO/xml_io_manager.hpp"
#include "resources/resources_manager.hpp"
#include "ui_copy_to_conditions.h"


namespace tool::ex {

class ExVrController : public QObject{

    Q_OBJECT

    template<typename EnumType>
    QString ToString(const EnumType& enumValue)
    {
        const char* enumName = qt_getEnumName(enumValue);
        const QMetaObject* metaObject = qt_getEnumMetaObject(enumValue);
        if (metaObject)
        {
            const int enumIndex = metaObject->indexOfEnumerator(enumName);
            return QString("%1::%2::%3").arg(metaObject->className(), enumName, metaObject->enumerator(enumIndex).valueToKey(enumValue));
        }

        return QString("%1::%2").arg(enumName).arg(static_cast<int>(enumValue));
    }

public :

    ExVrController(const QString &nVersion, bool lncoComponents);

    inline Experiment *exp(){return m_experiment.get();}
    inline DesignerWindow *ui(){return m_designerWindow.get();}
    inline ExpLauncher *exp_launcher(){return m_expLauncher.get();}
    inline XmlIoManager *xml(){return m_xmlManager.get();}
    inline QtLogger *log(){return QtLogger::get();}
    // dialogs
    inline SettingsDialog *set(){return m_settingsD.get();}
    inline BenchmarkDialog *benchmark(){return m_benchmarkD.get();}
    inline DocumentationDialog *doc(){return m_documentationD.get();}
    inline ResourcesManagerDialog *res(){return m_resourcesD.get();}

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event){

        Bench::start("ExVrController::Filter::ALL");
        bool ret;
        if(event->type() == QEvent::Paint){
            Bench::start("ExVrController::Filter::Paint");
            ret = QObject::eventFilter(watched, event);
            Bench::stop();
        }else{
            ret = QObject::eventFilter(watched, event);
        }
        Bench::stop();
//        if(!countEvents.contains(event->type())){
//            countEvents[event->type()] = {};
//        }else{
//            if(!countEvents[event->type()].contains(watched->objectName())){
//                countEvents[event->type()][watched->objectName()] = 0;
//            }else{
//                countEvents[event->type()][watched->objectName()]++;
//            }
//        }

        return ret;
    }

    std::unordered_map<QEvent::Type, std::unordered_map<QString, int>> countEvents;

private slots:

    void close_exvr();
    void generate_instances();
    void start_specific_instance();

    void save_full_exp_with_default_instance();

    void go_to_current_specific_instance_element();
    void got_to_specific_instance_element();

    void load_full_exp_with_default_instance_to_unity();
    void load_selected_routine_with_default_instance_to_unity();
    void load_from_selected_routine_with_default_instance_to_unity();
    void load_until_selected_routine_with_default_instance_to_unity();

    void show_component_informations(ComponentKey componentKey);

signals:

    void load_experiment_unity_signal(QString expFilePath, QString instanceFilePath);
    void close_exp_launcher_signal();
    void go_to_specific_instance_element_signal(int elementOrderId);
    void play_delay_experiment_signal(int delaySeconds);

    void start_experiment_launcher_signal(Settings settings);

    void start_communication_signal();
    void stop_communication_signal();

private:

    void generate_global_signals_connections();
    void generate_main_window_connections();
    void generate_components_manager_connections();
    void generate_flow_diagram_connections();

    void generate_controller_connections();
    void generate_resources_manager_connections();
    void generate_logger_connections();
    void generate_dialogs_connections();

private :    

    // data
    std::unique_ptr<Experiment> m_experiment = nullptr;
    std::unique_ptr<Instance> m_currentInstance = nullptr;

    // I/O
    std::unique_ptr<XmlIoManager> m_xmlManager = nullptr;

    // main window  ui
    std::unique_ptr<DesignerWindow> m_designerWindow = nullptr;

    // dialogs ui
    std::unique_ptr<CopyToConditionDialog> m_copyToCondD    = nullptr;
    std::unique_ptr<QDialog> m_componentsInfoD              = nullptr;
    std::unique_ptr<QDialog> m_goToD                        = nullptr;
    std::unique_ptr<QDialog> m_playDelayD                   = nullptr;
    std::unique_ptr<BenchmarkDialog> m_benchmarkD           = nullptr;
    std::unique_ptr<SettingsDialog> m_settingsD             = nullptr;
    std::unique_ptr<ResourcesManagerDialog> m_resourcesD    = nullptr;
    std::unique_ptr<DocumentationDialog> m_documentationD   = nullptr;
    std::unique_ptr<QDialog> m_addActionDetailsD            = nullptr;

    // experiment launcher
    std::unique_ptr<ExpLauncher> m_expLauncher = nullptr;
    QThread m_expLauncherT;

    int lastDelayS = 10;

    QTimer experimentUpdateTimer;


};

}
