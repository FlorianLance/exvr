/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;

namespace Ex{

    [Serializable]
    public class TimeLine{

        public TimeLine(XML.Timeline updateTimeline, XML.Timeline visiblityTimeline) {

            // generate intervals
            for (int ii = 0; ii < updateTimeline.Interval.Count; ++ii) {
                updateIntervals.Add(new Interval(updateTimeline.Interval[ii].T1, updateTimeline.Interval[ii].T2));
            }
            for (int ii = 0; ii < visiblityTimeline.Interval.Count; ++ii) {
                visiblityIntervals.Add(new Interval(visiblityTimeline.Interval[ii].T1, visiblityTimeline.Interval[ii].T2));
            }
        }

        public bool is_timeLine_enabled(double timeS) {

            bool enabled = false;
            foreach (Interval interval in updateIntervals) {
                enabled |= interval.is_in_interval(timeS);
            }
            return enabled;
        }

        public double max_time_update_s() {
            double max = 0;
            foreach (Interval interval in updateIntervals) {
                if (interval.tEndS > max) {
                    max = interval.tEndS;
                }
            }
            return max;
        }

        public double max_time_visibility_s() {
            double max = 0;
            foreach (Interval interval in visiblityIntervals) {
                if (interval.tEndS > max) {
                    max = interval.tEndS;
                }
            }
            return max;
        }

        public double max_time_s() {
            return Math.Max(max_time_update_s(), max_time_visibility_s());
        }


        public bool inside_update_intervals(double timeS) {
            
            foreach (Interval interval in updateIntervals) {
                if (interval.is_in_interval(timeS)) {
                    return true;
                }
            }
            return false;
        }

        public bool inside_visibility_intervals(double timeS) {

            foreach (Interval interval in visiblityIntervals) {
                if (interval.is_in_interval(timeS)) {
                    return true;
                }
            }
            return false;
        }

        public Interval get_upate_time_interval(double timeS){
            foreach (Interval interval in updateIntervals) {
                if (interval.is_in_interval(timeS)) {
                    return interval;
                }
            }
            return null;
        }

        public Interval get_visibility_time_interval(double timeS) {
            foreach (Interval interval in visiblityIntervals) {
                if (interval.is_in_interval(timeS)) {
                    return interval;
                }
            }
            return null;
        }

        public List<Interval> updateIntervals    = new List<Interval>();
        public List<Interval> visiblityIntervals = new List<Interval>();
    }
}