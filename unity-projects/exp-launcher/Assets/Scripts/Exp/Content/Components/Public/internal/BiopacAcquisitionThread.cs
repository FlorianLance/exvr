
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
using System.Threading;
using System.Diagnostics;
using System.Collections.Generic;

// unity
using UnityEngine.Profiling;

using MP        = Biopac.API.MPDevice.MPDevImports;
using MPCODE    = Biopac.API.MPDevice.MPDevImports.MPRETURNCODE;

namespace Ex {

    //  Advanced Data Transfer Functions
    //  getMPDaemonLastError()
    //  startMPAcqDaemon()
    //  receiveMPData()
    //
    //  This set of functions improves the usability of the API.The function startMPAcqDaemon() s
    //  tarts a virtual server that will stream acquired data to the client once the startAcquisition() has been invoked.
    //  The client program can read the stream by calling the receiveMPData() function. This allows for real-time processing of data while a
    //  dedicated thread downloads, caches and streams the data to the client program.The thread is spawned from the same process that attached to the DLL.
    //  If a call to receiveMPData() fails, the client program can query what happened to the acquisition daemon by calling getMPDaemonLastError().
    //  If the user decides to use this data transfer mechanism, the function startMPAcqDaemon() must called before the startAcquisition().
    //  Simple Data Transfer Functions should not be used in conjunction with this set of functions per acquisitio


    // sample:
    // create a buffer that is 3 time the frequency in Hz
    // this is large enough to hold 1 second of 
    // samples from all three acquisition channels
    // uint numberOfDataPoints = (uint)sampleFreq * 3;
    // double[] buffer = new double[numberOfDataPoints];
    // while(true) {
    //  retval = MP.receiveMPData(buffer,numberOfDataPoints, out received);
    //  // ...
    // }


    //MPSUCCESS = 1,
    //MPDRVERR,
    //MPDLLBUSY,
    //MPINVPARA,
    //MPNOTCON,
    //MPREADY,
    //MPWPRETRIG,
    //MPWTRIG,
    //MPBUSY,
    //MPNOACTCH,
    //MPCOMERR,
    //MPINVTYPE,
    //MPNOTINNET,
    //MPSMPLDLERR,
    //MPMEMALLOCERR,
    //MPSOCKERR,
    //MPUNDRFLOW,
    //MPPRESETERR,
    //MPPARSERERR

    public struct FrameTimestamp {
        public long startingTick;
        public long afterDataReadingTick;
        public long afterDigitalIoReadingTick;
    }

    public class BiopacSettings {

        public MP.DIGITALOPT readDigitalMode;
        public bool readDigitalEnabled = false;
        public MP.MPTYPE device;
        public MP.MPCOMTYPE connection;
        public int enabledChannelsNb = 0;
        public int nbMaxChannels;
        public bool[] channelsState      = null; // size: nbMaxChannels
        public List<string> channelsName = null; // size: enabledChannelsNb
        public List<int> channelsId      = null; // size: enabledChannelsNb
        public int writeEveryNbLines = 10000;

        public int nbSamplesPerCall = 10;
        public double samplingRate = 0.0;
        public int capacityChannelSeconds = 0;        
        public uint numberOfDataPoints = 0;

        public static string code_to_string(MPCODE code) {
            switch (code) {
                case MPCODE.MPSUCCESS:
                    return " [successful execution] ";
                case MPCODE.MPDRVERR:
                    return " [error communicating with the device drivers] ";
                case MPCODE.MPDLLBUSY:
                    return " [a process is attached to the DLL, only one process may use the DLL] ";
                case MPCODE.MPINVPARA:
                    return " [invalid parameter(s)] ";
                case MPCODE.MPNOTCON:
                    return " [MP device is not connected] ";
                case MPCODE.MPREADY:
                    return " [MP device is ready] ";
                case MPCODE.MPWPRETRIG:
                    return " [MP device is waiting for pre-trigger (pre-triggering is not implemented)] ";
                case MPCODE.MPWTRIG:
                    return " [MP device is waiting for trigger] ";
                case MPCODE.MPBUSY:
                    return " [MP device is busy] ";
                case MPCODE.MPNOACTCH:
                    return " [there are no active channels, in order to acquire data at least one analog channel must be active] ";
                case MPCODE.MPCOMERR:
                    return " [generic communication error] ";
                case MPCODE.MPINVTYPE:
                    return " [the function is incompatible with the selected MP device or communication method] ";
                case MPCODE.MPNOTINNET:
                    return " [the specified MP150 is not in the network] ";
                case MPCODE.MPSMPLDLERR:
                    return " [MP device overwrote samples that had not been transferred from the device (buffer overflow)] ";
                case MPCODE.MPMEMALLOCERR:
                    return " [error allocating memory] ";
                case MPCODE.MPSOCKERR:
                    return " [internal socket error] ";
                case MPCODE.MPUNDRFLOW:
                    return " [MP device returned a data pointer that is less than the last data pointer] ";
                case MPCODE.MPPRESETERR:
                    return " [error with the specified preset file] ";
                case MPCODE.MPPARSERERR:
                    return " [preset file parsing error, the XML file must be valid according to the schema] ";
                default:
                    return "[unknow error]";
            }
        }
    }


