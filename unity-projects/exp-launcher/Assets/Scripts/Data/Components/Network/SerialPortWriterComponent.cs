
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using System.IO.Ports;
using System.IO;

// unity
using UnityEngine;

namespace Ex{

    public class SerialPortWriterComponent : ExComponent{

        private SerialPort port = null;
        private string m_message = "";
        List<byte> m_messageBytes = null;

        
        private static byte convert_bool_array_to_byte(bool[] source) {
            
            byte result = 0;
            // This assumes the array never contains more than 8 elements!
            int index = 8 - source.Length;

            // Loop through the array
            foreach (bool b in source) {
                // if the element is 'true' set the bit at that position
                if (b)
                    result |= (byte)(1 << (7 - index));

                index++;
            }

            return result;
        }

        private void process_message() {

            m_message = currentC.get<string>("message");
            m_messageBytes = new List<byte>();

            if (currentC.get<bool>("bits_mode")) {
                string m = m_message.Replace('\t', ' ');
                m = m.Replace('\n', ' ');
                var splits = m.Split(' ');
                foreach (string split in splits) {

                    string r = Regex.Replace(split, "[^0-1]", "");
                    if (r.Length != 8) {
                        continue;
                    }

                    List<bool> newByte = new List<bool>(8);
                    foreach (char c in r) {
                        if (c != '0' && c != '1') {
                            break;
                        }
                        newByte.Add(c == '0' ? false : true);
                    }
                    if (newByte.Count == 8) {
                        // valid byte
                        m_messageBytes.Add(convert_bool_array_to_byte(newByte.ToArray()));
                    }
                }
            } else if (currentC.get<bool>("int_mode")) {
                string m = m_message.Replace('\t', ' ');
                m = m.Replace('\n', ' ');
                var splits = m.Split(' ');
                foreach (string split in splits) {
                    int b = Int32.Parse(split);
                    if(b < 0) {
                        b = 0;
                    }else if( b > 255) {
                        b = 255;
                    }
                    m_messageBytes.Add((byte)b);
                }
            }
        }


        protected override bool initialize() {

            port = new SerialPort(initC.get<string>("port_to_write"), initC.get<int>("baud_rate"), Parity.None, 8, StopBits.None);
            port.Handshake = Handshake.None;
            try {
                port.Open();
            } catch (UnauthorizedAccessException e) {
                log_error(e.Message);
            } catch (IOException e) {
                log_error(e.Message);
            }

            if (!port.IsOpen) {
                log_error("Serial port " + initC.get<string>("port_to_write") + " cannot be opened");
                return false;
            }
            return true;
        }

        protected override void clean() {
            port.Close();
        }

        protected override void start_experiment() {

            //port.WriteTimeout = 500;
            // Allow the user to set the appropriate properties.
            //_serialPort.PortName = SetPortName(_serialPort.PortName);
            //_serialPort.BaudRate = SetPortBaudRate(_serialPort.BaudRate);
            //_serialPort.Parity = SetPortParity(_serialPort.Parity);
            //_serialPort.DataBits = SetPortDataBits(_serialPort.DataBits);
            //_serialPort.StopBits = SetPortStopBits(_serialPort.StopBits);
            //_serialPort.Handshake = SetPortHandshake(_serialPort.Handshake);
        }

        protected override void start_routine() {

            process_message();

            if (currentC.get<bool>("send_new_routine")){
                write();
            }
        }

        protected override void set_update_state(bool doUpdate) {
            if (doUpdate && currentC.get<bool>("send_new_update_block")) {
                write();
            }else if (!doUpdate && currentC.get<bool>("send_end_update_block")){
                write();
            }            
        }

        protected override void update() {
            if (currentC.get<bool>("send_every_frame")) {
                write();
            }
        }

        protected override void update_parameter_from_gui(XML.Arg arg) {
            if(arg.Name == "message") {
                process_message();
            }
        }

        private void write() {

            if (currentC.get<bool>("bits_mode")) {
                Debug.Log(m_messageBytes.ToArray().Length);
                write_bytes(m_messageBytes.ToArray(), 0, m_messageBytes.Count);
            } else if (currentC.get<bool>("int_mode")){
                write_bytes(m_messageBytes.ToArray(), 0, m_messageBytes.Count);
            } else {
                write_line(m_message);
            }
        }

        public void write_bytes(byte[] buffer, int offset, int count) {
            if (port.IsOpen) {


                try {
                    port.Write(buffer, offset, count);
                } catch (ArgumentNullException e) {
                    Debug.Log("e1-- " + e);
                } catch (InvalidOperationException e) {
                    Debug.Log("e2-- " + e);
                } catch (ArgumentOutOfRangeException e) {
                    Debug.Log("e3-- " + e);
                } catch (TimeoutException e) {
                    Debug.Log("e4-- " + e);
                }
            }
        }
       
        public void write_line(string message) {
            if (port.IsOpen) {
                port.WriteLine(message);
            }
            // maybe see http://www.sparxeng.com/blog/software/must-use-net-system-io-ports-serialport implementation
        }
    }

}