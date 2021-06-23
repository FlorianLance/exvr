
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"
#include "ex_double_spin_box_w.hpp"
#include "ex_combo_box_index_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_line_edit_w.hpp"
#include "ex_resource_w.hpp"

namespace tool::ex {

class BiopacMP36InitConfigParametersW : public ConfigParametersW{

public :

    ExCheckBoxW m_debugBypassDevice;

    ExComboBoxIndexW m_device;
    ExComboBoxIndexW m_connection;
    ExComboBoxIndexW m_readIoMode;

    std_a1<ExCheckBoxW, 16> m_channels;
    std_a1<ExLineEditW, 16> m_channelsName;
    std_a1<ExLineEditW, 16> m_channelsPresetUid;
    std_v1<QWidget*> m_channelsParentWidgets;

    ExLineEditW m_serialNumber;
    ExSpinBoxW m_samplesPerCall;
    ExSpinBoxW m_samplingRate;
    ExSpinBoxW m_maxNbSecondsToSave;

    ExResourceW m_presetFile;

    void insert_widgets() override{

        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Device:"), m_device(), ui::W::txt("Connection:"), m_connection()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Serial MP150:"), m_serialNumber()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Read digital mode:"), m_readIoMode()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Nb samples per call:"), m_samplesPerCall(), ui::W::txt("Sampling rate (Hz):"), m_samplingRate()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{ui::W::txt("Max number seconds to save:"), m_maxNbSecondsToSave()}, LStretch{true}, LMargins{false},QFrame::NoFrame));
        add_widget(ui::F::gen(ui::L::HB(),{m_presetFile()}, LStretch{false}, LMargins{false},QFrame::NoFrame));

        QScrollArea *area = new QScrollArea();
        area->setWidgetResizable(true);

        QWidget *w = new QWidget();
        auto scrollL = ui::L::VB();
        w->setLayout(scrollL);
        area->setWidget(w);
        add_widget(area);
        for(size_t ii = 0; ii < 16; ++ii){

            auto pw = ui::F::gen(ui::L::HB(),{
                m_channels[ii](),
                ui::W::txt("Name:") ,m_channelsName[ii](),
                ui::W::txt("Preset uid: "), m_channelsPresetUid[ii]()
            }, LStretch{true}, LMargins{false},QFrame::NoFrame);

            scrollL->addWidget(pw);
            m_channelsParentWidgets.emplace_back(pw);
        }

        add_widget(m_debugBypassDevice());
    }

    void init_and_register_widgets() override{

        m_inputUiElements["device_type"] = m_device.init_widget({"MP36","MP150","MP160"});
        m_inputUiElements["device_connection"] = m_connection.init_widget({"USB","UDP"});
        m_inputUiElements["serial"] = m_serialNumber.init_widget("AUTO");
        m_inputUiElements["read_digital_mode"] = m_readIoMode.init_widget({"DISABLED", "LOW_BYTES", "HIGHT_BYTES"},0);

        m_inputUiElements["preset_xml_file"] = m_presetFile.init_widget(Resource::Type::Text, "Preset xml file (optional): ");
        m_inputUiElements["nb_samples_per_call"] = m_samplesPerCall.init_widget(MinV<int>{1}, V<int>{10}, MaxV<int>{1000}, StepV<int>{1});

        m_inputUiElements["sampling_rate"] = m_samplingRate.init_widget(MinV<int>{10}, V<int>{250}, MaxV<int>{400000}, StepV<int>{10},1);
        m_inputUiElements["max_nb_seconds_to_save"] = m_maxNbSecondsToSave.init_widget(MinV<int>{100}, V<int>{1000}, MaxV<int>{10000}, StepV<int>{1});

        for(size_t ii = 0; ii < 16; ++ii){
            auto idStr = QString::number(ii);
            m_inputUiElements[QSL("channel") % idStr] = m_channels[ii].init_widget(QSL("Enable channel ") % QString::number(ii+1), false);
            m_inputUiElements[QSL("channel") % idStr % QSL("_name")] = m_channelsName[ii].init_widget(QSL("channel") % QString::number(ii+1));
            m_inputUiElements[QSL("channel") % idStr % QSL("_preset_uid")] = m_channelsPresetUid[ii].init_widget("");
        }

        m_inputUiElements["debug_bypass"] = m_debugBypassDevice.init_widget("Enable it for testing the experiment without the device", false);
    }

    void create_connections() override{
        connect(&m_device, &ExComboBoxIndexW::ui_change_signal, this, [&]{
            late_update_ui();
        });
    }

    void late_update_ui() override{
        int id = m_device.w->currentIndex();
        bool extraChannels = id > 0;
        for(size_t ii = 4; ii < m_channels.size(); ++ii){
            m_channelsParentWidgets[ii]->setEnabled(extraChannels);
        }
    }
};


class BiopacMP36ConfigParametersW : public ConfigParametersW{

public :


    void insert_widgets() override{

    }

    void init_and_register_widgets() override{

    }

    void create_connections() override{

    }


    void late_update_ui() override{}
};

}
