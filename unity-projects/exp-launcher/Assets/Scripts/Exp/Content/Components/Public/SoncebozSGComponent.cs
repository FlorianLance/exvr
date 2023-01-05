/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class SoncebozSGComponent : ExComponent{

        private static readonly string m_feedbackS = "feedback";
        private UdpCommunication m_udp = null;
        private bool m_movementStarted = false;

        public TransformValue lastFeedback = new TransformValue();
        public List<TransformValue> lastFeedbacks = new List<TransformValue>();

        #region ex_functions

        protected override bool initialize() {
            
            m_udp = new UdpCommunication(
                true,
                true,
                init_config().get<int>("writing_port"),
                initC.get<string>("writing_address"),
                init_config().get<int>("reading_port"),
                initC.get<string>("reading_address")
            );

            add_signal(m_feedbackS);
            log_message(string.Format("Sonceboz communication initialized: {0}",(m_udp.receiver_initialized() && m_udp.sender_initialized())));

            return m_udp.receiver_initialized() && m_udp.sender_initialized();
        }

        protected override void start_experiment() {
            m_udp.set_reading_mode(true);
        }

        protected override void stop_experiment() {
            m_udp.set_reading_mode(false);
        }

        //protected override void set_update_state(bool doUpdate) {
        //    m_udp.set_reading_mode(doUpdate);
        //}

        protected override void start_routine() {
            m_movementStarted = false;         
        }

        protected override void pre_update() {

            if (is_updating()) {
                move_plateform();
            }

            // process messages
            UnityEngine.Profiling.Profiler.BeginSample("[ExVR][SoncebozSGComponent] READ MESSAGES");
            var messages = m_udp.read_all_messages();
            UnityEngine.Profiling.Profiler.EndSample();

            UnityEngine.Profiling.Profiler.BeginSample("[ExVR][SoncebozSGComponent] PROCESS MESSAGES");
            if (messages != null) {
            
                List<string[]> feedbacks = new List<string[]>();
                List<string[]> profiles = new List<string[]>();

                lastFeedbacks = new List<TransformValue>();

                foreach (var message in messages) {

                    var content = message.Item3;
                    var split = content.Split('%');
                    if (split.Length < 3) {
                        continue;
                    }

                    string command = split[0];
                    if (command.Length == 0) {
                        continue;
                    }

                    string id = split[1];
                    var values = split[2].Split(' ');

                    if (command[0] == 'F') {
                        if (id[0] == '0') {
                            feedbacks.Add(values);
                            //read_feedback(values);
                        }
                    } else if (command[0] == 'P') {
                        if (id[0] == '0') {
                            profiles.Add(values);
                            //read_profile(values);
                        }
                    }
                }

                if(feedbacks.Count > 0) {
                    read_feedback(feedbacks[feedbacks.Count-1]);                    
                }
                if (profiles.Count > 0) {
                    read_profile(profiles[profiles.Count - 1]);
                }
                
            }
            UnityEngine.Profiling.Profiler.EndSample();

            UnityEngine.Profiling.Profiler.BeginSample("[ExVR][SoncebozSGComponent] SIGNALS");
            // send last feedback values
            if (is_updating()) {
                invoke_signal(m_feedbackS, lastFeedback);
            }
            UnityEngine.Profiling.Profiler.EndSample();
        }

        protected override void clean() {
            m_udp.clean();
        }

        public override string format_frame_data_for_global_logger(bool header) {

            if (header) {
                return "Sonceboz: nb_feedbacks tx_n ty_n tz_n rx_n ry_n rz_n";
            }

            return string.Format("{0} {1} {1}",
                Converter.to_int(lastFeedbacks.Count),
                Converter.to_string(lastFeedback.position, Converter.g7, " "),
                Converter.to_string(lastFeedback.rotation.eulerAngles, Converter.g7, " "));
        }

        #endregion

        #region private_functions

        private void move_plateform() {

            if (!m_movementStarted) {
                if (currentC.get<bool>("apply_command_list")) {

                    var data = currentC.get_resource_text_data("command_list_file");
                    if (data != null) {
                        log_message(string.Concat("Send command to sonceboz platform: ", Converter.to_string(data.content.Length)));
                        m_udp.send_message(string.Format("$$FILE$${0}", data.content));
                    } else {
                        var message = currentC.get<string>("command_list_text");
                        if (message.Length > 0) {
                            log_message(string.Concat("Send command to sonceboz platform: ", Converter.to_string(message.Length)));
                            m_udp.send_message(string.Format("$$FILE$${0}", message));
                        } else {
                            log_warning("Message is empty, no command has been sended.");
                        }
                    }
                }
                m_movementStarted = true;
            }
        }

        private void read_feedback(string[] values) {

            // F%0%1.58784 -9.02029 49.223 1.61245 2.41867 0
            if (values.Length < 6) {
                return;
            }

            lastFeedback.position =
                new Vector3(
                    Converter.to_float(values[0]),
                    Converter.to_float(values[2]),
                    Converter.to_float(values[1])
            );
            lastFeedback.rotation = Quaternion.Euler(new Vector3(
                    Converter.to_float(values[3]),
                    Converter.to_float(values[4]),
                    Converter.to_float(values[5])
            ));
            lastFeedbacks.Add(new TransformValue(lastFeedback.position, lastFeedback.rotation, Vector3.one));
            //log_message("add feedback " + Converter.to_string(lastFeedback.position));
        }

        private void read_profile(string[] values) {

            // P%0%
            // 0; 1.5; 1.50241; 3.00241; 3.00241; 4.50241; 4.50483;
            // 6.00483; 34.5; 34.6668; 207.5; 207.5; 380.333; 380.5; 415; 69;
            // 69.2221; 138.222; 138.222; 69.2221; 69; 0; 138.222; 0; 92; 92

            //log_message("Received: " + split[2]);
            //var values = split[2].Split(' ');
            //if (values.Length > 25) {
            //    var tZero = values[0];
            //    var tEnd = values[7];
            //    log_message("Duration: " + tZero + " " + tEnd);
            //    //    trajectoriesValues[0] = values[0]; /** tZero */
            //    //    trajectoriesValues[1] = values[1]; /** tAcc0 */
            //    //    trajectoriesValues[2] = values[2]; /** tAcc1 */
            //    //    trajectoriesValues[3] = values[3]; /** tAcc  */
            //    //    trajectoriesValues[4] = values[4]; /** tDec  */
            //    //    trajectoriesValues[5] = values[5]; /** tDec0 */
            //    //    trajectoriesValues[6] = values[6]; /** tDec1 */
            //    //    trajectoriesValues[7] = values[7]; /** tEnd  */
            //    //    trajectoriesValues[8] = values[8]; /** sAcc0 */
            //    //    trajectoriesValues[9] = values[9]; /** sAcc1 */
            //    //    trajectoriesValues[10] = values[10];/** sAcc  */
            //    //    trajectoriesValues[11] = values[11];/** sDec  */
            //    //    trajectoriesValues[12] = values[12];/** sDec0 */
            //    //    trajectoriesValues[13] = values[13];/** sDec1 */
            //    //    trajectoriesValues[14] = values[14];/** sEnd  */
            //    //    trajectoriesValues[15] = values[15];/** vAcc0 */
            //    //    trajectoriesValues[16] = values[16];/** vAcc1 */
            //    //    trajectoriesValues[17] = values[17];/** vAcc  */
            //    //    trajectoriesValues[18] = values[18];/** vDec  */
            //    //    trajectoriesValues[19] = values[19];/** vDec0 */
            //    //    trajectoriesValues[20] = values[20];/** vDec1 */
            //    //    trajectoriesValues[21] = values[21];/** vEnd  */
            //    //    trajectoriesValues[22] = values[22];/** vMax  */
            //    //    trajectoriesValues[23] = values[23];/** vInit */
            //    //    trajectoriesValues[24] = values[24];/** accMax*/
            //    //    trajectoriesValues[25] = values[25];/** decMax*/
            //}
        }

        #endregion
    }
}

