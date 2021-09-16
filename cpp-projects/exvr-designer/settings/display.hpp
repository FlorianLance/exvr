
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <unordered_map>

// Qt
#include <QColor>

// local
#include "data/element.hpp"

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

    static inline const std::unordered_map<Element::Type, FlowElement> flowElements = {
                                         // sel_txt     unsel_txt       sel_line        unsel_line      sel_box         unsel_box
        {Element::Type::Node,           {QC("#000000"), QC("#000000"),  QC("#000000"),  QC("#000000"),  QC("#000000"),  QC("#000000")}},
        {Element::Type::LoopStart,      {QC("#FFFFFF"), QC("#FFFFFF"),  QC("#427b89"),  QC("#000000"),  QC("#427b89"),  QC("#427b89")}},
        {Element::Type::LoopEnd,        {QC("#FFFFFF"), QC("#FFFFFF"),  QC("#427b89"),  QC("#000000"),  QC("#427b89"),  QC("#427b89")}},
        {Element::Type::Routine,        {QC("#FFFFFF"), QC("#FFFFFF"),  QC("#279340"),  QC("#000000"),  QC("#279340"),  QC("#279340")}},
        {Element::Type::Isi,            {QC("#FFFFFF"), QC("#FFFFFF"),  QC("#ff8c00"),  QC("#000000"),  QC("#ff8c00"),  QC("#ff8c00")}},
        {Element::Type::Loop,           {QC("#FFFFFF"), QC("#FFFFFF"),  QC("#427b89"),  QC("#000000"),  QC("#427b89"),  QC("#427b89")}},
        {Element::Type::AddElement,     {QC("#FFFFFF"), inused,         QC("#000000"),  inused,         QC("#FFFFFF"),  inused}},
        {Element::Type::RemoveElement,  {QC("#FFFFFF"), inused,         QC("#000000"),  inused,         QC("#000000"),  inused}},
        {Element::Type::MoveElement,    {QC("#000000"), inused,         QC("#000000"),  inused,         QC("#FFFFFF"),  inused}},
        {Element::Type::MoveElement,    {QC("#000000"), inused,         QC("#000000"),  inused,         QC("#FFFFFF"),  inused}},
        {Element::Type::Default,        {inused,        inused,         inused,         inused,         inused,         inused}},
    };

};
}
