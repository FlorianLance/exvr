
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#pragma once

// local
// # data
#include "routine.hpp"
#include "isi.hpp"
#include "loop.hpp"
#include "settings.hpp"
#include "gui.hpp"
#include "interval.hpp"
#include "argument.hpp"
#include "components_manager.hpp"
#include "states.hpp"
// # resources
#include "resources/resources_manager.hpp"
// # experiment
#include "randomizer.hpp"


namespace tool::ex{

// ############################################################################### CONSTANTS

constexpr static int UpdateFlow        = 0b1;
constexpr static int UpdateSelection   = 0b10;
constexpr static int UpdateComponents  = 0b100;
constexpr static int UpdateRoutines    = 0b1000;
constexpr static int UpdateUI          = 0b10000;
constexpr static int UpdateResources   = 0b100000;
[[maybe_unused]] constexpr static int ResetUI   = 0b1000000;
[[maybe_unused]] constexpr static int UpdateAll = UpdateComponents | UpdateFlow | UpdateSelection | UpdateUI | UpdateRoutines | UpdateResources;

enum class Update{
    ELEMENT, select_element,unselect_elements, add_element, remove_element, move_element, modify_element_name,
    ROUTINE, select_condition, move_condition,
    CONDITION, modify_condition,
    ACTION, fill_action, remove_actions,
};


struct Up{

    Up(bool all) : m_all(all){
    }

    Up(std_v1<Update> updates){
        for(auto &update : updates){
            m_updates.emplace(update);
        }
    }

    bool check(Update u) const{
        return m_all ? true : (m_updates.count(u) != 0);
    }

private:
    bool m_all = false;
    std::unordered_set<Update> m_updates;
};


class Experiment;
using ExperimentUP = std::unique_ptr<Experiment>;

class Experiment : public QObject{

    Q_OBJECT

public:

    Experiment(QString nVersion);



    void set_update_all_flag(){
        updateFlag = UpdateAll;
    }

    void add_to_update_flag(int flag){
        updateFlag |= flag;
    }

    void reset_update_flag(){
        updateFlag = 0;
    }

    // getters
    Element *get_element(ElementKey elementKey) const;
    Routine *get_routine(ElementKey routineKey) const;
    Isi *get_isi(ElementKey isiKey) const;
    Loop *get_loop(ElementKey loopKey) const;
    Condition *get_condition(ConditionKey conditionKey) const;
    Condition *get_condition(ElementKey routineKey, ConditionKey conditionKey) const;
    Action *get_action(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey) const;
    Component *get_component(ComponentKey componentKey) const;
    Config *get_config(ComponentKey componentKey, ConfigKey configKey) const;

    // check
    void check_integrity();

public slots:

    // update
    void compute_loops_levels();
    void update_conditions();
    // # randomization
    void update_randomization_seed(unsigned int seed);

    // files
    void new_experiment();
    void clean_experiment();
    void set_instance_name(QString instanceName);

    // settings
    void reset_settings();
    void update_settings(Settings settings);

    // resources
    void add_resources(Resource::Type type, QStringList filesPath);
    void update_resource_path(QString currentPath, QString newPath);
    void update_resource_alias(QString currentAlias, QString newAlias);
    void select_resource(Resource::Type type, size_t index);
    void remove_resource(Resource::Type type, size_t index);
    void clean_resources(Resource::Type type);
    void update_reload_resource_code(int reloadCode);

    // ui
    void toggle_actions_connections_separation();
    void toggle_design_mode();
    void toggle_follow_condition_mode();
    // # infos
    void update_connector_dialog_with_info(ElementKey elementKey, ConditionKey conditionKey, ConnectorKey connectorKey, QStringView id, QStringView value);
    void update_component_dialog_with_info(ComponentKey componentKey, ConfigKey configKey, QStringView id, QStringView value);
    // # states
    void update_exp_launcher_state(ExpLauncherState state, QStringView infos);
    void update_exp_state(ExpState state, QStringView infos);

