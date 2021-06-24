/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;


namespace Ex{

    [Serializable]
    public class Interval{

        public Interval(double startS, double endS) {
            tStartS  = startS;
            tEndS    = endS;
        }

        public bool is_in_interval(double time) {
            return (time >= tStartS) && (time <= tEndS);
        }

        public double tStartS    = 0.0;
        public double tEndS      = 0.0;
    }

    [Serializable]
    public class TimestampInterval {

        public TimestampInterval(long startTick, long endTick) {
            this.startTick = startTick;
            this.endTick   = endTick;
        }

        public bool is_in_interval(long tick) {
            return (tick >= startTick) && (tick <= endTick);
        }

        public long startTick   = -1;
        public long endTick     = -1;
    }
}