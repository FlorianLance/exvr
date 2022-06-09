
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
using System.Text;
using System.Threading;
using System.Diagnostics;
using System.Collections.Generic;
using System.Collections.Concurrent;

// unity
using UnityEngine.Profiling;

using MP        = Biopac.API.MPDevice.MPDevImports;
using MPCODE    = Biopac.API.MPDevice.MPDevImports.MPRETURNCODE;

namespace Ex {

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

    public class BData {

        public int id                   = 0;        
        public double beforeExpTime     = 0.0;
        public double afterExpTime      = 0.0;
        public double[] channelsData    = null;
        public bool[] digitalInputsData = null;
        public double[] timesData       = null;
        private static int counter      = 0;

        public BData(BiopacSettings bSettings) {
            channelsData = new double[bSettings.numberOfDataPoints];
            if (bSettings.readDigitalEnabled) {
                digitalInputsData = new bool[bSettings.enabledChannelsNb];
            }
            id = counter++;
        }
        public static void reset_counter() {
            counter = 0;
        }
    }


    public class BiopacAcquisitionThread : ThreadedJob {

        volatile public bool doLoop = false;
        volatile public bool processData = false;
        volatile private bool loopFinished = false;

        public BiopacSettings bSettings     = null;
        public ConcurrentQueue<BData> data = new ConcurrentQueue<BData>();

        private CustomSampler retrievePointsSampler = CustomSampler.Create("[biopac] acquisition retrieve_points");        
        private CustomSampler insertDataSampler     = CustomSampler.Create("[biopac] acquisition insert_data");

        public List<BData> force() {

            while (processData) {
                Thread.Sleep(1);
            }

            List<BData> dataRemaining = new List<BData>();
            BData bData;
            while (data.TryDequeue(out bData)) {
                dataRemaining.Add(bData);
            }
            return dataRemaining;
        }

        protected override void thread_function() {

            Thread.CurrentThread.Name = "BiopacAcquisitionThread";
            Profiler.BeginThreadProfiling("BiopacAcquisitionThread", "BiopacAcquisitionThread 1");

            // start reading loop
            var waitBuffer = new double[bSettings.enabledChannelsNb];

            while (doLoop) {
                
                if (!processData) { // read only minimum data
                    MP.receiveMPData(waitBuffer, (uint)bSettings.enabledChannelsNb, out uint notUsed);
                    continue;
                } else {

                    // retrieve points
                    retrievePointsSampler.Begin();
                    BData d = new BData(bSettings);
     
                    d.beforeExpTime = ExVR.Time().ellapsed_exp_ms();
                    MPCODE retval = MP.receiveMPData(d.channelsData, bSettings.numberOfDataPoints, out uint received);                    
                    d.afterExpTime = ExVR.Time().ellapsed_exp_ms();

                    // check for error condition
                    if (retval != MPCODE.MPSUCCESS) {
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
                            retval = MP.getDigitalIO((uint)bSettings.channelsId[ii], out d.digitalInputsData[ii], bSettings.readDigitalMode);
                            if (retval != MPCODE.MPSUCCESS) {
                                ExVR.Log().error(string.Format("Biopack getDigitalIO({0}) error code {1} ",
                                    bSettings.channelsId[ii], 
                                    BiopacSettings.code_to_string(retval))
                                );
                                continue;
                            }
                        }
                    }
                    retrievePointsSampler.End();

                    insertDataSampler.Begin();
                    data.Enqueue(d);
                    insertDataSampler.End();
                }
            }

