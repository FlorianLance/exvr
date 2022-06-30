
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

    static inline QString blackHex     = "#000000";
    static inline QString whiteHex     = "#FFFFFF";
    static inline QString greenHex     = "#279340";
    static inline QString navyBlueHex  = "#427B89";
    static inline QString orangeHex    = "#FF8C00";
    static inline QString lightGrayHex = "#BDBDBD";
    static inline QString darkGrayHex  = "#2D2D2D";

    using QC = QColor;
    static inline QC blackC     = QC(blackHex);
    static inline QC whiteC     = QC(whiteHex);
    static inline QC greenC     = QC(greenHex);
    static inline QC navyBlueC  = QC(navyBlueHex);
    static inline QC orangeC    = QC(orangeHex);
    static inline QC lightGrayC = QC(lightGrayHex);
    static inline QC darkGrayC  = QC(darkGrayHex);


    struct FlowElementColors{
        QC selectedTextColor;
        QC unselectedTextColor;
        QC selectedLineBoxColor;
        QC unselectedLineBoxColor;
        QC selectedFillBoxColor;
        QC unselectedFillBoxColor;
    };

    struct ButtonColors{
        QC unselectedTextColor;
        QC unselectedLineBoxColor;
        QC unselectedFillBoxColor;
    };

    using FT = tool::ex::FlowElement::Type;
    static inline const std::unordered_map<tool::ex::FlowElement::Type, FlowElementColors> flowElements = {
                         // sel_txt unsel_txt sel_line    unsel_line   sel_box    unsel_box
        {FT::Node,       {blackC,   blackC,   blackC,     blackC,      blackC,    blackC}},
        {FT::LoopStart,  {whiteC,   whiteC,   navyBlueC,  blackC,      navyBlueC, navyBlueC}},
        {FT::LoopEnd,    {whiteC,   whiteC,   navyBlueC,  blackC,      navyBlueC, navyBlueC}},
        {FT::Routine,    {whiteC,   whiteC,   greenC,     blackC,      greenC,    greenC}},
        {FT::Isi,        {whiteC,   whiteC,   orangeC,    blackC,      orangeC,   orangeC}},
        {FT::Loop,       {whiteC,   whiteC,   navyBlueC,  blackC,      navyBlueC, navyBlueC}},
    };

    using BT = tool::ex::ButtonType;
    static inline const std::unordered_map<tool::ex::ButtonType, ButtonColors> buttons = {
        // sel_txt           unsel_txt  unsel_line  unsel_box
        {BT::AddElement,     {whiteC,   blackC,     whiteC}},
        {BT::RemoveElement,  {whiteC,   blackC,     blackC}},
        {BT::MoveElement,    {blackC,   blackC,     whiteC}},
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

    static inline const QColor& text(tool::ex::ButtonType type){
        return buttons.at(type).unselectedTextColor;
    }

    static inline const QColor& line_box( tool::ex::ButtonType type){
        return buttons.at(type).unselectedLineBoxColor;
    }

    static inline const QColor& fill_box(tool::ex::ButtonType type){
        return buttons.at(type).unselectedFillBoxColor;
    }
};

struct Styles{

    using C = Colors;

    /**
     * @brief Return stylesheet rgb color format string
     */
    static inline QString sc(const QColor &col){
        return QString("rgb(%1,%2,%3)").arg(col.red(), col.green(), col.blue());
    }

    static inline QString qlabel(QString objectName ="", QString colorHex = C::whiteHex, QString backgroundColorHex = C::darkGrayHex){
        return QString("QLabel%1{color: %2; background-color: %3;}").arg((objectName.length() > 0 ? QString("[objectName=%1]").arg(objectName) : ""),
            colorHex,backgroundColorHex
        );
    }

    static inline QString qcheck_box(QString objectName ="", QString colorHex = C::whiteHex, QString backgroundColorHex = C::darkGrayHex){
        return QString("QCheckBox%1{color: %2; background-color: %3;}").arg((objectName.length() > 0 ? QString("[objectName=%1]").arg(objectName) : ""),
            colorHex, backgroundColorHex
        );
    }

//    static inline QString qspin_box(QString objectName ="", QString colorHex = C::whiteHex, QString backgroundColorHex = C::darkGrayHex){
//        return QString("QSpinBox%1{color: %2; background-color: %3;}").arg((objectName.length() > 0 ? QString("[objectName=%1]").arg(objectName) : ""),
//            colorHex, backgroundColorHex
//        );
//    }

    static inline QString qtext_edit(QString objectName ="", QString colorHex = C::blackHex, QString backgroundColorHex = C::lightGrayHex){
        return QString("QTextEdit%1{color: %2; background-color: %3;}").arg((objectName.length() > 0 ? QString("[objectName=%1]").arg(objectName) : ""),
            colorHex, backgroundColorHex
        );
    }

//    static inline QString qlabel    = QString("QLabel{color: %1}").arg(sc(C::whiteC));
//    static inline QString qTextEditStyle = QString("QTextEdit{color: %1; background-color: %2;}").arg(sc(C::blackC),sc(C::lightGrayC));

};

}
