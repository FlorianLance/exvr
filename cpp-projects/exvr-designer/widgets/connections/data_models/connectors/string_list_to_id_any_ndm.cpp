
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "string_list_to_id_any_ndm.hpp"

using namespace tool::ex;

void StringListToIdAnyNodeDataModel::compute(){

    if(check_infinity_loop()){
        return;
    }

    auto inputs = get_inputs();

    // missing inputs
    if(check_if_missing_inputs(inputs)){
        return;
    }

    // runtime inputs
    if(check_if_runtime_inputs(inputs)){
        auto strData = std::make_shared<StringData>(QSL("runtime"));
        strData->set_runtime();
        propagate_default_runtime({std::make_shared<IdAnyData>(IdAny{0, std::move(strData)})}, 0);
        return;
    }

    // cast
    auto data = dcast<StringListData>(inputs[0]);
    if(!data){
        set_invalid_cast();
        return;
    }

    // propagate
    QStringList txt = data->value();
    std_v1<std::shared_ptr<BaseNodeData>> outputs;
    for(int ii = 0; ii < txt.size(); ++ii){
        outputs.emplace_back(std::make_shared<IdAnyData>(IdAny{ii, std::make_shared<StringData>(txt[ii])}));
    }

    propagate_data(
        str::Convertor::to_str(QSL("Nb: ") % QString::number(txt.size())),
        std::move(outputs), 0
    );
}

void StringListToIdAnyNodeDataModel::init_ports_caption(){
    const auto io = Connector::get_io(m_type);
    for(size_t ii = 0; ii < io.inNb; ++ii){
        inPortsInfo[ii].caption = QSL("in (") % get_name(io.inTypes[ii]) % QSL(")");
    }
    for(size_t ii = 0; ii < io.outNb; ++ii){
        outPortsInfo[ii].caption = QSL("out (") % get_name(io.outTypes[ii]) % QSL(")");
    }
}

#include "moc_string_list_to_id_any_ndm.cpp"
