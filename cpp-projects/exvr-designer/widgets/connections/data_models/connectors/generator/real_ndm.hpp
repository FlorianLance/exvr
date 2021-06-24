
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "ex_double_spin_box_w.hpp"
#include "widgets/connections/data_models/connectors/connector_node_data_model.hpp"
#include "widgets/connections/data_models/data/nodes_data.hpp"

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
    QString portCaption(QtNodes::PortType t , QtNodes::PortIndex i) const override;
};


}