//public class SoncebozCommand{
//    public double time = 0.0;
//    public Vector3 position = Vector3.zero;
//    public Vector3 rotation = Vector3.zero;
//}

//public Vector3 currentPosition = Vector3.zero;
//public Vector3 currentRotation = Vector3.zero;

//int count = 0;

//SoncebozCommand lastCommandSent = null;
//private List<SoncebozCommand> commandsToSend = new List<SoncebozCommand>();

//    string.Format("M01 {0} {1} {2} {3} {4} {5}",
//            commandToSend.position.x, commandToSend.position.y, commandToSend.position.z,
//            commandToSend.rotation.x, commandToSend.rotation.y, commandToSend.rotation.z
//        )
//    );


//return;

//public void move_linear_offset(Vector3 position, Vector3 rotation) {

//var cmd = new SoncebozCommand();
//cmd.position = position;
//cmd.rotation = rotation;
//cmd.time = ellapsed_time_routine_ms();
//commandsToSend.Add(cmd);

//m_udp.send_message(
//string.Format("M01 {0} {1} {2} {3} {4} {5}",
//        translateOffset.x,  translateOffset.y,  translateOffset.z,
//        rotateOffset.x,     rotateOffset.y,     rotateOffset.z
//    )
//);
//}

//SoncebozCommand commandToSend = null;

//if (commandsToSend.Count > 0) {
//    commandToSend = commandsToSend[commandsToSend.Count - 1];
//} else {
//    return;
//}

//if (lastCommandSent != null) {

//    if(commandToSend.time - lastCommandSent.time < 30) {
//        log_message("CANCEL1");
//        return;
//    }

//    if(((commandToSend.position - lastCommandSent.position).magnitude == 0) &&
//       ((commandToSend.rotation - lastCommandSent.rotation).magnitude == 0)) {
//        log_message("CANCEL2");
//        return;
//    }
//}

//commandsToSend.Clear();

//if (commandToSend != null) {
//    lastCommandSent = commandToSend;
//    log_message("commandToSend: " + commandToSend.position + " " + commandToSend.rotation + " " + commandToSend.time + " -> " + count);
//    m_udp.send_message(

//    ++count;
//}




// send