    // components
    void add_component(Component::Type type, RowId id);
    void duplicate_component(ComponentKey componentKey);
    void remove_component(ComponentKey componentKey);
    void update_component_position(ComponentKey componentKey, RowId id);
    void update_component_name(ComponentKey componentKey, QString name);
    void sort_components_by_category();
    void sort_components_by_type();
    void sort_components_by_name();
    // # components configs
    void insert_config_in_component(ComponentKey componentKey, RowId id, QString configName);
    void copy_config_from_component(ComponentKey componentKey, RowId id, QString configName);
    void remove_config_from_component(ComponentKey componentKey, RowId id);
    void move_config_in_component(ComponentKey componentKey, RowId from, RowId to);
    void rename_config_in_component(ComponentKey componentKey, RowId id, QString configName);
    // ## arguments
    void arg_updated(ComponentKey componentKey, ConfigKey configKey, QString name, Arg arg, bool initConfig);
    void arg_removed(ComponentKey componentKey, ConfigKey configKey, QString name, bool initConfig);
    void move_arg_up(ComponentKey componentKey, ConfigKey configKey, QString previousName, QString name, bool initConfig);
    void move_arg_down(ComponentKey componentKey, ConfigKey configKey, QString nextName, QString name, bool initConfig);
    void new_arg(ComponentKey componentKey, ConfigKey configKey, QString name, Arg arg, bool initConfig);

    // elements
    size_t get_element_position(Element *element) const;
    void unselect_all_elements(bool updateSignal = true) noexcept;
    void select_element(ElementKey elementKey, bool updateSignal = true);
    void add_element(Element::Type type, size_t index);
    void remove_element(Element *elemToDelete);    
    void remove_element_of_key(ElementKey elementKey);
    void duplicate_element(ElementKey elementKey);
    void clean_current_routine_condition(ElementKey routineKey);
    void clean_all_routine_conditions(ElementKey routineKey);
    void set_duration_for_all_routine_conditions(ElementKey routineKey);
    void remove_selected_element();
    void move_left(size_t id);
    void move_right(size_t id);
    void update_element_name(ElementKey elementKey, QString elemName);

    // # loop
    void select_loop_set(ElementKey loopKey, QString setName);
    void add_loop_sets(ElementKey loopKey, QString sets, RowId id);
    void modify_loop_set_name(ElementKey loopKey, QString setName, RowId id);
    void modify_loop_set_occurrencies_nb(ElementKey loopKey, int setOccuranciesNb, RowId id);
    void modify_loop_type(ElementKey loopKey, Loop::Mode type);
    void modify_loop_nb_reps(ElementKey loopKey, int nbReps);
    void remove_set(ElementKey loopKey, RowId id);
    void move_loop_set_up(ElementKey loopKey, RowId id);
    void move_loop_set_down(ElementKey loopKey, RowId id);
    void load_loop_sets_file(ElementKey loopKey, QString path);
    void reload_loop_sets_file(ElementKey loopKey);

    // # isi
    void add_isi_interval(ElementKey isiKey, qreal value, RowId id);
    void remove_isi_interval(ElementKey isiKey, RowId id);
    void set_isi_randomize(ElementKey isiKey, bool randomize);
    void modify_isi_interval(ElementKey isiKey, qreal value, RowId id);
    void move_isi_interval_up(ElementKey isiKey, RowId id);
    void move_isi_interval_down(ElementKey isiKey, RowId id);