            Profiler.EndThreadProfiling();
        }    
    }

    public class BiopacProcessingThread : ThreadedJob {

        public string headerLine;
        public BiopacSettings bSettings = null;

        volatile public bool doLoop = false;
        volatile public bool addHeaderLine = false;
        volatile private bool loopFinished = false;

        private double m_firstExpTime = 0.0;

        CustomSampler fullSampler           = CustomSampler.Create("[biopac] processing full");        
        CustomSampler appendDigitalSampler  = CustomSampler.Create("[biopac] processing append_digital");
        CustomSampler appendChannelsSampler = CustomSampler.Create("[biopac] processing append_channels");

        ConcurrentQueue<BData> dataList = new ConcurrentQueue<BData>();
        ConcurrentQueue<List<string>> linesList = new ConcurrentQueue<List<string>>();

        StringBuilder digitalInputStrF = new StringBuilder();
        StringBuilder dataStrF = new StringBuilder(1000);

        private static readonly string timestampStrAccuracy = "G8";


        public List<string> force(List<BData> bData) {

            foreach(var data in bData) {
                linesList.Enqueue(data_to_string(data));
            }
            return get_lines();
        }

        public void add_data(BData data) {
            if (data == null) {
                return;
            }
            dataList.Enqueue(data);
        }

        public List<string> get_lines() {
            List<string> newLines;
            if (linesList.TryDequeue(out newLines)) {
                return newLines;
            }
            return null;
        }

        protected override void thread_function() {

            Thread.CurrentThread.Name = "BiopacProcessingThread";
            Profiler.BeginThreadProfiling("BiopacProcessingThread", "BiopacProcessingThread 1");

            BData data;
            loopFinished = false;
            while (doLoop) {
                
                while(dataList.TryDequeue(out data)) {
                    linesList.Enqueue(data_to_string(data));                        
                }
                Thread.Sleep(1);
            }

            while (dataList.TryDequeue(out data)) {
                linesList.Enqueue(data_to_string(data));
            }

            loopFinished = true;

            Profiler.EndThreadProfiling();
        }

        private List<string> data_to_string(BData data) {

            int nbValuesPerChannel = data.channelsData.Length / bSettings.enabledChannelsNb;

            // init lines array
            int nbLines = nbValuesPerChannel + (addHeaderLine ? 1 : 0);
            List<string> dataStr = new List<string>(nbLines);
            for (int ii = 0; ii < nbLines; ++ii) {
                dataStr.Add(null);
            }

            int idLines = 0;
            if (addHeaderLine) {
                dataStr[idLines++] = headerLine;
                addHeaderLine = false;
            }
   
            fullSampler.Begin();

            digitalInputStrF.Clear();
            dataStrF.Clear();

            appendDigitalSampler.Begin();
            string digitalInputStr = "";
            var digital = data.digitalInputsData;
            if (bSettings.readDigitalEnabled) {

                digitalInputStrF.Clear();
                for (int idC = 0; idC < bSettings.enabledChannelsNb; ++idC) {
                    if (idC < bSettings.enabledChannelsNb - 1) {
                        digitalInputStrF.Append(digital[idC] ? '1' : '0').Append('\t');
                    } else {
                        digitalInputStrF.Append(digital[idC] ? '1' : '0');
                    }
                }
                digitalInputStr = digitalInputStrF.ToString();
            }
            appendDigitalSampler.End();

            appendChannelsSampler.Begin();

            int idLinesMinusHeader = 0;
            int idData = 0;
            double rate = 1000.0 / bSettings.samplingRate;
            var idTotal = (data.id * bSettings.nbSamplesPerCall);

            var beforeExpTimeStr       = data.beforeExpTime.ToString(timestampStrAccuracy);
            var durationAcquisitionStr = (data.afterExpTime - data.beforeExpTime).ToString(timestampStrAccuracy);

            if(data.id == 0) {
                m_firstExpTime = data.beforeExpTime;
            }

            for (int idSample = 0; idSample < bSettings.nbSamplesPerCall; ++idSample, ++idTotal) {
                              
                dataStrF.Clear();

                // id packet
                dataStrF.Append(data.id).Append('\t');
                // id sample
                dataStrF.Append(idSample).Append('\t');
                // sample exp time
                var time = (idTotal * rate);
                dataStrF.Append((time + m_firstExpTime).ToString(timestampStrAccuracy)).Append('\t');
                // sample time
                dataStrF.Append(time.ToString(timestampStrAccuracy)).Append('\t');
                // before acquisition timestamp
                dataStrF.Append(beforeExpTimeStr).Append('\t');
                // duration acquisition
                dataStrF.Append(durationAcquisitionStr).Append('\t');
                
                idLinesMinusHeader++;

                // add values
                for (int idChannel = 0; idChannel < bSettings.enabledChannelsNb; ++idChannel) {
                    dataStrF.Append(data.channelsData[idData++].ToString());
                    if (bSettings.readDigitalEnabled || (idChannel < bSettings.enabledChannelsNb - 1)) {
                        dataStrF.Append('\t');
                    }
                }

                // add digital
                if (bSettings.readDigitalEnabled) {
                    dataStrF.Append(digitalInputStr);
                }

                // add full line
                dataStr[idLines++] = dataStrF.ToString();
            }
            appendChannelsSampler.End();           

            fullSampler.End();
            return dataStr;
        }
    }
}