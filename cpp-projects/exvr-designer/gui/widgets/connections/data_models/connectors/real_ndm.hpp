
/***********************************************************************************
** exvr-designer                                                                  **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

#pragma once

// qt-utility
#include "gui/ex_widgets/ex_double_spin_box_w.hpp"

// local
#include "gui/widgets/connections/data_models/connectors/connector_node_data_model.hpp"

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
    void wheel_event(QWheelEvent *event)override;
public:
    void init_ports_caption() override;
};

class RandomRealNodeDataModel : public TypedConnectorDataModel<Connector::Type::Random_real, PlaceHolderEmbeddedW>{
    Q_OBJECT
public slots:
    void compute() override;
public:
    void init_ports_caption() override;
};

}
