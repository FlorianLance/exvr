
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once


// local
#include "config_pw.hpp"
#include "ex_list_labels_w.hpp"

namespace tool::ex {

class MicrophoneInitConfigParametersW : public ConfigParametersW{

public :

    ExListLabelsW devices;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;

    void update_with_info(QStringView id, QStringView value) override;
};

class MicrophoneConfigParametersW : public ConfigParametersW{

public :

//    ExCheckBoxW m_cbPlayAtStart;
//    ExCheckBoxW m_cbLoop;
//    ExCheckBoxW m_cbSpatialized;
//    ExSliderDoubleW m_sdVolume;
//    ExSliderDoubleW m_sdPitch;
//    ExSliderDoubleW m_sdMinDistance;
//    ExSliderDoubleW m_sdMaxDistance;
//    ExTransformationW m_transfo;

    void insert_widgets() override;

    void init_and_register_widgets() override;

    void create_connections() override;
    void late_update_ui() override;
};

}
