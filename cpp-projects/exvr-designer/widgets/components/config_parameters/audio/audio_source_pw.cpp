
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "audio_source_pw.hpp"

// Qt
#include <QDesktopServices>
#include <QDirIterator>
#include <QDir>
#include <QListWidget>

// local
#include "path_utility.hpp"
#include "ex_slider_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_combo_box_index_w.hpp"
#include "ex_text_edit_w.hpp"
#include "ex_line_edit_w.hpp"
#include "ex_radio_button_w.hpp"
#include "ex_resource_w.hpp"

using namespace tool::ex;

struct AudioSourceInitConfigParametersW::Impl{
    ExResourceW sound;
    ExCheckBoxW generateNewSound;
    ExComboBoxIndexW newSoundChannels;
    ExTextEditW infoText;
    std_v1<std::unique_ptr<ExLineEditW>> channelsToCopy;
};

struct AudioSourceConfigParametersW::Impl{
    ExCheckBoxW displaySoundOrigin;
    ExCheckBoxW playNewBlock;
    ExRadioButtonW pauseEndBlock;
    ExRadioButtonW stopEndBlock;
    ExRadioButtonW nothingEndBlock;
    ExCheckBoxW doLoop;
    ExCheckBoxW isSpatialized;
    ExSliderFloatW volume;
    ExSliderFloatW stereo;
    ExSliderFloatW spatialBlend;
    ExSliderFloatW pitch;
    ExSliderFloatW maxDistance;
    ExSliderFloatW minDistance;
    DefaultTransformSubPart transfo;
};

AudioSourceInitConfigParametersW::AudioSourceInitConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}


void AudioSourceInitConfigParametersW::insert_widgets(){


    // top
    add_widget(ui::F::gen(ui::L::HB(), {m_p->sound()}, LStretch{false}, LMargins{true}, QFrame::Box));

    for(int ii = 0; ii < 8; ++ ii){
        m_p->channelsToCopy.emplace_back(std::make_unique<ExLineEditW>());
    }

    // infos
    add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("Input file infos"), m_p->infoText()}, LStretch{true}, LMargins{true}, QFrame::Box));
    m_p->infoText.w->setMinimumHeight(100);

    // new sound
    std_v1<QWidget*> channelsW;
    for(size_t ii = 0; ii < 8; ++ii){
        auto layout = ui::L::HB();
        layout->addWidget(ui::W::txt("Copy channel " + QString::number(ii+1) + " to channel: "));
        layout->addWidget(m_p->channelsToCopy[ii]->w.get());
        layout->setContentsMargins(0,0,0,0);

        auto w = new QWidget();
        w->setLayout(layout);
        channelsW.emplace_back(w);
    }

    auto outputChannelsNb = ui::F::gen(ui::L::HB(),{ui::W::txt("Number channels:"), m_p->newSoundChannels()}, LStretch{true}, LMargins{false});
    add_widget(ui::F::gen(ui::L::VB(), {
        m_p->generateNewSound(), outputChannelsNb,
        channelsW[0],channelsW[1],channelsW[2],channelsW[3],
        channelsW[4],channelsW[5],channelsW[6],channelsW[7]},
        LStretch{false}, LMargins{true}, QFrame::Box)
    );
}

void AudioSourceInitConfigParametersW::init_and_register_widgets(){

    m_inputUiElements["sound"] = m_p->sound.init_widget(Resource::Type::Audio, "Audio resource: ");
    m_inputUiElements["generate_new_sound"]   = m_p->generateNewSound.init_widget("Generate new sound", false);
    m_inputUiElements["new_sound_channel"] = m_p->newSoundChannels.init_widget({"1", "2", "3", "4", "5", "6", "7", "8"}, 0, true);

    for(size_t ii = 0; ii < m_p->channelsToCopy.size(); ++ii){
        m_inputUiElements["channel_" + QString::number(ii) + "_copy_destination"] = m_p->channelsToCopy[ii]->init_widget({}, true);
    }
    m_p->channelsToCopy[0]->w->setText("1 2");
}

void AudioSourceInitConfigParametersW::create_connections(){
}

void AudioSourceInitConfigParametersW::late_update_ui(){}

void AudioSourceInitConfigParametersW::update_with_info(QStringView id, QStringView value){

    if(id == QSL("input_sound_info")){
        if(auto infos = value.split('?'); infos.size() > 5){
            m_p->infoText.w->setText(
                QSL("Name: ") % infos[0] %
                QSL("\nChannels:") % infos[1] %
                QSL("\nFrequency: ") % infos[2] %
                QSL("\nLength: ") % infos[3] %
                QSL("s Samples: ") % infos[4] %
                QSL("\nAmbisonic: ") % infos[5]);
        }
    }
}

AudioSourceConfigParametersW::AudioSourceConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){
}

