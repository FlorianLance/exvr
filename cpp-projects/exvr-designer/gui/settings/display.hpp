
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

// std
#include <unordered_map>

// Qt
#include <QColor>

// local
#include "data/flow_elements/flow_element.hpp"

namespace tool::ex::display {

struct Colors{

    struct FlowElement{
        QColor selectedTextColor;
        QColor unselectedTextColor;
        QColor selectedLineBoxColor;
        QColor unselectedLineBoxColor;
        QColor selectedFillBoxColor;
        QColor unselectedFillBoxColor;
    };

    static inline QColor inused = Qt::black;

    using QC = QColor;

    using T = tool::ex::FlowElement::Type;

    static inline const std::unordered_map<tool::ex::FlowElement::Type, FlowElement> flowElements = {
                            // sel_txt      unsel_txt       sel_line        unsel_line      sel_box         unsel_box
        {T::Node,           {QC("#000000"), QC("#000000"),  QC("#000000"),  QC("#000000"),  QC("#000000"),  QC("#000000")}},
        {T::LoopStart,      {QC("#FFFFFF"), QC("#FFFFFF"),  QC("#427b89"),  QC("#000000"),  QC("#427b89"),  QC("#427b89")}},
        {T::LoopEnd,        {QC("#FFFFFF"), QC("#FFFFFF"),  QC("#427b89"),  QC("#000000"),  QC("#427b89"),  QC("#427b89")}},
        {T::Routine,        {QC("#FFFFFF"), QC("#FFFFFF"),  QC("#279340"),  QC("#000000"),  QC("#279340"),  QC("#279340")}},
        {T::Isi,            {QC("#FFFFFF"), QC("#FFFFFF"),  QC("#ff8c00"),  QC("#000000"),  QC("#ff8c00"),  QC("#ff8c00")}},
        {T::Loop,           {QC("#FFFFFF"), QC("#FFFFFF"),  QC("#427b89"),  QC("#000000"),  QC("#427b89"),  QC("#427b89")}},
        {T::AddElement,     {QC("#FFFFFF"), inused,         QC("#000000"),  inused,         QC("#FFFFFF"),  inused}},
        {T::RemoveElement,  {QC("#FFFFFF"), inused,         QC("#000000"),  inused,         QC("#000000"),  inused}},
        {T::MoveElement,    {QC("#000000"), inused,         QC("#000000"),  inused,         QC("#FFFFFF"),  inused}},
        {T::MoveElement,    {QC("#000000"), inused,         QC("#000000"),  inused,         QC("#FFFFFF"),  inused}},
    };

    static inline const QColor& text(bool selected, tool::ex::FlowElement::Type type){
        return selected ? flowElements.at(type).selectedTextColor : flowElements.at(type).unselectedTextColor;
    }

    static inline const QColor& line_box(bool selected, tool::ex::FlowElement::Type type){
        return selected ? flowElements.at(type).selectedLineBoxColor : flowElements.at(type).unselectedLineBoxColor;
    }

    static inline const QColor& fill_box(bool selected, tool::ex::FlowElement::Type type){
        return selected ? flowElements.at(type).selectedFillBoxColor : flowElements.at(type).unselectedFillBoxColor;
    }

};
}
