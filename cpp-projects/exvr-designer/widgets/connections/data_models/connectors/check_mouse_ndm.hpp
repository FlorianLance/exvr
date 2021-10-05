
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_combo_box_text_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"

namespace tool::ex {

class CheckMouseButtonEmbeddedW : public NodeContainerW<ExComboBoxTextW>{
Q_OBJECT
public:
    void initialize() override;
};

class CheckMouseButtonNodeDataModel : public TypedConnectorDataModel<Connector::Type::Check_mouse_button, CheckMouseButtonEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};
}