void AudioSourceConfigParametersW::insert_widgets(){

    m_p = std::make_unique<Impl>();

    add_sub_part_widget(m_p->transfo);

    add_widget(ui::F::gen(ui::L::VB(), {
        m_p->playNewBlock(), m_p->pauseEndBlock(), m_p->stopEndBlock(),
        m_p->nothingEndBlock(), m_p->doLoop(), m_p->isSpatialized(), m_p->displaySoundOrigin()},
        LStretch{false}, LMargins{true}, QFrame::Box)
    );

    auto gl = new QGridLayout();
    gl->addWidget(m_p->volume.title,    0, 0, 1, 1);
    gl->addWidget(m_p->volume.minMax,   0, 1, 1, 1);
    gl->addWidget(m_p->volume.value,    0, 2, 1, 1);
    gl->addWidget(m_p->volume.valueTxt, 0, 3, 1, 1);

    gl->addWidget(m_p->stereo.title,    1, 0, 1, 1);
    gl->addWidget(m_p->stereo.minMax,   1, 1, 1, 1);
    gl->addWidget(m_p->stereo.value,    1, 2, 1, 1);
    gl->addWidget(m_p->stereo.valueTxt, 1, 3, 1, 1);

    gl->addWidget(m_p->spatialBlend.title,    2, 0, 1, 1);
    gl->addWidget(m_p->spatialBlend.minMax,   2, 1, 1, 1);
    gl->addWidget(m_p->spatialBlend.value,    2, 2, 1, 1);
    gl->addWidget(m_p->spatialBlend.valueTxt, 2, 3, 1, 1);

    gl->addWidget(m_p->pitch.title,    3, 0, 1, 1);
    gl->addWidget(m_p->pitch.minMax,   3, 1, 1, 1);
    gl->addWidget(m_p->pitch.value,    3, 2, 1, 1);
    gl->addWidget(m_p->pitch.valueTxt, 3, 3, 1, 1);

    gl->addWidget(m_p->minDistance.title,    4, 0, 1, 1);
    gl->addWidget(m_p->minDistance.minMax,   4, 1, 1, 1);
    gl->addWidget(m_p->minDistance.value,    4, 2, 1, 1);
    gl->addWidget(m_p->minDistance.valueTxt, 4, 3, 1, 1);

    gl->addWidget(m_p->maxDistance.title,    5, 0, 1, 1);
    gl->addWidget(m_p->maxDistance.minMax,   5, 1, 1, 1);
    gl->addWidget(m_p->maxDistance.value,    5, 2, 1, 1);
    gl->addWidget(m_p->maxDistance.valueTxt, 5, 3, 1, 1);

    add_widget(ui::F::gen_frame(gl, {}, 0, LMarginsD{4,2,4,2,2}, QFrame::Shape::Box));
}

void AudioSourceConfigParametersW::init_and_register_widgets(){

    m_inputUiElements["play_new_block"]     = m_p->playNewBlock.init_widget("Play when update block starts", true);
    m_inputUiElements["pause_end_block"]    = m_p->pauseEndBlock.init_widget("Pause when update block ends", false);
    m_inputUiElements["stop_end_block"]     = m_p->stopEndBlock.init_widget("Stop when update block ends", true);
    m_inputUiElements["nothing_end_block"]  = m_p->nothingEndBlock.init_widget("Do nothing when update block ends", false);
    m_inputUiElements["display"]            = m_p->displaySoundOrigin.init_widget("Display sound origin", false);
    m_inputUiElements["loop"]               = m_p->doLoop.init_widget("Loop", false);
    m_inputUiElements["spatialized"]        = m_p->isSpatialized.init_widget("Spatialized", false);
    m_inputUiElements["volume"]             = m_p->volume.init_widget("Volume", MinV<qreal>{0.}, V<qreal>{1.}, MaxV<qreal>{1.}, StepV<qreal>{0.01});
    m_inputUiElements["stereo"]             = m_p->stereo.init_widget("Stereo", MinV<qreal>{-1.}, V<qreal>{0.0}, MaxV<qreal>{1.}, StepV<qreal>{0.01});
    m_inputUiElements["spatial_blend"]      = m_p->spatialBlend.init_widget("Spatial blend", MinV<qreal>{0.}, V<qreal>{0.5}, MaxV<qreal>{1.}, StepV<qreal>{0.01});
    m_inputUiElements["pitch"]              = m_p->pitch.init_widget("Pitch", MinV<qreal>{0.}, V<qreal>{1.}, MaxV<qreal>{5.}, StepV<qreal>{0.01});
    m_inputUiElements["min_distance"]       = m_p->minDistance.init_widget("Min distance", MinV<qreal>{0.}, V<qreal>{0.01}, MaxV<qreal>{10.}, StepV<qreal>{0.01});
    m_inputUiElements["max_distance"]       = m_p->maxDistance.init_widget("Max distance", MinV<qreal>{0.}, V<qreal>{5.}, MaxV<qreal>{10.}, StepV<qreal>{0.01});
    map_sub_part(m_p->transfo.init_widget());
    m_p->transfo.tr.set_scale_values({0.3,0.3,0.3});
}

void AudioSourceConfigParametersW::create_connections(){}

void AudioSourceConfigParametersW::late_update_ui(){}
