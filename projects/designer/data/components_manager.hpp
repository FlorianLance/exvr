
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <unordered_map>
#include <set>

// Qt
#include <QStringList>
#include <QDebug>

// base
#include "utility/vector_utility.hpp"

// qt-utility
#include "qt_logger.hpp"

// local
#include "component.hpp"


namespace tool::ex {

class ComponentsManager;
using ComponentsManagerUP = std::unique_ptr<ComponentsManager>;

class ComponentsManager{

public:

    static void init();
    static ComponentsManager *get();

    void clean_components();
    void sort_by_category();
    void sort_by_type();
    void sort_by_name();

    Component *get_component(ComponentKey componentKey, bool displayError= true) const;
    Component *get_component(Component::Type type, const QString &name) const;

    std::pair<size_t, Component*> get_component_and_position(ComponentKey componentKey) const;

    void insert_new_component(Component::Type type, RowId id);
    bool update_component_name(ComponentKey componentKey, QString newName);

    std_v1<Component*> get_components(Component::Type type) const;    

    std_v1<ComponentUP> components;


private:

    static inline ComponentsManagerUP m_componentsManager = nullptr;

    // TODO: add map (for quick access to types)
};
}
