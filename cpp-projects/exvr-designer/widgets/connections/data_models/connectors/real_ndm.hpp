
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "ex_widgets/ex_double_spin_box_w.hpp"

// local
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"

namespace tool::ex {

class RealEmbeddedW : public NodeContainerW<ExDoubleSpinBoxW>{
Q_OBJECT
public:
    void initialize() override;
    static constexpr MinV<qreal> min{-100000000.};
    static constexpr MaxV<qreal> max{100000000.};
    static constexpr StepV<qreal> step{0.01};
    static constexpr V<qreal> value{1.};
};

class RealNodeDataModel : public TypedConnectorDataModel<Connector::Type::Real, RealEmbeddedW>{
Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};
}
