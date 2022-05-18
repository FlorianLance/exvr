
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
//#include <memory>
//#include <optional>

// Qt
#include <QString>
//#include <QList>
//#include <QVector>

// base
//#include "utility/vector.hpp"
//#include "utility/tuple_array.hpp"

// qt-utility
#include "data/id_key.hpp"

namespace tool::ex {

using namespace std::literals::string_view_literals;

struct FlowElement {

public:

    enum class Type : int {
        Node,LoopStart,LoopEnd,Routine,Isi,Loop,AddElement,RemoveElement,MoveElement,
        SizeEnum};

    enum class Category : int{
        Movable, Fixed, Button,
        SizeEnum
    };

    using Name     = std::string_view;

    using TElement = std::tuple<Type, Name, Category>;
    static constexpr TupleArray<Type::SizeEnum,TElement> elements ={{
        TElement
        {Type::Node,         "Node"sv,          Category::Fixed},
        {Type::LoopStart,    "LoopStart"sv,     Category::Movable},
        {Type::LoopEnd,      "LoopEnd"sv,       Category::Movable},
        {Type::Routine,      "Routine"sv,       Category::Movable},
        {Type::Isi,          "Isi"sv,           Category::Movable},
        {Type::Loop,         "Loop"sv,          Category::Movable},
        {Type::AddElement,   "AddElement"sv,    Category::Button},
        {Type::RemoveElement,"RemoveElement"sv, Category::Button},
        {Type::MoveElement,  "MoveElement"sv,   Category::Button}
    }};

    static constexpr Type get_type(Name n) {
        return elements.at<1,0>(n);
    }

    static constexpr Name get_type_name(Type t) {
        return elements.at<0,1>(t);
    }

    static constexpr Category get_category(Type t) {
        return elements.at<0,2>(t);
    }

    FlowElement() = delete;
    FlowElement(Type t, QString n, int id = -1, QString infos = "") :
          type(t), informations(infos),
          m_key(Category(t) == Category::Button ? IdKey::Type::ButtonFlowElement : IdKey::Type::FlowElement, id),
          m_name(n){
    }
    FlowElement(const FlowElement &) = delete;
    FlowElement& operator=(const FlowElement&) = delete;


    inline void set_selected(bool select) noexcept {
        m_isSelected = select;
    }

    inline void update_name(QString name)noexcept{
        m_name = name;
    }

    inline QString name()const noexcept{
        return m_name;
    }

    constexpr bool is_selected() const noexcept {
        return m_isSelected;
    }

    constexpr bool is_routine()const noexcept{
        return type == Type::Routine;
    }

    constexpr bool is_isi()const noexcept{
        return type == Type::Isi;
    }

    virtual void check_integrity(){}

    constexpr int key() const noexcept{ return m_key();}
//    constexpr ElementKey e_key() const noexcept {return ElementKey{key()};}

    Type type;

    std::vector<ElementKey> insideLoopsID;       /**< all loop id containing the element */
    std::vector<FlowElement*> insideLoops;
    QString informations;

private:

    IdKey m_key;
    QString m_name = "";
    bool m_isSelected = false;  /**< is the element selected ? */
};

}
