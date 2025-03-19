
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

#include "ex_element.hpp"

using namespace tool;
using namespace ex;

auto ExElement::set_exp(ExExperiment *e) -> void{
    exp = e;
}

auto ExElement::get_array_size(ParametersContainer pc, std::string_view name) const -> int{
    if(contains_array(pc, name)){
        return std::get<1>(arrayContainers.at(pc).at(name));
    }
    Log::error(std::format("get_array_size: no value with name {}", name));
    return 0;
}

auto ExElement::log_message(std::string message) -> void{
    if(exp->logMessageIdCBP != nullptr){
        (*exp->logMessageIdCBP)(message.c_str(), (int)sender_type(), key());
    }else{

    }
}

auto ExElement::log_warning(std::string warningMessage) -> void{
    if(exp->logWarningIdCBP != nullptr){
        (*exp->logWarningIdCBP)(warningMessage.c_str(), (int)sender_type(), key());
    }else{

    }
}

auto ExElement::log_error(std::string errorMessage) -> void{
    if(exp->logErrorIdCBP != nullptr){
        (*exp->logErrorIdCBP)(errorMessage.c_str(), (int)sender_type(), key());
    }else{

    }
}

auto ExElement::stack_trace_log(std::string stackTraceMessage) -> void{
    if(exp->stackTraceCBP != nullptr){
        (*exp->stackTraceCBP)(stackTraceMessage.c_str());
    }else{

    }
}

auto ExElement::next() -> void{
    if(exp->nextCBP != nullptr){
        (*exp->nextCBP)();
    }else{

    }
}

auto ExElement::previous() -> void{
    if(exp->previousCBP != nullptr){
        (*exp->previousCBP)();
    }else{

    }
}

auto ExElement::pause_editor() -> void{
    if(exp->pauseEditorCBP != nullptr){
        (*exp->pauseEditorCBP)();
    }else{

    }
}

auto ExElement::close(int key) -> void{
    if(exp->closeCBP != nullptr){
        (*exp->closeCBP)(key);
    }else{

    }
}

auto ExElement::component_key(std::string componentName) -> int{
    return (*exp->getCBP)(componentName.c_str());
}
