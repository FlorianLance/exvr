

/*******************************************************************************
** Toolset-base                                                               **
** MIT License                                                                **
** Copyright (c) [2024] [Florian Lance]                                       **
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
#include "utility/logger.hpp"

namespace tool {

class ExLoggerM : public Logger{

public:

    enum class SenderT : int {
        GUI, Component, Resource
    };

    static auto get_instance() noexcept -> ExLoggerM*{
        if(auto instance = BaseLogger::get_instance()){
            return dynamic_cast<ExLoggerM*>(instance);
        }
        return nullptr;
    }

    auto message_id(std::string_view message, SenderT sType, int sKey) -> void;
    auto warning_id(std::string_view warning, SenderT sType, int sKey) -> void;
    auto error_id(std::string_view error, SenderT sType, int sKey) -> void;    

    // signals
    sigslot::signal<std::string, SenderT, int> message_id_signal;
    sigslot::signal<std::string, SenderT, int> warning_id_signal;
    sigslot::signal<std::string, SenderT, int> error_id_signal;
    sigslot::signal<std::string, int> status_signal;
    sigslot::signal<int> progress_signal;
};

}

