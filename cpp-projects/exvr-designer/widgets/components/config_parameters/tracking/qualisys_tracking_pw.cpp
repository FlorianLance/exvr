

#include "qualisys_tracking_pw.hpp"

void tool::ex::QualisysTrackingInitConfigParametersW::insert_widgets(){

    auto radioF = ui::F::gen(ui::L::VB(), {connectToFirstAvailable(), specifyServer()}, LStretch{false}, LMargins{true}, QFrame::NoFrame);
    auto hostNameF = ui::F::gen(ui::L::HB(), {ui::W::txt("Host name:"), hostName()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto ipAdressF = ui::F::gen(ui::L::HB(), {ui::W::txt("Ip address:"), ipAdress()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
//    auto portF = ui::F::gen(ui::L::HB(), {ui::W::txt("Port:"), port()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
    auto serverInfosF = ui::F::gen(ui::L::VB(), {ui::W::txt("<b>Server infos:</b>"), hostNameF, hostNameF, ipAdressF}, LStretch{false}, LMargins{true}, QFrame::NoFrame);
    add_widget(ui::F::gen(ui::L::VB(), {radioF, serverInfosF}, LStretch{false}, LMargins{true}, QFrame::Box));
}

void tool::ex::QualisysTrackingInitConfigParametersW::init_and_register_widgets(){

    m_inputUiElements["connect_to_first"] = connectToFirstAvailable.init_widget("Connect to first server available", true);
    m_inputUiElements["connect_to_specific"] = specifyServer.init_widget("Connect to server matching infos", false);
    m_inputUiElements["host_name"] = hostName.init_widget("");
    m_inputUiElements["ip_address"] = ipAdress.init_widget("");
}

void tool::ex::QualisysTrackingInitConfigParametersW::create_connections(){

}

void tool::ex::QualisysTrackingInitConfigParametersW::late_update_ui(){}

void tool::ex::QualisysTrackingConfigParametersW::insert_widgets(){

    add_sub_part_widget(transform);
    auto objectsF = ui::F::gen(ui::L::VB(), {ui::W::txt("Objects names to track (one per line):"), objects()}, LStretch{false}, LMargins{true}, QFrame::NoFrame);
    add_widget(ui::F::gen(ui::L::VB(), {objectsF}, LStretch{false}, LMargins{true}, QFrame::Box));
}

void tool::ex::QualisysTrackingConfigParametersW::init_and_register_widgets(){

    map_sub_part(transform.init_widget());
    m_inputUiElements["objects"] = objects.init_widget("6DOF object name 1\n6DOF object name 2");
}

void tool::ex::QualisysTrackingConfigParametersW::create_connections(){

}

void tool::ex::QualisysTrackingConfigParametersW::late_update_ui(){

}
