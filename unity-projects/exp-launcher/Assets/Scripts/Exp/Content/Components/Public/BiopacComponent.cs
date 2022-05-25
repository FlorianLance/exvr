
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
using System.Threading;
using System.Collections.Generic;
using System.Collections.Concurrent;
using UnityEngine;
using UnityEngine.Profiling;

using MP     = Biopac.API.MPDevice.MPDevImports;
using MPCODE = Biopac.API.MPDevice.MPDevImports.MPRETURNCODE;

namespace Ex {

    //internal static class StringBuilderCache {
    //    // The value 360 was chosen in discussion with performance experts as a compromise between using
    //    // as litle memory (per thread) as possible and still covering a large part of short-lived
    //    // StringBuilder creations on the startup path of VS designers.
    //    private const int MAX_BUILDER_SIZE = 360;

    //    [ThreadStatic]
    //    private static StringBuilder CachedInstance;

    //    public static StringBuilder Acquire(int capacity = StringBuilder.DefaultCapacity) {
    //        if (capacity <= MAX_BUILDER_SIZE) {
    //            StringBuilder sb = StringBuilderCache.CachedInstance;
    //            if (sb != null) {
    //                // Avoid stringbuilder block fragmentation by getting a new StringBuilder
    //                // when the requested size is larger than the current capacity
    //                if (capacity <= sb.Capacity) {
    //                    StringBuilderCache.CachedInstance = null;
    //                    sb.Clear();
    //                    return sb;
    //                }
    //            }
    //        }
    //        return new StringBuilder(capacity);
    //    }

    //    public static void Release(StringBuilder sb) {
    //        if (sb.Capacity <= MAX_BUILDER_SIZE) {
    //            StringBuilderCache.CachedInstance = sb;
    //        }
    //    }

    //    public static string GetStringAndRelease(StringBuilder sb) {
    //        string result = sb.ToString();
    //        Release(sb);
    //        return result;
    //    }
    //}


    public class BiopacProcessingThread : ThreadedJob {

        public int enabledChannelsNb;
        public bool readDigitalEnabled;
        public string headerLine;

        volatile public bool doLoop = false;
        volatile public bool addHeaderLine = false;
        CustomSampler s1 = CustomSampler.Create("biopac1");
        CustomSampler s2 = CustomSampler.Create("biopac2");
        CustomSampler s3 = CustomSampler.Create("biopac3");


        ConcurrentQueue<BiopacData> dataList = new ConcurrentQueue<BiopacData>();
        ConcurrentQueue<List<string>> linesList = new ConcurrentQueue<List<string>>();

        private static readonly string timestampStrAccuracy = "G8";

        public void add_data(BiopacData data) {
            if(data == null) {
                return;
            }
            dataList.Enqueue(data);     
        }

        public List<string> get_lines() {
            List<string> newLines = null;
            if (linesList.TryDequeue(out newLines)) {
                return newLines;
            }
            return null;
        }

        protected override void ThreadFunction() {

            Thread.CurrentThread.Name = "BiopacProcessingThread";
            Profiler.BeginThreadProfiling("BiopacProcessingThread", "BiopacProcessingThread 1");

            while (doLoop) {
                BiopacData currentData = null;
                if(dataList.TryDequeue(out currentData)) {
                    linesList.Enqueue(data_to_string(currentData));
                }
                Thread.Sleep(1);
            }
            Profiler.EndThreadProfiling();

        }

