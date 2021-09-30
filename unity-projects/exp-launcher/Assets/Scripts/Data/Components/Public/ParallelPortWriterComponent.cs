
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Runtime.InteropServices;
using System.Collections;
using System.Management;

// unity
using UnityEngine;


//public static List<COMPortInfo> GetCOMPortsInfo() {
//    List<COMPortInfo> comPortInfoList = new List<COMPortInfo>();
//    ConnectionOptions options = ProcessConnection.ProcessConnectionOptions();
//    ManagementScope connectionScope = ProcessConnection.ConnectionScope(Environment.MachineName, options, @"\root\CIMV2");
//    ObjectQuery objectQuery = new ObjectQuery("SELECT * FROM Win32_PnPEntity WHERE ConfigManagerErrorCode = 0");
//    ManagementObjectSearcher comPortSearcher = new ManagementObjectSearcher(connectionScope, objectQuery);
//    using (comPortSearcher) {
//        string caption = null;
//        foreach (ManagementObject obj in comPortSearcher.Get()) {
//            if (obj != null) {
//                object captionObj = obj["Caption"];
//                if (captionObj != null) {
//                    caption = captionObj.ToString();
//                    if (caption.Contains("(COM")) {
//                        COMPortInfo comPortInfo = new COMPortInfo();
//                        comPortInfo.Name = caption.Substring(caption.LastIndexOf("(COM")).Replace("(", string.Empty).Replace(")",
//                                                             string.Empty);
//                        comPortInfo.Description = caption;
//                        comPortInfoList.Add(comPortInfo);
//                    }
//                }
//            }
//        }
//    }
//    return comPortInfoList;
//}

namespace Ex{

    public class ParallelPortWriterComponent : ExComponent{

        [DllImport("inpoutx32.dll", EntryPoint = "Out32")]
        private static extern void out32_x32(short port, short Data);

        [DllImport("inpoutx32.dll", EntryPoint = "DlPortWritePortUshort")]
        private static extern void dl_port_write_port_ushort_x32(ushort port, ushort Data);

        [DllImport("inpoutx32.dll", EntryPoint = "DlPortWritePortUlong")]
        private static extern void dl_port_write_port_ulong_x32(uint port, uint Data);

        [DllImport("inpoutx64.dll", EntryPoint = "IsInpOutDriverOpen")]
        private static extern UInt32 is_inpout_driver_opened();

        [DllImport("inpoutx64.dll", EntryPoint = "Out32")]
        private static extern void out32_x64(short port, short Data);

        [DllImport("inpoutx64.dll", EntryPoint = "DlPortWritePortUshort")]
        private static extern void dl_port_write_port_ushort_x64(ushort port, ushort Data);

        [DllImport("inpoutx64.dll", EntryPoint = "DlPortWritePortUlong")]
        private static extern void dl_port_write_port_ulong_x64(uint port, uint Data);

        private bool m_x32Mode = false;
        private bool m_int16Mode = false;
        private bool m_available = false;

        private float m_pulseTime = 1f;
        private int m_port = 888;

        protected override bool initialize() {

            m_x32Mode   = initC.get<bool>("x32_mode");
            m_int16Mode = initC.get<bool>("int16_mode");

            add_slot("write", (value) => {
                write((int)value);
            });
            add_slot("send pulse", (value) => {
                ExVR.Coroutines().start(send_pulse((int)value));
            });

            try {
                if (is_inpout_driver_opened() == 0) {
                    log_error("Inpout driver not opened. No signal can be sent.");
                } else {
                    m_available = true;
                }
            } catch (DllNotFoundException) {
                log_error("inpoutx64.dll not found.");
                return false;
            }

            //log_message("1");
            //var parallelPort = new System.Management.ManagementObjectSearcher("Select * From Win32_ParallelPort");
            //log_message("2 ");

            //foreach (var rec in parallelPort.Get()) {
            //    var wql = "Select * From Win32_PnPAllocatedResource";
            //    var pnp = new ManagementObjectSearcher(wql);

            //    var searchTerm = rec.Properties["PNPDeviceId"].Value.ToString();
            //    // compensate for escaping
            //    searchTerm = searchTerm.Replace(@"\", @"\\");

            //    foreach (var pnpRec in pnp.Get()) {
            //        var objRef = pnpRec.Properties["dependent"].Value.ToString();
            //        var antref = pnpRec.Properties["antecedent"].Value.ToString();

            //        if (objRef.Contains(searchTerm)) {
            //            var wqlPort = "Select * From Win32_PortResource";
            //            var port = new ManagementObjectSearcher(wqlPort);
            //            foreach (var portRec in port.Get()) {
            //                if (portRec.ToString() == antref) {
            //                    Console.WriteLine("{0} [{1};{2}]",
            //                        rec.Properties["Name"].Value,
            //                        portRec.Properties["StartingAddress"].Value,
            //                        portRec.Properties["EndingAddress"].Value);
            //                }
            //            }
            //        }
            //    }
            //}

            //using (parallelPort) {
            //    foreach (ManagementObject obj in parallelPort.Get()) {
            //        if (obj != null) {
            //            foreach(var c in obj.Container.Components) {
            //                log_message("c " + c.ToString());
            //            }

            //            //object captionObj = obj["Caption"];
            //            //if (captionObj != null) {
            //            //    log_message("Port: " + captionObj.ToString());
            //            //}
            //            //object captionObj = obj["Caption"];
            //            //if (captionObj != null) {
            //            //    string caption = captionObj.ToString();
            //            //    if (caption.Contains("(COM")) {
            //            //        COMPortInfo comPortInfo = new COMPortInfo();
            //            //        comPortInfo.Name = caption.Substring(caption.LastIndexOf("(COM")).Replace("(", string.Empty).Replace(")",
            //            //                                             string.Empty);
            //            //        comPortInfo.Description = caption;
            //            //        comPortInfoList.Add(comPortInfo);
            //            //    }
            //            //}
            //        }
            //    }
            //}



            return true;
        }
   
