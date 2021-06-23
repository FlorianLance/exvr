
/*******************************************************************************
** exvr-export                                                                **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// components
#include "exvr/ex_component.hpp"

// export
#include "export_utility.hpp"

extern "C"{

    DECL_EXPORT void delete_ex_component(tool::ex::ExComponent *c);
    DECL_EXPORT int initialize_ex_component(tool::ex::ExComponent*c);
    DECL_EXPORT void start_experiment_ex_component(tool::ex::ExComponent*c);
    DECL_EXPORT void stop_experiment_ex_component(tool::ex::ExComponent*c);
    DECL_EXPORT void start_routine_ex_component(tool::ex::ExComponent*c);
    DECL_EXPORT void stop_routine_ex_component(tool::ex::ExComponent*c);
    DECL_EXPORT void update_ex_component(tool::ex::ExComponent*c);
    DECL_EXPORT void set_visibility_ex_component(tool::ex::ExComponent*c,int visible);
    DECL_EXPORT void set_update_state_ex_component(tool::ex::ExComponent*c,int doUpdate);
    DECL_EXPORT void play_ex_component(tool::ex::ExComponent*c);
    DECL_EXPORT void pause_ex_component(tool::ex::ExComponent*c);
    DECL_EXPORT void clean_ex_component(tool::ex::ExComponent*c);
    DECL_EXPORT void call_slot_ex_component(tool::ex::ExComponent*c, int index);

    DECL_EXPORT int contains_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName);

    DECL_EXPORT void update_parameter_bool_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, int value);
    DECL_EXPORT void update_parameter_int_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, int value);
    DECL_EXPORT void update_parameter_float_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, float value);
    DECL_EXPORT void update_parameter_double_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, double value);
    DECL_EXPORT void update_parameter_string_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, const char* value);

    DECL_EXPORT int get_parameter_int_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName);
    DECL_EXPORT float get_parameter_float_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName);
    DECL_EXPORT double get_parameter_double_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName);
    DECL_EXPORT const char* get_parameter_string_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName);

    DECL_EXPORT int get_size_parameter_array_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName);
    DECL_EXPORT void get_parameter_array_int_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, int* values);
    DECL_EXPORT void get_parameter_array_float_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, float* values);
    DECL_EXPORT void get_parameter_array_double_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, double* values);

//    DECL_EXPORT void update_parameter_array_bool_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, bool* values, int size);
    DECL_EXPORT void update_parameter_array_int_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, int* values, int size);
    DECL_EXPORT void update_parameter_array_float_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, float* values, int size);
    DECL_EXPORT void update_parameter_array_double_ex_component(tool::ex::ExComponent*c, int containerId, const char* paramName, double* values, int size);

    DECL_EXPORT void init_callbacks_ex_component(
        StrackTraceCB strackTraceCB,
        LogCB logCB,
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
        SignalStringCB signalStringCB
    );
}

