
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

using MP        = Biopac.API.MPDevice.MPDevImports;
using MPCODE    = Biopac.API.MPDevice.MPDevImports.MPRETURNCODE;

namespace Ex {

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

        public int nbSamplesPerCall = 10;
        public double samplingRate = 0.0;
        public int sizeMaxChannelSeconds = 0;        
        public uint numberOfDataPoints = 0;

        public string headerLine;

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
            int capacity = bps.sizeMaxChannelSeconds * (int)bps.samplingRate / bps.nbSamplesPerCall;
            channelsData = new List<double[]>(capacity);
            digitalInputData = new List<bool[]>(capacity);
            times = new List<FrameTimestamp>(bps.sizeMaxChannelSeconds);
        }
    }

    public class BiopacAcquisitionThread : ThreadedJob {

        public BiopacSettings bSettings = null;
        public BiopacData bData     = null;

        volatile public bool doLoop         = false;
        volatile public bool processData    = false;
        private ReaderWriterLock rwl        = new ReaderWriterLock();

        private System.Text.StringBuilder digitalInputStrF = new System.Text.StringBuilder();
        private System.Text.StringBuilder dataStrF     = new System.Text.StringBuilder();

        private static readonly string tab = "\t";
        private static readonly string timestampStrAccuracy = "G8";
                
        protected override void ThreadFunction() {

            // initialize data
            bData = new BiopacData(bSettings);

            ExVR.Log().message(
                string.Format("Number of channels: {0}\nNumber of point asked per call per chanel: {1}\nNumber of point per call to receiveMPData: {2}", 
                Converter.to_string(bSettings.enabledChannelsNb), Converter.to_string(bSettings.nbSamplesPerCall), Converter.to_string(bSettings.numberOfDataPoints))
            );

            // start reading loop
            while (doLoop) {

                // raw data
                var buffer    = new double[bSettings.numberOfDataPoints];
                var digitalIO = new bool[bSettings.enabledChannelsNb];
                for (int ii = 0; ii < digitalIO.Length; ++ii) {
                    digitalIO[ii] = false;
                }

                if (!processData) { // read only minimum data
                    MP.receiveMPData(buffer, (uint)bSettings.enabledChannelsNb, out uint notUsed);
                    continue;
                }

                FrameTimestamp times = new FrameTimestamp();

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
            }
        }

        public Tuple<List<FrameTimestamp>, List<double[]>> get_last_values() {

            List<FrameTimestamp> lastTimes = null;
            List<double[]> lastData = null;

            try {
                rwl.AcquireReaderLock(10); // 1
                try {
                    lastTimes = bData.times.GetRange(bData.lastFrameReadId, bData.times.Count);
                    lastData = bData.channelsData.GetRange(bData.lastFrameReadId, bData.times.Count);
                    bData.lastFrameReadId = bData.times.Count;
                } finally {
                    rwl.ReleaseReaderLock();
                }
            } catch (ApplicationException) {
                return null;
            }

            return Tuple.Create(lastTimes, lastData);
        }

        public List<string> data_to_string(bool addHeaderLine) {

            BiopacData bDataSwap = null;
            BiopacData bNewData  = new BiopacData(bSettings);

            // swap data
            try {
                rwl.AcquireWriterLock(1000);
                try {
                    bDataSwap = bData;
                    bData     = bNewData;
                } finally {
                    rwl.ReleaseWriterLock();
                }
            } catch (ApplicationException) {
                return null;
            }

            int countLines = 0;
            for (int idF = 0; idF < bDataSwap.times.Count; ++idF) {
                var data = bDataSwap.channelsData[idF];
                int nbValuesPerChannel = data.Length / bSettings.enabledChannelsNb;
                countLines += nbValuesPerChannel;
            }

            // init lines array
            List<string> dataStr = new List<string>(countLines + (addHeaderLine ? 1 : 0));
            if (addHeaderLine) {
                dataStr.Add(bSettings.headerLine);
            }

            // fill lines
            for (int idF = 0; idF < bDataSwap.times.Count; ++idF) {

                var data    = bDataSwap.channelsData[idF];
                var digital = bDataSwap.digitalInputData[idF];
                int nbValuesPerChannel = data.Length / bSettings.enabledChannelsNb;

                // compute times
                var time = bDataSwap.times[idF];
                var beforeT = ExVR.Time().ms_since_start_experiment(time.startingTick);
                var duration = TimeManager.ticks_to_ms(time.afterDataReadingTick - time.startingTick);
                List<string> timesPerLine = new List<string>(nbValuesPerChannel);

                if(nbValuesPerChannel == 1) {
                    timesPerLine.Add(string.Concat(Converter.to_string(beforeT, timestampStrAccuracy), tab));
                } else {
                    for (int idV = 0; idV < nbValuesPerChannel; ++idV) {
                        timesPerLine.Add(string.Concat(Converter.to_string(beforeT + (1.0 * idV / (nbValuesPerChannel - 1) * duration), timestampStrAccuracy), tab));
                    }
                }

                // retrieve digital line
                if (bSettings.readDigitalEnabled) {
                    digitalInputStrF.Clear();
                    for (int idC = 0; idC < bSettings.enabledChannelsNb; ++idC) {
                        if (idC < bSettings.enabledChannelsNb - 1) {
                            digitalInputStrF.Append(string.Concat(Converter.to_string(digital[idC], false), tab));
                        } else {
                            digitalInputStrF.Append(Converter.to_string(digital[idC], false));
                        }
                    }
                }

                int idD = 0;
                for (int idV = 0; idV < nbValuesPerChannel; ++idV) {

                    // retrieve data line
                    dataStrF.Clear();
                    for (int idC = 0; idC < bSettings.enabledChannelsNb; ++idC) {
                        if (bSettings.readDigitalEnabled || (idC < bSettings.enabledChannelsNb - 1)) {
                            dataStrF.Append(string.Concat(Converter.to_string(data[idD++]), tab));
                        } else {
                            dataStrF.Append(Converter.to_string(data[idD++]));
                        }
                    }                
                     
                    // create full line
                    if (bSettings.readDigitalEnabled) {
                        dataStr.Add(string.Concat(timesPerLine[idV], dataStrF.ToString(), digitalInputStrF.ToString()));
                    } else {
                        dataStr.Add(string.Concat(timesPerLine[idV], dataStrF.ToString()));
                    }
                }
            }

            ExVR.Log().message(string.Format("Number of entries: {0}", dataStr.Count.ToString()));
            return dataStr;
        }
    }
}