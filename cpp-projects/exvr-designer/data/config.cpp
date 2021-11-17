
/***********************************************************************************
** exvr-designer                                                                  **
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


#include "config.hpp"

// qt-utility
#include "qt_logger.hpp"

using namespace tool::ex;

ConfigUP Config::copy_with_new_element_id(const Config &configToCopy, const QString &newName){

    ConfigUP config = std::make_unique<Config>(newName, ConfigKey{-1});
    for(const auto &arg : configToCopy.args){ // create a new element id for each arg when we duplicate
        config->args[arg.first] = Arg::copy_with_new_element_id(arg.second);
    }
    return config;
}

void Config::swap_arg(QStringView arg1Name, QStringView arg2Name){
    auto &item1 = args[arg1Name];
    auto &item2 = args[arg2Name];
    std::swap(item1.generator->order, item2.generator->order);
}

void Config::update_arg(Arg arg){

    QStringView aName = arg.name;
    if(args.count(aName) != 0){
        args[aName] = std::move(arg);
        return;
    }
    QtLogger::error(QSL("Arg with name ") % name % QSL(" doesn't exists: ") % arg.name % QSL(" ") % arg.value() % QSL(" ") % arg.separator());
}

void Config::add_arg(Arg arg){

    QStringView aName = arg.name;
    if(args.count(aName)==0){
        args[aName] = std::move(arg);
    }else{
        qWarning() << "Config::error: arg " << arg.name << " already added.";
    }
}

void Config::remove_arg(QStringView argName){
    args.erase(argName);
}

