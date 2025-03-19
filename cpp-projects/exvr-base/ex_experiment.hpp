

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

// std
#include <memory>
#include <string>
#include <unordered_map>
#include <any>

// local
#include "utility/format.hpp"
#include "utility/tuple_array.hpp"
#include "ex_logger.hpp"


typedef void (__stdcall * LogMessageCB)(const char*);
typedef void (__stdcall * LogWarningCB)(const char*);
typedef void (__stdcall * LogErrorCB)(const char*);

typedef void (__stdcall * LogMessageIdCB)(const char*, int, int);
typedef void (__stdcall * LogWarningIdCB)(const char*, int, int);
typedef void (__stdcall * LogErrorIdCB)(const char*, int, int);

typedef int (__stdcall * GetCB)(const char*);
typedef int (__stdcall * IsVisibleCB)(int);
typedef int (__stdcall * IsUpdatingCB)(int);
typedef int (__stdcall * IsClosedCB)(int);

typedef void (__stdcall * SignalBoolCB)(int, int,int);
typedef void (__stdcall * SignalIntCB)(int, int,int);
typedef void (__stdcall * SignalFloatCB)(int, int,float);
typedef void (__stdcall * SignalDoubleCB)(int, int,double);
typedef void (__stdcall * SignalStringCB)(int, int,const char*);

typedef void (__stdcall * NextCB)();
typedef void (__stdcall * PreviousCB)();
typedef void (__stdcall * CloseCB)(int);

typedef long (__stdcall * EllapsedTimeExpMsCB)();
typedef long (__stdcall * EllapsedTimeRoutineMsCB)();

// debug
typedef void (__stdcall * StackTraceCB)(const char*);
typedef void (__stdcall * PauseEditorCB)();

namespace tool::ex {

class ExExperiment{
public:

    bool generate_logger(std::string_view pathDir, std::string_view fileName);
    void generate_logger_no_file();
    
    // std::unique_ptr<Logger, LoggerCleaner> logger = nullptr;

    std::unique_ptr<LogMessageCB> logMessageCBP = nullptr;
    std::unique_ptr<LogWarningCB> logWarningCBP = nullptr;
    std::unique_ptr<LogErrorCB> logErrorCBP     = nullptr;
    std::unique_ptr<LogMessageIdCB> logMessageIdCBP = nullptr;
    std::unique_ptr<LogWarningIdCB> logWarningIdCBP = nullptr;
    std::unique_ptr<LogErrorIdCB> logErrorIdCBP     = nullptr;
    std::unique_ptr<EllapsedTimeExpMsCB> ellapsedTimeExpMsCBP = nullptr;
    std::unique_ptr<EllapsedTimeRoutineMsCB> ellapsedTimeRoutineMsCBP = nullptr;
    std::unique_ptr<GetCB> getCBP = nullptr;
    std::unique_ptr<IsVisibleCB> isVisibleCBP= nullptr;
    std::unique_ptr<IsUpdatingCB> isUpdatingCBP= nullptr;
    std::unique_ptr<IsClosedCB> isClosedCBP= nullptr;
    std::unique_ptr<NextCB> nextCBP = nullptr;
    std::unique_ptr<PreviousCB> previousCBP = nullptr;
    std::unique_ptr<CloseCB> closeCBP = nullptr;
    std::unique_ptr<SignalBoolCB> signalBoolCBP= nullptr;
    std::unique_ptr<SignalIntCB> signalIntCBP= nullptr;
    std::unique_ptr<SignalFloatCB> signalFloatCBP= nullptr;
    std::unique_ptr<SignalDoubleCB> signalDoubleCBP= nullptr;
    std::unique_ptr<SignalStringCB> signalStringCBP= nullptr;

    std::unique_ptr<StackTraceCB> stackTraceCBP     = nullptr;
    std::unique_ptr<PauseEditorCB> pauseEditorCBP   = nullptr;

    void init_callbacks(
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
    );
};
}

