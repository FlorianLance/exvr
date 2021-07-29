/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;
//using System.IO;

namespace Ex {

    public class LoggerConditionComponent : BaseLoggerComponent {

        // parameters
        private Dictionary<string, List<string>> m_filesLines = null;
        private HashSet<string> m_filesNames = null;

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
            m_filesLines = new Dictionary<string, List<string>>();

            foreach (var elementInfo in ExVR.Schreduler().get_elements_info_order(false)) {
                if (elementInfo.type() == FlowElement.FlowElementType.Routine) {
                    var routineInfo = (RoutineInfo)elementInfo;
                    foreach (var action in routineInfo.condition().actions) {
                        if (action.component().key == key) {
                            string filePath = get_file_path(routineInfo.name(), routineInfo.condition().name);
                            if (!m_filesNames.Contains(filePath)) {
                                m_filesNames.Add(filePath);
                                m_filesLines[filePath] = new List<string>();
                            }                            
                            break;
                        }
                    }
                }
            }

            foreach (var fileName in m_filesNames) {

                if (!create_file(fileName)) {
                    return;
                }

                m_lines = m_filesLines[fileName];

                if (initC.get<bool>("add_header_line")) {
                    write(initC.get<string>("header_line"), true);
                }
            }
        }

        protected override void start_routine() {
            m_fileFullPath = get_file_path(currentRoutine.name, currentCondition.name);
            m_lines = m_filesLines[m_fileFullPath];
        }


        protected override void stop_experiment() {

            foreach (var fileName in m_filesNames) {

                m_fileFullPath = fileName;
                m_lines = m_filesLines[m_fileFullPath];
                write_to_file();
            }
        }
    }
}
