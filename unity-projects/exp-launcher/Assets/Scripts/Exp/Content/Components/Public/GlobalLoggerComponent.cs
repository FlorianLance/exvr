
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
using System;
using System.Collections.Generic;

namespace Ex {

    public class GlobalLoggerComponent : ExComponent {



        private List<ExComponent> inputComponents = null;
        private FileLogger inputFrameEventsFL   = null;     // log each frame
        private FileLogger inputTriggerEventsFL = null;     // log when trigger


        #region ex_functions

        protected override bool initialize() {

            string resourceDirectoryPath = initC.get_resource_path(ResourcesManager.ResourceType.Directory, "directory");
            if (resourceDirectoryPath.Length == 0) {
                log_error("No directory resource defined.");
                return false;
            }

            string topSubDirPath = string.Format("{0}{1}{2}{3}",
                string.Concat(resourceDirectoryPath, "/global_logs_"),
                initC.get<string>("base_sub_directory_name"),
                initC.get<bool>("add_current_instance_to_sub_directory_name") ? 
                    string.Format("_{0}", ExVR.Experiment().instanceName) : "",
                initC.get<bool>("add_date_to_sub_directory_name") ? 
                    string.Format("_{0}", DateTime.Now.ToString(initC.get<string>("date_time_format"))) : ""
            );

            int count = 1;
            string globalDirectoryPath = topSubDirPath;            
            while (System.IO.Directory.Exists(topSubDirPath)) {
                globalDirectoryPath = string.Format("{0}_{1}", topSubDirPath, count++);
            }

            var folder = System.IO.Directory.CreateDirectory(globalDirectoryPath);
            if (!folder.Exists) {
                log_error(string.Format("Cannot create top directory [{0}].", topSubDirPath));
                return false;
            }

            // retrieve components
            inputComponents = initC.get_components_list("inputs_components");
            if(inputComponents.Count > 0) {

                int countFrame = 0, countTrigger = 0;
                foreach(var component in inputComponents) {
                    if (component.has_frame_logging()) {
                        countFrame++;
                    }
                    if (component.has_trigger_logging()) {
                        countTrigger++;
                    }
                }

                if (countFrame > 0) {

                    string inputFrameLoggerFilePath = string.Format("{0}/log_frame_input{1}", globalDirectoryPath, initC.get<string>("file_extension"));        
                    if (!FileLogger.create_file(inputFrameLoggerFilePath,"",false,false)) {
                        return false;
                    }

                    inputFrameEventsFL = new FileLogger();
                    if (!inputFrameEventsFL.open_file(inputFrameLoggerFilePath)) {
                        return false;
                    }
                }

                if (countTrigger > 0) {
                    
                    string inputTriggerLoggerFilePath = string.Format("{0}/log_trigger_input{1}", globalDirectoryPath, initC.get<string>("file_extension"));
                    if (!FileLogger.create_file(inputTriggerLoggerFilePath, "", false, false)) {
                        return false;
                    }

                    inputTriggerEventsFL = new FileLogger();
                    if (!inputTriggerEventsFL.open_file(inputTriggerLoggerFilePath)) {
                        return false;
                    }
                }
            }

            log_message("global -> " + (inputFrameEventsFL == null) + " " + (inputTriggerEventsFL == null));


            //events.Sort(delegate (Input.KeyboardButtonEvent e1, Input.KeyboardButtonEvent e2)
            //{
            //    if(e1.triggeredExperimentTime < e2.triggeredExperimentTime) {
            //        return 1;
            //    }else if(e1.triggeredExperimentTime > e2.triggeredExperimentTime) {
            //        return -1;
            //    }
            //    return 0;
            //});



            // global_logs/
            //    base_instance_name




            // data dir resource
            // -> global_logs
            //     -> experience
            //         -> frame
            //         -> trigger
            //     -> input
            //         -> frame
            //         -> trigger
            //     -> network
            //         -> trigger
            //     -> ui
            //         -> frame
            //         -> trigger
            //     -> tracking
            //         -> frame
            //         -> trigger

            //if (!read_common_init_parameters()) {
            //    return false;
            //}
            //m_addDateToFileName = initC.get<bool>("add_date_to_file_name");
            //m_dateTimeFormat = initC.get<string>("date_time_format");




            //    m_addDateToFileName = initC.get<bool>("add_date_to_file_name");
            //    m_dateTimeFormat = initC.get<string>("date_time_format");
            //    m_separator = initC.get<string>("separator");
            //    m_eachFrame = initC.get<bool>("each_frame");

            //    if (m_addTimeExp = initC.get<bool>("time_exp")) { m_countColumns++; }
            //    if (m_addTimeRoutine = initC.get<bool>("time_routine")) { m_countColumns++; }
            //    if (m_addRoutine = initC.get<bool>("routine")) { m_countColumns++; }
            //    if (m_addRoutineIter = initC.get<bool>("routine_iter")) { m_countColumns++; }
            //    if (m_addCondition = initC.get<bool>("condition")) { m_countColumns++; }
            //    if (m_addConditionIter = initC.get<bool>("condition_iter")) { m_countColumns++; }
            //    if (m_addFrameId = initC.get<bool>("frame_id")) { m_countColumns++; }

            return true;
        }

