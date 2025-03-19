


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

#include "ex_logger.hpp"

// std
#include <iostream>

auto tool::ExLoggerM::message_id(std::string_view message, SenderT sType, int sKey) -> void{

    const auto &conf = config(MessageType::normal);
    if(conf.displayToConsole){
        std::cout << message;
    }

    if(conf.saveToFile && !conf.formatHTMLForFile){
        insert_to_log_file(message, false);
    }

    if((conf.saveToFile && conf.formatHTMLForFile) || (conf.triggerSignals && conf.formatHTMLForSignals)){
        auto htmlMessage = to_html_paragraph(conf.htmlColor, message, conf.addTimestampToHtml);
        if(conf.saveToFile && conf.formatHTMLForFile){
            insert_to_log_file(htmlMessage, false);
        }
        if(conf.triggerSignals && conf.formatHTMLForSignals){
            message_id_signal(std::move(htmlMessage), sType, sKey);
        }
    }

    if(conf.triggerSignals && !conf.formatHTMLForSignals){
        message_id_signal(std::string(message), sType, sKey);
    }
}

auto tool::ExLoggerM::warning_id(std::string_view warning, SenderT sType, int sKey) -> void{

    const auto &conf = config(MessageType::warning);
    if(conf.displayToConsole){
        std::cerr << warning;
    }

    if(conf.saveToFile && !conf.formatHTMLForFile){
        insert_to_log_file(warning, true);
    }

    if((conf.saveToFile && conf.formatHTMLForFile) || (conf.triggerSignals && conf.formatHTMLForSignals)){
        auto htmlWarning = to_html_paragraph(conf.htmlColor, warning, conf.addTimestampToHtml);
        if(conf.saveToFile && conf.formatHTMLForFile){
            insert_to_log_file(htmlWarning, true);
        }
        if(conf.triggerSignals && conf.formatHTMLForSignals){
            warning_id_signal(std::move(htmlWarning), sType, sKey);
        }
    }

    if(conf.triggerSignals && !conf.formatHTMLForSignals){
        warning_id_signal(std::string(warning), sType, sKey);
    }
}

auto tool::ExLoggerM::error_id(std::string_view error, SenderT sType, int sKey) -> void{

    const auto &conf = config(MessageType::error);
    if(conf.displayToConsole){
        std::cerr << error;
    }

    if(conf.saveToFile && !conf.formatHTMLForFile){
        insert_to_log_file(error, true);
    }

    if((conf.saveToFile && conf.formatHTMLForFile) || (conf.triggerSignals && conf.formatHTMLForSignals)){
        auto htmlError = to_html_paragraph(conf.htmlColor, error, conf.addTimestampToHtml);
        if(conf.saveToFile && conf.formatHTMLForFile){
            insert_to_log_file(htmlError, true);
        }
        if(conf.triggerSignals && conf.formatHTMLForSignals){
            error_id_signal(std::move(htmlError), sType, sKey);
        }
    }

    if(conf.triggerSignals && !conf.formatHTMLForSignals){
        error_id_signal(std::string(error), sType, sKey);
    }
}
