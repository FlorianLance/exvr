/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;

namespace Ex{

    public class LoggerComponent : BaseLoggerComponent {

        // parameters
        private bool m_insertNewRoutineInfo;
        protected bool m_addDateToFileName;
        protected string m_dateTimeFormat;

        protected override string generate_file_name() {
            string dateStr = string.Format("_{0}", DateTime.Now.ToString(m_dateTimeFormat));
            return string.Format("{0}{1}{2}.{3}", m_baseFileName, m_addInstanceToFileName ? 
                string.Concat("_", ExVR.Experiment().instanceName) : "", m_addDateToFileName ? dateStr : "", m_fileExtension);
        }

        protected override bool initialize() {

            if (!read_common_init_parameters()) {
                return false;
            }
            m_insertNewRoutineInfo = initC.get<bool>("insert_new_routine_infos");
            m_addDateToFileName    = initC.get<bool>("add_date_to_file_name");
            m_dateTimeFormat       = initC.get<string>("date_time_format");

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
            base.start_experiment();
        }

        protected override void start_routine() {

            if(m_insertNewRoutineInfo) {
                string startRoutineLine = String.Format("[Routine:{0}][Condition:{1}][Time(ms):{2}])", 
                    currentRoutine.name, currentCondition.name, ExVR.Time().ms_start_routine_since_start_experiment().ToString());
                write(startRoutineLine, true);
            }
        }

        protected override void stop_experiment() {
            base.stop_experiment();
        }
    }
}