        public IEnumerator send_pulse(int value) {
            write(value);
            yield return new WaitForSeconds(m_pulseTime);
            write(0);
        }

        public IEnumerator send_test(int value) {
            for(int ii = 0; ii < 1000; ++ii) {
                write(value, ii);
                log_message("port " + ii);
                yield return new WaitForSeconds(0.02f);
                //write(0);
            }
        }


        public override void update_from_current_config() {
            m_pulseTime = (float)currentC.get<double>("pulse_time");
            m_port      = currentC.get<int>("port");
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            update_from_current_config();
        }


        private void write(int value, int port) {

            if (!m_available) {
                return;
            }

            if (m_x32Mode) {
                if (m_int16Mode) {

                    dl_port_write_port_ushort_x32(
                        (ushort)Mathf.Clamp(port, 0, 65535),
                        (ushort)Mathf.Clamp(value, 0, 65535)
                    );

                } else {

                    dl_port_write_port_ulong_x32(
                        (uint)port,
                        (uint)value
                    );
                }
            } else {
                if (m_int16Mode) {

                    dl_port_write_port_ushort_x64(
                        (ushort)Mathf.Clamp(port, 0, 65535),
                        (ushort)Mathf.Clamp(value, 0, 65535)
                    );

                } else {

                    dl_port_write_port_ulong_x64(
                        (uint)port,
                        (uint)value
                    );
                }
            }
        }
         public void write(int value) {
            write(value, m_port);
        }
    }
}


////Functions exported from DLL.
////For easy inclusion is user projects.
////Original InpOut32 function support
//void _stdcall Out32(short PortAddress, short data);
//short _stdcall Inp32(short PortAddress);

////My extra functions for making life easy
//BOOL _stdcall IsInpOutDriverOpen();  //Returns TRUE if the InpOut driver was opened successfully

////DLLPortIO function support
//UCHAR _stdcall DlPortReadPortUchar(USHORT port);
//void _stdcall DlPortWritePortUchar(USHORT port, UCHAR Value);

//USHORT _stdcall DlPortReadPortUshort(USHORT port);
//void _stdcall DlPortWritePortUshort(USHORT port, USHORT Value);

//ULONG _stdcall DlPortReadPortUlong(ULONG port);
//void _stdcall DlPortWritePortUlong(ULONG port, ULONG Value);


//DLLPortIO function support
//UCHAR _stdcall DlPortReadPortUchar(USHORT port);
//void _stdcall DlPortWritePortUchar(USHORT port, UCHAR Value);

//USHORT _stdcall DlPortReadPortUshort(USHORT port);
//void _stdcall DlPortWritePortUshort(USHORT port, USHORT Value);

//ULONG _stdcall DlPortReadPortUlong(ULONG port);
//void _stdcall DlPortWritePortUlong(ULONG port, ULONG Value);

//[DllImport("inpoutx64.dll", EntryPoint = "Inp32")]
//private static extern char Inp32_x64(short PortAddress);

//[DllImport("inpoutx64.dll", EntryPoint = "DlPortReadPortUshort")]
//private static extern ushort DlPortReadPortUshort_x64(ushort PortAddress);

//[DllImport("inpoutx64.dll", EntryPoint = "DlPortReadPortUlong")]
//private static extern uint DlPortReadPortUlong_x64(int PortAddress);
