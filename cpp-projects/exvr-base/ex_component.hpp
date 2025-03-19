

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

// local
#include "ex_element.hpp"

namespace tool::ex {


class ExComponent : public ExElement{

public:

    virtual ~ExComponent(){}

    virtual bool initialize(){return true;}
    virtual void clean(){}

    virtual void start_experiment(){}
    virtual void stop_experiment(){}

    virtual void set_current_config(const std::string &configName){static_cast<void>(configName);}
    virtual void update_from_current_config(){}
    virtual void pre_start_routine(){}
    virtual void start_routine(){}
    virtual void post_start_routine(){}
    virtual void stop_routine(){}

    virtual void on_gui(){}
    virtual void pre_update(){}
    virtual void update(){}
    virtual void post_update(){}

    virtual void set_visibility(bool visible){static_cast<void>(visible);}
    virtual void set_update_state(bool doUpdate){static_cast<void>(doUpdate);}    
    virtual void play(){}
    virtual void pause(){}

    virtual void update_parameter_from_gui(const std::string &updatedParameter){static_cast<void>(updatedParameter);}
    virtual void action_from_gui(bool initConfig, const std::string &action){static_cast<void>(initConfig);static_cast<void>(action);}

    virtual void slot(int index){static_cast<void>(index);}

    int key() override{
        return get<int>(ParametersContainer::Global, "component_key");
    }
    
    ExLoggerM::SenderT sender_type() override{
        return ExLoggerM::SenderT::Component;
    }

    // callbacks
    bool is_visible(int cKey);
    bool is_updating(int cKey);
    bool is_closed(int cKey);

    long ellapsed_time_exp_ms();
    long ellapsed_time_routine_ms();

    void signal_bool(int index, bool value);
    void signal_int(int index, int value);
    void signal_float(int index, float value);
    void signal_double(int index, double value);
    void signal_string(int index, std::string value);

};
}

