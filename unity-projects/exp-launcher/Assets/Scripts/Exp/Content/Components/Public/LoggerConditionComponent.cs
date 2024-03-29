﻿
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
using System.Collections.Generic;


namespace Ex {

    public class LoggerConditionComponent : BaseLoggerComponent {

        // parameters       
        private HashSet<string> m_filesNames = null;

        #region ex_functions
        protected override bool initialize() {

            if (!read_common_init_parameters()) {
                return false;
            }

            // slots
            add_slot("write", (any) => {
                write(any, false);
            });
            add_slot("write line", (any) => {
                write(any, true);
            });
            add_slot("write lines", (list) => {
                write_lines((List<string>)list);
            });

            return true;
        }

        protected override void start_experiment() {

            m_filesNames = new HashSet<string>();

            foreach (var elementInfo in ExVR.Instance().get_elements_info_order(false)) {
                if (elementInfo.type() == FlowElement.Type.Routine) {
                    var routineInfo = (RoutineInfo)elementInfo;
                    foreach (var action in routineInfo.condition().actions) {
                        if (action.component().key == key) {
                            string filePath = get_file_path(routineInfo.name(), routineInfo.condition().name);
                            if (!m_filesNames.Contains(filePath)) {
                                m_filesNames.Add(filePath);
                            }
                            break;
                        }
                    }
                }
            }

            foreach (var fileName in m_filesNames) {

                if (!FileLogger.create_file(
                    fileName,
                    initC.get<bool>("add_header_line") ? initC.get<string>("header_line") : string.Empty,
                    initC.get<bool>("dont_write_if_file_exists"),
                    initC.get<bool>("add_to_end_if_file_exists"))) {
                    return;
                }
            }
            m_fileLogger = new FileLogger();
            m_fileLogger.start_logging();
        }

        protected override void pre_start_routine() {
            m_fileLogger.set_file_path(get_file_path(currentRoutine.name, currentCondition.name));
        }

        #endregion

        #region private_functions

        private string get_file_path(string routineName, string conditionName) {

            string idName = "";
            if (initC.get<bool>("add_both")) {
                idName = string.Format("{0}_{1}", routineName, conditionName);
            } else if (initC.get<bool>("add_routine")) {
                idName = routineName;
            } else if (initC.get<bool>("add_condition")) {
                idName = conditionName;
            }

            if (idName.Length != 0) {
                if (m_addInstanceToFileName) {
                    return string.Format("{0}/{1}_{2}_{3}.{4}", m_directoryPath, m_baseFileName, ExVR.Experiment().instanceName, idName, m_fileExtension);
                } else {
                    return string.Format("{0}/{1}_{2}.{3}", m_directoryPath, m_baseFileName, idName, m_fileExtension);
                }
            } else {
                if (m_addInstanceToFileName) {
                    return string.Format("{0}/{1}_{2}.{3}", m_directoryPath, m_baseFileName, ExVR.Experiment().instanceName,m_fileExtension);
                } else {
                    return string.Format("{0}/{1}.{2}", m_directoryPath, m_baseFileName, m_fileExtension);
                }
            }
        }

        #endregion

    }
}
