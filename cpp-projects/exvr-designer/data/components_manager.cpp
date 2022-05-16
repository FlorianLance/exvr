
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

#include "components_manager.hpp"

// qt-utility
#include "qt_str.hpp"

using namespace tool;
using namespace tool::ex;


void ComponentsManager::clean_components(){
    components.clear();
}

void ComponentsManager::sort_by_category(){

    std::sort(std::begin(components), std::end(components), [&](const std::unique_ptr<Component> &c1,  const std::unique_ptr<Component> &c2){
        if(c1->category != c2->category){
            return c1->category < c2->category;
        }
        if(c1->type != c2->type){
            return c1->type < c2->type;
        }
        return c1->name().toUpper() < c2->name().toUpper();
    });
}

void ComponentsManager::sort_by_type(){
    std::sort(std::begin(components), std::end(components), [&](const std::unique_ptr<Component> &c1,  const std::unique_ptr<Component> &c2){
        if(c1->type != c2->type){
            return c1->type < c2->type;
        }
        return c1->name().toUpper() < c2->name().toUpper();
    });
}

void ComponentsManager::sort_by_name(){
    std::sort(std::begin(components), std::end(components), [&](const std::unique_ptr<Component> &c1,  const std::unique_ptr<Component> &c2){
        return c1->name().toUpper() < c2->name().toUpper();
    });
}

//void ComponentsManager::add_component(std::unique_ptr<Component> component){
//    components.push_back(std::move(component));
//}

void ComponentsManager::duplicate_component(ComponentKey componentKey){

    if(const auto compoInfo = get_component_and_position(componentKey); compoInfo.second != nullptr){
        if(Component::get_unicity(compoInfo.second->type)){
            QtLogger::error(QSL("You can only have one component of type [") % from_view(Component::get_type_name(compoInfo.second->type)) % QSL("] in the experiment."));
        }else{
            components.insert(
                components.begin() + static_cast<std_v1<std::unique_ptr<Component>>::difference_type>(compoInfo.first + 1),
                Component::copy_with_new_element_id(*compoInfo.second, compoInfo.second->name() % QSL("(copy)"))
            );
        }
    }
}

void ComponentsManager::remove_component(ComponentKey componentKey){

    auto componentToRemove = get_component(componentKey);

    for(size_t id = 0; id < components.size(); ++id){
        if(components[id]->key() == componentToRemove->key()){
            QtLogger::message(QSL("Remove component ") % components[id]->to_string());
            components.erase(components.begin() + static_cast<int>(id));
            break;
        }
    }
}

void ComponentsManager::update_component_position(ComponentKey componentKey, RowId id){

    if(const auto compoInfo = get_component_and_position(componentKey); compoInfo.second != nullptr){
        auto compoToMove = std::move(components[compoInfo.first]);
        components.erase(components.begin() + static_cast<std::vector<std::unique_ptr<Component>>::difference_type>(compoInfo.first));
        components.insert(components.begin() + id.v, std::move(compoToMove));
    }else{
        QtLogger::error(QSL("Cannot update component position."));
    }
}

Component *ComponentsManager::get_component(RowId id, bool displayError) const{
    if(id.v < components.size()){
        return components[id.v].get();
    }
    if(displayError){
        QtLogger::error(QSL("Component from row [") % QString::number(id.v) % QSL("] not found."));
    }

    return nullptr;
}


Component *ComponentsManager::get_component(ComponentKey componentKey, bool displayError) const{

    auto componentFound = std::find_if(std::begin(components), std::end(components), [componentKey](const std::unique_ptr<Component> &component){
        return component->key() == componentKey.v;
    });

    if(componentFound != std::end(components)){
        return componentFound->get();
    }

    if(displayError){
        QtLogger::error(QSL("Component with key [") % QString::number(componentKey.v) % QSL("] not found."));
    }

    return nullptr;
}

