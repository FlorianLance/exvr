

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

#include "ex_component.hpp"

using namespace tool::ex;

bool ExComponent::is_visible(int cKey){
    if(exp->isVisibleCBP != nullptr){
        return (*exp->isVisibleCBP)(cKey);
    }else{
        return false;
    }
}

bool ExComponent::is_updating(int cKey){
    if(exp->isUpdatingCBP != nullptr){
        return (*exp->isUpdatingCBP)(cKey);
    }else{
        return false;
    }
}

bool ExComponent::is_closed(int cKey){
    if(exp->isClosedCBP != nullptr){
        return (*exp->isClosedCBP)(cKey);
    }else{
        return false;
    }
}

long ExComponent::ellapsed_time_exp_ms(){
    if(exp->ellapsedTimeExpMsCBP != nullptr){
        return (*exp->ellapsedTimeExpMsCBP)();
    }else{
        return 0;
    }
}

long ExComponent::ellapsed_time_routine_ms(){
    if(exp->ellapsedTimeRoutineMsCBP != nullptr){
        return (*exp->ellapsedTimeRoutineMsCBP)();
    }else{
        return 0;
    }
}

void ExComponent::signal_bool(int index, bool value){
    if(exp->signalBoolCBP != nullptr){
        (*exp->signalBoolCBP)(key(), index, value ? 1 : 0);
    }else{

    }
}

void ExComponent::signal_int(int index, int value){
    if(exp->signalIntCBP != nullptr){
        (*exp->signalIntCBP)(key(), index, value);
    }else{

    }
}

void ExComponent::signal_float(int index, float value){
    if(exp->signalFloatCBP != nullptr){
        (*exp->signalFloatCBP)(key(), index, value);
    }else{

    }
}

void ExComponent::signal_double(int index, double value){
    if(exp->signalDoubleCBP != nullptr){
        (*exp->signalDoubleCBP)(key(), index, value);
    }else{

    }
}

void ExComponent::signal_string(int index, std::string value){
    if(exp->signalStringCBP != nullptr){
        (*exp->signalStringCBP)(key(), index, value.c_str());
    }else{

    }
}