        private List<string> data_to_string(BiopacData bData) {

            int countLines = 0;
            for (int idF = 0; idF < bData.times.Count; ++idF) {
                var data = bData.channelsData[idF];
                int nbValuesPerChannel = data.Length / enabledChannelsNb;
                countLines += nbValuesPerChannel;
            }

            // init lines array
            int nbLines = countLines + (addHeaderLine ? 1 : 0);

            List<string> dataStr = new List<string>(nbLines);
            for (int ii = 0; ii < nbLines; ++ii) {
                dataStr.Add(null);
            }

            int idLines = 0;
            if (addHeaderLine) {
                dataStr[idLines++] = headerLine;
                addHeaderLine = false;
            }

            if (bData.times.Count == 0) {
                return dataStr;
            }

            var firstTime = ExVR.Time().ms_since_start_experiment(bData.times[0].startingTick);
            var lastTime = ExVR.Time().ms_since_start_experiment(bData.times[bData.times.Count - 1].afterDataReadingTick);
            var interval = (lastTime - firstTime) / countLines;


            System.Text.StringBuilder digitalInputStrF = new System.Text.StringBuilder();
            System.Text.StringBuilder dataStrF = new System.Text.StringBuilder(1000);

            int idLinesMinusHeader = 0;
            for (int idF = 0; idF < bData.times.Count; ++idF) {


                var data = bData.channelsData[idF];
                var digital = bData.digitalInputData[idF];
                int nbValuesPerChannel = data.Length / enabledChannelsNb;

                // retrieve digital line

                string digitalInputStr = "";
                if (readDigitalEnabled) {

                    digitalInputStrF.Clear();
                    for (int idC = 0; idC < enabledChannelsNb; ++idC) {
                        if (idC < enabledChannelsNb - 1) {
                            digitalInputStrF.Append(digital[idC] ? '1' : '0').Append('\t');
                        } else {
                            digitalInputStrF.Append(digital[idC] ? '1' : '0');
                        }
                    }
                    digitalInputStr = digitalInputStrF.ToString();
                }
                                
                int idData = 0;                                
                for (int idValue = 0; idValue < nbValuesPerChannel; idValue++) {

                    // add time
                    s1.Begin();
                    dataStrF.Clear();
                    dataStrF.Append((firstTime + idLinesMinusHeader * interval).ToString(timestampStrAccuracy)).Append('\t');
                    idLinesMinusHeader++;
                    s1.End();

                    s2.Begin();

                    // add values
                    for (int idChannel = 0; idChannel < enabledChannelsNb; ++idChannel) {

                        dataStrF.Append(data[idData++].ToString());

                        if (readDigitalEnabled || (idChannel < enabledChannelsNb - 1)) {         
                            dataStrF.Append('\t');
                        }
                    }
                    s2.End();

                    s3.Begin();

                    // add digital
                    if (readDigitalEnabled) {
                        dataStrF.Append(digitalInputStr);
                    }

                    // add full line
                    dataStr[idLines++] = dataStrF.ToString();

                    s3.End();
                }

            }

            return dataStr;
        }


    }


    public class BiopacComponent : ExComponent{

        // infos
        public BiopacSettings bSettings = null;

        // thread
        public BiopacAcquisitionThread acquisitionThread = null;
        public BiopacProcessingThread processThread = null;

        // signals
        private static readonly string lastValueChannelStr       = "channelX last value";
        private static readonly string lastRangeValuesChannelStr = "channelX last range values";
        //private static readonly string endRoutineDataLogStr      = "end routine data log";
        private static readonly string callDurationAPIStr        = "call duration API";
        private static readonly string readDataStr               = "read data";
        private static readonly List<int> samplingRateValues = new List<int>(new int[] {
            10,25,50,100,200,250,500,1000,2000,2500,5000,10000,20000,25000
        });

        private List<System.Tuple<double, List<double>>> m_debugData = null;
        private int m_currentDebugId = 0;
        //private bool m_addHeaderLine = false;
        private LoggerComponent m_logger = null;
        private bool m_debugBypass = false;



        //private System.Text.StringBuilder dataStrF = new System.Text.StringBuilder();

        private static readonly string tab = "\t";
        

        #region ex_functions

