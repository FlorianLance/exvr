
/***********************************************************************************
** exvr-exp                                                                       **
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

// system
using System.Runtime.InteropServices;

namespace Ex {

    public class CppExperiment {

        // once per exvr-exp starting
        public static bool init_logger(string pathDir = "", string loggerFileName = "") {
            if(pathDir.Length == 0 || loggerFileName.Length == 0) {
                ExVR.Log().error("NO LOG");
                init_logger_no_file_ex_experiment();
            } else {
                return init_logger_ex_experiment(pathDir, loggerFileName) == 1;
            }
            return true;
        }

        [DllImport("exvr-export", EntryPoint = "init_logger_ex_experiment", CallingConvention = CallingConvention.Cdecl)]
        static private extern int init_logger_ex_experiment(string pathDir, string loggerFileName);

        [DllImport("exvr-export", EntryPoint = "init_logger_no_file_ex_experiment", CallingConvention = CallingConvention.Cdecl)]
        static private extern void init_logger_no_file_ex_experiment();
    }
}