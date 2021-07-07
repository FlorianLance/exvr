
/*******************************************************************************
** exvr-export                                                                **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "ex_component_export.hpp"

using namespace tool;
using namespace tool::ex;

void delete_ex_component(ExComponent *c){delete c;}
int initialize_ex_component(ExComponent*c){return c->initialize()?1:0;}
void start_experiment_ex_component(ExComponent*c){c->start_experiment();}
void stop_experiment_ex_component(ExComponent*c){c->stop_experiment();}
void start_routine_ex_component(ExComponent*c){c->start_routine();}
void stop_routine_ex_component(ExComponent*c){c->stop_routine();}
void update_ex_component(ExComponent*c){c->update();}
void set_visibility_ex_component(ExComponent*c,int visible){c->set_visibility(visible==1);}
void set_update_state_ex_component(ExComponent *c, int doUpdate){c->set_update_state(doUpdate==1);}
void play_ex_component(ExComponent*c) {c->play();}
void pause_ex_component(ExComponent*c) {c->pause();}
void clean_ex_component(ExComponent*c) {c->clean();}
void call_slot_ex_component(ExComponent *c, int index){c->slot(index);}


ExComponent::ParametersContainer to_container(int containerId){
    return static_cast<ExComponent::ParametersContainer>(containerId);
}

void update_parameter_bool_ex_component(ExComponent *c, int containerId, const char* paramName, int value){
    c->update_parameter<bool>(to_container(containerId), paramName, value==1);
}
void update_parameter_int_ex_component(ExComponent *c, int containerId, const char* paramName, int value){
    c->update_parameter<int>(to_container(containerId),paramName, value);
}
void update_parameter_float_ex_component(ExComponent *c, int containerId, const char* paramName, float value){
    c->update_parameter<float>(to_container(containerId),paramName, value);
}
void update_parameter_double_ex_component(ExComponent *c, int containerId, const char* paramName, double value){
    c->update_parameter<double>(to_container(containerId),paramName, value);
}
void update_parameter_string_ex_component(ExComponent *c, int containerId, const char* paramName, const char* value){
    c->update_parameter<std::string>(to_container(containerId),paramName, std::string{value});
}

void update_parameter_array_int_ex_component(ExComponent *c, int containerId, const char *paramName, int *values, int size){
    std_v1<int> v(static_cast<size_t>(size));
    std::copy(values, values + size, v.begin());
    c->update_parameter_array<int>(to_container(containerId), paramName, std::move(v));
}

void update_parameter_array_float_ex_component(ExComponent *c, int containerId, const char *paramName, float *values, int size){
    std_v1<float> v(static_cast<size_t>(size));
    std::copy(values, values + size, v.begin());
    c->update_parameter_array<float>(to_container(containerId), paramName, std::move(v));
}

void update_parameter_array_double_ex_component(ExComponent *c, int containerId, const char *paramName, double *values, int size){
    std_v1<double> v(static_cast<size_t>(size));
    std::copy(values, values + size, v.begin());
    c->update_parameter_array<double>(to_container(containerId), paramName, std::move(v));
}

int get_size_parameter_array_ex_component(ExComponent *c, int containerId, const char *paramName){
    return c->get_array_size(to_container(containerId), paramName);
}

void get_parameter_array_int_ex_component(ExComponent *c, int containerId, const char *paramName, int *values){
    auto vec = c->get_array<int>(to_container(containerId), paramName);
    std::copy(std::begin(vec), std::end(vec), values);
}

void get_parameter_array_float_ex_component(ExComponent *c, int containerId, const char *paramName, float *values){
    auto vec = c->get_array<float>(to_container(containerId), paramName);
    std::copy(std::begin(vec), std::end(vec), values);
}

void get_parameter_array_double_ex_component(ExComponent *c, int containerId, const char *paramName, double *values){
    auto vec = c->get_array<double>(to_container(containerId), paramName);
    std::copy(std::begin(vec), std::end(vec), values);
}

int get_parameter_int_ex_component(ExComponent *c, int containerId, const char *paramName){
    return c->get<int>(to_container(containerId), paramName);
}

float get_parameter_float_ex_component(ExComponent *c, int containerId, const char *paramName){
    return c->get<float>(to_container(containerId), paramName);
}

double get_parameter_double_ex_component(ExComponent *c, int containerId, const char *paramName){
    return c->get<double>(to_container(containerId), paramName);
}

const char *get_parameter_string_ex_component(ExComponent *c, int containerId, const char *paramName){
    return c->const_get<std::string>(to_container(containerId), paramName).c_str();
}

int contains_ex_component(ExComponent *c, int containerId, const char *paramName){
    return c->contains(to_container(containerId), paramName) ? 1 : 0;
}

void init_callbacks_ex_component(
    StrackTraceCB strackTraceCB,
    LogCB logCB,
    LogWarningCB logWarningCB,
    LogErrorCB logErrorCB,
    EllapsedTimeExpMsCB ellapsedTimeExpMsCB,
    EllapsedTimeRoutineMsCB ellapsedTimeRoutineMsCB,
    GetCB getCB,
    IsInitializedCB isInitializedCB,
    IsVisibleCB isVisibleCB,
    IsUpdatingCB isUpdatingCB,
    IsClosedCB isClosedCB,
    NextCB nextCB,
    PreviousCB previousCB,
    CloseCB closeCB,
    SignalBoolCB signalBoolCB,
    SignalIntCB signalIntCB,
    SignalFloatCB signalFloatCB,
    SignalDoubleCB signalDoubleCB,
    SignalStringCB signalStringCB){

    ExComponent::strackTraceCB            = std::make_unique<StrackTraceCB>(strackTraceCB);
    ExComponent::logCB                    = std::make_unique<LogCB>(logCB);
    ExComponent::logWarningCB             = std::make_unique<LogWarningCB>(logWarningCB);
    ExComponent::logErrorCB               = std::make_unique<LogErrorCB>(logErrorCB);
    ExComponent::ellapsedTimeExpMsCB      = std::make_unique<EllapsedTimeExpMsCB>(ellapsedTimeExpMsCB);
    ExComponent::ellapsedTimeRoutineMsCB  = std::make_unique<EllapsedTimeRoutineMsCB>(ellapsedTimeRoutineMsCB);
    ExComponent::getCB                    = std::make_unique<GetCB>(getCB);
    ExComponent::isInitializedCB          = std::make_unique<IsInitializedCB>(isInitializedCB);
    ExComponent::isVisibleCB              = std::make_unique<IsVisibleCB>(isVisibleCB);
    ExComponent::isUpdatingCB             = std::make_unique<IsUpdatingCB>(isUpdatingCB);
    ExComponent::isClosedCB               = std::make_unique<IsClosedCB>(isClosedCB);
    ExComponent::nextCB                   = std::make_unique<NextCB>(nextCB);
    ExComponent::previousCB               = std::make_unique<PreviousCB>(previousCB);
    ExComponent::closeCB                  = std::make_unique<CloseCB>(closeCB);    
    ExComponent::signalBoolCB             = std::make_unique<SignalBoolCB>(signalBoolCB);
    ExComponent::signalIntCB              = std::make_unique<SignalIntCB>(signalIntCB);
    ExComponent::signalFloatCB            = std::make_unique<SignalFloatCB>(signalFloatCB);
    ExComponent::signalDoubleCB           = std::make_unique<SignalDoubleCB>(signalDoubleCB);
    ExComponent::signalStringCB           = std::make_unique<SignalStringCB>(signalStringCB);
}