        protected override bool initialize() {

            // initialize signals/slots
            add_slot(readDataStr, (nullArg) => { trigger_channels(); });
            add_signal(lastValueChannelStr);
            add_signal(lastRangeValuesChannelStr);
            //add_signal(endRoutineDataLogStr);
            add_signal(callDurationAPIStr);

            // retrieve components
            m_logger = initC.get_component<LoggerComponent>("logger");

            // debug
            if (m_debugBypass = initC.get<bool>("debug_bypass")) {
                read_debug_file();
                return true;
            }

            // init settings
            bSettings = new BiopacSettings();

            // # retrieve device            
            switch (initC.get<int>("device_type")) {
                case 0:
                    bSettings.device = MP.MPTYPE.MP36;
                    bSettings.nbMaxChannels = 4;
                    break;
                case 1:
                    bSettings.device = MP.MPTYPE.MP150;
                    bSettings.nbMaxChannels = 16;
                    break;
                case 2:
                    bSettings.device = MP.MPTYPE.MP160;
                    bSettings.nbMaxChannels = 16;
                    break;
            }

            // # retrieve connection
            bSettings.connection = (initC.get<int>("device_connection") == 0) ? MP.MPCOMTYPE.MPUSB : MP.MPCOMTYPE.MPUDP;

            // # retrieve and count enabled channels
            bSettings.channelsState   = new bool[bSettings.nbMaxChannels];
            bSettings.channelsName    = new List<string>();
            bSettings.channelsId      = new List<int>();
            for (int ii = 0; ii < bSettings.nbMaxChannels; ++ii) {
                bSettings.channelsState[ii] = initC.get<bool>(string.Format("channel{0}", ii));
                if (bSettings.channelsState[ii]) {
                    ++bSettings.enabledChannelsNb;                    
                    bSettings.channelsName.Add(initC.get<string>(string.Format("channel{0}_name", ii)));
                    bSettings.channelsId.Add(ii);
                }
            }

            // check channels
            if (bSettings.enabledChannelsNb == 0) {
                log_error("No channel enabled.");
                return false;
            }

            // initialize device
            if (!connect_device()) {
                return false;
            }

            if (!setup_device()) {
                return false;
            }

            if (!start_acquisition()) {
                return false;
            }

            // initialize thread
            bSettings.writeEveryNbLines         = initC.get<int>("write_every_nb_lines")*1000;
            bSettings.nbSamplesPerCall          = initC.get<int>("nb_samples_per_call");
            bSettings.samplingRate              = samplingRateValues[initC.get<int>("sampling_rate_id")];// initC.get<int>("sampling_rate");
            bSettings.capacityChannelSeconds     = initC.get<int>("max_nb_seconds_to_save");
            bSettings.numberOfDataPoints        = (uint)(bSettings.nbSamplesPerCall * bSettings.enabledChannelsNb);

            if (initC.get<int>("read_digital_mode") != 0) {
                bSettings.readDigitalMode = initC.get<int>("read_digital_mode") == 1 ? MP.DIGITALOPT.READ_LOW_BITS : MP.DIGITALOPT.READ_HIGH_BITS;
                bSettings.readDigitalEnabled = true;
            } else {
                bSettings.readDigitalEnabled = false;
            }

            // init header line        
            System.Text.StringBuilder titleLineB = new System.Text.StringBuilder();

            // # time column
            titleLineB.Append("[Timestamp(ms)]\t");

            // # channels data columns
            for (int ii = 0; ii < bSettings.enabledChannelsNb; ++ii) {
                titleLineB.AppendFormat("[Val-{0}]\t", bSettings.channelsName[ii]);
            }

            // # channels digital read columns
            if (bSettings.readDigitalEnabled) {
                for (int ii = 0; ii < bSettings.enabledChannelsNb; ++ii) {
                    titleLineB.AppendFormat("[Tr-{0}]\t", bSettings.channelsName[ii]);
                }
            }

            // init threads
            acquisitionThread             = new BiopacAcquisitionThread();
            acquisitionThread.bSettings   = bSettings;
            acquisitionThread.processData = false;
            acquisitionThread.doLoop      = true;            
            acquisitionThread.start();
            acquisitionThread.set_priority(System.Threading.ThreadPriority.AboveNormal);

            processThread = new BiopacProcessingThread();
            processThread.doLoop = true;
            processThread.headerLine = titleLineB.ToString();
            processThread.readDigitalEnabled = bSettings.readDigitalEnabled;
            processThread.enabledChannelsNb = bSettings.enabledChannelsNb;
            processThread.start();
            processThread.set_priority(System.Threading.ThreadPriority.AboveNormal);


            return true;
        }

        protected override void set_update_state(bool doUpdate) {

            if (m_debugBypass) {
                return;
            }
            acquisitionThread.processData = doUpdate;
        }
       
        protected override void clean() {

            if (m_debugBypass) {
                return;
            }

            stop_acquisition();
        }

        protected override void start_experiment() {

            processThread.addHeaderLine = true;
            //m_addHeaderLine  = true;
            m_currentDebugId = 0;
            if (m_debugBypass) {
                return;
            }
            acquisitionThread.bData.reset(bSettings);
        }

        protected override void post_update() {

            if (m_debugBypass) {
                return;
            }

            if (acquisitionThread.askWrite) {
                Profiler.BeginSample("biopac getdata");
                var data = acquisitionThread.get_data();
                Profiler.EndSample();

                Profiler.BeginSample("biopac add data");
                processThread.add_data(data);
                Profiler.EndSample();
            }

            Profiler.BeginSample("biopac write data");
            write_data();
            Profiler.EndSample();
        }

        protected override void stop_experiment() {
            if (m_debugBypass) {
                return;
            }

            write_data();
        }


        #endregion

