
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// base
#include "utility/joypad_utility.hpp"

// local
#include "ex_combo_box_text_w.hpp"
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

namespace tool::ex {

class CheckJoypadButtonEmbeddedW : public NodeContainerW<ExComboBoxTextW>{
Q_OBJECT
public:
    void initialize() override;
};

class CheckJoypadButtonNodeDataModel : public TypedConnectorDataModel<Connector::Type::Check_joypad_button, CheckJoypadButtonEmbeddedW>{
Q_OBJECT
public slots:

void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

class CheckJoypadAxisEmbeddedW : public NodeContainerW<ExComboBoxTextW>{
Q_OBJECT
public:
    void initialize() override;
};

class CheckJoypadAxisNodeDataModel : public TypedConnectorDataModel<Connector::Type::Check_joypad_axis, CheckJoypadAxisEmbeddedW>{
Q_OBJECT

public slots:

void compute() override;
public:
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};

}
