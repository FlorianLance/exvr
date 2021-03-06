/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Diagnostics;
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{
    public class TimeManager : MonoBehaviour {

        // states
        private bool m_isPaused = false;
        private bool m_isExperimentStarted = false;

        // timers        
        private Stopwatch m_programTimer = new Stopwatch();
        private Stopwatch m_experimentTimer = new Stopwatch();
        private Stopwatch m_elementTimer = new Stopwatch();
        private Stopwatch m_frameTimer = new Stopwatch();                
        private long idFrame = 0;
        private double previousStartFrameTimeMs = 0.0;
        private double previousEndFrameTimeMs = 0.0;
        private double startFrameTimeMs = 0.0;
        private double endFrameTimeMs = 0.0;

        // timestamps
        private long startProgramTimestamp    = -1;
        private long startExperimentTimestamp = -1;
        private long stopExperimentTimestamp  = -1;
        private long startElementTimestamp    = -1;        
        private List<TimestampInterval> pauseEventsExperimentTimestamp = new List<TimestampInterval>();
        private List<TimestampInterval> pauseEventsElementTimestamp    = new List<TimestampInterval>();

        // states functions
        public bool is_experiment_started() {
            return m_isExperimentStarted;
        }

        public bool is_paused() {
            return m_isPaused;
        }

        // timers functions
        public bool is_experiment_running() {
            return m_experimentTimer.IsRunning;
        }

        public double ellapsed_program_ms() {
            return m_programTimer.Elapsed.TotalMilliseconds;
        }

        public double ellapsed_exp_ms() {
            return m_experimentTimer.Elapsed.TotalMilliseconds;
        }

        public double ellapsed_element_ms() {
            return m_elementTimer.Elapsed.TotalMilliseconds;
        }

        public double ellapsed_frame_ms() {
            return m_frameTimer.Elapsed.TotalMilliseconds;
        }

        public double ellapsed_exp_s() {
            return ellapsed_exp_ms() * 0.001;
        }

        public double ellapsed_element_s() {
            return ellapsed_element_ms() * 0.001;
        }

        public long frame_id() {
            return idFrame;
        }

        public double previous_frame_duration_ms() {
            return previousEndFrameTimeMs - previousStartFrameTimeMs;
        }

        public double frame_start_since_experiment_ms() {
            return startFrameTimeMs;
        }

        // timestamps functions
        public void start_program() {
            // program
            m_programTimer.Start();
            startProgramTimestamp = Stopwatch.GetTimestamp();
        }
        public void start_experiment() {

            // timestamps
            startExperimentTimestamp = Stopwatch.GetTimestamp();
            startElementTimestamp    = -1;
            stopExperimentTimestamp  = -1;
            // exp
            m_experimentTimer.Reset();
            m_experimentTimer.Start();
            // frame
            previousStartFrameTimeMs = 0;
            startFrameTimeMs = 0;
            previousEndFrameTimeMs = 0;
            endFrameTimeMs = 0;
            idFrame = 0;
            // states
            m_isPaused = false;
            m_isExperimentStarted = true;

            // clean previous  play/pause timestamps
            pauseEventsExperimentTimestamp.Clear();
            pauseEventsElementTimestamp.Clear();
        }

        public void stop_experiment() {

            // timestamps
            stopExperimentTimestamp = Stopwatch.GetTimestamp();
            // exp
            m_experimentTimer.Stop();
            m_experimentTimer.Reset();
            // elem
            m_elementTimer.Stop();
            m_elementTimer.Reset();
            // states
            m_isPaused = false;
            m_isExperimentStarted = false;
        }

        public void pause_experiment() {

            if (m_isPaused) {
                return;
            }

            // timestamps
            var ticks = Stopwatch.GetTimestamp();
            pauseEventsExperimentTimestamp.Add(new TimestampInterval(ticks, -1));
            pauseEventsElementTimestamp.Add(new TimestampInterval(ticks, -1));
            // exp
            m_experimentTimer.Stop();
            // elem
            m_elementTimer.Stop();
            // states
            m_isPaused = true;
        }

        public void play_experiment() {

            if (!m_isPaused) {
                return;
            }

            // timestamps
            var ticks = Stopwatch.GetTimestamp();
            pauseEventsExperimentTimestamp[pauseEventsExperimentTimestamp.Count - 1].endTick = ticks;
            pauseEventsElementTimestamp[pauseEventsElementTimestamp.Count - 1].endTick = ticks;
            // exp
            m_experimentTimer.Start();
            // elem
            m_elementTimer.Start();
            // states
            m_isPaused = false;
        }

        public void start_element() {

            // timestamps
            startElementTimestamp = Stopwatch.GetTimestamp();
            pauseEventsElementTimestamp.Clear();

            // elem
            m_elementTimer.Reset();
            if (!m_isPaused) {
                m_elementTimer.Start();
            }
        }

        public void start_new_frame() {

            // start frame timer
            m_frameTimer.Restart();

            // retrieve frame start time
            previousStartFrameTimeMs = startFrameTimeMs;
            startFrameTimeMs = ellapsed_exp_ms();
        }

        public void end_frame() {

            // stop frame timer
            m_frameTimer.Stop();

            // retrieve frame end time
            previousEndFrameTimeMs = endFrameTimeMs;
            endFrameTimeMs = ellapsed_exp_ms();

            // increment id frame
            ++idFrame;
        }

        public long to_ticks(Stopwatch timer) {
            return timer.ElapsedTicks;
        }


        public double s_start_routine_since_start_experiment() {
            return s_since_start_experiment(startElementTimestamp);
        }
        public double ms_start_routine_since_start_experiment() {
            return ms_since_start_experiment(startElementTimestamp);
        }
        public double ns_start_routine_since_start_experiment() {
            return ns_since_start_experiment(startElementTimestamp);
        }


        public long remove_pause_intervals_from_tick(List<TimestampInterval> intervals, long ticks) {

            long currentOffset = 0;
            foreach (var interval in intervals) {

                if (ticks < interval.startTick) {
                    // smaller than current interval, stop counting offset
                    break;
                } else if (ticks < interval.endTick) {
                    // ticks inside pause interval, don't count the offset
                    break;
                } else if (interval.endTick == -1) {
                    // pause still ongoing
                    break;
                } else {
                    // add pause interval in offset
                    currentOffset += interval.endTick - interval.startTick;
                }
            }
            return ticks - currentOffset;
        }

        public double s_since_start_experiment(long ticks) {

            if (startExperimentTimestamp < 0) {
                UnityEngine.Debug.LogError("Start experiment timestamp not initialized");
                return 0.0;
            }

            return ticks_to_s(remove_pause_intervals_from_tick(pauseEventsExperimentTimestamp, ticks) - startExperimentTimestamp);
        }

        public double ms_since_start_experiment(long ticks) {

            if (startExperimentTimestamp < 0) {
                UnityEngine.Debug.LogError("Start experiment timestamp not initialized");
                return 0.0;
            }

            return ticks_to_ms(remove_pause_intervals_from_tick(pauseEventsExperimentTimestamp, ticks) - startExperimentTimestamp);
        }

        public double ns_since_start_experiment(long ticks) {

            if (startExperimentTimestamp < 0) {
                UnityEngine.Debug.LogError("Start experiment timestamp not initialized");
                return 0.0;
            }

            return ticks_to_ns(remove_pause_intervals_from_tick(pauseEventsExperimentTimestamp, ticks) - startExperimentTimestamp);
        }

        public double s_since_start_routine(long ticks) {

            if (startElementTimestamp < 0) {
                UnityEngine.Debug.LogError("Start routine timestamp not initialized");
                return 0.0;
            }

            return ticks_to_s(remove_pause_intervals_from_tick(pauseEventsElementTimestamp, ticks) - startElementTimestamp);
        }

        public double ms_since_start_routine(long ticks) {

            if (startElementTimestamp < 0) {
                UnityEngine.Debug.LogError("Start routine timestamp not initialized");
                return 0.0;
            }

            return ticks_to_ms(remove_pause_intervals_from_tick(pauseEventsElementTimestamp, ticks) - startElementTimestamp);
        }

        public double ns_since_start_routine(long ticks) {

            if (startElementTimestamp < 0) {
                UnityEngine.Debug.LogError("Start routine timestamp not initialized");
                return 0.0;
            }

            return ticks_to_ns(remove_pause_intervals_from_tick(pauseEventsElementTimestamp, ticks) - startElementTimestamp);
        }

        // stopwatch functions
        public static double ticks_to_s(long ticks) {
            return (1.0 * ticks / Stopwatch.Frequency);
        }
        public static double ticks_to_ms(long ticks) {
            return (1.0* ticks / Stopwatch.Frequency) * 1000.0;
        }

        public static double ticks_to_ns(long ticks) {
            return (1.0 * ticks / Stopwatch.Frequency) * 1000000.0;
        }

        public static long nanoseconds_accuracy() {
            return (1000L * 1000L * 1000L) / Stopwatch.Frequency;
        }

        public static bool high_resolution_timer() {
            return Stopwatch.IsHighResolution;
        }
    }
}