    // # routine
    void select_routine_condition(ElementKey routineKey, RowId  conditionTabId);
    void move_routine_condition_down(ElementKey routineKey, RowId id);
    void move_routine_condition_up(ElementKey routineKey, RowId id);
    void set_routine_as_randomizer(ElementKey routineKey, bool isARandomizer);
    // ## condition
    void update_condition_timeline(ElementKey routineKey, ConditionKey conditionKey, double duration, double scale, double uiFactorSize);
    void copy_to_conditions(ElementKey routineKey, ConditionKey conditionKey, std_v1<std::pair<ElementKey,ConditionKey>> conditionsToBeEcrased, bool copyActions, bool copyConnections);
    void delete_actions_from_condition(ElementKey routineKey, ConditionKey conditionKey);
    void fill_actions_from_condition(ElementKey routineKey, ConditionKey conditionKey);
    void clean_actions_from_condition(ElementKey routineKey, ConditionKey conditionKey);
    // ### action
    void add_action(ElementKey routineKey, ConditionKey conditionKey, ComponentKey componentKey);
    void add_action_to_all_selected_routine_conditions(ElementKey routineKey, ComponentKey componentKey);
    void add_action_to_all_routines_conditions(ComponentKey componentKey);
    void remove_action_from_all_selected_routine_conditions(ElementKey routineKey, ComponentKey componentKey);
    void remove_action_from_all_routines_conditions(ComponentKey componentKey);
    void remove_action_from_condition(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, bool update = true);
    void fill_action(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, bool update, bool visibility);
    void clean_action(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, bool update, bool visibility);
    void move_action_up(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey);
    void move_action_down(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey);
    // #### timeline
    void add_timeline_interval(ElementKey routineKey,ConditionKey conditionKey, ActionKey actionKey, bool updateTimeline, TimelineKey timelineKey, Interval interval);
    void remove_timeline_interval(ElementKey routineKey,ConditionKey conditionKey, ActionKey actionKey, bool updateTimeline, TimelineKey timelineKey, Interval interval);
    // #### config
    void select_config(ElementKey routineKey, ConditionKey conditionKey, ActionKey actionKey, RowId  configTabId);
    // ### connection
    void create_connection(ElementKey routineKey,ConditionKey conditionKey, Connection *connection);
    void delete_connections(ElementKey routineKey, ConditionKey conditionKey);
    // ### component node
    void create_component_node(ElementKey routineKey,ConditionKey conditionKey, ComponentKey componentKey, QPointF pos);
    void move_component_node(ElementKey routineKey,ConditionKey conditionKey, ComponentKey componentKey, QPointF pos);
    // ### connector node
    void create_connector_node(ElementKey routineKey,ConditionKey conditionKey, Connector *connector);
    void modify_connector_node(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey, QString name, Arg arg);
    void move_connector_node(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey, QPointF pos);
    void duplicate_connector_node(ElementKey routineKey,ConditionKey conditionKey, ConnectorKey connectorKey);
    void set_connector_input_connection_validity(ElementKey routineKey, ConditionKey conditionKey, ConnectorKey connectorKey, bool state);
    // ### connections / connectors / components
    void unselect_nodes_and_connections(ElementKey routineKey, ConditionKey conditionKey, bool doUpdate);
    void delete_nodes_and_connections(ElementKey routineKey, ConditionKey conditionKey,
                                      std_v1<ConnectorKey> connectorsKey, std_v1<ComponentKey> componentsKey, std_v1<ConnectionKey> connectionsKey, bool doUpdate);
    void select_nodes_and_connections(ElementKey routineKey, ConditionKey conditionKey,
                                      std_v1<ConnectorKey> connectorsKey, std_v1<ComponentKey> componentsKey, std_v1<ConnectionKey> connectionsKey, bool doUpdate);



private :    

    // clean
    void remove_elements_not_in_flow();

public :

    std_v1<Loop*> get_loops() const;
    std_v1<Element*> get_elements() const;
    std_v1<Element*> get_elements_from_type(Element::Type type) const;

    template<class T>
    std_v1<T*> get_elements_from_type() const{
        std_v1<T*> children;
        for(const auto &elem : elements){
            if(auto child = dynamic_cast<T*>(elem.get()); child != nullptr){
                children.emplace_back(child);
            }
        }
        return children;
    }

    template<class T>
    T* get_element_from_type_and_id(ElementKey key) const{
        for(const auto &elem : elements){
            if(T* child = dynamic_cast<T*>(elem.get()); child != nullptr){
                if(elem->key() == key.v){
                    return child;
                }
            }
        }
        return nullptr;
    }

public :

    Settings settings;
    GUI gui;
    Randomizer randomizer;

    // elements
    std_v1<ElementUP> elements;
    std_v1<LoopUP> loops; // not in the flow
    Element *selectedElement = nullptr;
    Routine *lastRoutineSelected = nullptr;
    Isi *lastIsiSelected = nullptr;

    // states
    States states;

    // infos
    using UiKey   = QStringView;
    using UiValue = QStringView;
    template<class T1,class T2>
    using umap = std::unordered_map<T1,T2>;
    umap<int, umap<int, umap<int, umap<UiKey, UiValue>>>> connectorsInfo;
    umap<int, umap<int, umap<UiKey, UiValue>>>  componentsInfo;

    // update
    int updateFlag = 0;

private :

    // components
    ComponentsManager *m_compM = nullptr;

    // resources
    ResourcesManager *m_resM = nullptr;
};
}

