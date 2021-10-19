/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;

namespace Ex {

    public class LoggerColumnsComponent : BaseLoggerComponent {

        // parameters
        protected bool m_addDateToFileName;
        protected string m_dateTimeFormat;
        protected bool m_writeCurrentColumnsAtEachFrame;
        protected string m_columnsSeparator;

        private List<string> columnsValue = null;

        #region ex_functions
        protected override bool initialize() {

            if (!read_common_init_parameters()) {
                return false;
            }
            m_addDateToFileName = initC.get<bool>("add_date_to_file_name");
            m_dateTimeFormat = initC.get<string>("date_time_format");
            m_writeCurrentColumnsAtEachFrame = initC.get<bool>("write_each_frame");
            m_columnsSeparator = initC.get<string>("separator");

            // slots
            add_slot("set column value", (idAny) => {
                var colValue = (IdAny)idAny;
                update_column_value(colValue.id, colValue.value);
            });
            add_slot("write current line", (nullArg) => {
                write(String.Join(m_columnsSeparator, columnsValue), true);
            });

            return true;
        }

        protected override void start_experiment() {
            base.start_experiment();
            columnsValue = new List<string>();
        }


        protected override void post_update() {
            if (m_writeCurrentColumnsAtEachFrame) {
                write_current_colums();
            }
        }

        protected override void stop_experiment() {
            base.stop_experiment();
        }

        #endregion

        #region private_functions

        protected override string generate_file_name() {
            string dateStr = string.Format("_{0}", DateTime.Now.ToString(m_dateTimeFormat));
            return string.Format("{0}{1}{2}.{3}", m_baseFileName, m_addInstanceToFileName ?
                string.Concat("_", ExVR.Experiment().instanceName) : "", m_addDateToFileName ? dateStr : "", m_fileExtension);
        }


        #endregion

        #region public_functions

        public void write_current_colums() {
            write(String.Join(m_columnsSeparator, columnsValue), true);
        }

        public void update_column_value(int idColumn, object value) {

            while (idColumn >= columnsValue.Count) {
                columnsValue.Add("-");
            }
            columnsValue[idColumn] = Converter.to_string(value);
        }

        #endregion
    }
}
