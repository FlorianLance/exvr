

/*******************************************************************************
** Toolset-base                                                               **
** MIT License                                                                **
** Copyright (c) [2018] [Florian Lance]                                       **
**                                                                            **
** Permission is hereby granted, free of charge, to any person obtaining a    **
** copy of this software and associated documentation files (the "Software"), **
** to deal in the Software without restriction, including without limitation  **
** the rights to use, copy, modify, merge, publish, distribute, sublicense,   **
** and/or sell copies of the Software, and to permit persons to whom the      **
** Software is furnished to do so, subject to the following conditions:       **
**                                                                            **
** The above copyright notice and this permission notice shall be included in **
** all copies or substantial portions of the Software.                        **
**                                                                            **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    **
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    **
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        **
** DEALINGS IN THE SOFTWARE.                                                  **
**                                                                            **
********************************************************************************/

#pragma once

// base
#include "utility/unordered_map.hpp"
#include "utility/string_unordered_map.hpp"

// local
#include <any>

// local
#include "ex_experiment.hpp"

namespace tool::ex {

using namespace std::literals::string_view_literals;

enum class ParametersContainer : int {
    InitConfig=0, CurrentConfig=1, Dynamic=2, Global=3,SizeEnum
};

using PC  = ParametersContainer;
using Name = std::string_view;
using TParametersContainer = std::tuple<PC, Name>;

static constexpr TupleArray<ParametersContainer::SizeEnum,TParametersContainer> parametersContainers ={{
    TParametersContainer
    {PC::InitConfig,     "init"sv  },
    {PC::CurrentConfig,  "current"sv },
    {PC::Dynamic,        "dynamic"sv },
    {PC::Global,         "global"sv },
}};

[[maybe_unused]] constexpr static auto get_name(ParametersContainer pc) -> Name{
    return parametersContainers.at<0,1>(pc);
}

class ExElement{
public:

    auto set_exp(tool::ex::ExExperiment *e) -> void;

    // callbacks
    auto log_warning(std::string warningMessage) -> void;
    auto log_error(std::string errorMessage) -> void;
    auto log_message(std::string message) -> void;
    auto stack_trace_log(std::string stackTraceMessage) -> void;
    auto close(int cKey) -> void;
    auto next() -> void;
    auto previous() -> void;
    auto pause_editor() -> void;
    auto component_key(std::string componentName) -> int;

    // containers
    auto contains(ParametersContainer pc, std::string_view name) const -> bool{
        if(containers.contains(pc)){
            return containers.at(pc).contains(name);
        }
        return false;
    }

    template<typename T>
    auto get(ParametersContainer pc, std::string_view name) -> T{
        if(contains(pc,name)){
            try{
                return std::any_cast<T>(containers[pc][name]);
            }catch (const std::bad_any_cast& e){
                log_error(std::format("get: cast error: {}", e.what()));
            }
        }
        return T{};
    }

    template<typename T>
    auto get_ptr(ParametersContainer pc, std::string_view name) -> T*{
        if(contains(pc,name)){
            try{
                return std::any_cast<T>(&containers[pc][name]);
            }catch (const std::bad_any_cast& e){
                log_error(std::format("get_ptr: cast error: {}", e.what()));
            }
        }
        return nullptr;
    }


    template<typename T>
    auto set(ParametersContainer pc, std::string_view name, T value) -> void{
        if(!containers.contains(pc)){
            containers[pc] = {};
        }
        containers[pc][name] = value;
    }

    // array
    auto contains_array(ParametersContainer pc, std::string_view name) const -> bool{
        if(arrayContainers.contains(pc)){
            return arrayContainers.at(pc).contains(name);
        }
        return false;
    }

    template<typename T>
    auto set_array(ParametersContainer pc, std::string_view name, std::vector<T> values) -> void{
        if(!containers.contains(pc)){
            arrayContainers[pc] = {};
        }
        arrayContainers[pc][name] = std::make_tuple(std::move(values), static_cast<int>(values.size()));
    }

    template<typename T>
    auto get_array(ParametersContainer pc, std::string_view name) -> std::vector<T>{
        if(contains_array(pc,name)){
            try{
                return std::any_cast<std::vector<T>>(std::get<0>(arrayContainers[pc][name]));
            }catch (const std::bad_any_cast& e){
                log_error(std::format("get_array: cast error: {}", e.what()));
            }
        }
        return std::vector<T>{};
    }

    auto get_array_size(ParametersContainer pc, std::string_view name) const -> int;


    virtual auto key() -> int = 0;
    virtual auto sender_type() -> ExLoggerM::SenderT = 0;

    tool::ex::ExExperiment *exp = nullptr;

protected:

    umap<ParametersContainer, s_umap<std::string, std::any>> containers = {
        {ParametersContainer::Global,        {}}
    };
    umap<ParametersContainer, s_umap<std::string, std::tuple<std::any,int>>> arrayContainers{
        {ParametersContainer::Global,        {}}
    };
};
}