        protected override void start_experiment() {

            //base.start_experiment();
        }

        //protected override void start_routine() {

        //    if (!initC.get<bool>("each_frame")) {
        //        write_line();
        //    }
        //}
        protected override void post_update() {

            if(inputComponents != null) {
                foreach(var inputComponent in inputComponents){
                    var formatedData = inputComponent.format_trigger_data_for_global_logger();
                    if(formatedData != null) {
                        log_message(formatedData);
                    }
                }
            }
        }


        #endregion

        #region private_functions

        //protected override string generate_file_name() {
        //    string dateStr = string.Format("_{0}", DateTime.Now.ToString(m_dateTimeFormat));
        //    return string.Format("{0}{1}{2}.{3}", m_baseFileName, m_addInstanceToFileName ?
        //        string.Concat("_", ExVR.Experiment().instanceName) : "", m_addDateToFileName ? dateStr : "", m_fileExtension);
        //}

        //private void write_header_line() {

        //    System.Text.StringBuilder builder = new System.Text.StringBuilder();
        //    int count = 0;
        //    if (m_addTimeExp) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, "[time_exp(ms)]", m_separator);
        //        } else {
        //            builder.Append("[time_exp(ms)]");
        //        }
        //        ++count;
        //    }
        //    if (m_addTimeRoutine) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, "[time_routine(ms)]", m_separator);
        //        } else {
        //            builder.Append("[time_routine(ms)]");
        //        }
        //        ++count;
        //    }
        //    if (m_addRoutine) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, "[routine]", m_separator);
        //        } else {
        //            builder.Append("[routine]");
        //        }
        //        ++count;
        //    }
        //    if (m_addRoutineIter) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, "[routine_iter]", m_separator);
        //        } else {
        //            builder.Append("[routine_iter]");
        //        }
        //        ++count;
        //    }
        //    if (m_addCondition) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, "[condition]", m_separator);
        //        } else {
        //            builder.Append("[condition]");
        //        }
        //        ++count;
        //    }
        //    if (m_addConditionIter) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, "[condition_iter]", m_separator);
        //        } else {
        //            builder.Append("[condition_iter]");
        //        }
        //        ++count;
        //    }
        //    if (m_addFrameId) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, "[frame_id]", m_separator);
        //        } else {
        //            builder.Append("[frame_id]");
        //        }
        //        ++count;
        //    }

        //    write(builder.ToString(), true);
        //}

        //private void write_line() {

        //    System.Text.StringBuilder builder = new System.Text.StringBuilder();
        //    int count = 0;
        //    if (m_addTimeExp) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, Converter.to_string(ExVR.Time().ellapsed_exp_ms()), m_separator);
        //        } else {
        //            builder.Append(Converter.to_string(ExVR.Time().ellapsed_exp_ms()));
        //        }
        //        ++count;
        //    }
        //    if (m_addTimeRoutine) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, Converter.to_string(ExVR.Time().ellapsed_element_ms()), m_separator);
        //        } else {
        //            builder.Append(Converter.to_string(ExVR.Time().ellapsed_element_ms()));
        //        }
        //        ++count;
        //    }
        //    if (m_addRoutine) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, currentRoutine.name, m_separator);
        //        } else {
        //            builder.Append(currentRoutine.name);
        //        }
        //        ++count;
        //    }
        //    if (m_addRoutineIter) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, Converter.to_string(currentRoutine.element_iteration()), m_separator);
        //        } else {
        //            builder.Append(Converter.to_string(currentRoutine.element_iteration()));
        //        }
        //        ++count;
        //    }
        //    if (m_addCondition) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, currentCondition.name, m_separator);
        //        } else {
        //            builder.Append(currentCondition.name);
        //        }
        //        ++count;
        //    }
        //    if (m_addConditionIter) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, Converter.to_string(currentRoutine.condition_iteration()), m_separator);
        //        } else {
        //            builder.Append(Converter.to_string(currentRoutine.condition_iteration()));
        //        }
        //        ++count;
        //    }
        //    if (m_addFrameId) {
        //        if (count < m_countColumns - 1) {
        //            builder.AppendFormat(lineC, Converter.to_string(ExVR.Time().frame_id()), m_separator);
        //        } else {
        //            builder.Append(Converter.to_string(ExVR.Time().frame_id()));
        //        }
        //        ++count;
        //    }

        //    write(builder.ToString(), true);
        //}

        #endregion
    }
}
