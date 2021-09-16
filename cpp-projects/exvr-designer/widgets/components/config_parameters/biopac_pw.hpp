
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// qt-utility
#include "ex_widgets/ex_combo_box_index_w.hpp"
#include "ex_widgets/ex_checkbox_w.hpp"
#include "ex_widgets/ex_spin_box_w.hpp"
#include "ex_widgets/ex_line_edit_w.hpp"

// local
#include "ex_widgets/ex_resource_w.hpp"
#include "config_pw.hpp"


namespace tool::ex {

class BiopacMP36InitConfigParametersW : public ConfigParametersW{

public :

    ExCheckBoxW m_debugBypassDevice{"debug_bypass"};

    ExComboBoxIndexW m_device{"device_type"};
    ExComboBoxIndexW m_connection{"device_connection"};
    ExComboBoxIndexW m_readIoMode{"read_digital_mode"};

    using CB = ExCheckBoxW;
    std_a1<ExCheckBoxW, 16> m_channels{
        CB{"channel0"}, CB{"channel1"}, CB{"channel2"}, CB{"channel3"},
        CB{"channel4"}, CB{"channel5"}, CB{"channel6"}, CB{"channel7"},
        CB{"channel8"}, CB{"channel9"}, CB{"channel10"},CB{"channel11"},
        CB{"channel12"},CB{"channel13"},CB{"channel14"},CB{"channel15"},
    };

    using LE = ExLineEditW;
    std_a1<ExLineEditW, 16> m_channelsName{
        LE{"channel0_name"}, LE{"channel1_name"}, LE{"channel2_name"}, LE{"channel3_name"},
        LE{"channel4_name"}, LE{"channel5_name"}, LE{"channel6_name"}, LE{"channel7_name"},
        LE{"channel8_name"}, LE{"channel9_name"}, LE{"channel10_name"},LE{"channel11_name"},
        LE{"channel12_name"},LE{"channel13_name"},LE{"channel14_name"},LE{"channel15_name"},
    };

    std_a1<ExLineEditW, 16> m_channelsPresetUid{
        LE{"channel0_preset_uid"}, LE{"channel1_preset_uid"}, LE{"channel2_preset_uid"}, LE{"channel3_preset_uid"},
        LE{"channel4_preset_uid"}, LE{"channel5_preset_uid"}, LE{"channel6_preset_uid"}, LE{"channel7_preset_uid"},
        LE{"channel8_preset_uid"}, LE{"channel9_preset_uid"}, LE{"channel10_preset_uid"},LE{"channel11_preset_uid"},
        LE{"channel12_preset_uid"},LE{"channel13_preset_uid"},LE{"channel14_preset_uid"},LE{"channel15_preset_uid"},
    };

    std_v1<QWidget*> m_channelsParentWidgets;

    ExLineEditW m_serialNumber{"serial"};
    ExSpinBoxW m_samplesPerCall{"nb_samples_per_call"};
    ExSpinBoxW m_samplingRate{"sampling_rate"};
    ExSpinBoxW m_maxNbSecondsToSave{"max_nb_seconds_to_save"};

    ExResourceW m_presetFile{"preset_xml_file"};

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

        add_input_ui(m_device.init_widget({"MP36","MP150","MP160"}));
        add_input_ui(m_connection.init_widget({"USB","UDP"}));
        add_input_ui(m_serialNumber.init_widget("AUTO"));
        add_input_ui(m_readIoMode.init_widget({"DISABLED", "LOW_BYTES", "HIGHT_BYTES"},0));

        add_input_ui(m_presetFile.init_widget(Resource::Type::Text, "Preset xml file (optional): "));
        add_input_ui(m_samplesPerCall.init_widget(MinV<int>{1}, V<int>{10}, MaxV<int>{1000}, StepV<int>{1}));

        add_input_ui(m_samplingRate.init_widget(MinV<int>{10}, V<int>{250}, MaxV<int>{400000}, StepV<int>{10},1));
        add_input_ui(m_maxNbSecondsToSave.init_widget(MinV<int>{100}, V<int>{1000}, MaxV<int>{10000}, StepV<int>{1}));

        for(size_t ii = 0; ii < 16; ++ii){
            auto idStr = QString::number(ii);
            add_input_ui(m_channels[ii].init_widget(QSL("Enable channel ") % QString::number(ii+1), false));
            add_input_ui(m_channelsName[ii].init_widget(QSL("channel") % QString::number(ii+1)));
            add_input_ui(m_channelsPresetUid[ii].init_widget(""));
        }
        add_input_ui(m_debugBypassDevice.init_widget("Enable it for testing the experiment without the device", false));
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
