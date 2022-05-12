
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
#include <set>

// Qt
#include <QStringList>
#include <QDebug>

// base
#include "utility/vector.hpp"

// qt-utility
#include "qt_logger.hpp"

// local
#include "component.hpp"

namespace tool::ex {

class ComponentsManager{

public:

    void clean_components();
    void sort_by_category();
    void sort_by_type();
    void sort_by_name();

    void add_component(std::unique_ptr<Component> component);
    void insert_copy_of_component(Component *component, std::vector<ConfigKey> configKeys, RowId id);
    void insert_new_component(Component::Type type, RowId id);
    void duplicate_component(ComponentKey componentKey);

    void remove_component(ComponentKey componentKey);
    void update_component_position(ComponentKey componentKey, RowId id);
    Component *get_component(RowId id, bool displayError= true) const;
    Component *get_component(ComponentKey componentKey, bool displayError= true) const;
    Component *get_component(Component::Type type, const QString &name) const;

    std::pair<size_t, Component*> get_component_and_position(ComponentKey componentKey) const;


    bool update_component_name(ComponentKey componentKey, QString newName);

    std::vector<Component*> get_components() const;
    std::vector<Component*> get_components(Component::Type type) const;
    std::vector<Component*> get_components(Component::Category category) const;

    inline size_t count() {return components.size();}
    inline size_t count(Component::Type type) {return m_counter[type];}

    std::vector<std::unique_ptr<Component>> components;
private:


    std::unordered_map<Component::Type, size_t> m_counter = {};

//    if(m_counter.count(type) > 0){
//        m_counter[type]--;
//    }
};
}