    public class BiopacData {

        public int lastFrameReadId = 0;
        public List<double[]> channelsData = null;
        public List<bool[]> digitalInputData = null;
        public List<FrameTimestamp> times = null;

        public BiopacData(BiopacSettings bps) {
            reset(bps);
        }
        public void reset(BiopacSettings bps) {
            int capacity = bps.capacityChannelSeconds * (int)bps.samplingRate / bps.nbSamplesPerCall;
            channelsData = new List<double[]>(capacity);
            digitalInputData = new List<bool[]>(capacity);
            times = new List<FrameTimestamp>(bps.capacityChannelSeconds);
        }
    }


    public class BiopacAcquisitionThread : ThreadedJob {

        public BiopacSettings bSettings = null;
        public BiopacData bData     = null;
        
        volatile public bool doLoop         = false;
        volatile public bool processData    = false;
        volatile public bool askWrite       = false;

        private ReaderWriterLock rwl        = new ReaderWriterLock();

        protected override void ThreadFunction() {

            Thread.CurrentThread.Name = "BiopacAcquisitionThread";
            Profiler.BeginThreadProfiling("BiopacAcquisitionThread", "BiopacAcquisitionThread 1");

            // initialize data
            bData = new BiopacData(bSettings);

            // start reading loop
            var waitBuffer = new double[bSettings.enabledChannelsNb];

            while (doLoop) {

                if (!processData) { // read only minimum data
                    MP.receiveMPData(waitBuffer, (uint)bSettings.enabledChannelsNb, out uint notUsed);
                    //Thread.SpinWait(1);
                    continue;
                }

                FrameTimestamp times = new FrameTimestamp();

                // raw data
                var buffer = new double[bSettings.numberOfDataPoints];
                var digitalIO = new bool[bSettings.enabledChannelsNb];
                for (int ii = 0; ii < digitalIO.Length; ++ii) {
                    digitalIO[ii] = false;
                }

                // retrieve points
                times.startingTick          = Stopwatch.GetTimestamp();
                MPCODE retval               = MP.receiveMPData(buffer, bSettings.numberOfDataPoints, out uint received);
                times.afterDataReadingTick  = Stopwatch.GetTimestamp();

                // check for error condition
                if (retval != MPCODE.MPSUCCESS ) {
                    ExVR.Log().error(string.Format("Biopack receiveMPData error code: {0}", BiopacSettings.code_to_string(retval)));
                    continue;
                }

                // check number of points read
                if (received != bSettings.numberOfDataPoints) {
                    ExVR.Log().error(string.Format("Biopack receiveMPData warning, received {0} values instead of {1}", received, bSettings.numberOfDataPoints));
                    continue;
                }

                // retrieve values from the Digital Lines
                if (bSettings.readDigitalEnabled) {
                    for (int ii = 0; ii < bSettings.channelsId.Count; ++ii) {
                        retval = MP.getDigitalIO((uint)bSettings.channelsId[ii], out digitalIO[ii], bSettings.readDigitalMode);
                        if (retval != MPCODE.MPSUCCESS) {
                            ExVR.Log().error(string.Format("Biopack getDigitalIO({0}) error code {1} ", bSettings.channelsId[ii], BiopacSettings.code_to_string(retval)));
                            continue;
                        }
                    }
                }
                times.afterDigitalIoReadingTick = Stopwatch.GetTimestamp();               

                // store values
                try {
                    rwl.AcquireWriterLock(1000); // 5
                    try {

                        // time
                        bData.times.Add(times);
                        // data
                        bData.channelsData.Add(buffer);
                        // digital line IO
                        bData.digitalInputData.Add(digitalIO);

                    } finally {
                        // Ensure that the lock is released.
                        rwl.ReleaseWriterLock();
                    }
                } catch (ApplicationException) {
                    ExVR.Log().error("Can't get writer lock.");
                }

                askWrite = (1f* bData.channelsData.Count * bSettings.numberOfDataPoints / bSettings.enabledChannelsNb) > bSettings.writeEveryNbLines;
            }

            Profiler.EndThreadProfiling();
        }

        public Tuple<List<FrameTimestamp>, List<double[]>> get_last_values() {

            List<FrameTimestamp> lastTimes = null;
            List<double[]> lastData = null;

            try {
                rwl.AcquireReaderLock(10); // 1☺
                try {
                    int startId = bData.lastFrameReadId;
                    int count   = bData.times.Count - bData.lastFrameReadId;

                    lastTimes = bData.times.GetRange(startId, count);
                    lastData  = bData.channelsData.GetRange(startId, count);
                    bData.lastFrameReadId = bData.times.Count;
                } finally {
                    rwl.ReleaseReaderLock();
                }
            } catch (ApplicationException) {
                return null;
            }

            return Tuple.Create(lastTimes, lastData);
        }


        public BiopacData get_data() {

            BiopacData retievedBData = null;
            BiopacData newBData      = new BiopacData(bSettings);

            // swap data
            try {
                rwl.AcquireWriterLock(1000);
                try {
                    retievedBData = bData;
                    bData         = newBData;

                } finally {
                    rwl.ReleaseWriterLock();
                }
            } catch (ApplicationException) {
                return null;
            }
            return retievedBData;
        }        
    }
}