        #region private_functions
            private bool connect_device() {

            int retry = 3;
            for (int ii = 0; ii < retry; ++ii) {

                log_message( message : string.Format("Try to connect, try n°{0} with method {1}", (ii+1).ToString(), bSettings.connection.ToString()),  append : false);

                // remember to change the parameters to suit your MP configuration
                // Auto connect to MP150 was introduced in BHAPI 1.1
                // passing "AUTO" or "auto" instead of the full serial number of the MP150
                // will cause BHAPI to connect to the first respoding MP150.  This is usually
                // the closest MP150 to the host computer.
                var retval = MP.connectMPDev(bSettings.device, bSettings.connection, initC.get<string>("serial"));
                if (retval == MPCODE.MPNOTINNET) {
                    log_error(string.Format("MP150 with serial number '{0}' is not in the network.", initC.get<string>("serial")));
                    continue;
                }

                if (retval == MPCODE.MPSUCCESS) {
                    log_message(message : "Connection established.", append : false);
                    return true;
                } else {
                    log_error(string.Format("connectMPDev error: {0}", BiopacSettings.code_to_string(retval)));
                }
            }

            MP.disconnectMPDev();
            log_error("Cannot connect to the device. No data will be received.", false);

            return false;
        }

        private bool setup_device() {

            // ex: set sample rate to 5 msec per sample = 200 Hz  -> retval = setSampleRate(5.0);
            double sampleRate = 1000.0 / samplingRateValues[initC.get<int>("sampling_rate_id")];
            MPCODE retval = MP.setSampleRate(sampleRate);
            log_message(message : string.Format("Frequency {0} {1} {2}", initC.get<int>("sampling_rate_id"), samplingRateValues[initC.get<int>("sampling_rate_id")], sampleRate), append : false);
            if (retval != MPCODE.MPSUCCESS) {
                log_error(string.Format("Sampling error {0} with rate: {1}", BiopacSettings.code_to_string(retval), Converter.to_string(sampleRate)));
                return false;
            }

            // set the acquisition channels
            retval = MP.setAcqChannels(bSettings.channelsState);
            if (retval != MPCODE.MPSUCCESS) {
                log_error(string.Format("Channels acquisition error {0}, disconnecting device", BiopacSettings.code_to_string(retval)));
                return false;
            }

            // read xml preset file
            var presetTxTData = initC.get_resource_text_data("preset_xml_file");
            if (presetTxTData != null) {
                retval = MP.loadXMLPresetFile(presetTxTData.path);
                if (retval != MPCODE.MPSUCCESS) {
                    log_error(string.Format("Error during xml preset loading {0}", BiopacSettings.code_to_string(retval)));
                    return false;
                }

                // set preset id for each channel
                for (int ii = 0; ii < bSettings.channelsId.Count; ++ii) {
                    string uid = initC.get<string>(string.Format("channel{0}_preset_uid", (bSettings.channelsId[ii]).ToString()));
                    if (uid.Length > 0) {
                        retval = MP.configChannelByPresetID((uint)bSettings.channelsId[ii], uid);
                        if (retval != MPCODE.MPSUCCESS) {
                            log_error(string.Format("Error {0} during preset file configuration for channel {1} with uid {2}",
                                BiopacSettings.code_to_string(retval), (bSettings.channelsId[ii] + 1).ToString(), uid));
                            return false;
                        }
                    }
                }
            }

            return true;
        }

        private bool start_acquisition() {

            // start acquisition daemon
            MPCODE retval = MP.startMPAcqDaemon();
            if (retval != MPCODE.MPSUCCESS) {
                log_error(string.Format("Biopac acquisition failed: cannot start acquisition daemon, error: {0}", BiopacSettings.code_to_string(retval)));

                retval = MP.stopAcquisition();
                if (retval != MPCODE.MPSUCCESS) {
                    log_error(string.Format("Cannot stop biopac acquisition, error: {0}", BiopacSettings.code_to_string(retval)));
                }

                return false;
            }

            // start biopac acquisition
            retval = MP.startAcquisition();
            if (retval != MPCODE.MPSUCCESS) {
                log_error(string.Format("Biopac acquisition failed: cannot start, error: {0}", BiopacSettings.code_to_string(retval)));

                retval = MP.stopAcquisition();
                if (retval != MPCODE.MPSUCCESS) {
                    log_error(string.Format("Cannot stop biopac acquisition, error: {0}", BiopacSettings.code_to_string(retval)));
                }

                return false;
            }

            return true;
        }