Component *ComponentsManager::get_component(Component::Type type, const QString &name) const{
    for(auto &component : get_components(type)){
        if(component->name() == name){
            return component;
        }
    }
    QtLogger::error(QSL("Component with name [") % name % QSL("] and type [") % from_view(Component::get_type_name(type)) % QSL("] not found."));
    return  nullptr;
}

std::pair<size_t, Component *> ComponentsManager::get_component_and_position(ComponentKey componentKey) const{

    for(size_t ii = 0; ii < components.size(); ++ii){
        if(components[ii]->key() == componentKey.v){
            return {ii, components[ii].get()};
        }
    }
    QtLogger::error(QSL("Component with key [") % QString::number(componentKey.v) % QSL("] and its position not found."));
    return {0, nullptr};
}

void ComponentsManager::insert_copy_of_component(Component *component, std::vector<ConfigKey> configKeys, RowId id){

    if(Component::get_unicity(component->type) && count(component->type) > 0){
        QtLogger::error(QSL("Unique component already inside experiment."));
        return;
    }

    size_t offset = 1;
    QString name;
    bool isInside = false;
    do{
        name = component->name() %  ((offset != 1) ? (QSL(" ") % QString::number(offset)) : QSL(""));
        isInside = false;
        for(auto &component : components){
            if(component->name() == name){
                isInside = true;
                break;
            }
        }
        ++offset;
    }while(isInside);
    component->set_name(name);

    if(count(component->type) == 0){
        m_counter[component->type] = 1;
    }else{
        m_counter[component->type]++;
    }

    components.insert(
        std::begin(components) + id.v,
        Component::copy_with_new_element_id(*component, component->name() % QSL("(imported)"), std::move(configKeys))
    );
}

bool ComponentsManager::insert_new_component(Component::Type type, RowId id){

    if(Component::get_unicity(type) && count(type) > 0){
        QtLogger::error(QSL("[ComponentsManager::insert_new_component] Unique component already inside experiment."));
        return false;
    }

    const QString baseName = QString::fromStdString(std::string(Component::get_full_name(type)));
    size_t offset = 1;
    QString name;
    bool isInside = false;
    do{
        name = baseName %  ((offset != 1) ? (QSL(" ") % QString::number(offset)) : QSL(""));
        isInside = false;
        for(auto &component : components){
            if(component->name() == name){
                isInside = true;
                break;
            }
        }
        ++offset;
    }while(isInside);

    if(m_counter.count(type) == 0){
        m_counter[type] = 1;
    }else{
        m_counter[type]++;
    }

    auto component =
        std::make_unique<Component>(
        type, ComponentKey{-1}, name,
        std::make_unique<Config>("standard", ConfigKey{-1})
    );
    component->add_config(std::make_unique<Config>("standard", ConfigKey{-1}));

    components.insert(
        std::begin(components) + id.v,
        std::move(component)
    );
    return true;
}

bool ComponentsManager::update_component_name(ComponentKey componentKey, QString newName){

    if(newName.length() == 0){
        QtLogger::error(QSL("Component name must not be empty."));
        return false;
    }

    for(auto &component : components){
        if(component->name() == newName){
            QtLogger::error(QSL("Component name already used."));
            return false;
        }
    }

    if(auto component = get_component(componentKey); component != nullptr){
        component->set_name(newName);
        return true;
    }
    return false;
}

std::vector<Component *> ComponentsManager::get_components() const{
    std::vector<Component*> componentsPtr;
    componentsPtr.resize(components.size());
    for(auto &component : components){
        componentsPtr.push_back(component.get());
    }
    return componentsPtr;
}

std::vector<Component*> ComponentsManager::get_components(Component::Type type) const{
    std::vector<Component*> componentsOfType;
    for(auto &component : components){
        if(component->type == type){
            componentsOfType.push_back(component.get());
        }
    }
    return componentsOfType;
}

std::vector<Component *> ComponentsManager::get_components(Component::Category category) const{
    std::vector<Component*> componentsOfCategory;
    for(auto &component : components){
        if(component->category == category){
            componentsOfCategory.push_back(component.get());
        }
    }
    return componentsOfCategory;
}

