
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "microphone_pw.hpp"

// qt-utility
#include "ex_widgets/ex_list_labels_w.hpp"

using namespace tool::ex;


struct MicrophoneInitConfigParametersW::Impl{
    ExListLabelsW devices;
};

struct MicrophoneConfigParametersW::Impl{

};

MicrophoneInitConfigParametersW::MicrophoneInitConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){

}

void MicrophoneInitConfigParametersW::insert_widgets(){
    //        QFrame *frame1 = ui::F::gen(ui::L::HB(), {ui::W::txt("Audio file path:"), &m_pbSetPathAudioFile}, LStretch{true}, LMargins{true});
    //        QFrame *frame2 = ui::F::gen(ui::L::HB(),{&m_lePathAudioFile.w }, LStretch{false}, LMargins{true});
    //        add_widget(ui::F::gen(ui::L::VB(),{frame1, frame2}, LStretch{true}, LMargins{false},QFrame::Box));

    add_widget(ui::F::gen(ui::L::VB(), {ui::W::txt("<b>Recording devices detected:</b>"),m_p->devices()}, LStretch{true}, LMargins{true}, QFrame::Box));
}

void MicrophoneInitConfigParametersW::init_and_register_widgets(){
    m_p->devices.init_widget(false);
    //        m_inputUiElements["path_audio_file"]        = m_lePathAudioFile.init_widget("");
    //        m_neutralUiElements["set_audio_file"]  = ui::W::init(&m_pbSetPathAudioFile, "Set");
}

void MicrophoneInitConfigParametersW::create_connections(){
    //        connect(&m_pbSetPathAudioFile, &QPushButton::clicked, this, [&]{
    //            // select audio file
    //            QString path = QFileDialog::getOpenFileName(nullptr, "Select audio file", utility::Paths::assetsBundlesDir, "Audio files (*.ogg *.wav *.aiff *.aif)");// *.mod *.it *.s3m *.xm
    //            if(path.size() > 0){
    //                m_lePathAudioFile.w.setText(path);
    //                emit m_lePathAudioFile.w.textChanged(m_lePathAudioFile.w.text());
    //            }
    //        });
}

void MicrophoneInitConfigParametersW::late_update_ui(){}

void MicrophoneInitConfigParametersW::update_with_info(QStringView id, QStringView value){

    if(id == QSL("microphones_info")){
        m_p->devices.w->clear();

        int id = 0;
        for(const auto &device : value.split('%')){
            if(device.length() == 0){
                break;
            }
            m_p->devices.w->addItem(QSL("R") % QString::number(id++) % QSL(" ") % device);
        }
    }
}

MicrophoneConfigParametersW::MicrophoneConfigParametersW() :  ConfigParametersW(), m_p(std::make_unique<Impl>()){

}

void MicrophoneConfigParametersW::insert_widgets(){

    //        add_widget(ui::F::gen(ui::L::VB(), {&m_cbPlayAtStart.w, &m_cbLoop.w, &m_cbSpatialized.w,}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
    //        add_widget(ui::F::gen(ui::L::VB(), {&m_sdVolume.w,&m_sdPitch.w,&m_sdMinDistance.w,&m_sdMaxDistance.w}, LStretch{false}, LMargins{false}, QFrame::NoFrame));
    //        add_widget(ui::F::gen(ui::L::VB(), {&m_transfo.w}, LStretch{true}, LMargins{true},QFrame::NoFrame));
}

void MicrophoneConfigParametersW::init_and_register_widgets(){

    //        ui::W::init(&m_transfo.scX,  MinV<qreal>{0.01}, V<qreal>{0.1}, MaxV<qreal>{1.}, StepV<qreal>{0.001}, 3, true);
    //        ui::W::init(&m_transfo.scY,  MinV<qreal>{0.01}, V<qreal>{0.1}, MaxV<qreal>{1.}, StepV<qreal>{0.001}, 3, true);
    //        ui::W::init(&m_transfo.scZ,  MinV<qreal>{0.01}, V<qreal>{0.1}, MaxV<qreal>{1.}, StepV<qreal>{0.001}, 3, true);

    //        m_inputUiElements["play_at_start"]  = m_cbPlayAtStart.init_widget("Play at start", true);
    //        m_inputUiElements["loop"]           = m_cbLoop.init_widget("Loop", false);
    //        m_inputUiElements["spatialized"]    = m_cbSpatialized.init_widget("Spatialized", true);
    //        m_inputUiElements["volume"]         = m_sdVolume.init_widget("Volume", MinV<qreal>{0.}, V<qreal>{1.}, MaxV<qreal>{1.}, StepV<qreal>{0.01});
    //        m_inputUiElements["pitch"]          = m_sdPitch.init_widget("Pitch", MinV<qreal>{-3.}, V<qreal>{1.}, MaxV<qreal>{3.}, StepV<qreal>{0.01});
    //        m_inputUiElements["min_distance"]   = m_sdMinDistance.init_widget("Min distance", MinV<qreal>{0.}, V<qreal>{0.01}, MaxV<qreal>{10.}, StepV<qreal>{0.01});
    //        m_inputUiElements["max_distance"]   = m_sdMaxDistance.init_widget("Max distance", MinV<qreal>{0.}, V<qreal>{5.}, MaxV<qreal>{10.}, StepV<qreal>{0.01});
    //        m_inputUiElements["transformation"] = m_transfo.init_widget("Transformation");
}

void MicrophoneConfigParametersW::create_connections(){}

void MicrophoneConfigParametersW::late_update_ui(){}
