

/***********************************************************************************
** exvr-export                                                                    **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

#include "ex_experiment_export.hpp"

// base
#include "utility/logger.hpp"

using namespace tool::ex;

ExExperiment *create_ex_experiment(){
    return new ExExperiment();
}

void delete_ex_experiment(tool::ex::ExExperiment *e){
    delete e;
}

void init_callbacks_ex_experiment(
    tool::ex::ExExperiment *e,
    LogMessageCB logMessageCB,
    LogWarningCB logWarningCB,
    LogErrorCB logErrorCB,
    LogMessageIdCB logMessageIdCB,
    LogWarningIdCB logWarningIdCB,
    LogErrorIdCB logErrorIdCB,
    StackTraceCB stackTraceCB,
    PauseEditorCB pauseEditorCB,
    EllapsedTimeExpMsCB ellapsedTimeExpMsCB,
    EllapsedTimeRoutineMsCB ellapsedTimeRoutineMsCB,
    GetCB getCB,
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
    ){

    e->init_callbacks(
        logMessageCB, logWarningCB, logErrorCB,
        logMessageIdCB, logWarningIdCB, logErrorIdCB, stackTraceCB, pauseEditorCB,
        ellapsedTimeExpMsCB, ellapsedTimeRoutineMsCB,
        getCB, isVisibleCB, isUpdatingCB, isClosedCB,
        nextCB, previousCB, closeCB,
        signalBoolCB,signalIntCB,signalFloatCB,signalDoubleCB,signalStringCB
    );
}


int init_logger_ex_experiment(tool::ex::ExExperiment *e, const char *pathDir, const char *fileName){
    return e->generate_logger(pathDir,fileName) ? 1 : 0;
}

void init_logger_no_file_ex_experiment(tool::ex::ExExperiment *e){
    e->generate_logger_no_file();
}

void test_call_backs_ex_experiment(tool::ex::ExExperiment *e){
    (*e->logMessageCBP)("test_message_callback_1");
    (*e->logWarningCBP)("test_warning_callback_1");
    (*e->logErrorCBP)("test_error_callback_1");
    tool::Log::get()->message("test_message_callback_2");
    tool::Log::get()->warning("test_warning_callback_2");
    tool::Log::get()->error("test_error_callback_2");
    tool::Log::message("test_message_callback_3");
    tool::Log::warning("test_warning_callback_3");
    tool::Log::error("test_error_callback_3");
}

void test_log_ex_experiment(tool::ExLoggerM *logger){
    logger->message("test_log_message1");
    logger->warning("test_log_warning1");
    logger->error("test_log_error1");
}

tool::ExLoggerM *get_logger_ptr_ex_experiment(tool::ex::ExExperiment *e){
    return tool::ExLoggerM::get_instance();
}