        private void stop_acquisition() {

            if (acquisitionThread == null) {
                return;
            }

            // kill thread            
            acquisitionThread.processData = false;
            acquisitionThread.doLoop      = false;
            Thread.Sleep(500);
            acquisitionThread.stop();

            processThread.doLoop = false;
            Thread.Sleep(500);
            processThread.stop();

            MPCODE retval = MP.stopAcquisition();
            if (retval != MPCODE.MPSUCCESS) {
                log_error(string.Format("Cannot stop biopac acquisition, error: {0}", BiopacSettings.code_to_string(retval)));
            }

            retval = MP.disconnectMPDev();
            if (retval != MPCODE.MPSUCCESS) {
                log_error(string.Format("Cannot disconnect biopac, error: {0}", BiopacSettings.code_to_string(retval)));
            }
        }

        private void write_data() {
            if (m_logger == null) {
                return;
            }

            if (m_debugBypass) {
                m_logger.write("Generated-biopac-debug-line");
            }

            var lines = processThread.get_lines();
            if (lines != null && lines.Count > 0) {
                m_logger.write_lines(lines);
            }
        }


        void read_debug_file() {

            if (initC.get_resource_alias("debug_log_file").Length > 0) {

                var content = Text.split_lines(initC.get_resource_text_data("debug_log_file").content);
                log_message("content: " + content.Length);
                m_debugData = new List<System.Tuple<double, List<double>>>(content.Length);
                int nbCols = 0;
                foreach (var line in content) {
                    if (line.StartsWith("[Routine")) {
                        continue;
                    }
                    if (line.StartsWith("[Timestamp(ms)]	")) {
                        nbCols = Text.split_tabs(line).Length;
                    }
                    if (nbCols == 0) {
                        continue;
                    }
                    var split = Text.split_tabs(line);
                    if (split.Length != nbCols) {
                        continue;
                    }
                    var lineValues = new System.Tuple<double, List<double>>(Converter.to_double(split[0]), new List<double>(nbCols));
                    for (int ii = 1; ii < nbCols; ++ii) {
                        lineValues.Item2.Add(Converter.to_double(split[ii]));
                    }
                    m_debugData.Add(lineValues);
                }
            } 
           
        }


        #endregion

        #region public_functions

        public void trigger_channels() {

            if (m_debugBypass) {
                if (m_debugData != null) {
                    var currTime = ExVR.Time().ellapsed_exp_ms();
                    for (int ii = m_currentDebugId; ii < m_debugData.Count; ++ii) {
                        if (m_currentDebugId >= m_debugData.Count) {
                            return;
                        }
                        if (m_debugData[m_currentDebugId].Item1 < currTime) {
                            ++m_currentDebugId;
                        } else {
                            break;
                        }
                    }

                    for (int ii = 0; ii < m_debugData[m_currentDebugId].Item2.Count; ++ii) {
                        invoke_signal(lastValueChannelStr, new IdAny(ii + 1, m_debugData[m_currentDebugId].Item2[ii]));
                    }
                }
                return;
            } else {

                var values = acquisitionThread.get_last_values();
                if (values == null) {
                    return;
                }
                
                List<double[]> data = values.Item2;                

                // count values
                int nbValues = 0;
                for (int ii = 0; ii < data.Count; ++ii) {
                    nbValues += data[ii].Length;
                }

                // init channel list
                List<List<double>> channelsData = new List<List<double>>(bSettings.enabledChannelsNb);
                for(int ii = 0; ii < bSettings.enabledChannelsNb; ++ii) {
                    channelsData.Add(new List<double>(nbValues/ bSettings.enabledChannelsNb));
                }

                // copy data
                for (int ii = 0; ii < data.Count; ++ii) {
                    for(int jj = 0; jj < data[ii].Length; ++jj) {
                        int idChannel = jj % bSettings.enabledChannelsNb;
                        channelsData[idChannel].Add(data[ii][jj]);
                    }
                }

                // send values
                for (int ii = 0; ii < bSettings.enabledChannelsNb; ++ii) {
                    List<double> channelData = channelsData[ii];
                    if (channelData.Count > 0) {
                        invoke_signal(lastValueChannelStr, new IdAny(bSettings.channelsId[ii] + 1, channelData[channelData.Count - 1]));
                        invoke_signal(lastRangeValuesChannelStr, new IdAny(bSettings.channelsId[ii] + 1, channelData));
                    }
                }

                // send last delay
                List<FrameTimestamp> times = values.Item1;
                if (times.Count > 0) {
                    var lastFrameTimestamp = times[times.Count - 1];
                    invoke_signal(callDurationAPIStr, TimeManager.ticks_to_ms(lastFrameTimestamp.afterDataReadingTick - lastFrameTimestamp.startingTick));
                }
            }
        }

        #endregion
    }
}
