
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/



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

// system
using System;
using System.Runtime.InteropServices;
using System.Collections;

// unity
using UnityEngine;

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

        private float pulseTime = 1f;
        private int port = 40000;

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

            return true;
        }
   
        public IEnumerator send_pulse(int value) {
            write(value);
            yield return new WaitForSeconds(pulseTime);
            write(0);
        }

        public override void update_from_current_config() {
            pulseTime = (float)currentC.get<double>("pulse_time");
            port      = currentC.get<int>("port");
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            update_from_current_config();
        }

        public void write(int value) {

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
                        (ushort)Mathf.Clamp(port,  0, 65535),
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
    }
}